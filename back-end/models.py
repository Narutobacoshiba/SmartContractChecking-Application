# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey and OneToOneField has `on_delete` set to the desired behavior
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
from django.db import models


class Account(models.Model):
    aid = models.AutoField(primary_key=True)
    username = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    password = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    role = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'account'


class Argument(models.Model):
    fid = models.ForeignKey('Functions', models.DO_NOTHING, db_column='fid')
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    type = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'argument'


class Checkedbatchsc(models.Model):
    bid = models.AutoField(primary_key=True)
    aid = models.ForeignKey(Account, models.DO_NOTHING, db_column='aid')
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    checkeddate = models.DateField(db_column='checkedDate', blank=True, null=True)  # Field name made lowercase.
    description = models.TextField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'checkedbatchsc'


class Checkedsmartcontractdetail(models.Model):
    cscdid = models.AutoField(primary_key=True)
    status = models.IntegerField(blank=True, null=True)
    isltltemplate = models.IntegerField(db_column='isLTLTemplate', blank=True, null=True)  # Field name made lowercase.
    ltlformula = models.TextField(db_column='LTLFormula', blank=True, null=True)  # Field name made lowercase.
    result = models.TextField(blank=True, null=True)
    lnid = models.ForeignKey('Lnafile', models.DO_NOTHING, db_column='lnid')
    sid = models.ForeignKey('Smartcontract', models.DO_NOTHING, db_column='sid')
    lteid = models.ForeignKey('Ltltemplate', models.DO_NOTHING, db_column='lteid')
    cid = models.ForeignKey('Cpncontext', models.DO_NOTHING, db_column='cid')
    bid = models.ForeignKey(Checkedbatchsc, models.DO_NOTHING, db_column='bid')
    imid = models.ForeignKey('Initialmarking', models.DO_NOTHING, db_column='imid')

    class Meta:
        managed = False
        db_table = 'checkedsmartcontractdetail'


class Contact(models.Model):
    firstname = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    lastname = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    email = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    phone = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    birthdate = models.DateField(db_column='birthDate', blank=True, null=True)  # Field name made lowercase.
    avartar = models.TextField(blank=True, null=True)
    address = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    aid = models.ForeignKey(Account, models.DO_NOTHING, db_column='aid')

    class Meta:
        managed = False
        db_table = 'contact'


class Contexttype(models.Model):
    ctid = models.AutoField(primary_key=True)
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    description = models.TextField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'contexttype'


class Cpncontext(models.Model):
    cid = models.AutoField(primary_key=True)
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    content = models.TextField(blank=True, null=True)
    description = models.TextField(blank=True, null=True)
    ctid = models.ForeignKey(Contexttype, models.DO_NOTHING, db_column='ctid')

    class Meta:
        managed = False
        db_table = 'cpncontext'


class Functions(models.Model):
    fid = models.AutoField(primary_key=True)
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    bodycontent = models.TextField(db_column='bodyContent', blank=True, null=True)  # Field name made lowercase.
    sid = models.ForeignKey('Smartcontract', models.DO_NOTHING, db_column='sid')

    class Meta:
        managed = False
        db_table = 'functions'


class Globalvariable(models.Model):
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    vartype = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    type = models.CharField(max_length=25, db_collation='utf8_general_ci', blank=True, null=True)
    value = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    sid = models.ForeignKey('Smartcontract', models.DO_NOTHING, db_column='sid')

    class Meta:
        managed = False
        db_table = 'globalvariable'


class History(models.Model):
    hid = models.AutoField(primary_key=True)
    description = models.TextField(blank=True, null=True)
    modifieddate = models.DateField(db_column='modifiedDate', blank=True, null=True)  # Field name made lowercase.
    aid = models.ForeignKey(Account, models.DO_NOTHING, db_column='aid')

    class Meta:
        managed = False
        db_table = 'history'


class HistoryType(models.Model):
    history_name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    hid = models.ForeignKey(History, models.DO_NOTHING, db_column='hid')

    class Meta:
        managed = False
        db_table = 'history_type'


class Imtemplate(models.Model):
    imtid = models.AutoField(primary_key=True)
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    formula = models.TextField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'imtemplate'


class Initialmarking(models.Model):
    imid = models.AutoField(primary_key=True)
    numberuser = models.IntegerField(db_column='numberUser', blank=True, null=True)  # Field name made lowercase.
    balance = models.IntegerField(blank=True, null=True)
    value = models.IntegerField(blank=True, null=True)
    orther_parameter = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    imtid = models.ForeignKey(Imtemplate, models.DO_NOTHING, db_column='imtid')

    class Meta:
        managed = False
        db_table = 'initialmarking'


class Lnafile(models.Model):
    lnid = models.AutoField(primary_key=True)
    hcpnfile = models.TextField(db_column='hcpnFile', blank=True, null=True)  # Field name made lowercase.
    propfile = models.TextField(db_column='propFile', blank=True, null=True)  # Field name made lowercase.

    class Meta:
        managed = False
        db_table = 'lnafile'


class Localvariable(models.Model):
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    vartype = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    type = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    value = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    fid = models.ForeignKey(Functions, models.DO_NOTHING, db_column='fid')

    class Meta:
        managed = False
        db_table = 'localvariable'


class Ltltemplate(models.Model):
    lteid = models.AutoField(primary_key=True)
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    formula = models.TextField(blank=True, null=True)
    description = models.TextField(blank=True, null=True)
    ltyid = models.ForeignKey('Ltltype', models.DO_NOTHING, db_column='ltyid')

    class Meta:
        managed = False
        db_table = 'ltltemplate'


class Ltltype(models.Model):
    ltyid = models.AutoField(primary_key=True)
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    description = models.TextField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'ltltype'


class Smartcontract(models.Model):
    sid = models.AutoField(primary_key=True)
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    type = models.CharField(max_length=50, db_collation='utf8_general_ci', blank=True, null=True)
    content = models.TextField(blank=True, null=True)
    description = models.TextField(blank=True, null=True)
    aid = models.ForeignKey(Account, models.DO_NOTHING, db_column='aid')

    class Meta:
        managed = False
        db_table = 'smartcontract'
