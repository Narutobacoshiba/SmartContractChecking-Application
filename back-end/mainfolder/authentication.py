import jwt
import datetime
from django.conf  import settings
from rest_framework import exceptions
from rest_framework.authentication import BaseAuthentication
from account.models import Account

class JSONWebTokenAuthentication(BaseAuthentication):
    def authenticate(self, request):
        jwt_token = request.headers['authorization']
        try:
            payload = jwt.decode(jwt_token, settings.SECRET_KEY, algorithms=['HS256'])
            user = Account.objects.get(username=payload['user_name'])
        except (jwt.DecodeError, Account.DoesNotExist):
            raise exceptions.AuthenticationFailed('Invalid token')
        except jwt.ExpiredSignatureError:
            raise exceptions.AuthenticationFailed('Token has expired')
        return (user,payload)

    @staticmethod
    def generate_jwt(username,tokentype,num):
        payload = {
            'user_name': username,
            'token_type': tokentype,
            'exp': datetime.datetime.utcnow() + datetime.timedelta(hours = num),
            'iat': datetime.datetime.utcnow()
        }
        return jwt.encode(payload, settings.SECRET_KEY, algorithm='HS256')
