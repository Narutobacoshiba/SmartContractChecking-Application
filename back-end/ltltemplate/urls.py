from django.urls import path
from .import views
from .views import ltltemplateAPIView

urlpatterns = [
    path('api/',views.ltltemplateAPIView.as_view()),
    # path('ltlbyid',views.getLTLById)
]