from django.urls import path, include
from .views import GetAllContextAPIView,ContextAPIView

urlpatterns = [
    path("get-all", GetAllContextAPIView.as_view(), name="getall"),
    path("cpn-context-crud",ContextAPIView.as_view())
]
