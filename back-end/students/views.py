from django.shortcuts import render
# from django.http import JsonResponse
from rest_framework.viewsets import ModelViewSet
from .models import SmartContract
from .serializers import SmartContractSerializer
# Create your views here.


class SmartContractViewSet(ModelViewSet):
    queryset = SmartContract.objects.all()
    serializer_class = SmartContractSerializer

