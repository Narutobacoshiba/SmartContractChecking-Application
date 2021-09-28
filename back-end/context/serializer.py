from django.db import models
from django.db.models import fields
from rest_framework import serializers
from .models import Context
class ContextSerializer(serializers.ModelSerializer):
    class Meta:
        model = Context
        fields = '__all__'