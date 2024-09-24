import argparse, shutil
from src.server import Server

def cleanup():
    try:
        shutil.rmtree('./static/random/')
        shutil.rmtree('./static/output/')
    except Exception:
        pass
if __name__ == '__main__':
    cleanup()
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--port', default=12345, type=int)
    parser.add_argument('-c', '--create_db', action='store_true', default=False)

    args = parser.parse_args()
    s = Server(port=args.port, create_database=args.create_db)