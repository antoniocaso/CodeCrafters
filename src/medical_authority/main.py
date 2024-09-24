from src.app import get_app
import ssl
context = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
context.load_cert_chain(certfile="./keys/cert.pem", keyfile="./keys/private_key.pem")

if __name__ == '__main__':
    app = get_app()
    app.run(host='0.0.0.0')
