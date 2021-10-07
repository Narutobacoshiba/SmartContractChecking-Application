from MySQLdb._mysql import result
from rest_framework.views import APIView
from rest_framework.response import Response

from rest_framework import status
from .serializers import SerializerCheckedbatchsc
from .models import Checkedbatchsc
from django.db import connection

# Create your views here.


class Listofcheckedtransactions(APIView):
    def get(self, request):
        try:
            if request.method == 'GET':
                transaction = Checkedbatchsc.objects.all()
                serializer = SerializerCheckedbatchsc(transaction, many=True)
                return Response(serializer.data, status=status.HTTP_200_OK)
        except:
            return Response({"message": "Get Data Fail!!"}, status=status.HTTP_400_BAD_REQUEST)

class Checkreentrancydetail(APIView):
    def get(self,request):
        try:
            if request.method == 'GET':
                sql = '''select sc.name as sc,ct.name as ct ,lt.name as lt,cscd.status,cscd.result from checkedbatchsc cb join checkedsmartcontractdetail cscd 
                        on cb.bid = cscd.bid
                        join smartcontract sc on sc.sid = cscd.sid
                        join cpncontext ct on ct.cid = cscd.cid
                        join ltltemplate lt on lt.lteid = cscd.lteid 
                        where cb.bid = %s'''
            cursor = connection.cursor()
            try:
                cursor.execute(sql,[request.GET['id']] )
                data = cursor.fetchall()
                return Response(data, status=status.HTTP_200_OK)
            except Exception as e:
                cursor.close
        except:
            return Response({"message": "Get Data Fail!!"}, status=status.HTTP_400_BAD_REQUEST)
