from django import forms
from .models import GetModel


class GetForms(forms.ModelForm):
	class Meta:
		model = GetModel
		fields = ['name','para','path']
		