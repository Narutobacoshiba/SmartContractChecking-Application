from django.db import models
from django.db.models import fields
from rest_framework import serializers
from .models import LTLTemplate

class LTLproSerializer(serializers.ModelSerializer):
    class Meta:
        model = LTLTemplate
        fields = '__all__'