from django.urls import path
from . import views

urlpatterns = [
    path("", views.Login.as_view(), name="login"),
    path("signup/", views.Signup.as_view(), name="signup"),
]