from rest_framework import status
from rest_framework.views import APIView
from rest_framework.response import Response
from mainfolder.authentication import JSONWebTokenAuthentication
from .models import LTLTemplate
# Create your views here.

class GetLTLTemplateAPIView(APIView):
	authentication_classes  = [JSONWebTokenAuthentication]
	def get(self, request):
		
		try:
			ltl_templates = LTLTemplate.objects.all()
			
			ret = []
			for temp in ltl_templates:
				temp_el = {}
				temp_el["id"] = temp.lteid
				temp_el["name"] = temp.name
				temp_el["formula"] = temp.formula
				temp_el["template_type"] = temp.template_type
				temp_el["description"] = temp.description
				ret.append(temp_el)
			return Response(ret,status=status.HTTP_200_OK)	
		except:
			return Response({"detail":"Getting ltl-template error!"},status=status.HTTP_500_INTERNAL_SERVER_ERROR)
		return 
