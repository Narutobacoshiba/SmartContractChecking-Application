from django.urls import path, include
from .views import GenerateCpnModelAPIView, CheckCpnModelAPIView

urlpatterns = [
    path("generate-cpn-model", GenerateCpnModelAPIView.as_view(), name="generate_cpn_model"),
    path("check-cpn-model", CheckCpnModelAPIView.as_view(), name="check_cpn_model"),
]
