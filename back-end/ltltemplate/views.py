from django.core.exceptions import ValidationError
from rest_framework.serializers import Serializer
from rest_framework import exceptions
from .serializer import ltltemplateSerializer
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from .models import ltltemplate
from rest_framework.decorators import api_view
# Create your views here.

class ltltemplateAPIView(APIView):

	    #----------GET ALL LTL properties-----------
	def get(self,request):
		try:
			if request.method == 'GET':
				LTLproDB = ltltemplate.objects.all()
				serializeLTLpro = ltltemplateSerializer(LTLproDB, many=True)
				return Response(serializeLTLpro.data, status=status.HTTP_202_ACCEPTED)
		except Exception as e: 
			return Response({"message": "Get Data Fail!!"}, status=status.HTTP_400_BAD_REQUEST)
	
	def getCTById(request):
		try:
			if request.method == 'GET':
				idClient = request.GET['id']
				ContextFrontDBById = ltltemplate.objects.get(id=idClient)
				serializeContext = ltltemplateSerializer(ContextFrontDBById)
				return Response(serializeContext.data,status=status.HTTP_200_OK)
		except:
			return Response({"message":"Get Data Fail!!"},status=status.HTTP_400_BAD_REQUEST)