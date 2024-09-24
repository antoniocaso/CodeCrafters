import subprocess 

"""Commitment Scheme
"""
def calculate_sha256(file_path):
    openssl_cmd = ['openssl', 'dgst', '-sha256', file_path]

    # Execute the OpenSSL command
    result = subprocess.run(openssl_cmd, capture_output=True, text=True)

    # Extract the SHA256 hash from the output
    output_lines = result.stdout.split('\n')
    sha256_hash = output_lines[0].split('= ')[1]

    return sha256_hash

def commit(message, random_bytes=None):
    with open('/tmp/commit_message', 'wb') as f:
        if random_bytes is None:
            random_bytes = open('/dev/random', 'rb').read(32)

        f.write(bytes(message, 'utf-8'))
        f.write(random_bytes)
    
    return random_bytes, calculate_sha256('/tmp/commit_message')

def verify_commitment(message, random_bytes, commitment):
    return commitment == commit(message, random_bytes)[1]
