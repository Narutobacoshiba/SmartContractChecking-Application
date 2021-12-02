from rest_framework import status
from rest_framework.views import APIView
from rest_framework.response import Response
from mainfolder.authentication import JSONWebTokenAuthentication
from .serializer import ContextSerializer
from .models import CPNContext
from rest_framework.decorators import api_view
# Create your views here.

class GetAllContextAPIView(APIView):
	authentication_classes  = [JSONWebTokenAuthentication]
	def get(self, request):
		user = request.user
		try:
			contexts = user.cpncontext_set.all()
			
			response = []
			for c in contexts:
				if c.name != "free_context":
					response.append({"ccid":c.ccid,"name":c.name,
					    "description":c.description,"context_type":c.context_type,"content":c.content})				
			return Response(response,status=status.HTTP_200_OK)
		except:
			return Response({"detail":{"message":"Some thing wrong!"}},status=status.HTTP_400_BAD_REQUEST) 
			
class ContextAPIView(APIView):
    authentication_classes  = [JSONWebTokenAuthentication]
    #----------GET ALL CONTEXT-----------
    def get(self, request):
        try:
            if request.method == "GET":
                contextDB = CPNContext.objects.all()
                serializeContext = ContextSerializer(contextDB, many=True)
                return Response(serializeContext.data, status=status.HTTP_202_ACCEPTED)
        except Exception as e:
            return Response({"message": "Get Data Fail!!"}, status=status.HTTP_400_BAD_REQUEST)


    #----------CREATE CONTEXT-----------
    def post(self, request):
        try:
            if request.method == "POST":
                serializerClient = ContextSerializer(data=request.data)
                if serializerClient.is_valid():
                    serializerClient.save()
                    return Response({"message": "Created"}, status=status.HTTP_201_CREATED)
                return Response({"message": "Field of Context is not Valid"}, status=status.HTTP_400_BAD_REQUEST)
        except Exception as e:
            print(e)
            return Response({"message": "Create Faill!!!"}, status=status.HTTP_400_BAD_REQUEST)


    #----------UPDATE CONTEXT-----------
    def put(self, request):
        try:
            if request.method == "PUT":
                idClient = request.data['ccid']
                ContextFromDBById = CPNContext.objects.get(ccid=idClient)
                serializeUpdate = ContextSerializer(
                    instance=ContextFromDBById, data=request.data)
                if serializeUpdate.is_valid():
                    serializeUpdate.save()
                    return Response({"message": "Update Successfully!!"})
                return Response({"message": "Context Data is Invalid"}, status=status.HTTP_409_CONFLICT)
        except Exception as e:
            return Response({"message": "Faill!"}, status=status.HTTP_404_NOT_FOUND)

    #----------DELETE CONTEXT-----------
    def delete(self, request):
        try:
            if request.method =="DELETE":
                idClient = request.GET['ccid']
                ContextById = CPNContext.objects.get(ccid=idClient)
                print('Here')
                print(ContextById)
                ContextById.delete()
                return Response({"message":"Delete Successfull"},status=status.HTTP_200_OK)
        except Exception as e:
            return Response({"message":"Delete Faill!!!"},status=status.HTTP_400_BAD_REQUEST)

@api_view(['GET'])
def getCTById(request):
        try:
            if request.method == 'GET':
                idClient = request.GET['id']
                ContextFrontDBById = CPNContext.objects.get(id=idClient)
                serializeContext = ContextSerializer(ContextFrontDBById)
                return Response(serializeContext.data,status=status.HTTP_200_OK)
        except:
            return Response({"message":"Get Data Fail!!"},status=status.HTTP_400_BAD_REQUEST)
