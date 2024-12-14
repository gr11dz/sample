from flask import Flask, request, render_template, redirect, url_for, session, flash
from webScrap import Scrapper
import os

from sqlConn import Crud
from TableClasses import Personal, Scrapped

APP = Flask(__name__)
APP.secret_key = "really-secret!"

class WebUI:
    
    def __init__(self, debug: bool):
        try:
            APP.run(debug = debug)
        except:
            print("Internal Error")
            os._exit(os.EX_OK)
    
    @APP.route("/")
    def home():
        return render_template("home.html")
    
    @APP.route("/logout/")
    def logout():
        session.pop["username", None]
        flash("You have logged out!", "info")
        return redirect(url_for("home"))
    
    @APP.route("/loginfail/")
    def loginfail():
        flash("Invalid login!", "info")
        return redirect(url_for("home"))
    
    @APP.route("/loginsuccess/")
    def loginSuccess():
        flash("You have logged in!", "info")
        return redirect(url_for("home"))
    
    @APP.route("/login/", methods=["GET", "POST"])
    def login():
        if request.method == "POST":
            newPrs = Personal()
            newPrs.username = request.form["username"]
            newPrs.password = request.form["password"]
            
            crudO = Crud.getInstance()
            password = crudO.searchPass(newPrs.username)
            
            if password == newPrs.password:
                session["username"] = newPrs.username
                return redirect(url_for("loginSuccess"))
            
            return redirect(url_for("loginfail"))
            
        else:
            return render_template("login.html")
            
    @APP.route("/signin/", methods=["GET", "POST"])
    def signIn():
        if request.method == "POST":
            newPrs = Personal()
            newPrs.username = request.form["username"]
            newPrs.password = request.form["password"]
            newPrs.age = request.form["age"]
            
            crudO = Crud.getInstance()
            if not crudO.validateName(newPrs.username):
                return redirect(url_for("loginfail"))
            
            crudO.createPerson(newPrs)
            
            session["username"] = newPrs.username

            return redirect(url_for("loginSuccess"))
        else:
            return render_template("signin.html")

    @APP.route("/checkUser/")
    def checkUser():
        if "username" in session:
            return redirect(url_for("setUrlKey"))
        else:
            return redirect(url_for("loginfail"))
    
    @APP.route("/setUrlKey/", methods=["GET", "POST"])
    def setUrlKey():
        
        if request.method == "POST":
            session["url"] = request.form["url"]
            session["keyword"] = request.form["keyword"]
            
            return redirect(url_for("scrapp"))
        else:
            return render_template("setUrlKey.html")
        
    @APP.route("/scrapp/")
    def scrapp():
        
        newScrapp = Scrapper()
        newScrapp.url = session.get("url")
        newScrapp.subString = session.get("keyword")
        
        text = str(newScrapp.scrapp())
        
        del newScrapp
        session.pop("url", None)
        session.pop("keyword", None)
        
        newsc = Scrapped()
        crudO = Crud.getInstance()
        newsc.prsID = crudO.searchID(session["username"])
        newsc.scrapped = text
        crudO.createScrapped(newsc)
        del newsc

        return text

if __name__ == "__main__":
    newUI = WebUI(True)
    