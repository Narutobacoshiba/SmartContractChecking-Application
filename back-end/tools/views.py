from django.shortcuts import render
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status
from .runscripts import *

# Create your views here.

# -----------receive data-------------------


@api_view(['POST'])
def calltools(request):
    try:
        if request.method == 'POST':
            data = request.data
            # ------test data------
            print(data.keys())
            toolname = data["toolname"]
            print("toolname: ", toolname)

            # -----unfolding--------
            if (toolname == 'unfolding'):
                lna = ""
                context = ""
                param = ""
                unfolding(lna, context, param)
            # -----dcr2cpn----------
            elif (toolname == 'dcr2cpn'):
                xml = ""
                dcr2cpn(xml)
            elif (toolname == 'helena'):
                runHelena()
            elif (toolname == 'ltl'):
                ltlToPro()

            return Response({"message": "Run Tool Successfully!"}, status=status.HTTP_200_OK)
    except:
        return Response({"message": "Get Data Fail!!"}, status=status.HTTP_400_BAD_REQUEST)
