from django.shortcuts import render
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status
from .runscripts import unfoldingTool

# Create your views here.
# -------------receive data for unfolding-------------
@api_view(['POST'])
def unfolding(request):
    try:
        if request.method == 'POST':
            data = request.data
            # ------test data------
            print(">>>", data.keys())
            lna = data["lna"]
            context = data["context"]
            param = data["param"]
            # ------unfolding------
            # unfolding_script(lna, context, param)
            unfoldingTool(lna, context, param)
            return Response({"message": "Run Tool Successfully!"}, status=status.HTTP_200_OK)
    except:
        return Response({"message": "Get Data Fail!!"}, status=status.HTTP_400_BAD_REQUEST)

# -------------receive data for dcr2cpn-------------
@api_view(['POST'])
def dcr2cpn(request):
    try:
        if request.method == 'POST':
            data = request.data
            # ------test data------
            print(data.keys())
            # ------unfolding------
            # dcr2pnTool(xml)
            return Response({"message": "Run Tool Successfully!"}, status=status.HTTP_200_OK)
    except:
        return Response({"message": "Get Data Fail!!"}, status=status.HTTP_400_BAD_REQUEST)

