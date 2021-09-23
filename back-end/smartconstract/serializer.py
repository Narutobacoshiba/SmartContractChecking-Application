from django.db import models
from django.db.models import fields
from rest_framework import serializers
from .models import SmartConstract

class GetSmartConstractSerializer(serializers.ModelSerializer):
    class Meta:
        model = SmartConstract
        #fields = '__all__'
        fields = ['id','name','type']
