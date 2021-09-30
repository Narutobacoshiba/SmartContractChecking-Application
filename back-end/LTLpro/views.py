from django.core.exceptions import ValidationError
from rest_framework.serializers import Serializer
from rest_framework import exceptions
from .serializer import LTLproSerializer
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from .models import LTLpro
from rest_framework.decorators import api_view
# Create your views here.

class LTLproAPIView(APIView):

	    #----------GET ALL LTL properties-----------
	def get(self,request):
		try:
			if request.method == 'GET':
				LTLproDB = LTLpro.objects.all()
				serializeLTLpro = LTLproSerializer(LTLproDB, many=True)
				return Response(serializeLTLpro.data, status=status.HTTP_202_ACCEPTED)
		except Exception as e: 
			return Response({"message": "Get Data Fail!!"}, status=status.HTTP_400_BAD_REQUEST)

        ##----------CREATE LTL properties-----------
	def post(self, request):
		try:
			if request.method == "POST":
				serializerClient = LTLproSerializer(data=request.data)
				if serializerClient.is_valid():
					serializerClient.save()
					return Response({"message": "Created"}, status=status.HTTP_201_CREATED)
				return Response({"message": "Field of LTL properties is not Valid"}, status=status.HTTP_400_BAD_REQUEST)
		except exceptions as e:
			print(e)
			return Response({"message": "Create Faill!!!"}, status=status.HTTP_400_BAD_REQUEST)

		#----------UPDATE -----------
	def put(self, request):
		try:
			if request.method == "PUT":
				idClient = request.data['id']
				LTLproFromDBById = LTLpro.objects.get(id=idClient)
				serializeUpdate = LTLproSerializer(instance=LTLproFromDBById, data=request.data)
				if serializeUpdate.is_valid():
					serializeUpdate.save()
					return Response({"message": "Update Successfully!!"})
				return Response({"message": "LTL Data is Invalid"}, status=status.HTTP_409_CONFLICT)
		except Seri as e:
			return Response({"message": "Faill!"}, status=status.HTTP_404_NOT_FOUND)

    	#----------DELETE -----------
	def delete(self, request):
		try:
			if request.method =="DELETE":
				idClient = request.GET['id']
				LTLproDBById = LTLpro.objects.get(id=idClient)
				print('Here')
				print(LTLproDBById)
				LTLproDBById.delete()
				return Response({"message":"Delete Successfull"},status=status.HTTP_200_OK)
		except Exception as e:
			return Response({"message":"Delete Faill!!!"},status=status.HTTP_400_BAD_REQUEST)

@api_view(['GET'])
def getLTLById(request):
	try:
		if request.method == 'GET':
			idClient = request.GET['id']
			LTLproFrontDBById = LTLpro.objects.get(id=idClient)
			serializeLtl = LTLproSerializer(LTLproFrontDBById)
			return Response(serializeLtl.data,status=status.HTTP_200_OK)
	except:
		return Response({"message":"Get Data Fail!!"},status=status.HTTP_400_BAD_REQUEST)