from django.db import models

from account.models import Account

class CheckedBatchSC(models.Model):
	cbsid = models.CharField(max_length=64, db_collation='utf8_general_ci', primary_key=True)
	lnid = models.CharField(max_length=64, db_collation='utf8_general_ci', null=True, blank=True)
	vusid = models.CharField(max_length=64, db_collation='utf8_general_ci', null=True, blank=True)
	ccid = models.CharField(max_length=64, db_collation='utf8_general_ci', null=True, blank=True)
	imid = models.CharField(max_length=64, db_collation='utf8_general_ci', null=True, blank=True)
	noSC = models.IntegerField(null=True)
	checkedDate = models.BigIntegerField(null=True)
	status = models.BooleanField(null=True)
	result = models.TextField(blank=True, null=True)
	
	aid = models.ForeignKey(Account, models.DO_NOTHING,db_column='aid')
	
	class Meta:
		managed = False
		db_table = 'CheckedBatchSC'
		
class VulnerabilitySetting(models.Model):
	vusid = models.CharField(max_length=64, db_collation='utf8_general_ci', primary_key=True)
	type = models.CharField(max_length=50, db_collation='utf8_general_ci', null=True, blank=True)
	subtype = models.CharField(max_length=50, db_collation='utf8_general_ci', null=True, blank=True)
	formula_id = models.CharField(max_length=64, db_collation='utf8_general_ci', null=True, blank=True)
	formula_name = models.CharField(max_length=200, db_collation='utf8_general_ci', null=True, blank=True)
	formula_description = models.TextField(blank=True, null=True)
	formula_content = models.TextField(blank=True, null=True)
	
	class Meta:
		managed = False
		db_table = 'VulnerabilitySetting'
		
class CPNContext(models.Model):
	ccid = models.CharField(max_length=64, db_collation='utf8_general_ci', primary_key=True)
	aid = models.ForeignKey(Account, models.DO_NOTHING,db_column='aid')
	name = models.CharField(max_length=200, db_collation='utf8_general_ci', null=True, blank=True)
	content = models.TextField(blank=True, null=True)
	context_type = models.CharField(max_length=50, db_collation='utf8_general_ci', null=True, blank=True)
	description = models.TextField(blank=True, null=True)
	
	class Meta:
		managed = False
		db_table = 'CPNContext'

class CheckedSmartContractDetail(models.Model):
	cscid = models.AutoField(verbose_name='CSCID',serialize=False,auto_created=True,primary_key=True)
	sid = models.CharField(max_length=64, db_collation='utf8_general_ci', null=True, blank=True)
	cbsid = models.ForeignKey(CheckedBatchSC, models.DO_NOTHING,db_column='cbsid')
	
	class Meta:
		managed = False
		db_table = 'CheckedSmartContractDetail'

class LNAFile(models.Model):
	lnid = models.CharField(max_length=64, db_collation='utf8_general_ci', primary_key=True)
	hcpn_name = models.CharField(max_length=200, db_collation='utf8_general_ci', null=True, blank=True)
	hcpn_content = models.TextField(blank=True, null=True)
	prop_name = models.CharField(max_length=200, db_collation='utf8_general_ci', null=True, blank=True)
	prop_content = models.TextField(blank=True, null=True)
	class Meta:
		managed = False
		db_table = 'LNAFile'
		
class InitialMarking(models.Model):
	imid = models.CharField(max_length=64, db_collation='utf8_general_ci', primary_key=True)
	num_user = models.IntegerField(null=True)
	IM_type = models.CharField(max_length=50, db_collation='utf8_general_ci', null=True, blank=True)

	class Meta:
		managed = False
		db_table = 'InitialMarking'

class Balance(models.Model):
	blid = models.AutoField(verbose_name='BLID',serialize=False,auto_created=True,primary_key=True)
	type = models.CharField(max_length=50, db_collation='utf8_general_ci', null=True, blank=True)
	from_value = models.IntegerField(null=True)
	to_value = models.IntegerField(null=True)
	fixed_value = models.IntegerField(null=True)
	range_value = models.CharField(max_length=1000, db_collation='utf8_general_ci', null=True, blank=True)
	imid = models.ForeignKey(InitialMarking, models.DO_NOTHING,db_column='imid')

	class Meta:
		managed = False
		db_table = 'Balance'

class IMFunction(models.Model):
	imfid = models.CharField(max_length=64, db_collation='utf8_general_ci', primary_key=True)
	sc_name = models.CharField(max_length=200, db_collation='utf8_general_ci', null=True, blank=True)
	func_name = models.CharField(max_length=200, db_collation='utf8_general_ci', null=True, blank=True)
	sender_from = models.IntegerField(null=True)
	sender_to = models.IntegerField(null=True)
	imid = models.ForeignKey(InitialMarking, models.DO_NOTHING,db_column='imid') 

	class Meta:
		managed = False
		db_table = 'IMFunction'

class IMArgument(models.Model):
	imaid = models.AutoField(verbose_name='IMAID',serialize=False,auto_created=True,primary_key=True)
	arg_name = models.CharField(max_length=200, db_collation='utf8_general_ci', null=True, blank=True)
	range_from = models.IntegerField(null=True)
	range_to = models.IntegerField(null=True)
	imfid = models.ForeignKey(IMFunction, models.DO_NOTHING,db_column='imfid') 
	
	class Meta:
		managed = False
		db_table = 'IMArgument'
