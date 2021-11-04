from django.urls import path, include
from .views import GetAllAPIView, GetInforAPIView

urlpatterns = [
    path("get_all", GetAllAPIView.as_view(), name="getall"),
    path("get_vfinfor", GetInforAPIView.as_view(), name="get_vfinfor"),
]
