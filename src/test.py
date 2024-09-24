import argparse
import os
import random

import albumentations
import cv2
import matplotlib.pyplot as plt
import numpy as np
import torch
from PIL import Image
from torch import nn
from torch.nn import (LSTM, BatchNorm2d, Conv2d, Dropout, Linear, Module,
                      Softmax)
from torchvision import models, transforms
from tqdm import tqdm


class CNN(Module):
    """
    Convolutional Neural Network (CNN) module.

    Args:
        feature_dim (int): Dimensionality of the output feature.

    Attributes:
        pretrained (nn.Module): Pretrained SqueezeNet model.
        
    Methods:
        forward(x): Forward pass of the CNN module.

    """
    def __init__(self, feature_dim) -> None:
        """
        Initialize the CNN module.

        Args:
            feature_dim (int): Dimensionality of the output feature.

        """
        super().__init__()
        self.pretrained = models.squeezenet1_0(weights=models.SqueezeNet1_0_Weights.DEFAULT)

        #SqueezeNet has been integrated with a normalization layer in order to decouple the different layers of 
        #the net. 
        self.pretrained.classifier[0] = BatchNorm2d(num_features=512)

        #SqueezeNet has been integrated with a convolutional layer in order to provide the LRCN with a feature vector. 
        self.pretrained.classifier[1] = Conv2d(in_channels=512, out_channels=feature_dim, kernel_size=(1,1), stride=(1,1))

    def forward(self, x):
        """
        Forward pass of the CNN module.

        Args:
            x (torch.Tensor): Input tensor.

        Returns:
            torch.Tensor: Output tensor.

        """
        return self.pretrained(x)

class LRCN(Module):
    """
    Long-term Recurrent Convolutional Network (LRCN) module.

    Args:
        feature_dim (int): Dimensionality of the CNN output feature. Default is 512.
        hidden_size (int): Size of the LSTM hidden state. Default is 256.

    Attributes:
        NUM_CLASSES (int): Number of output classes.

    Methods:
        forward(x, verbose=False): Forward pass of the LRCN module.

    """
    NUM_CLASSES = 2

    def __init__(self, feature_dim=512, hidden_size=256) -> None:
        """
        Initialize the LRCN module.

        Args:
            feature_dim (int): Dimensionality of the CNN output feature. Default is 512.
            hidden_size (int): Size of the LSTM hidden state. Default is 256.

        """
        super().__init__()
        
        self.cnn = CNN(feature_dim)
        
        self.lstm = LSTM(
            input_size=feature_dim,
            hidden_size=hidden_size,
            num_layers=2,
            dropout=0.6,
            batch_first=True
            )
        
        self.fc = Linear(hidden_size, self.NUM_CLASSES)

        self.softmax = Softmax(dim=-1)

    def forward(self, x, verbose=False):
        """
        Forward pass of the LRCN module.

        Args:
            x (torch.Tensor): input tensor.
            verbose (bool, optional): if True, print the shape of intermediate tensors. Default is False.

        Returns:
            torch.Tensor: output tensor.

        """
        if verbose:
            print("Input ", x.shape)

        batch_size, num_frames, channels, width, height = x.shape
        conv_input = x.view(batch_size*num_frames, channels, width, height)
        
        if verbose:
            print("Conv input ",conv_input.shape)

        conv_output = self.cnn(conv_input)

        if verbose:
            print("Conv output ",conv_output.shape)

        lstm_input = conv_output.view(batch_size, num_frames, -1)

        if verbose:
            print("LSTM input ",lstm_input.shape)

        self.lstm.flatten_parameters()
        lstm_output, _ = self.lstm(lstm_input, None)
        
        if verbose:
            print("LSTM output ", lstm_output.shape)

        predictions = self.fc(lstm_output[:,-1,:])
        
        if verbose:
            print("Prediction ", predictions.shape)

        return self.softmax(predictions)

class ImglistOrdictToTensor(torch.nn.Module):
    """
    Converts a list or a dict of numpy images to a torch.FloatTensor
    of shape (NUM_IMAGES x CHANNELS x HEIGHT x WIDTH).
    Can be used as first transform for ``VideoFrameDataset``.
    """
    @staticmethod
    def forward(img_list_or_dict):
        """
        Converts each numpy image in a list or a dict to
        a torch Tensor and stacks them into a single tensor.

        Args:
            img_list_or_dict: list or dict of numpy images.
        Returns:
            tensor of size ``NUM_IMAGES x CHANNELS x HEIGHT x WIDTH``
        """
        if isinstance(img_list_or_dict, list):
            return torch.stack([transforms.functional.to_tensor(img)
                                for img in img_list_or_dict])
        else:
            return torch.stack([transforms.functional.to_tensor(img_list_or_dict[k])
                                for k in img_list_or_dict.keys()])

def init_parameter():   
    """
    Initializes command-line argument parser for testing.

    Returns:
        args: parsed command-line arguments.
    """
    parser = argparse.ArgumentParser(description='Test')
    parser.add_argument("--videos", type=str, default='foo_videos/', help="Dataset folder")
    parser.add_argument("--results", type=str, default='foo_results/', help="Results folder")
    args = parser.parse_args()
    return args

def get_preprocess():
    """
    Returns a preprocessing transform for image augmentation.

    Returns:
        albumentations.Compose: Image preprocessing transform.
    """
    preprocessing = albumentations.Sequential([
        albumentations.Resize(height=256, width=256, always_apply=True),
        albumentations.CenterCrop(height=224, width=224),
        albumentations.Normalize(mean=[0.485, 0.456, 0.406],
                                 std=[0.229, 0.224, 0.225],
                                 max_pixel_value=255.,
                                 always_apply=True),                
    ])

    additional_targets = {}

    for i in range(5):
        additional_targets["image%d" % i] = "image"
    
    transform = albumentations.Compose([preprocessing],
                                            additional_targets=additional_targets,
                                            p=1)
    return transform


NUM_FRAMES = 5 

def build_model():
    """
    Builds and loads the pre-trained model.

    Returns:
        torch.nn.Module: Loaded and pre-trained model.

    """
    model = LRCN(feature_dim=256, hidden_size=256)
    model.load_state_dict(torch.load('model.pth', map_location=torch.device('cpu')))
    model = model.eval()
    return model
    

args = init_parameter()

model = build_model()
preprocess = get_preprocess()
to_tensor = ImglistOrdictToTensor()

true_pos = 0

# For all the test videos
for video in tqdm(os.listdir(args.videos)):
    """
    Processes each test video to detect a certain event.

    Args:
        video (str): Name of the video file.

    """
    # Process the video
    ret = True
    cap = cv2.VideoCapture(os.path.join(args.videos,video))

    frame_rate = cap.get(cv2.CAP_PROP_FPS)

    i = 0
    j = 0
    pos_neg = 0

    # Here you should add your code for applying your method  
    frames = []

    while ret:
        ret, frame = cap.read()
        j+=1

        if j % int(frame_rate) != 0:
            continue
        
        frames.append(frame)
    
        
    while i < len(frames)-(NUM_FRAMES+1):
        """
        Processes a sequence of frames to detect a certain event (fire in this case).

        Args:
            frames (list): List of frames from the video.

        """
        
        image = cv2.cvtColor(frames[i], cv2.COLOR_BGR2RGB)
        transform_input = {"image": image} #Color conversion 

        for k, image in enumerate(frames[i+1:i+NUM_FRAMES]):
            image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
            transform_input["image%d" % k] = image

        images = preprocess(**transform_input)
        
        input_tensor = to_tensor(images)
        input_tensor = input_tensor.unsqueeze(0)
        
        # move the input and model to GPU for speed if available
        if torch.cuda.is_available():
            input_tensor = input_tensor.to('cuda')
            model.to('cuda')

        with torch.no_grad():
            output = model(input_tensor)
            output = torch.argmax(output,dim=-1).item()

        if output == 1:
            pos_neg = 1
            true_pos += 1
            break
    
        i+=1
        
    ########################################################
    #Print results
    cap.release()
    f = open(args.results+video+".txt", "w")
    
    if pos_neg:
        t = i
        f.write(str(t))
    ########################################################
    f.close()