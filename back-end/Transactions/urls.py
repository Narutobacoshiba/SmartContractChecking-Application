from django.contrib import admin
from django.urls import path,include
from .views import Listofcheckedtransactions

urlpatterns = [
    path('admin/', admin.site.urls),
    path('listofcheckedtransactions/',Listofcheckedtransactions.as_view()),
]