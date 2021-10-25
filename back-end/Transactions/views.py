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
                sql = '''select a.aid as id ,c.firstname as firstname,c.lastname as lastname, cb.checkedDate as CheckedDate, cb.noSC as num from contact as c 
                        inner join account as a
                        on c.aid = a.aid
                        inner join checkedbatchsc as cb
                        on a.aid = cb.aid'''
            cursor = connection.cursor()
            try:
                cursor.execute(sql)
                data = cursor.fetchall()
                return Response(data, status=status.HTTP_200_OK)
            except Exception as e:
                cursor.close
        except:
            return Response({"message": "Get Data Fail!!"}, status=status.HTTP_400_BAD_REQUEST)

class Checkreentrancydetail(APIView):
    def get(self,request):
        try:
            if request.method == 'GET':
                sql = '''SELECT result FROM soliditycpn.checkedbatchsc
                        where aid = %s'''
            cursor = connection.cursor()
            try:
                cursor.execute(sql,[request.GET['id']] )
                data = cursor.fetchall()
                return Response(data, status=status.HTTP_200_OK)
            except Exception as e:
                cursor.close
        except:
            return Response({"message": "Get Data Fail!!"}, status=status.HTTP_400_BAD_REQUEST)
