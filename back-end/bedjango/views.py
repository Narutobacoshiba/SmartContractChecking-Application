from django.views.decorators.csrf import csrf_exempt
from django.http import request
from django.shortcuts import render
from bedjango.models import Newuser, SmartContract
from django.contrib import messages
from django.contrib.auth.hashers import make_password, check_password
from django.contrib.auth import authenticate, login, logout
from django.http import JsonResponse
import json
import jwt
import datetime
# import requests


def Indexpage(request):
    # cai nay thay bang file index.vue cua ong
    return render(request, 'index.html')


def Userreg(request):
    if request.method == 'POST':
        Username = request.POST['Username']
        Realname = request.POST['Realname']
        Role = request.POST['Role']
        # Password=make_password(request.POST['Pwd'])
        Password = request.POST['Pwd']
        Newuser(Username=Username, Realname=Realname,
                Role=Role, Password=Password).save()
        mess = {'message': messages.success(
            request, 'The New User'+request.POST['Username']+"IS Saved Successfully..!")}
        # thay bang file registration.vue cua ong
        return render(request, 'Registration.html', mess)
    else:
        # thay bang file registration.vue cua ong
        return render(request, 'Registration.html')


@csrf_exempt
def loginpage(request):
    #     # if request.method=='POST':
    #     #     username= request.POST.get('Username',False)
    #     #     password= make_password(request.POST.get('Pwd',False))
    #     #     user=authenticate(request,username=username,password=password)
    #     #     if user is not None:
    #     #         login(request,user)
    #     #         return render(request,'index.html')
    #     #     else:
    #     #         messages.success(request,'Username/Password Invalid..!')
    #     #         return render(request,'Login.html')
    data = {'exist': "false"}
    if request.method == "POST":
        try:
            # print(request.POST.getall())

            # print(request.POST.get('Pwd'))
            # from json import loads
            # body_unicode = request.body.decode('utf-8')
            # print(body_unicode)
            # #body = json.loads(body_unicode)
            # json = loads(body_unicode)
            #
            # p = json['Pwd']
            # print(p)
            # print(json['Username'])
            # Userdetails = Newuser.objects.get(
            #     Username=json['Username'], Password=json['Pwd'])

            # data = {
            #     'id': Userdetails.id,
            #     'Username': Userdetails.Username,
            #     'Password': Userdetails.Password,
            #     'Realname': Userdetails.Realname,
            #     'Role': Userdetails.Role,
            # }
            data = {
                'id': '1',
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

            token = jwt.encode(payload, 'secret', algorithm='HS256')

            data["jwt"] = token
            print(data)
            return JsonResponse(data, safe=False)
            # return render(request,'index.html',data)
        except Newuser.DoesNotExist as e:
            data = {'exist': "false"}
            print(data)
            return JsonResponse(data, safe=False)
    return JsonResponse(data, safe=False)


def json(request):
    data = Userdetail = [
        {'id': 1, 'name': "Mathematics for Engineering",
         'date_modified': 1607110465663, 'type': "common"},
        {'id': 2, 'name': "Property 2: Fairness",
         'date_modified': 1607110465663, 'type': "common"},
        {'id': 3, 'name': "Course competencies",
         'date_modified': 1607110465663, 'type': "common"},
        {'id': 4, 'name': "Build Web Apps with Vue JS 3 & Firebase",
         'date_modified': 1607110465663, 'type': "common"},
    ]
    return JsonResponse(data, safe=False)


def logout(request):
    try:
        del request.session['Username']
    except:
        return render(request, 'index.html')
    return render(request, 'index.html')
