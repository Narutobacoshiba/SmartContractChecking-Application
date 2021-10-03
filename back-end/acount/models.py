from django.db import models
from django.contrib.auth.models import AbstractBaseUser,  UserManager
from rest_framework_simplejwt.tokens import RefreshToken
# Create your models here.
class User(AbstractBaseUser):
    username = models.CharField(max_length=250, unique=True)
    password = models.CharField(max_length=250, unique=True)
    role = models.CharField(max_length=10)

    USERNAME_FIELD = 'username'
    REQUIRED_FIELDS = []

    objects = UserManager()
    class Meta:
        db_table = "account"

    def __str__(self):
        return self.username

    def tokens(self):
        refresh = RefreshToken.for_user(self)
        return {
            'refresh': str(refresh),
            'access': str(refresh.access_token)
        }



class Contact(models.Model):
    firstname = models.CharField(max_length=50)
    lastname = models.CharField(max_length=50)
    email = models.EmailField(max_length=50)
    phone = models.CharField(max_length=50)
    birthdate = models.DateTimeField()
    avartar = models.ImageField(upload_to='img')
    address = models.CharField(max_length=150)
    aid = models.ForeignKey('User', on_delete=models.CASCADE)

    def __str__(self):
        return self.id

    class Meta:
        db_table = "contact"

