from .import views
from django.urls import path, include

app_name ='export2lna'
urlpatterns = [
    path('dcr2cpn/', views.requestdcrToCpn, name = 'dcrToCpn'),
    path('unfolding/', views.requestunfolding, name = 'unfoldingTool'),
    path('ltlpro/', views.requestltlToPro, name = 'ltlToPro'),
    path('helena/', views.requestrunHelena, name = 'runHelena'),
]