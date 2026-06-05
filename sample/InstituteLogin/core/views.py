from django.shortcuts import render, redirect
from django.views import View
from django.http import HttpResponse
from django.contrib import messages


from core.manager import Dispatcher

class Login(View):
    def get(self, request):
        return render(request, "login.html")
    
    def post(self, request):
        data = request.POST

        service = Dispatcher().get("user")
        result = service.validate_user(data)

        if result is None:
            messages.error(request, "کاربر وجود ندارد")
            return render(request, "login.html")
        elif result is False:
            messages.error(request, "نام کاربری یا رمز ورود نادرست است")
            return render(request, "login.html")
        else:
            messages.success(request, "ورود با موفقیت انجام شد")
            return redirect("login")
            
    
class Signup(View):
    def get(self, request):
        return render(request, "signup.html")
    
    def post(self, request):
        data = request.POST

        if data["password"] != data["password_repeat"]:
            messages.error(request, "رمز عبور با تکرار رمز عبور مطابقت ندارد")
            return render(request, "signup.html")
        elif data["rules"] != "on":
            messages.error(request, "قوانین و مقررات باید پذیرفته شود")
            return render(request, "signup.html")
        
        result = Dispatcher().get("user").create(data)
        if result == 100:
            messages.error(request, "نام کاربری تکراری است")
            return render(request, "signup.html")
        elif result == 200:
            messages.success(request, "کاربر با موفقیت ثبت نام شد")
            return redirect("login")
        

        