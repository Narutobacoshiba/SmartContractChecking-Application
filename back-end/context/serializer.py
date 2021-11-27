from django.db import models
from django.db.models import fields
from rest_framework import serializers
from .models import CPNContext
class ContextSerializer(serializers.ModelSerializer):
    class Meta:
        model = CPNContext
        fields = '__all__'