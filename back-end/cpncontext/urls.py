from django.urls import path
from .import views
from .views import cpncontextAPIView

urlpatterns = [
    path('api/', views.cpncontextAPIView.as_view()),
    # path('ltlbyid',views.getLTLById)
]