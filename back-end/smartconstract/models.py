from django.db import models

# Create your models here.

class SmartConstract(models.Model):
  #  id = models.CharField(max_length=300,primary_key=True)
    name = models.CharField(max_length=300)
    description = models.TextField(null = True);
    date_modified = models.DateTimeField()
    type = models.CharField(max_length=300)
    aid = models.IntegerField(null = True)