"new development branch" 
# test

branch front-end hiện đang là branch đang phát triển front-end

branch back-end hiện đang là branch đang phát triển back-end


## Project setup

```

# update to python 3 
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3 1

# install Django and Django REST framework into the virtual environment
pip install django
pip install djangorestframework

# install jwt
pip install djangorestframework-simplejwt

# adds CORS (Cross-Origin Resource Sharing) headers to responses.
python -m pip install django-cors-headers

# connect to database
pip install mysqlclient
```

### run file back-end 
```
python manage.py runserver
```

### run file front-end
```
npm run serve
```
