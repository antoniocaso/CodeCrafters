import sqlite3, time, threading

from .socket import ServerSocket
from .lobby import Lobby
from .lib.random import random_number_generator, sha256

class Server:

    RANGE_MAX = 90
    SEED_LENGTH = 32

    def __init__(self, host='localhost', port=12345, create_database=False) -> None:
        self.lobbies = [Lobby()]
        self.last_lobby = self.lobbies[0] 
        self.inverted_index = {}
        self.socket = ServerSocket(host, port)
        self.socket._context = self
        
        if create_database:
            self.init_database()
        
        lobby_thread = threading.Thread(target=self.handle_lobby, args=(self.last_lobby,))
        lobby_thread.start()

        self.socket.start()
        # WARNING: do not put anything under this line
        # because the start() method is blocking
    
    def init_database(self):
        with sqlite3.connect("users.db") as con:
            cur = con.cursor()
            cur.execute("DROP TABLE IF EXISTS user")
            cur.execute("CREATE TABLE user(id PRIMARY KEY, wallet)")

    def add_to_lobby(self, conn):
        if self.last_lobby.is_full():
            self.lobbies.append(self.last_lobby)
            self.last_lobby = Lobby()
            lobby_thread = threading.Thread(target=self.handle_lobby, args=(self.last_lobby,))
            lobby_thread.start()
        
        self.last_lobby.add(conn)
        self.inverted_index[conn] = self.last_lobby

    def remove_from_lobby(self, conn):
        lobby = self.inverted_index[conn]
        lobby.remove(conn)
        if len(lobby) == 0:
            if lobby == self.last_lobby:
                if len(self.lobbies) != 1:
                    self.last_lobby = self.lobbies[-2]
                else:
                    self.last_lobby = Lobby()
            self.lobbies.remove(lobby)

    def handle_lobby(self, lobby:Lobby):
        """
        Random Number Generation
        """
        print(f"Lobby {lobby.idx} thread started")
        while True:
            time.sleep(0.5)
            if lobby.is_ready():
                print(f"Initializing random number generation")
                seed_path = f"./static/random/{lobby.idx}"
                generator = random_number_generator(seed_path, len(lobby)+1, Server.SEED_LENGTH)

                print(f"Sending random number to lobby {lobby.idx}")
                num = next(generator) % Server.RANGE_MAX
                print("Got number", num)
                lobby.broadcast_msg(str(num))

                lobby.broadcast_msg(str(len(lobby) + 1))
                for i in range(len(lobby)+1):
                    with open(seed_path + f'/s{i}/seed', 'rb') as f:
                        seed = f.read(Server.SEED_LENGTH)
                        for conn in lobby._connections:
                            conn.sendall(seed)

                if num in lobby.bets:
                    lobby.winner = lobby.bets.index(num)
                else:
                    lobby.winner = -2

                lobby.bets = [-1] * len(lobby.bets)

    def is_registered(self, user_id):
        with sqlite3.connect("users.db") as con:
            cur = con.cursor()
            cur.execute("SELECT * FROM user WHERE id = ?", (sha256(bytes(user_id, 'utf-8')).decode(), ))
            row = list(cur.fetchall())
            if len(row) == 0:
                return False
            else:
                return True
   
    def register_user(self, user_id):
        with sqlite3.connect("users.db") as con:
            cur = con.cursor()
            cur.execute("INSERT INTO user VALUES(:id, 0)",( sha256(bytes(user_id, 'utf-8')).decode(), ))