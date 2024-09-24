import sqlite3
import os
from base64 import b64encode
import json
from .lib.commit import commit
from .lib.sign import sign, generate_keys
import io
import zipfile


class MedicalAuth:
    
    ATTRIBUTES = ["name", "surname", "date_of_birth", "disease", "vaccine_type", "vaccine_medicinal_product", "vaccine_manufacturer", "number_of_dose", "date_of_vaccination", "member_state_of_vaccination", "certificate_issuer"]
    
    def __init__(self, custom_data=None, create_database=False):
        if not os.path.exists('./keys'):
            generate_keys("keys")
        
        if create_database:
            self.init_database(custom_data)


    def get_user_data(self, row):
        return { key: value for key, value in zip(MedicalAuth.ATTRIBUTES, row[1:-2])}
    
    def init_database(self, data=None):
        if data is None:
            data = [{'id': '000000', 'name': 'Miriam', 'surname': 'Amendola', 'date_of_birth': '01/07/2000', 'disease': 'COVID-19', 'vaccine_type': 'RNA_Vaccine', 'vaccine_medicinal_product': 'Comirnaty', 'vaccine_manufacturer': 'Biontech', 'number_of_dose': '3/3', 'date_of_vaccination': '01/07/2023', 'member_state_of_vaccination': 'Italy', 'certificate_issuer': 'Ministero della Salute'}, {'id': '000001', 'name': ' Valerio', 'surname': ' Battipaglia', 'date_of_birth': ' 10/01/2001', 'disease': ' COVID-19', 'vaccine_type': ' RNA_Vaccine', 'vaccine_medicinal_product': ' Comirnaty', 'vaccine_manufacturer': ' Biontech', 'number_of_dose': ' 3/3', 'date_of_vaccination': ' 01/04/2022', 'member_state_of_vaccination': ' Italy', 'certificate_issuer': ' Ministero della Salute'}, {'id': '000002', 'name': ' Giuseppe', 'surname': " Dell'Orto", 'date_of_birth': ' 10/03/2001', 'disease': ' COVID-19', 'vaccine_type': ' RNA_Vaccine', 'vaccine_medicinal_product': ' Comirnaty', 'vaccine_manufacturer': ' Biontech', 'number_of_dose': ' 3/3', 'date_of_vaccination': ' 01/04/2022', 'member_state_of_vaccination': ' Italy', 'certificate_issuer': ' Ministero della Salute'}]

        with sqlite3.connect("certs.db") as con:
            cur = con.cursor()
            cur.execute("DROP TABLE IF EXISTS cert")
            cur.execute("CREATE TABLE cert(id PRIMARY KEY, " + ",".join(MedicalAuth.ATTRIBUTES) + ", emitted, expiration_date)")

            cur.executemany("INSERT INTO cert VALUES(:id, :"+ ",:".join(MedicalAuth.ATTRIBUTES)+ ",0, NULL)", data)

    def prepare_certificate(self, user_id):
        """Generates Green Pass associated to user with id equal to user_id 
        """
        with sqlite3.connect("certs.db") as con:
            cur = con.cursor()

            cur.execute("SELECT * FROM cert WHERE id = ?", (user_id,))

            row = list(cur.fetchall())[0]
            
            # if green pass was never emitted, generate keys
            if row[-2] == 0:
                generate_keys(user_id)

            user_data = self.get_user_data(row)
            
            green_pass = {}

            green_pass["public_key"] = open(os.path.join('certs', user_id, 'public_key.pem')).read()

            for key, value in user_data.items():
                randomness, com = commit(value)
                user_data[key] = (user_data[key], b64encode(randomness).decode('ascii'))
                green_pass[key] = com

            green_pass["id"] = row[0]

            green_pass_path = os.path.join('certs', user_id, 'green_pass.json')
            
            with open(green_pass_path, "w") as f:
                json.dump(green_pass,f)
            
            sign(green_pass_path)

            with open(os.path.join('certs', user_id, 'all_user_data.json'), "w") as f:
                json.dump(user_data, f)
    
    def get_certificate(self, user_id):
        zip_buffer = io.BytesIO()
        
        base_path = os.path.join('certs', user_id)

        with zipfile.ZipFile(zip_buffer, 'w') as zipf:
            zipf.write(os.path.join(base_path, 'all_user_data.json'), arcname='all_user_data.json')
            zipf.write(os.path.join(base_path, 'green_pass.json'), arcname='green_pass.json')
            zipf.write(os.path.join(base_path, 'private_key.pem'), arcname='private_key.pem')
            zipf.write(os.path.join(base_path, 'signature.bin'), arcname='signature.bin')
        
        zip_buffer.seek(0)

        return zip_buffer