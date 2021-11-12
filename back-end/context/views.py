from rest_framework import status
from rest_framework.views import APIView
from rest_framework.response import Response
from mainfolder.authentication import JSONWebTokenAuthentication
# Create your views here.

class GetAllContextAPIView(APIView):
	authentication_classes  = [JSONWebTokenAuthentication]
	def get(self, request):
		user = request.user
		try:
			contexts = user.cpncontext_set.all()
			
			response = []
			for c in contexts:
				response.append({"ccid":c.ccid,"name":c.name,"description":c.description,"context_type":c.context_type,"content":c.content})				
			return Response(response,status=status.HTTP_200_OK)
		except:
			return Response({"detail":{"message":"Some thing wrong!"}},status=status.HTTP_400_BAD_REQUEST) 
			
