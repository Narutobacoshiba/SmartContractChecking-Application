from rest_framework import status
from rest_framework.views import APIView
from rest_framework.response import Response
from mainfolder.authentication import JSONWebTokenAuthentication
from .functionals import saveFileToTemp, saveTempFile, unfolding, removeFolder, helenaCheck
import os
# Create your views here.

class GenerateCpnModelAPIView(APIView):
	authentication_classes  = [JSONWebTokenAuthentication]
	def post(self, request):
		data = request.data
		user = request.user
		
		smart_contract = data["selected-smartcontract"]
		context = data["selected-context"]
		vulnerability = data["selected-vulnerability"]
		initial_marking = data["initial-marking"]
		
		current_path = "./tools/temp/"
		full_path = current_path + str(user.aid) + "_generate" + "/"
		try:
			if os.path.exists(full_path):
				list_dir = os.listdir(full_path)
				if len(list_dir) > 0:
					for file_path in list_dir:
						os.remove(full_path+file_path)
			else:	
				os.makedirs(full_path)
		except OSError:
			removeFolder(full_path)
			return Response({"detail":"Generate file error!"},status=status.HTTP_500_INTERNAL_SERVER_ERROR)	
		
		success = True
		context_name = context["data"]["name"]
		if context["data"]["context_type"] == "DCR":
			context_name += ".xml"
		elif context["data"]["context_type"] == "CPN":
			context_name += ".lna"
		elif context["data"]["context_type"] == "FREE":
			context_name += ".txt"
		else:
			context_name += ".txt"
			
		success = saveFileToTemp(full_path,context_name,context["data"]["content"],dtype="text") & success
		success = saveFileToTemp(full_path,"vulnerability.json",vulnerability,dtype="json") & success
		success = saveTempFile(full_path) & success
		#saveFileToTemp(full_path,"initial_marking",initial_marking,dtype="json")
		if not success:
			removeFolder(full_path)
			return Response({"detail":"Generate file error!"},status=status.HTTP_500_INTERNAL_SERVER_ERROR)
			
		output = unfolding(full_path,"EtherGame.lna",context_name,context["data"]["context_type"],"vulnerability.json","blindAuction.ast","etherGame.json")
		
		if len(output["err"]) > 0:
			removeFolder(full_path)
			return Response({"detail":output["err"]},status=status.HTTP_500_INTERNAL_SERVER_ERROR)
		else:
			hcpn_content = ""
			prop_content = ""
			context_content = ""
			try:
				with open(output["file_path"]+output["file_name"]+".context.lna","r") as f:
					context_content = f.read()
				with open(output["file_path"]+output["file_name"]+".lna","r") as f:
					hcpn_content = f.read()
				with open(output["file_path"]+output["file_name"]+".prop.lna","r") as f:
					prop_content = f.read()
				
				removeFolder(full_path)
				return Response({"hcpn":{"name":output["file_name"]+".lna","content":hcpn_content},
				                 "prop":{"name":output["file_name"]+".prop.lna","content":prop_content},
				                 "context":{"name":context["data"]["name"],"content":context_content,"context_type":"CPN"}}
				                 ,status=status.HTTP_200_OK)	
			except:
				removeFolder(full_path)
				return Response({"detail":"Generate file error!"},status=status.HTTP_500_INTERNAL_SERVER_ERROR)	
					
		removeFolder(full_path)
		return Response("Generate success!",status=status.HTTP_200_OK)
	
	
class CheckCpnModelAPIView(APIView):
	authentication_classes  = [JSONWebTokenAuthentication]
	def post(self, request):
		data = request.data
		user = request.user
		
		hcpn_data = data["hcpn-data"]

		current_path = "./tools/temp/"
		full_path = current_path + str(user.aid) + "_checking" + "/"
		try:
			if os.path.exists(full_path):
				list_dir = os.listdir(full_path)
				if len(list_dir) > 0:
					for file_path in list_dir:
						os.remove(full_path+file_path)
			else:	
				os.makedirs(full_path)
		except OSError:
			removeFolder(full_path)
			return Response({"detail":"Check file error!"},status=status.HTTP_500_INTERNAL_SERVER_ERROR)
			
		success = True
		success = saveFileToTemp(full_path,hcpn_data["hcpn"]["name"],hcpn_data["hcpn"]["content"],dtype="text") & success
		success = saveFileToTemp(full_path,hcpn_data["prop"]["name"],hcpn_data["prop"]["content"],dtype="text") & success
		
		if not success:
			removeFolder(full_path)
			return Response({"detail":"Check file error!"},status=status.HTTP_500_INTERNAL_SERVER_ERROR)
		
		output = helenaCheck(full_path,hcpn_data["hcpn"]["name"],hcpn_data["prop"]["name"])
		
		start = output["output"].find("Helena report")
		if start > 0:
			result = output["output"][start:]
			removeFolder(full_path)
			return Response(result,status=status.HTTP_200_OK)
		else:
			removeFolder(full_path)
			return Response({"detail":output["output"]},status=status.HTTP_500_INTERNAL_SERVER_ERROR)
			
		removeFolder(full_path)
		return Response("Checking success!",status=status.HTTP_200_OK)
