from msilib.schema import File
import os, json

from flask import Flask
from . import db

from paho.mqtt import client

HOST = "test.mosquitto.org"
mqtt = client.Client(userdata="Birdhub Server")

def on_publish(client,userdata,mid):
    print("User", str(userdata), "has published something")

mqtt.connect(HOST,1883,60)

mqtt.on_publish = on_publish

# starting listening for messages
mqtt.loop_start()

with open(os.getcwd() + "\\birdhub\\static\\config.json", "r") as fp:
    mqtt.publish("birdhub/parameters/config", fp.read(), retain=True)

def create_app(test_config=None):
    # create and configure the app
    app = Flask(__name__, instance_relative_config=True)
    app.config.from_mapping(
        SECRET_KEY='dev',
        DATABASE=os.path.join(app.instance_path, 'birdhub.sqlite'),
    )

    if test_config is None:
        # load the instance config, if it exists, when not testing
        app.config.from_pyfile('config.py', silent=True)
    else:
        # load the test config if passed in
        app.config.from_mapping(test_config)

    # ensure the instance folder exists
    try:
        os.makedirs(app.instance_path)
    except OSError:
        pass
    
    db.init_app(app)

    from . import home
    app.register_blueprint(home.bp)
    app.add_url_rule('/', endpoint='index')
    return app