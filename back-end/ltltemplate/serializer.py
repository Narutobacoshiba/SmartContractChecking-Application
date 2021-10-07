from django.db import models
from django.db.models import fields
from rest_framework import serializers
from .models import ltltemplate

class ltltemplateSerializer(serializers.ModelSerializer):
    class Meta:
        model = ltltemplate
        fields = ['lteid', 'name', 'formula', 'description','ltyid']