from django.db import models

# Create your models here.

class Account(models.Model):
	aid = models.AutoField(verbose_name='AID',serialize=False,auto_created=True,primary_key=True)
	username = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True, unique=True)
	password = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	role = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	
	class Meta:
		managed = False
		db_table = 'Account'	
		
class Contact(models.Model):
	cid = models.AutoField(verbose_name='AID',serialize=False,auto_created=True,primary_key=True)
	firstname = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	lastname = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	email = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	aid = models.ForeignKey(Account, models.DO_NOTHING, db_column='aid')
	
	class Meta:
		managed = False
		db_table = 'Contact'
