import subprocess 
import csv
import sqlite3
import os
import json
""" Digital Signature
"""

def create_challenge_data(path, challenge):

    with open(os.path.join(path, 'challenge'), 'wb') as f:
        with open(os.path.join(path,'green_pass.json')) as green_pass:
            with open(os.path.join(path,'user_data.json')) as user_data:
                f.write(bytes(green_pass.read(), 'utf-8'))
                f.write(bytes(user_data.read(), 'utf-8') )
                f.write(challenge)

def generate_keys(name):
    # create dir
    path = os.path.join('certs', name)
    if not os.path.exists(path):
        os.mkdir(path)
    # generate DSA parameters
    subprocess.run(['openssl', 'dsaparam', '-out', str(path) + '/dsaparam.pem', '2048'])
    # generate private key
    subprocess.run(['openssl', 'gendsa', '-out', str(path) + '/private_key.pem', str(path) +'/dsaparam.pem'])
    # generate public key
    subprocess.run(['openssl', 'dsa', '-in', str(path) + '/private_key.pem', '-pubout', '-out', str(path) + '/public_key.pem'])

def sign(file_path, private_key="keys/private_key.pem", signature_name="signature.bin"):
    dirname = os.path.dirname(file_path)
    
    subprocess.run(["openssl", "dgst", "-sha256", "-sign",
                     private_key, "-out", os.path.join(dirname, signature_name), file_path])


def verify_signature(public_key, file_path, signature):
    result = subprocess.run([
        "openssl", "dgst", "-verify", public_key, "-signature", signature, file_path 
        ], capture_output=True, text=True)
    
    if "OK" in result.stdout:
        return True
    else:
        return False
