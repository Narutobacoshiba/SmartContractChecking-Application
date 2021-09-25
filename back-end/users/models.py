from django.db import models
from django.contrib.auth.models import AbstractUser
from datetime import datetime

# Create your models here.
class User(AbstractUser):
    username = models.CharField(max_length=250, unique=True)
    password = models.CharField(max_length=250, unique=True)
    role = models.CharField(max_length=10)



class Contact(models.Model):
    id = models.AutoField(primary_key = True)
    firstname = models.CharField(max_length=50)
    lastname = models.CharField(max_length=50)
    email = models.EmailField(max_length=50)
    phone = models.CharField(max_length=50)
    birthdate = models.DateTimeField(default=datetime.now(), blank=True)
    avartar = models.ImageField(upload_to='img')
    address = models.CharField(max_length=150)
    aid = models.ForeignKey('User', on_delete=models.CASCADE)

    def __str__(self):
        return self.id


