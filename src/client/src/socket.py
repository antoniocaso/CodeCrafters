import socket, ssl, struct, os

class Socket:

    BUFF_SIZE = 1024

    def __init__(self, host = "localhost", port=12345) -> None:
        self.host = host
        self.port = port
        self.connection = None
        self.state = 0
        self._context = None
        self.interrupt = False
        self.messages = []

    def start(self):

        self.connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connection.connect((self.host, self.port))
        print(f"Connected to {self.host}:{self.port}")

    def stop(self):
        self.connection.close()

    def recv(self, size):
        return self.connection.recv(size)
        
    def send(self, data):
        self.connection.send(data)

    
    def send_msg(self, message):
        message_bytes = message.encode()
        message_length = len(message_bytes)
        header = struct.pack("!I", message_length)
        self.connection.sendall(header + message_bytes)
    
    def recv_msg(self):
        header = self.recv(4)
        message_length = struct.unpack("!I", header)[0]

        message = b""
        while len(message) < message_length:
            chunk = self.recv(min(message_length - len(message), 4096))
            if not chunk:
                break
            message += chunk
        
        return message.decode()
            
    def recv_data(self):
        msg_size = self.recv(32)
        msg_size = int(msg_size, 2)
        
        chunksize = Socket.BUFF_SIZE

        data = b''
        while msg_size > 0:
            if msg_size < chunksize:
                chunksize = msg_size
            data += self.recv(chunksize)
            msg_size -= len(data)

        return data.decode('utf-8')

    def send_file(self, filename):
    
        try:
            filesize = os.path.getsize(filename)
            filesize = bin(filesize)[2:].zfill(32)
            self.connection.send(filesize.encode())
            
            f = open(filename, "rb")

            data = f.read()
            self.connection.sendall(data)
            f.close()
        except IOError:
            print('Invalid filename.')

