from django.db import models

# Create your models here.

class Contexttype(models.Model):
    ctid = models.AutoField(primary_key=True)
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    description = models.TextField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'contexttype'

class Context(models.Model):
    cid = models.AutoField(primary_key=True)
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    content = models.TextField(blank=True, null=True)
    description = models.TextField(blank=True, null=True)
    ctid = models.ForeignKey(Contexttype, models.DO_NOTHING, db_column='ctid')

    class Meta:
        managed = False
        db_table = 'cpncontext'