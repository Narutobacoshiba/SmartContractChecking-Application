from django.urls import path
from tools import views

urlpatterns = [
    # path('unfolding', views.unfolding),
    # path('dcr2cpn', views.dcr2cpn),
    path('', views.calltools)
]
