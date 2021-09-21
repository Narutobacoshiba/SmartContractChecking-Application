from django.urls import path
from ltl import views
urlpatterns = [
    path('api/',views.LTLAPIView.as_view()),
    path('ltlbyid',views.getCTById)
]
