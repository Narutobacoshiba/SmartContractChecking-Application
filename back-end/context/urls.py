from django.urls import path, include
from .views import GetAllContextAPIView

urlpatterns = [
    path("get-all", GetAllContextAPIView.as_view(), name="getall"),
]
