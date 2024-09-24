import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox
import os, json
import threading
from .lib.sign import create_challenge_data, sign
from .lib.random import random_number_generator
from datetime import datetime
import shutil
from .socket import Socket

def threaded(func):
    def wrapper(*args, **kwargs):
        thread = threading.Thread(target=func, args=args, kwargs=kwargs)
        thread.start()
        return thread
    return wrapper

class App:
    """ Tasto per creare il green pass e salvare su file
    """
    def __init__(self, root:tk.Tk, port):

        self.root = root
        self.root.title("Client")
        
        self.state_label = tk.Label(root, text='Placeholder')
        self.state_label.pack(side=tk.BOTTOM)

        self.left_frame = tk.Frame(root, width=300, height=300)
        self.right_frame = tk.Frame(root, width=300, height=300)

        self.left_frame.pack(side=tk.LEFT)
        self.right_frame.pack(side=tk.LEFT)
        
        self.load_button = tk.Button(self.left_frame, text="Upload Green Pass Data", command=self.upload_data)
        self.load_button.pack()

        self.button = tk.Button(self.left_frame, text="Login", command=lambda: self.login(b'1') )
        self.button.pack()

        self.signup_button = tk.Button(self.left_frame, text="Signup", command=lambda: self.login(b'0'))
        self.signup_button.pack()

        self.label = tk.Label(self.left_frame, text="Place bet")
        self.text_field = tk.Text(self.left_frame)
        self.bet_button = tk.Button(self.left_frame, text="Bet", command=self.place_bet)
        self.verify_button = tk.Button(self.left_frame, text='Verify', command=self.verify)

        tk.Label(self.right_frame, text="Log").pack()
        self.log = tk.Text(self.right_frame, wrap=tk.WORD, state=tk.DISABLED)
        self.log.pack()

        try:
            self.socket = Socket(port=port)
            self.socket.start()
            self.set_state_label("Connected to server.")  
            self.socket._context = self
        except Exception as e:
            print(f"Error {e}")
            self.set_state_label("Errore di rete.")
        
    def set_state_label(self, text):
        self.state_label["text"] = text
        timestamp = datetime.now().strftime("[%Y-%m-%d %H:%M:%S]")
        self.log.config(state=tk.NORMAL)
        self.log.insert(tk.END, timestamp + " " + text + '\n')
        self.log.config(state=tk.DISABLED)
        self.log.see(tk.END) 

    def prepare_user_data():
        with open('config.json', 'r') as f:
            policy_config = json.load(f)
            POLICY = policy_config["required"]

        with open('./data/all_user_data.json', 'r') as f:
            policy_user_data = {}
            
            user_data = json.load(f)

            for key in POLICY:
                policy_user_data[key] = user_data[key]
            
            with open('./data/user_data.json', 'w') as f:
                json.dump(policy_user_data, f)

    @threaded
    def login(self, action):
        
        self.socket.send(action)
        challenge = self.socket.recv(32)

        create_challenge_data('./data/', challenge)
        
        sign('./data/challenge', './data/private_key.pem', 'challenge_signature.bin')
        filenames = ['green_pass.json', 'signature.bin', 'user_data.json', 'public_key.pem', 'challenge_signature.bin']
    
        for filename in filenames:
            filename = './data/' + filename
            self.socket.send_file(filename)

        reply = self.socket.recv(1)
        if reply == b'0':
            reason = self.socket.recv_msg()
            self.set_state_label(f'Access refused: {reason}')
        else:
            self.set_state_label("Access granted")

            self.button.forget()
            self.signup_button.forget()

            self.label.pack()
            self.text_field.pack()
            self.bet_button.pack()
            self.verify_button.pack()

            self.send_seed()

    def send_seed(self):
        with open('/dev/random', 'rb') as f:
            seed = f.read(32)

        self.socket.connection.sendall(seed)
        

    @threaded
    def upload_data(self):
        import shutil
        dir = filedialog.askdirectory(title="Select Green Pass directory")
        for src in os.listdir(dir):
            print("copied", src)
            shutil.copy(os.path.join(dir, src), "./data/" + src)

        App.prepare_user_data()

    @threaded
    def verify(self):
        m = len(os.listdir('./data/random'))
        print(m)
        seed_path = './data/random/'
        generator = random_number_generator(seed_path, m,n=32)
        self.set_state_label(f"Generator produced: {next(generator) % 90}")

    @threaded
    def place_bet(self):
    
        bet = self.text_field.get("1.0", "end-1c")
        
        if not bet or int(bet) <= 0 or int(bet) > 90:
            messagebox.showinfo('message', 'Please insert a number between 1 and 90.')
            return
        
        self.socket.send_msg(bet)
        self.set_state_label(f"Placed bet {bet}")
        self.bet_button.config(state="disabled")

        num = self.socket.recv_msg()
        print(f"Random number: {num}")
        self.set_state_label(f"Server drawn {int(num)}")

        m = self.socket.recv_msg()
        m = int(m)
        for i in range(m):
            seed = self.socket.recv(32)
            path = f"./data/random/s{i}"
            if not os.path.exists(path):
                try:
                    os.makedirs(path)  
                except FileExistsError:
                    shutil.rmtree(path)

            with open(path + '/seed', 'wb') as f:
                f.write(seed)

        msg = self.socket.recv_msg()
        self.set_state_label(msg)
        self.bet_button.config(state="active")
   
    def on_close(self):
        self.root.destroy()
        self.socket.stop()
        
