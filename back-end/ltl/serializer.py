from django.db import models
from django.db.models import fields
from rest_framework import serializers
from .models import LTL
class LTLSerializer(serializers.ModelSerializer):
    class Meta:
        model = LTL
        fields = '__all__'