from enum import unique

from django.db import models
from django.contrib.auth.models import AbstractBaseUser,  UserManager
from rest_framework_simplejwt.tokens import RefreshToken
# Create your models here.

class Account(AbstractBaseUser):
    username = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True, unique=True)
    password = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    role = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'Account'

    USERNAME_FIELD = 'username'
    REQUIRED_FIELDS = []
    objects = UserManager()

    def __str__(self):
        return self.username

    def tokens(self):
        refresh = RefreshToken.for_user(self)
        return {
            'refresh': str(refresh),
            'access': str(refresh.access_token)
        }



class Contact(models.Model):
    firstname = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    lastname = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    email = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    phone = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    birthdate = models.DateTimeField(blank=True, null=True)
    avartar = models.TextField(blank=True, null=True)
    address = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    aid = models.ForeignKey(Account, models.DO_NOTHING, db_column='aid')

    class Meta:
        managed = False
        db_table = 'Contact'

