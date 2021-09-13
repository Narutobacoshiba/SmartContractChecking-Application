from rest_framework import fields
from rest_framework.serializers import ModelSerializer

from .models import SmartContract


class SmartContractSerializer(ModelSerializer):
    class Meta:
        model = SmartContract
        fields = ['id', 'name', 'type', 'description']
