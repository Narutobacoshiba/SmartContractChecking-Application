# Generated by Django 3.2.7 on 2021-09-28 14:34

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('acount', '0006_alter_user_table'),
    ]

    operations = [
        migrations.AlterModelTable(
            name='user',
            table='account',
        ),
    ]
