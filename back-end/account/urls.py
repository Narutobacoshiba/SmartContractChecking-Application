from django.urls import path, include
from .views import LoginAPIView, CurrentAPIView, RefreshTokenAPIView
urlpatterns = [
    path("login", LoginAPIView.as_view(), name="login"),
    path("current", CurrentAPIView.as_view(), name="current"),
    path("refresh-tokens", RefreshTokenAPIView.as_view(), name="refresh"),
]
