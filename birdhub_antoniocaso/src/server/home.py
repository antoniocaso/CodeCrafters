from flask import (Blueprint, render_template, request)

from birdhub.db import get_db

bp = Blueprint('home', __name__)
from . import mqtt

def get_last_photo():
    return get_db().execute(
            'SELECT p.photo_name FROM photo p ORDER BY p.photo_id DESC LIMIT 1'
        ).fetchone()

### ENDPOINTS ###
@bp.route('/tare')
def tare():
    mqtt.publish("birdhub/loadCell/tare", "tare", qos=1)
    photo_name = get_last_photo()
    return render_template('base.html', photo=photo_name)

@bp.route('/calibrate/', methods=('GET', 'POST'))
def calibrate():
    known_weight = request.form['known-weight']
    mqtt.publish("birdhub/loadCell/calibration", known_weight, qos=1)
    photo_name = get_last_photo()
    return render_template('base.html', photo=photo_name)

@bp.route('/replenish/<supply>')
def replenish(supply):
    mqtt.publish("birdhub/replenish", supply, qos=2)
    photo_name = get_last_photo()
    return render_template('base.html', photo=photo_name)

@bp.route('/setAngle/', methods=('GET', 'POST'))
def set_angle():
    angle = request.form['angle']
    mqtt.publish("birdhub/parameters/setAngle", str(angle), qos=2)
    photo_name = get_last_photo()
    return render_template('base.html', photo=photo_name)

@bp.route('/setPumpTime/', methods=('GET', 'POST'))
def set_pump_time():
    time = request.form['pump-time']
    mqtt.publish("birdhub/parameters/setPumpTime", str(time))

    photo_name = get_last_photo()
    return render_template('base.html', photo=photo_name)

@bp.route('/cam', methods=('GET', 'POST'))
def get_data():
    if request.method == 'POST':
        print(request.data)
        base_name = "bird"
        db = get_db()
        
        last_id = db.execute(
            'SELECT p.photo_id FROM photo p ORDER BY p.photo_id DESC LIMIT 1'
        ).fetchone()
        print(last_id)

        photo_name = '/images/' + base_name + str(last_id[0]).zfill(3) + ".jpg"
        
        with open('./birdhub/static' + photo_name, 'wb') as file:
            file.write(request.data)

        db.execute(
            'INSERT INTO photo (photo_name) VALUES(?)',
            (photo_name,)
        )
        
        db.commit()
    return 'Got data'


@bp.route('/takePhoto')
def take_photo():
    mqtt.publish("birdhub/cam/takePhoto", "photo")
    photo_name = get_last_photo()
    return render_template('base.html', photo=photo_name)

@bp.route('/config', methods=('GET', 'POST'))
def save_config():
    if request.method == 'GET':
        with open("./birdhub/static/config.json", "rb") as f:
            return f.read()
    if request.method == 'POST':
        config_string = request.data
        with open("./birdhub/static/config.json", "wb") as f:
            f.write(config_string)
            return 'OK'


@bp.route('/')
def index():
    photo_name = get_last_photo()
    return render_template('base.html', photo=photo_name)