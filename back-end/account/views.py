from rest_framework import status
from rest_framework.views import APIView
from rest_framework.response import Response
from mainfolder.authentication import JSONWebTokenAuthentication
from .models import Account, Contact
from .serializers import LoginSerializer
from rest_framework import exceptions

class LoginAPIView(APIView):
	authentication_classes  = []
	def post(self, request):
		serializer = LoginSerializer(data=request.data)
		if serializer.is_valid():	
			username = serializer.data['username']
			password = serializer.data['password']
			try:
				user = Account.objects.get(username=username)
				if password != user.password:
					raise exceptions.AuthenticationFailed({"message":'Incorrect password!',"target":"password"})                
              
				return Response({'accessToken':JSONWebTokenAuthentication.generate_jwt(username,'access',1),
				                 'refreshToken':JSONWebTokenAuthentication.generate_jwt(username,'refresh',24)}, status=status.HTTP_200_OK)
			except Account.DoesNotExist:
				raise exceptions.AuthenticationFailed({"message":'User not found!',"target":"user"})
               
		else:
			return Response({"detail":{"message":"Login parameters not correct!!!"}},status=status.HTTP_400_BAD_REQUEST)
               
               
class CurrentAPIView(APIView):
	authentication_classes = [JSONWebTokenAuthentication]
	
	def get(self, request):
		user = request.user
		try:
			contact = Contact.objects.filter(aid=user.aid).first()
			return Response({'id':user.aid,'username':user.username,
			                 'role':user.role,'firstname':contact.firstname,
			                 'lastname':contact.lastname,'email':contact.email}, status=status.HTTP_200_OK)
		except Contact.DoesNotExist:
			return Response({'id':user.aid,'username':user.username,
			                 'role':user.role,'firstname':'',
			                 'lastname':'','email':''}, status=status.HTTP_200_OK)
			                 
class RefreshTokenAPIView(APIView):
	authentication_classes = []
	def post(self, request):
		username = request.data['username']
		return Response({'accessToken':JSONWebTokenAuthentication.generate_jwt(username,'access',1)})
		
