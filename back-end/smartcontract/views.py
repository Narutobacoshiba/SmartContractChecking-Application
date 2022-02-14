from rest_framework import status
from rest_framework.views import APIView
from rest_framework.response import Response
from mainfolder.authentication import JSONWebTokenAuthentication
from .models import Smartcontract
from .serializer import GetSmartConstractSerializer


class CrudSmartContract(APIView):
    authentication_classes = [JSONWebTokenAuthentication]
    def post(self, request):
        if request.method == 'POST':
            try:
                request.data['aid'] = request.user.aid
                serializeClient = GetSmartConstractSerializer(
                    data=request.data)
                if serializeClient.is_valid():
                    serializeClient.save()
                    return Response({"message": "Created"}, status=status.HTTP_201_CREATED)
                return Response({"message": "Not Created"}, status=status.HTTP_201_CREATED)
            except Exception as e:
                print(e)
                return Response({"message": "Error"}, status=status.HTTP_400_BAD_REQUEST)

    def put(self, request):
        if request.method == 'PUT':
            try:
                if request.method == 'PUT':
                    idClient = request.data['sid']
                    request.data['aid'] = request.user.aid
                    SmartConstractByID = Smartcontract.objects.get(
                        sid=idClient)
                    serializeUpdate = GetSmartConstractSerializer(
                        instance=SmartConstractByID, data=request.data)
                    if serializeUpdate.is_valid():
                        serializeUpdate.save()
                        return Response({"message": "Update Successfully!!!"}, status=status.HTTP_202_ACCEPTED)
                    return Response({"message": "SmartConstract Data Invalid!!!"}, status=status.HTTP_409_CONFLICT)
            except Exception as e:
                print(e)
                return Response({"message": "Fail!!"}, status=status.HTTP_404_NOT_FOUND)

    def delete(self, request):
        if request.method == 'DELETE':
            try:
                idClient = request.GET['sid']
                SmartConstractByID = Smartcontract.objects.get(sid=idClient)
                SmartConstractByID.delete()
                return Response('Success', status=status.HTTP_200_OK)
            except:
                return Response({"message":"Fail!!"},status=status.HTTP_400_BAD_REQUEST)


class GetAllAPIView(APIView):
    authentication_classes = [JSONWebTokenAuthentication]

    def get(self, request):
        user = request.user
        try:
            smart_contracts = user.smartcontract_set.all()

            response = []
            for sc in smart_contracts:
                response.append({"id": sc.sid, "name": sc.name, "description": sc.description,
                                "type": sc.type, "date_modified": sc.created_timestamp,"content":sc.content})
            return Response(response, status=status.HTTP_200_OK)
        except:
            return Response({"detail": {"message": "Some thing wrong!"}}, status=status.HTTP_400_BAD_REQUEST)


class GetInforAPIView(APIView):
    authentication_classes = [JSONWebTokenAuthentication]

    def post(self, request):
        data = request.data

        if "ids" in data:
            ids = data["ids"]
            ret = []
            for sm_id in ids:
                smart_contract_infor = {
                    "id": sm_id, "name": "", "globalVariables": [], "functions": []}
                try:
                    smart_contract = Smartcontract.objects.get(sid=sm_id)
                    smart_contract_infor["name"] = smart_contract.name

                    global_variables = smart_contract.globalvariable_set.all()
                    for gv in global_variables:
                        gv_infor = {}
                        gv_infor["id"] = gv.gid
                        gv_infor["name"] = gv.name
                        gv_infor["vartype"] = gv.vartype
                        gv_infor["type"] = gv.type
                        gv_infor["value"] = gv.value
                        smart_contract_infor["globalVariables"].append(
                            gv_infor)

                    functions = smart_contract.functions_set.all()
                    for func in functions:
                        function_infor = {
                            "id": func.fid, "name": func.name, "argument": [], "localVariables": []}

                        arguments = func.argument_set.all()

                        for arg in arguments:
                            arg_infor = {}
                            arg_infor["id"] = arg.arid
                            arg_infor["name"] = arg.name
                            arg_infor["vartype"] = arg.vartype
                            arg_infor["type"] = arg.type
                            arg_infor["value"] = arg.value
                            function_infor["argument"].append(arg_infor)

                        local_variables = func.localvariable_set.all()

                        for lv in local_variables:
                            lv_infor = {}
                            lv_infor["id"] = lv.lid
                            lv_infor["name"] = lv.name
                            lv_infor["vartype"] = lv.vartype
                            lv_infor["type"] = lv.type
                            lv_infor["value"] = lv.value
                            function_infor["localVariables"].append(lv_infor)

                        smart_contract_infor["functions"].append(
                            function_infor)
                    ret.append(smart_contract_infor)
                except:
                    pass
            return Response(ret, status=status.HTTP_200_OK)
        else:
            return Response({"detail": {"message": "Invalid argument!"}}, status=status.HTTP_400_BAD_REQUEST)
