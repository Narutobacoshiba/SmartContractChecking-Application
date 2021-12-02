from django.db import models

class LTLTemplate(models.Model):
	lteid = models.CharField(max_length=64, db_collation='utf8_general_ci', primary_key=True)
	name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	template_type = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	formula = models.TextField(blank=True, null=True)
	formula_text = models.TextField(blank=True, null=True)
	description = models.TextField(blank=True, null=True)

	class Meta:
		managed = False
		db_table = 'LTLTemplate'
