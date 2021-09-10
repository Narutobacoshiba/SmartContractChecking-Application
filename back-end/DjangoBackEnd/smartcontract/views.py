from .serializer import GetSmartConstractSerializer
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from .models import SmartConstract
# Create your views here.

class SmartConstractAPIView(APIView):
    def get(self,request):
        try:
            if request.method == 'GET':
                smartConstractDB = SmartConstract.objects.all()
                serialiSmartConstract = GetSmartConstractSerializer(smartConstractDB,many=True)
                return Response(serialiSmartConstract.data,status=status.HTTP_200_OK)
        except:
            return Response({"message":"Get Data Fail!!"},status=status.HTTP_400_BAD_REQUEST)

    def post(self,request):
        try:
            if request.method == 'POST':
                serializeClient = GetSmartConstractSerializer(data=request.data)
                if serializeClient.is_valid():
                    serializeClient.save()
                    return Response({"message":"Created"},status=status.HTTP_201_CREATED)
                return Response({"message":"Create fail!!!"},status=status.HTTP_400_BAD_REQUEST)
        except:
            return Response({"message":"Create fail!!!"},status=status.HTTP_400_BAD_REQUEST)

    def put(self,request):
        try:
            if request.method == 'PUT':
                idClient = request.data['id']
                SmartConstractByID = SmartConstract.objects.get(id=idClient)
                serializeUpdate = GetSmartConstractSerializer(instance=SmartConstractByID,data=request.data)
                if serializeUpdate.is_valid():
                    serializeUpdate.save()
                    return Response({"message":"Update Successfull!!!"},status=status.HTTP_202_ACCEPTED)
                return Response({"message":"SmartConstract Data Invalid!!!"},status=status.HTTP_409_CONFLICT)
        except:
            return Response({"message":"Fail!!"},status=status.HTTP_404_NOT_FOUND)
    
    def delete(self,request):
        try:
            if request.method == 'DELETE':
                idClient = request.data['id']
                SmartConstractByID = SmartConstract.objects.get(id=idClient)
                SmartConstractByID.delete()
                return Response({"message":"Delete Successfull!"},status=status.HTTP_200_OK)
        except:
            return Response({"message":"Fail!!"},status=status.HTTP_404_NOT_FOUND)