from django.db import models

# Create your models here.
class  LTLpro(models.Model):
	name = models.CharField(max_length=200,null = True);
	fomular = models.CharField(max_length=300,null = True);
	description = models.TextField(null = True);
	type = models.CharField(max_length=100,null = True);
	tpid = models.IntegerField(null = True);

	def __str__(self):
		return self.name;