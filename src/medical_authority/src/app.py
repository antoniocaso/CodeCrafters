from flask import Flask, jsonify, render_template, request, send_file
from .medical_auth import MedicalAuth
import sys
sys.path.insert(1, './lib')
def get_app():
    medical_auth = MedicalAuth()
    app = Flask(__name__)

    @app.route('/', methods=['GET'])
    def home():
        return render_template('index.html')

    @app.route('/green_pass', methods=['POST'])
    def green_pass():
        user_id = request.form['user_id']
        medical_auth.prepare_certificate(user_id)
        zip_buffer = medical_auth.get_certificate(user_id) 

        return send_file(zip_buffer,
                        mimetype='application/zip',
                        as_attachment=True,
                        download_name=f'{user_id}_green_pass.zip')

    @app.route('/policy', methods=['GET'])
    def get_policy():
        return jsonify({
            "required":
                ["date_of_vaccination", "name", "surname"],
                "expiration_date": 800
        })
    

    return app
    
