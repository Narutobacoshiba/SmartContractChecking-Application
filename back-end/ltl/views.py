from django.core.exceptions import ValidationError
from rest_framework.serializers import Serializer
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from .models import LTL
from .serializer import LTLSerializer
from rest_framework.decorators import api_view
from rest_framework import exceptions

class LTLAPIView(APIView):
    
    #----------GET ALL CONTEXT-----------
    def get(self, request):
        try:
            if request.method == "GET":
                contextDB = LTL.objects.all()
                serializeLTL = LTLSerializer(contextDB, many=True)
                return Response(serializeLTL.data, status=status.HTTP_202_ACCEPTED)
        except Exception as e:
            return Response({"message": "Get Data Fail!!"}, status=status.HTTP_400_BAD_REQUEST)


    #----------CREATE CONTEXT-----------
    def post(self, request):
        try:
            if request.method == "POST":
                serializerClient = LTLSerializer(data=request.data)
                if serializerClient.is_valid():
                    serializerClient.save()
                    return Response({"message": "Created"}, status=status.HTTP_201_CREATED)
                return Response({"message": "Field of Context is not Valid"}, status=status.HTTP_400_BAD_REQUEST)
        except exceptions as e:
            print(e)
            return Response({"message": "Create Fail!"}, status=status.HTTP_400_BAD_REQUEST)


    #----------UPDATE CONTEXT-----------
    def put(self, request):
        try:
            if request.method == "PUT":
                idClient = request.data['id']
                LTLFromDBById = LTL.objects.get(id=idClient)
                serializeUpdate = LTLSerializer(
                    instance=LTLFromDBById, data=request.data)
                if serializeUpdate.is_valid():
                    serializeUpdate.save()
                    return Response({"message": "Update Successfully!!"})
                return Response({"message": "LTL Data is Invalid"}, status=status.HTTP_409_CONFLICT)
        except Seri as e:
            return Response({"message": "Fail!"}, status=status.HTTP_404_NOT_FOUND)

    #----------DELETE CONTEXT-----------
    def delete(self, request):
        try:
            if request.method =="DELETE":
                idClient = request.GET['id']
                LTLById = LTL.objects.get(id=idClient)
                print('Here')
                print(LTLById)
                LTLById.delete()
                return Response({"message":"Delete Successfull"},status=status.HTTP_200_OK)
        except Exception as e:
            return Response({"message":"Delete Fail!!!"},status=status.HTTP_400_BAD_REQUEST)

@api_view(['GET'])
def getCTById(request):
        try:
            if request.method == 'GET':
                idClient = request.GET['id']
                LTLFrontDBById = LTL.objects.get(id=idClient)
                serializeLTL= LTLSerializer(LTLFrontDBById)
                return Response(serializeLTL.data,status=status.HTTP_200_OK)
        except:
            return Response({"message":"Get Data Fail!!"},status=status.HTTP_400_BAD_REQUEST)