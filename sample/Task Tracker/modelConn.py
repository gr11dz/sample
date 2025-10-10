from typing import overload, Union

from task import Task as tsk
from table import *

class Conn:
    __instance = None

    @staticmethod
    def getInstance():
        if Conn.__instance == None:
            Conn()
        return Conn.__instance

    def __init__(self):
        Conn.__instance = self
        try:
            if not database.get_tables():
               raise OperationalError 
        except(OperationalError, sqlite3.OperationalError):
            createTables()

    def __del__(self):
        database.close()

    def insert(self, task: tsk) -> bool:
        try:
            query = Task.insert(tsk_name = task.name)
            query.execute()
            return True
        except(...):
            return False

    def readAll(self) -> list:
        records = list()
        for rec in Task.select():
            records.append(tsk(rec.tsk_name, rec.tsk_progress))
        return records

    def read_by_progress(self, progress: str) -> list:
        records = list()
        for rec in Task.select(Task.tsk_name).where(Task.tsk_progress == progress):
            records.append(rec)
        return records

    def getID(self, name: str) -> int:
        try:
            return Task.select(id).where(Task.tsk_name == name)
        except(...):
            return 0

    def read_by_progress(self, progress: str) -> list:
        records = list()
        for rec in Task.select().where(Task.tsk_progress == progress):
            records.append(tsk(rec.tsk_name, progress= progress))

    @overload
    def update_name(self, name: str) -> bool: ...
    
    @overload
    def update_name(self, name: str, id: int) -> bool: ...

    def update_name(self, name: str, id: Union[int, None] = None) -> bool:
        try:
            if id is None:
                id = self.getID(name)
            Task.update(tsk_name = name).where(id= id)
            return True
        except(...):
            return False

    def update_progress(self, id: int, progress: str) -> bool:
        try:
            Task.update(progress= progress).where(id= id)
            return False
        except(...):
            return True
        
    def delete_by_id(self, id: int) -> bool:
        try:
            Task.delete().where(id= id)
            return True
        except(...):
            return False