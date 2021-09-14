from .import views
from django.urls import path, include

app_name ='export2lna'
urlpatterns = [
    path('input/',views.GetInfor, name ='input'),
    path('output/', views.submitInfor, name = 'output'),
]