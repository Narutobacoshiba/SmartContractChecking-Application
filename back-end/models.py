# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey and OneToOneField has `on_delete` set to the desired behavior
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
from django.db import models


class Account(models.Model):
    username = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    password = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    role = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'account'


class Argument(models.Model):
    fid = models.ForeignKey('Functionss', models.DO_NOTHING, db_column='fid')
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    type = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'argument'


class Contact(models.Model):
    firstname = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    lastname = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    email = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    phone = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    birthdate = models.DateTimeField(blank=True, null=True)
    avartar = models.TextField(blank=True, null=True)
    address = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    aid = models.ForeignKey(Account, models.DO_NOTHING, db_column='aid')

    class Meta:
        managed = False
        db_table = 'contact'


class Context(models.Model):
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    context = models.TextField(blank=True, null=True)
    description = models.TextField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'context'


class Functionss(models.Model):
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    bodycontent = models.TextField(blank=True, null=True)
    scid = models.ForeignKey('Smartcontract', models.DO_NOTHING, db_column='scid')

    class Meta:
        managed = False
        db_table = 'functionss'


class Globalvariable(models.Model):
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    vartype = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    type = models.CharField(max_length=25, db_collation='utf8_general_ci', blank=True, null=True)
    value = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    scid = models.ForeignKey('Smartcontract', models.DO_NOTHING, db_column='scid')

    class Meta:
        managed = False
        db_table = 'globalvariable'


class History(models.Model):
    description = models.TextField(blank=True, null=True)
    date_modified = models.DateField(blank=True, null=True)
    scid = models.ForeignKey('Smartcontract', models.DO_NOTHING, db_column='scid')

    class Meta:
        managed = False
        db_table = 'history'


class HistoryType(models.Model):
    history_name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    htid = models.ForeignKey(History, models.DO_NOTHING, db_column='htid')

    class Meta:
        managed = False
        db_table = 'history_type'


class Localvariable(models.Model):
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    vartype = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    type = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    value = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    fid = models.ForeignKey(Functionss, models.DO_NOTHING, db_column='fid')

    class Meta:
        managed = False
        db_table = 'localvariable'


class Provul(models.Model):
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    fomular = models.TextField(blank=True, null=True)
    description = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    type = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    tpid = models.ForeignKey('Template', models.DO_NOTHING, db_column='tpid')

    class Meta:
        managed = False
        db_table = 'provul'


class ScContext(models.Model):
    scid = models.ForeignKey('Smartcontract', models.DO_NOTHING, db_column='scid')
    ctid = models.ForeignKey(Context, models.DO_NOTHING, db_column='ctid')

    class Meta:
        managed = False
        db_table = 'sc_context'
        unique_together = (('id', 'scid', 'ctid'),)


class ScProvul(models.Model):
    scid = models.ForeignKey('Smartcontract', models.DO_NOTHING, db_column='scid')
    pvid = models.ForeignKey(Provul, models.DO_NOTHING, db_column='pvid')

    class Meta:
        managed = False
        db_table = 'sc_provul'
        unique_together = (('id', 'scid', 'pvid'),)


class Smartcontract(models.Model):
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    type = models.CharField(max_length=50, db_collation='utf8_general_ci', blank=True, null=True)
    content = models.TextField(blank=True, null=True)
    description = models.TextField(blank=True, null=True)
    aid = models.ForeignKey(Account, models.DO_NOTHING, db_column='aid')

    class Meta:
        managed = False
        db_table = 'smartcontract'


class Template(models.Model):
    name = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)
    formular = models.TextField(blank=True, null=True)
    description = models.CharField(max_length=200, db_collation='utf8_general_ci', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'template'
