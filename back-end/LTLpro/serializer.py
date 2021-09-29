from django.db import models
from django.db.models import fields
from rest_framework import serializers
from .models import LTLpro

class LTLproSerializer(serializers.ModelSerializer):
    class Meta:
        model = LTLpro
        fields = ['id', 'name', 'fomular', 'description','type','tpid']
