from django.urls import path, include
from .views import SaveCheckedBatchAPIView, GetCheckedBatchAPIView

urlpatterns = [
    path("save-checked-batch", SaveCheckedBatchAPIView.as_view(), name="save_checked_batch"),
    path("get-checked-batch", GetCheckedBatchAPIView.as_view(), name="get_checked_batch"),
]
