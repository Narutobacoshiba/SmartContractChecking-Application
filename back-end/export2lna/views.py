from django.shortcuts import render
from django.http import HttpResponse
import os
import subprocess
from .models import GetModel
from .forms import GetForms
from pathlib import Path
import re
import json
# Create your views here.

def GetInfor(request):
	Gf = GetForms
	return render(request, 'export2lna/input.html',{'Gf' : Gf})

def submitInfor(request):
	form = GetForms(request.POST)
	if form.is_valid():
		name1 = form.cleaned_data['name']
		path1 = form.cleaned_data['path']
		para1 = form.cleaned_data['para'] 
		a1 = processtool(name1,path1,para1)
		form.instance.out = a1
		form.save()
		return render(request, 'export2lna/output.html', {'a1' : a1} )
	else:
		return HttpResponse('false')


def processtool(name,path,para):
	command = "g++ -o "+ name +" "+ name + ".cpp"
	#cd1 = ["cd", path]
	#pro1 = subprocess.run(cd1, cwd= path, shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
	#print("-------------------------------")
	pro2 = subprocess.run(command, cwd= path,shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
	pro3 = subprocess.run(para, cwd= path,shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
	
	print("-------------------------------")

	helena = "helena "+"test.lna"
	#helena = "helena /home/thien/Downloads/SmartContractChecking-Application-hadt/tools/dcr2cpn/test.lna"
	pro4 = subprocess.run(helena, cwd= path,shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
	output = str(pro4.stdout.decode("cp932"))	
	start = output.find("Helena report")
	report = output[start:]
	return report
	

