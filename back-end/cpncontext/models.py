from django.db import models

# Create your models here.

class cpncontext(models.Model):
    cid = models.IntegerField(primary_key=True)
    name = models.CharField(max_length=200)
    content = models.CharField(max_length=200)
    description= models.CharField(max_length=200)
    ctid= models.IntegerField(max_length=200)
    name1 = models.CharField(max_length=200)

    
 

    