from django.db import models

# Create your models here.

class GetModel(models.Model):
	name = models.CharField(max_length = 355, null = True)
	para = models.CharField(max_length = 355, null = True)
	path = models.CharField(max_length = 355, null = True)
	lna = models.FileField(null = True)
	out = models.TextField(null = True)

	def __str__(self):
		return self.name 	