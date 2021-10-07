from django.shortcuts import render
from django.http import HttpResponse
from django.http import JsonResponse
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
	
def dcrToCpn():
    xmlFile = "test.xml"
    outFile = "outFile"
    commandDcr = "./dcr2cpn --xml ./test/"+ xmlFile +" --out_file "+ outFile
    pathDcr = r"C:\Users\Admin\Desktop\lab\(dev)SmartContractChecking-Application\tools\dcr2cpn"
    dcr2cpnpro = subprocess.run(commandDcr, cwd= pathDcr,shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)

def unfoldingTool():
    lnaFile = "EtherGame.lna"
    contextFile = "context.lna"
    param = "function1"
    outFileUnf = "outFile"
    commandUnf = "./unfolding --lna ./test/"+ lnaFile +"  --context ./test/"+ contextFile +" --param "+ param +" --out_file "+outFileUnf
    pathUnf = r"C:\Users\Admin\Desktop\lab\(dev)SmartContractChecking-Application\tools\unfolding"
    unfolding = subprocess.run(commandUnf, cwd= pathUnf,shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
	
def ltlToPro():
    lnaFileLtl = "out.lna"
    ltlFile = "test.prop"
    jsonFile = "etherGame.json"
    outltlFile = "outFile"
    ltlcommand="./ltl2prop --lna ./test/" + lnaFileLtl + " --json ./test/" + jsonFile + " --ltl ./test/"+ ltlFile + " --out_file " + outltlFile
    ltlPath = r"C:\Users\Admin\Desktop\lab\(dev)SmartContractChecking-Application\tools\ltl2prop"
    ltl2propro = subprocess.run(ltlcommand, cwd= ltlPath,shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)

def solidityToCpn():
	sodityFile = ""
	outsodility = ""
	soditycommand = ""
	soldityPath = r"C:\Users\Admin\Desktop\lab\(dev)SmartContractChecking-Application\tools\ltl2prop"
	solidity2cpnpro = subprocess.run(soditycommand, cwd= soldityPath,shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)


def runHelena():
	helenaFile="outltl.lna"
	helena = "helena -N=CHECK-prop "+helenaFile
	helenaPath = r"C:\Users\Admin\Desktop\lab\(dev)SmartContractChecking-Application\tools\ltl2prop"
	pro4 = subprocess.run(helena, cwd= helenaPath,shell=True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
	output = str(pro4.stdout.decode("cp932"))	
	start = output.find("Helena report")
	report = output[start:]
	print(report)
	return report

def requestdcrToCpn(request):
	dcrToCpn()
	resData = {
		'success': True,
	}
	return JsonResponse(resData)

def requestunfolding(request):
	unfoldingTool()
	resData = {
		'success': True,
	}
	return JsonResponse(resData)

def requestltlToPro(request):
	ltlToPro()
	resData = {
		'success': True,
	}
	return JsonResponse(resData)

def requestrunHelena(request):
	x=runHelena()
	a= "helena output \n adsfusiahfuwfhiof\ndfisahfoiehoirwei"
	resData = {
		'success': True,
		'mess': a,
		'message': x,
	}
	return JsonResponse(resData)
