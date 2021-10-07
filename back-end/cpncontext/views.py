from django.core.exceptions import ValidationError
from rest_framework.serializers import Serializer
from rest_framework import exceptions
from .serializer import cpncontextSerializer
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from .models import cpncontext
from rest_framework.decorators import api_view
from django.shortcuts import render
# Create your views here.

class cpncontextAPIView(APIView):

	    #----------GET ALL LTL properties-----------
	def get(self,request):
		try:
			if request.method == 'GET':
				LTLproDB = cpncontext.objects.raw('select cid, cpncontext.name as name, content, cpncontext.description, cpncontext.ctid, contexttype.name as name1 from cpncontext  join  contexttype on cpncontext.ctid= contexttype.ctid')	
				serializeLTLpro = cpncontextSerializer(LTLproDB, many=True)
				return Response(serializeLTLpro.data, status=status.HTTP_202_ACCEPTED)
				# return render(request, 'ContextOfSmartContract.vue', {'cpncontext': serializeLTLpro}, status= status.HTTP_202_ACCEPTED)
				return 
		except Exception as e: 
			return Response({"message": "Get Data Fail!!"}, status=status.HTTP_400_BAD_REQUEST)