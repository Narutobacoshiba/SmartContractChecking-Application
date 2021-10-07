from django.db import models

# Create your models here.
class LTLpro(models.Model):
    id = models.BigAutoField(primary_key=True)
    name = models.CharField(max_length=200, blank=True, null=True)
    fomular = models.CharField(max_length=300, blank=True, null=True)
    description = models.TextField(blank=True, null=True)
    type = models.CharField(max_length=100, blank=True, null=True)
    tpid = models.IntegerField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'provul'