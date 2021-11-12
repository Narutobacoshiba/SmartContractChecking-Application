from rest_framework import status
from rest_framework.views import APIView
from rest_framework.response import Response
from mainfolder.authentication import JSONWebTokenAuthentication
from .checked_batch import saveCheckedBatchData
from .models import CheckedBatchSC, VulnerabilitySetting, CPNContext, CheckedSmartContractDetail, LNAFile, InitialMarking, Balance, IMFunction, IMArgument
from smartcontract.models import Smartcontract

from .functionals import generateID
# Create your views here.

class SaveCheckedBatchAPIView(APIView):
	authentication_classes  = [JSONWebTokenAuthentication]
	def post(self, request):
		data = request.data
		user = request.user
		
		try:
			saveCheckedBatchData(data)
			return Response("Success!",status=status.HTTP_200_OK)
		except:
			return Response("Error!",status=status.HTTP_500_INTERNAL_SERVER_ERROR)

class GetCheckedBatchAPIView(APIView):
	authentication_classes  = [JSONWebTokenAuthentication]
	def get(self, request):
		user = request.user
		
		try:
			checked_batch = user.checkedbatchsc_set.all()
			contact = user.contact_set.first()
			response = []
			for cb in checked_batch:
				response.append({"id":cb.cbsid,"checkedDate":cb.checkedDate,"noSC":cb.noSC,
						  "checker":contact.firstname})				
			return Response(response,status=status.HTTP_200_OK)
		except:
			return Response("Error!",status=status.HTTP_500_INTERNAL_SERVER_ERROR)
	
	def post(self, request):
		data = request.data
		if "cbsid" in data:
			cbsid = data["cbsid"]
			ret = {"selected-sc":[],"selected-context":{},"selected-vulnerability":{},"initial-marking":{},"hcpn":{},"checking-result":""}
			try:
				checkedbatch = CheckedBatchSC.objects.get(cbsid=cbsid)
				ret["checking-result"] = checkedbatch.result
			except CheckedBatchSC.DoesNotExist:
				return Response("Request parameters error !!!",status=status.HTTP_400_BAD_REQUEST)
			
			try:
				listsc = checkedbatch.checkedsmartcontractdetail_set.all()
				for sc in listsc:
					try:
						smarcontract = Smartcontract.objects.get(sid=sc.sid)
						ret["selected-sc"].append({"id":smarcontract.sid,"name":smarcontract.name,
						                           "description":smarcontract.description,"type":smarcontract.type,
						                           "date_modified":smarcontract.created_timestamp})
					except:
						pass
				
				#contenxt
				try:	
					context = CPNContext.objects.get(ccid=checkedbatch.ccid)
					ret["selected-context"] = {"ccid":context.ccid,"name":context.name,"context_type":context.context_type,
						                   "content":context.content,"description":context.description}
				except:
					pass
					
				#vunerability	                           
				try:
					vulnerability = VulnerabilitySetting.objects.get(vusid=checkedbatch.vusid)
					ret["selected-vulnerability"] = {"type":vulnerability.type,"subtype":vulnerability.subtype,
						                         "id":vulnerability.formula_id,"name":vulnerability.formula_name,
						                         "description":vulnerability.formula_description,"content":vulnerability.formula_content}
				except:
					pass
				            
				#initial marking
				try:                     
					initialM = InitialMarking.objects.get(imid=checkedbatch.imid)
					ret["initial-marking"]["NumberOfUser"] = initialM.num_user
				except:
					pass
				
				try:
					balance = initialM.balance_set.first()
					balance_set = {"type":balance.type,"fixed":balance.fixed_value,
						       "random":{"from":balance.from_value,"to":balance.to_value},"map":balance.range_value}
					ret["initial-marking"]["Balance"] = balance_set
				except:
					pass
				
				try:
					functions = initialM.imfunction_set.all()
					function_list = []
					argument_list = []
					for func in functions:
						func_set = {"id":func.imfid,"sc_name":func.sc_name,"func_name":func.func_name,
							    "from":func.sender_from,"to":func.sender_to}
						function_list.append(func_set)
						
						arguments = func.imargument_set.all()
						for arg in arguments:
							arg_set = {"name":arg.arg_name,"func_id":func.imfid,
								    "from":arg.range_from,"to":arg.range_to}
							argument_list.append(arg_set)
					ret["initial-marking"]["imfunc"] = function_list
					ret["initial-marking"]["imarg"] = argument_list
				except:
					pass	
				
				#lna file
				try:
					lnafile = LNAFile.objects.get(lnid=checkedbatch.lnid)
					lnafile_set = {"hcpn":{"name":lnafile.hcpn_name,"content":lnafile.hcpn_content},
						       "prop":{"name":lnafile.prop_name,"content":lnafile.prop_content}}
					ret["hcpn"] = lnafile_set
				except:
					pass
				
				return Response(ret,status=status.HTTP_200_OK)
			except:
				return Response("Something error !!!",status=status.HTTP_500_INTERNAL_SERVER_ERROR)
		else:
			return Response("Request parameters error !!!",status=status.HTTP_400_BAD_REQUEST)
