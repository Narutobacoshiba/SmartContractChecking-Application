from django.db import models

# Create your models here.

# class SmartConstract(models.Model):
#     id = models.CharField(max_length=300,primary_key=True)
#     name = models.CharField(max_length=300)
#     date_modified = models.DateTimeField()
#     type = models.CharField(max_length=300)


class Account(models.Model):
    username = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    password = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    role = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'account'

class Smartcontract(models.Model):
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    type = models.CharField(max_length=50, db_collation='utf8_general_ci', blank=True, null=True)
    content = models.TextField(blank=True, null=True)
    description = models.TextField(blank=True, null=True)
    aid = models.ForeignKey(Account, models.DO_NOTHING, db_column='aid')

    class Meta:
        managed = False
        db_table = 'smartcontract'

