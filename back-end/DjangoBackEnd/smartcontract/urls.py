from django.contrib import admin
from django.urls import path
from .views import SmartConstractAPIView

urlpatterns = [
    path('api/',SmartConstractAPIView.as_view())
]
