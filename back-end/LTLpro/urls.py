from django.urls import path
from .import views
from .views import LTLproAPIView

urlpatterns = [
    path('api/',LTLproAPIView.as_view()),
    path('ltlbyid',views.getLTLById)
]
