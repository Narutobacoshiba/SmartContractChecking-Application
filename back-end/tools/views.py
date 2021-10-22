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
            toolname = data["toolname"]
            print("toolname: ", toolname)

            # -----unfolding--------
            if (toolname == 'unfolding'):
                xml = ""
                ltlJson = ""
                unfolding(xml, ltlJson)
            # -----dcr2cpn----------
            elif (toolname == 'dcr2cpn'):
                xml = ""
                dcr2cpn(xml)
            elif (toolname == 'ltl'):
                ltlToPro()
            elif (toolname == 'helena'):
                result = runHelena()
                return Response({"message": result}, status=status.HTTP_200_OK)
            return Response({"message": "Run Tool Successfully"}, status=status.HTTP_200_OK)
    except:
        return Response({"message": "Run Tool Fail!!"}, status=status.HTTP_400_BAD_REQUEST)
