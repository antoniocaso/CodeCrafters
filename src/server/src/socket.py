import os, socket, threading, json, struct
from enum import Enum
from uuid import uuid4
from .lobby import Lobby
from .util import check_GP


class State(Enum):
    WAITING = 1,
    LOGGED = 2,
    WAITING_FILES = 3,
    BETTING = 4


class ServerSocket:
    
    BUFF_SIZE = 1024

    def __init__(self, host = "localhost", port=12345) -> None:
        self.host = host
        self.port = port
        self._socket = None
        self.connections = []
        self._context = None

    def start(self):

        self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._socket.bind((self.host, self.port))
        self._socket.listen()
        print(f"Server listening on {self.host}:{self.port}")

        try:
            while True:
                conn, addr = self._socket.accept()
                
                print(f"Accepted connection from {addr}")
                secure_conn = conn
                self.connections.append(secure_conn)
                self._context.add_to_lobby(secure_conn)
               
                client_thread = threading.Thread(target=self.handle_client, args=(secure_conn, addr, self._context.last_lobby))
                client_thread.start()
        except socket.timeout:
            pass
        
    def handle_client(self, conn, addr, lobby : Lobby):
        
        print(f"Handling client {addr} in lobby {lobby.idx}")

        state = State.WAITING
        
        challenge = ""
        action = b''

        try:
            while True:
                match state:
                    case State.WAITING:
                        action = conn.recv(1)

                        challenge = open('/dev/random', 'rb').read(32)
                        conn.send(challenge)
                        state = State.WAITING_FILES
                        
                    case State.WAITING_FILES:
                        print(f"Waiting for user {addr} to send green pass files.")
                        uuid = str(uuid4())
                        # firmare green pass + sigma + user_data
                        filenames = ['green_pass.json', 'signature.bin', 'user_data.json', 'public_key.pem', 'challenge_signature.bin']
                
                        for filename in filenames:
                            filename = os.path.join('./static/output', uuid, filename)
                            user_path = os.path.join('./static/output', uuid)
                            if not os.path.exists(user_path):
                                try:
                                    os.makedirs(user_path)
                                except FileExistsError:
                                    pass            
                            
                            self.recv_data(conn, filename)
                            print(f"Received {filename} file.")
                        
                        with open(os.path.join('./static/output', uuid, 'user_data.json')) as f:
                            args = json.load(f)
                            args['challenge'] = challenge
                            args['uuid'] = uuid
                            
                            b = check_GP(args)

                            user_id = json.load(open(os.path.join('./static/output', uuid, 'green_pass.json')))["id"]

                            if b:
                                if action == b'1': # auth:
                                    if self._context.is_registered(user_id):
                                        print(f"User {addr} logged in correctly")   
                                        conn.send(b'1')
                                        state = State.LOGGED
                                    else:
                                        print(f"User {addr} is not registered.") 
                                        conn.send(b'0')
                                        self.send_msg(conn, f"You are not registered.")
                                        state = State.WAITING
                                elif action == b'0': # registration
                                    print(f"User {addr} passed the Green Pass check")
                                    if not self._context.is_registered(user_id):
                                        self._context.register_user(user_id)
                                        conn.send(b'1')
                                        state = State.LOGGED
                                    else:
                                        print(f"User is already registered")
                                        conn.send(b'0')
                                        self.send_msg(conn, f"You are already registered.")
                                        state = State.WAITING
                                else:
                                    print(f"Malformed command was sent: {action}")
                                    conn.send(b'0')
                                    self.send_msg(conn, f"Protocol error.")
                                    state = State.WAITING
                            else:
                                print(f"User {addr} did not pass the Green Pass check.")
                                conn.send(b'0')
                                self.send_msg(conn, f'Green Pass check failed, cause "{args["reason"]}".')
                                state = State.WAITING  

                    case State.LOGGED:

                        seed = self.recv(conn, 32)
                        i = lobby.find_player(conn)
                        path = f'./static/random/{lobby.idx}/s{i+1}'
                        if not os.path.exists(path):
                            os.makedirs(path)

                        with open(path + '/seed', 'wb') as f:
                            f.write(seed)

                        bet = self.recv_msg(conn)
                        bet = int(bet)
                        print(f"User {addr} has placed {bet}")
                        if bet > 0:
                            lobby.add_bet(conn, bet)
                        else:
                            print(f"Incorrect bet")

                        state = State.BETTING


                    case State.BETTING:
                        if lobby.winner != -1:
                            if lobby.is_winner(conn):
                                print("We have a winner")
                                self.send_msg(conn, "You won!")
                            else:
                                print("We don't have a winner")
                                self.send_msg(conn, "You lost!")
                            state = State.LOGGED

        except socket.error as e:
            print(f"Client {addr} has disconnected")
            #self.connections.remove(conn)
            lobby = self._context.inverted_index[conn]
            if lobby:
                self._context.remove_from_lobby(conn)
            print(e)
        except Exception as e:
            print(f"Closing {addr} thread")
            #self.connections.remove(conn)
            lobby = self._context.inverted_index[conn]
            if lobby:
                self._context.remove_from_lobby(conn)
            print(e)
    
    def is_socket_closed(self, conn):
        try:
            data = conn.recv(16, socket.MSG_DONTWAIT | socket.MSG_PEEK)
            if len(data) == 0:
                return True
        except BlockingIOError:
            return False
        except ConnectionResetError:
            return True
        except Exception as e:
            print(e)
            return False    
        return False
    
    def recv(self, conn, size):
        if self.is_socket_closed(conn):
            print(f"Client {conn} has disconnected")
            self.connections.remove(conn)
            self._context.remove_from_lobby(conn)
            raise Exception
        else:
            return conn.recv(size)

    def send_msg(self, conn, message):
        message_bytes = message.encode()
        message_length = len(message_bytes)
        header = struct.pack("!I", message_length)
        conn.sendall(header + message_bytes)

    def recv_msg(self, conn):
        header = conn.recv(4)
        message_length = struct.unpack("!I", header)[0]

        message = b""
        while len(message) < message_length:
            chunk = conn.recv(min(message_length - len(message), 4096))
            if not chunk:
                break
            message += chunk
        
        return message.decode()

    def recv_data(self, conn, filename):
        filesize = self.recv(conn, 32)
        filesize = int(filesize, 2)
        
        with open(filename, "wb") as f:

            chunksize = ServerSocket.BUFF_SIZE

            while filesize > 0:
                if filesize < chunksize:
                    chunksize = filesize
                data = self.recv(conn, chunksize)
                f.write(data)
                filesize -= len(data)

    def stop(self):
        for client_socket in self.connections:
            client_socket.close()
        if self._socket:
            self._socket.close()