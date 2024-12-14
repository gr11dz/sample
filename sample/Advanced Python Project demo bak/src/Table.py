from peewee import *
import datetime

TABLE_FAIL = 101

database = SqliteDatabase("Database/ScrappDB.db")
  
class Personal(Model):
    
    prs_username = TextField(constraints=[SQL("constraint UN__Personal_fName unique not null")])
    prs_password = TextField()
    prs_age = SmallIntegerField(constraints=[SQL("constraint CH__Personal_age check(prs_age > 0)")])
    
    class Meta:
        database = database
        db_table = "Personal"

class Scrapped(Model):
    
    prs_ID = ForeignKeyField(Personal, to_field="id")
    sc_text = TextField(default="NO-TEXT")
    sc_dateAdded = DateTimeField(default=datetime.datetime.now())
    
    class Meta:
        database = database 
        db_table = "Scrapped"

def createTables():
    
    try:
        database.create_tables([Personal, Scrapped])
    except(...):
        return TABLE_FAIL
        