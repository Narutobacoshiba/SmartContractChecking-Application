from django.db import models

# Create your models here.

class Account(models.Model):
    aid = models.AutoField(primary_key=True)
    username = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    password = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    role = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'account'
        
class Checkedbatchsc(models.Model):
    bid = models.AutoField(primary_key=True)
    aid = models.ForeignKey(Account, models.DO_NOTHING, db_column='aid')
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    checkeddate = models.DateField(db_column='checkedDate', blank=True, null=True)  # Field name made lowercase.
    description = models.TextField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'checkedbatchsc'