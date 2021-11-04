from django.db import models
from account.models import Account

class Smartcontract(models.Model):
	sid = models.AutoField(primary_key=True)
	name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	type = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	created_timestamp = models.IntegerField(null=True)
	content = models.TextField(blank=True, null=True)
	description = models.TextField(blank=True, null=True)
	aid = models.ForeignKey(Account, models.DO_NOTHING,db_column='aid')
	
	class Meta:
		managed = False
		db_table = 'SmartContract'

class Functions(models.Model):
	fid = models.AutoField(primary_key=True)
	name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	bodyContent = models.TextField(blank=True, null=True)
	sid = models.ForeignKey(Smartcontract, models.DO_NOTHING,db_column='sid')
	
	class Meta:
		managed = False
		db_table = 'Functions'

class GlobalVariable(models.Model):
	gid = models.AutoField(primary_key=True)
	name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	vartype = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	type = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	value = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	sid = models.ForeignKey(Smartcontract, models.DO_NOTHING,db_column='sid')
	
	class Meta:
		managed = False
		db_table = 'GlobalVariable'
		
class LocalVariable(models.Model):
	lid = models.AutoField(primary_key=True)
	name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	vartype = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	type = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	value = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	fid = models.ForeignKey(Functions, models.DO_NOTHING,db_column='fid')
	
	class Meta:
		managed = False
		db_table = 'LocalVariable'

class Argument(models.Model):
	arid = models.AutoField(primary_key=True)
	name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	vartype = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	type = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	value = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
	fid = models.ForeignKey(Functions, models.DO_NOTHING,db_column='fid')
	
	class Meta:
		managed = False
		db_table = 'Argument'
