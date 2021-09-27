## Back-end environment setup
#### 1. Update to python 3 
```
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3 1
```
#### 2. Install Django and Django REST framework into the virtual environment
```
pip install django
pip install djangorestframework
```
#### 3. Install jwt
```
pip install djangorestframework-simplejwt
```
#### 4. Adds CORS (Cross-Origin Resource Sharing) headers to responses.
```
python -m pip install django-cors-headers
```
#### 5. Connect to database MySQL
```
pip install mysqlclient (if error run: sudo apt-get install python3.x-dev libmysqlclient-dev)
```
#### 6. Create a database name "soliditycpn" in MySql

#### 7. Applying migrations to database
```
python manage.py migrate
```
#### 8. Done setup!                                          
                                           

## run file back-end 
```
python manage.py runserver
