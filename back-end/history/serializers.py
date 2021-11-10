from django.db.models import fields
from rest_framework import serializers
from .models import CheckedBatchSC, CPNContext, LNAFile, InitialMarking, Balance, IMFunction, IMArgument, VulnerabilitySetting, CheckedSmartContractDetail

class SetCheckedBatchSCSerializer(serializers.ModelSerializer):
	class Meta:
		model = CheckedBatchSC
		fields = '__all__'
		
class SetCPNContextSerializer(serializers.ModelSerializer):
	class Meta:
		model = CPNContext
		fields = '__all__'
		
class SetLNAFileSerializer(serializers.ModelSerializer):
	class Meta:
		model = LNAFile
		fields = '__all__'

class SetInitialMarkingSerializer(serializers.ModelSerializer):
	class Meta:
		model = InitialMarking
		fields = '__all__'

class SetBalanceSerializer(serializers.ModelSerializer):
	class Meta:
		model = Balance
		fields = ['type','from_value','to_value','fixed_value','range_value','imid']

class SetIMFunctionSerializer(serializers.ModelSerializer):
	class Meta:
		model = IMFunction
		fields = '__all__'

class SetIMArgumentSerializer(serializers.ModelSerializer):
	class Meta:
		model = IMArgument
		fields = ['arg_name','range_from','range_to','imfid']

class SetVulnerabilitySettingSerializer(serializers.ModelSerializer):
	class Meta:
		model = VulnerabilitySetting
		fields = '__all__'

class SetCheckedSmartContractDetailSerializer(serializers.ModelSerializer):
	class Meta:
		model = CheckedSmartContractDetail
		fields = ['sid','cbsid']
