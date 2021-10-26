from django.db import models
from django.db.models import fields
from rest_framework import serializers
from .models import cpncontext

class cpncontextSerializer(serializers.ModelSerializer):
    class Meta:
        model = cpncontext
        # fields = ['name', 'description', ]
        fields = '__all__'
