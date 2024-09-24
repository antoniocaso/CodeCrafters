import os, struct
from uuid import uuid4

class Lobby:

    SEED_LENGTH = 32

    def __init__(self) -> None:
        self.idx = uuid4()
        self._connections = []
        self.bets = []
        self.winner = -1
        self.create_seed()

    def create_seed(self):
        path = f'./static/random/{self.idx}/s0'
        os.makedirs(path)
        with open('/dev/random', 'rb') as f:
            seed = f.read(Lobby.SEED_LENGTH)
        
        with open(path + '/seed', 'wb') as f:
            f.write(seed)
            
    def add(self, conn):
        self._connections.append(conn)
        self.bets.append(-1)

    def find_player(self, conn):
        try:
            index = self._connections.index(conn)
        except ValueError:
            index = -1

        return index 
    
    def remove(self, conn):
        index = self.find_player(conn)
        self.bets.pop(index)
        self._connections.pop(index)

    def is_winner(self, conn):
        return self._connections.index(conn) == self.winner

    def is_full(self):
        return len(self) == 5
    
    def broadcast(self, message):
        for conn in self._connections:
            conn.send(str(message).encode('utf-8'))

    def broadcast_msg(self, message):
        message_bytes = message.encode()
        for conn in self._connections:
            message_length = len(message_bytes)
            header = struct.pack("!I", message_length)
            conn.sendall(header + message_bytes)
    
    def add_bet(self, conn, bet):
        i = self._connections.index(conn)
        self.bets[i] = bet
        print(self.bets)

    def is_ready(self):
        if len(self) > 1:
            try:
                self.bets.index(-1)
            except ValueError:
                return True
        return False
    
    def __len__(self):
        return len(self._connections)
