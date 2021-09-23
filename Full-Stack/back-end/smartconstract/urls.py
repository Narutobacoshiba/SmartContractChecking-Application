from django.contrib import admin
from django.urls import path
from .views import SmartConstractAPIView
from smartconstract import views

urlpatterns = [
    path('api/',SmartConstractAPIView.as_view()),
    path('scbyid',views.getScById)
]
