from peewee import *
import sqlite3

database = SqliteDatabase("db/Task.db")

class Task(Model):

    tsk_name = TextField(null= False)
    tsk_progress = TextField(default="Todo")

    class Meta:
        database = database
        db_table = "Task"

def createTables() -> bool:
    database.create_tables([Task])