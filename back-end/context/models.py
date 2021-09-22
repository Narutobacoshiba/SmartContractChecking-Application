from django.db import models

# Create your models here.

class Context(models.Model):
#    id = models.AutoField(primary_key=True)
    name = models.CharField(max_length=300)
    context = models.CharField(max_length=1000)
    description= models.CharField(max_length=700)