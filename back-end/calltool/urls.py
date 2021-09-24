from .import views
from django.urls import path, include

app_name ='export2lna'
urlpatterns = [
    path('', views.submitInfor, name = 'output'),
]