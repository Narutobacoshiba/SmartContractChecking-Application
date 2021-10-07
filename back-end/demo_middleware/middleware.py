from django.http.response import JsonResponse
from rest_framework import status
from rest_framework.response import Response
import jwt
class DemoMiddleWare:
    def __init__(self,get_response):
        self.get_response = get_response


    def __call__(self,request):
        response = self.get_response(request)
        #try:
            # path = request.path
            # if path.__eq__("/login"):
            #     print(request.path)
            #     # -> Cho thong qua -> tra ve cai request cua front end
            #     return response
            # else:
            #     jwtClient = request.headers['authorization']
            #     print(jwtClient)
            #     #verify token in here
            #     user = jwt.decode(jwtClient, "demo", algorithms=["HS256"])
            #     if user:
            #         return response
            #     else:
            #         return JsonResponse({"status":False,"message":"Token is Not Valid"},status=status.HTTP_401_UNAUTHORIZED,safe=False)
        return response
        # except Exception as e:
        #     return JsonResponse({"status":False},status=status.HTTP_401_UNAUTHORIZED,safe=False)

    
