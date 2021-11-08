from django.urls import path, include
from .views import GetLTLTemplateAPIView

urlpatterns = [
    path("get-ltltemplate", GetLTLTemplateAPIView.as_view(), name="generate_cpn_model"),
]
