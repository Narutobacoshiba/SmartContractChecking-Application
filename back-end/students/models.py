from django.db import models


# Create your models here.
class Student(models.Model):
    name = models.CharField(max_length=140)
    course = models.CharField(max_length=140)
    rating = models.IntegerField()

    def __str__(self):
        return self.name

    class Meta:
        ordering = ['name']

class SmartContract(models.Model):
    name = models.CharField(max_length=200)
    type = models.CharField(max_length=50)
    description = models.TextField()
    def __str__(self):
        return self.name

       
# CREATE TABLE SmartContract (
# id int primary key AUTO_INCREMENT,
# name nvarchar(200),
# type nvarchar(50),
# description text,
# aid int not null references Account(id)
# )
