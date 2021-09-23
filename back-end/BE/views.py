from django.views.decorators.csrf import csrf_exempt
from django.http import request
from django.shortcuts import render
from django.contrib import messages
from django.contrib.auth.hashers import make_password, check_password
from django.contrib.auth import authenticate, login, logout
from django.http import JsonResponse
import jwt
import datetime


@csrf_exempt
def loginpage(request):
    data = {'exist': "false"}
    if request.method == "POST":
        try:
            data = {
                'id': '12',
                'Username': 'sa',
                'Password': '1',
                'Realname': 'Hanh Ng',
                'Role': 'user',
            }

            payload = {
                'id': data["id"],
                'role': data["Role"],
                'exp': datetime.datetime.utcnow() + datetime.timedelta(minutes=60),
                'iat': datetime.datetime.utcnow()
            }

            token = jwt.encode(payload, 'demo', algorithm='HS256')
            resData = {
                'success': True,
                'accessToken': token
            }
            res = JsonResponse(resData, status=200)
            return res
        except Exception as e:
            data = {'success': False}
            return JsonResponse(data, safe=False)
    return JsonResponse(data, safe=False)

