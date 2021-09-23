from django.urls import path
from context import views
urlpatterns = [
    path('api/',views.ContextAPIView.as_view()),
    path('contextbyid',views.getCTById)
]
