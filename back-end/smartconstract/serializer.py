from django.db import models
from django.db.models import fields
from rest_framework import serializers
from .models import Smartcontract


class GetSmartConstractSerializer(serializers.ModelSerializer):
    class Meta:
        model = Smartcontract
        fields = '__all__'
        # fields = ['id','name']
