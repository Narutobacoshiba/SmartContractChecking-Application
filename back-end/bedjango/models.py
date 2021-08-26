from django.db import models
class Newuser(models.Model):
    Username = models.CharField(max_length=150)
    Password = models.CharField(max_length=150)
    Realname = models.CharField(max_length=150)
    Role = models.CharField(max_length=150)

class SmartContract(models.Model):
    name = models.CharField(max_length=150)
    date_modified = models.CharField(max_length=150)
    type = models.CharField(max_length=150)