from django.urls import path, include
from .views import GetAllAPIView, GetInforAPIView,CrudSmartContract

urlpatterns = [
    path("get_all", GetAllAPIView.as_view(), name="getall"),
    path("get_vfinfor", GetInforAPIView.as_view(), name="get_vfinfor"),
    path('crud-sc',CrudSmartContract.as_view(),name="create_sc")
]
