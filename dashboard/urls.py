# dashboard/urls.py
from django.urls import path
from . import views

urlpatterns = [
    path("", views.index, name="dashboard_index"),
    path("api/nodemcu/", views.nodemcu_proxy, name="nodemcu_proxy"),
]
