from peewee import *
import os

database = SqliteDatabase("DataBase/Users.db")
  
class Personal(Model):
   
    prs_fName = TextField(constraints=[SQL("constraint UN__Personal_fName unique not null")])
    prs_lName = TextField(constraints=[SQL("constraint UN__Personal_lName unique not null")])
    prs_age = SmallIntegerField(constraints=[SQL("constraint CH__Personal_age check(prs_age > 0)")])
    prs_birthPlace = TextField(constraints=[SQL("not null")])
    prs_birthYear = IntegerField(constraints=[SQL("not null")])
    
    class Meta:
        database = database
        db_table = "Personal"

def create_Personal():
    try:
        database.create_tables([Personal])
    except(...):
        os.system("color 04")
        print("TABLE CREATION FAIL")
        os._exit(os.EX_OK)
        