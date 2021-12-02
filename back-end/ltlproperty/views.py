from rest_framework import status
from rest_framework.views import APIView
from rest_framework.response import Response
from mainfolder.authentication import JSONWebTokenAuthentication
from .models import LTLTemplate
from .serializer import LTLproSerializer
# Create your views here.


class GetLTLTemplateAPIView(APIView):
    authentication_classes = [JSONWebTokenAuthentication]

    def get(self, request):

        try:
            ltl_templates = LTLTemplate.objects.all()

            ret = []
            for temp in ltl_templates:
                temp_el = {}
                temp_el["id"] = temp.lteid
                temp_el["name"] = temp.name
                temp_el["formula"] = temp.formula
                temp_el["formula_text"] = temp.formula_text
                temp_el["created_timestamp"] = temp.created_timestamp
                temp_el["template_type"] = temp.template_type
                temp_el["description"] = temp.description
                ret.append(temp_el)
            return Response(ret, status=status.HTTP_200_OK)
        except:
            return Response({"detail": "Getting ltl-template error!"}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

    def post(self, request):
        try:
            if request.method == "POST":
                serializerClient = LTLproSerializer(data=request.data)
                if serializerClient.is_valid():
                    serializerClient.save()
                    return Response({"message": "Created"}, status=status.HTTP_201_CREATED)
                return Response({"message": "Field of LTL properties is not Valid"}, status=status.HTTP_400_BAD_REQUEST)
        except Exception as e:
            print(e)
            return Response({"message": "Create Faill!!!"}, status=status.HTTP_400_BAD_REQUEST)

    def put(self, request):
        try:
            if request.method == "PUT":
                idClient = request.data['lteid']
                LTLproFromDBById = LTLTemplate.objects.get(lteid=idClient)
                serializeUpdate = LTLproSerializer(
                    instance=LTLproFromDBById, data=request.data)
                if serializeUpdate.is_valid():
                    serializeUpdate.save()
                    return Response({"message": "Update Successfully!!"})
                return Response({"message": "LTL Data is Invalid"}, status=status.HTTP_409_CONFLICT)
        except Exception as e:
            print(e)
            return Response({"message": "Create Faill!!!"}, status=status.HTTP_400_BAD_REQUEST)

    def delete(self, request):
        try:
            if request.method == "DELETE":
                idClient = request.GET['lteid']
                LTLproDBById = LTLTemplate.objects.get(lteid=idClient)
                LTLproDBById.delete()
                return Response({"message": "Delete Successfull"}, status=status.HTTP_200_OK)
        except Exception as e:
            print(e)
            return Response({"message": "Create Faill!!!"}, status=status.HTTP_400_BAD_REQUEST)
