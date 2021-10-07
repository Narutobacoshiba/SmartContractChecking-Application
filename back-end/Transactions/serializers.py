from rest_framework import serializers
from .models import Checkedbatchsc

class SerializerCheckedbatchsc(serializers.ModelSerializer):
    class Meta:
        model = Checkedbatchsc
        fields = '__all__'
        # fields = ['id','name']