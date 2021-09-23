# Full-Stack là nơi chứa cấu trúc hệ thống Web bao gồm 2 folder Backend-Front-end
# Script là nơi chưa các file Python để tạo Database, tất cả script sẽ đặt trong này
# Tools ...

"new development branch" 
# test

branch front-end hiện đang là branch đang phát triển front-end

branch back-end hiện đang là branch đang phát triển back-end


## Back-end environment setup
#### 1. Update to python 3 
```
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3 1
```
#### 2. Install Django and Django REST framework into the virtual environment
```Create a virtual environment
python3 -m venv <your virtual environment name> (i.e: python3 -m venv myVenv)
```on Window:
tutorial-env\Scripts\activate.bat
```on Unix:
source <your virtual environment name>/bin/activate
```install django and framework
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
pip install mysqlclient
```
#### 6. Create a database name "testcrud" in MySql

#### 7. Applying migrations to database
```
python manage.py migrate
```
#### 8. Done setup!
                                           
                                           

## run file back-end 
```
python manage.py runserver
```
## run file front-end
```
npm run serve
```
