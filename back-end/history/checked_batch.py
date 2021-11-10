from .serializers import SetCheckedBatchSCSerializer,SetCPNContextSerializer, SetLNAFileSerializer, SetInitialMarkingSerializer, SetBalanceSerializer,SetIMFunctionSerializer, SetIMArgumentSerializer, SetVulnerabilitySettingSerializer, SetCheckedSmartContractDetailSerializer

def saveCheckedBatchData(data):
	context = data["selected-context"]
	context_seri = SetCPNContextSerializer(data=context)
	if context_seri.is_valid():
		context_seri.save()
		
	vulnerability = data["selected-vulnerability"]
	vulnerability_seri = SetVulnerabilitySettingSerializer(data=vulnerability)
	if vulnerability_seri.is_valid():
		vulnerability_seri.save()
	
	hcpnData = data["hcpn-data"]
	hcpn_seri = SetLNAFileSerializer(data=hcpnData)
	if hcpn_seri.is_valid():
		hcpn_seri.save()
		
	checkedBatch = data["checked-batch"]
	checkedbatch_seri = SetCheckedBatchSCSerializer(data=checkedBatch)
	if checkedbatch_seri.is_valid():
		checkedbatch_seri.save()
	
	initialMarking = data["initial-marking"]
	
	im = initialMarking["IM"]
	initialmarking_seri = SetInitialMarkingSerializer(data=im)
	if initialmarking_seri.is_valid():
		initialmarking_seri.save()
	
	balance = initialMarking["balance"]
	balance_seri = SetBalanceSerializer(data=balance)
	if balance_seri.is_valid():
		balance_seri.save()
	
	imfuncs = initialMarking["IMFunc"]
	for imfunc in imfuncs:
		imfunc_seri = SetIMFunctionSerializer(data=imfunc)
		if imfunc_seri.is_valid():
			imfunc_seri.save()
	
	imargs = initialMarking["IMArg"]
	for imarg in imargs:
		imarg_seri = SetIMArgumentSerializer(data=imarg)
		if imarg_seri.is_valid():
			imarg_seri.save()
	
	selectedScs = data["selected-smartcontract"]
	for selectedSc in selectedScs:
		selectedsc_seri = SetCheckedSmartContractDetailSerializer(data=selectedSc)
		if selectedsc_seri.is_valid():
			selectedsc_seri.save()
