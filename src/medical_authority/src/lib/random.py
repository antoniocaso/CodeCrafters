
import subprocess
from .sign import sign
from datetime import datetime

def sha256(data):
    process = subprocess.Popen(['openssl', 'dgst', '-sha256'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate(input=data)
    return stdout.strip().split()[-1]

def _compute_merkle_tree(data_blocks):
    
    if len(data_blocks) == 0:
        return None

    if len(data_blocks) == 1:
        return [sha256(data_blocks[0])]

    if len(data_blocks) % 2 != 0:
        data_blocks.append(data_blocks[-1])

    tree = []

    for i in range(0, len(data_blocks), 2):
        combined_data = data_blocks[i] + data_blocks[i + 1]
        combined_hash = sha256(combined_data)
        tree.append(combined_hash)

    return _compute_merkle_tree(tree)

def merkle_tree(data_blocks):
    return _compute_merkle_tree(data_blocks)[0]

def compute_seed(path, n=32):
    seed = open('/dev/random', 'rb').read(n)
    print(seed)
    timestamp = int(round(datetime.now().timestamp()))
    print(timestamp)
    with open(path + '/seed', "wb") as f:
        f.write(seed)
        f.write(bytes(timestamp))
    
    sign(path + '/seed', 'static/keys/private_key.pem')

"""
RANDOM STRING GENERATION
"""

def get_initial_seed(seed_path, m, n=32):
    seeds = [None] * m
    for i in range(m):
        with open(seed_path + f'/s{i}/seed', 'rb') as f:
            seeds[i] = f.read(n)
    
    return bytearray(merkle_tree(seeds))


def random_string_generator(seed_path, m, n=32):
    initial_seed = get_initial_seed(seed_path, m, n=32)
    
    r = sha256(initial_seed)
    while True:
        yield bytearray(r)
        r = sha256(b''.join([initial_seed,r]))

def random_number_generator(seed_path, m, n=32):
    generator = random_string_generator(seed_path, m,n)

    r = next(generator)
    
    while True:
        if len(r) == 0:
            r = next(generator)
        num = int(r[:4], 16)
        #num = int.from_bytes(r[:16])
        r = r[4:] 
        yield num




if __name__ == '__main__':
    if False:
        print("Testing Merkle Tree")
        seeds = [None] * 10
        for i in range(10):
            seeds[i] = open('/dev/random', 'rb').read(32)

        print(merkle_tree(seeds))

    compute_seed('static/output/random/s0')
