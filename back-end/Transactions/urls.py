from django.contrib import admin
from django.urls import path,include
from .views import Listofcheckedtransactions,Checkreentrancydetail

urlpatterns = [
    path('admin/', admin.site.urls),
    path('listofcheckedtransactions/',Listofcheckedtransactions.as_view()),
    path('checkreentrancydetail/',Checkreentrancydetail.as_view()),
]