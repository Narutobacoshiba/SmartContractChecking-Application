from django.db import models

# Create your models here.
class  ltltemplate(models.Model):
    lteid= models.IntegerField(primary_key=True)
    name= models.CharField(max_length=200)
    formula=models.CharField(max_length=200)
    description= models.CharField(max_length=200)
    ltyid = models.IntegerField (null= False)

    class Meta:
        db_table = 'ltltemplate'