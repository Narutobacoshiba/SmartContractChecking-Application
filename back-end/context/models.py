from django.db import models


class CPNContext(models.Model):
    ccid = models.CharField(
        max_length=64, db_collation='utf8_general_ci', primary_key=True)
    aid = models.CharField(max_length=64,blank=True, null=True)
    name = models.CharField(max_length=200,blank=True, null=True)
    content = models.TextField(blank=True, null=True)
    context_type = models.CharField(max_length=50,blank=True, null=True)
    description = models.TextField(blank=True, null=True)
    created_timestamp = models.BigIntegerField(null=True)

    class Meta:
        managed = False
        db_table = 'CPNContext'
# Create your models here.
