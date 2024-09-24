import os, json
from datetime import datetime, timedelta
from base64 import b64decode
from .lib.commit import verify_commitment
from .lib.sign import verify_signature, create_challenge_data
"""
GREEN PASS VERIFICATION
"""

with open('config.json', 'r') as f:
        policy_config = json.load(f)
        EXPIRATION_DATE_POLICY = policy_config["expiration_date"]
        POLICY = policy_config["required"]


def hook_verify(args):
    return True

def check_date(d):
    past = datetime.strptime(d, "%d/%m/%Y")
    between = datetime.now() - past
    if between > timedelta(days=EXPIRATION_DATE_POLICY):
        return False
    else:
        return True

def check_GP(args):
        
    path = os.path.join('./static/output', args['uuid'])

    
    create_challenge_data(path, args['challenge'])
    b = verify_signature(path + '/public_key.pem', path + '/challenge' , path + '/challenge_signature.bin')
    if b == False:
        args['reason'] = "Challenge authentication failed"
        print(args['reason'])
        return 
    
    green_pass = {}

    with open(path + '/green_pass.json') as f:
        green_pass = json.load(f)
    
    b = verify_signature('./static/keys/medical_auth_key.pem', path + '/green_pass.json', path + '/signature.bin')
    if b == False:
        args['reason'] = "Medical Authority signature check failed"
        print(args['reason'])
        return False
    
    if 'date_of_vaccination' in args:
        b = check_date(args['date_of_vaccination'][0])
    else:
        b = False
    
    if b == False:
        args['reason'] = "Expired Green Pass"
        print(args['reason'])
        return False
    
    for attribute in POLICY:

        if attribute not in args:
            args['reason'] = f"Policy attribute {attribute} is required"
            print(args['reason'])
            return False
        
        b = verify_commitment(args[attribute][0], b64decode(args[attribute][1]), green_pass[attribute])
        if b == False:
            args['reason'] = f"Attribute {attribute} was tampered."
            print(args['reason'])
            return False
        
    b = hook_verify(args)
    if b == False:
        args['reason'] = "Server-defined criteria haven't been satisfied."
        print(args['reason'])
        return False
    
    return True

if __name__ == '__main__':
    if False:
        print("Testing Green Pass check...")
        user_id = '000000'
            
        with open(os.path.join('output', user_id, 'user_data.json')) as f:
            args = json.load(f)
            args['user_id'] = user_id
            check_GP(args)
    if False:
        print("Testing random string generation...")
        generator = random_string_generator(2)
        for i in range(10):
            print(next(generator))

    if False:
        print("Testing random number generation...")
        generator = random_number_generator(3)
        
        with open('data.csv', "w") as f:
            for i in range(10000):
                f.write(str(i) + ',' + str(next(generator) % 90) + '\n')