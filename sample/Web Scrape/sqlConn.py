from TableClasses import Personal as prs, Scrapped as scr
from Table import *
import os

DELETE_FAIL = 102

class Crud():
    
    __instance = None
    
    @staticmethod
    def getInstance():
        if Crud.__instance == None:
            Crud()
        
        return Crud.__instance
    
    #region Constructer and Deconstructer
    def __init__(self):
        Crud.__instance = self
        if not database.get_tables():
            createTables()
    
    def __del__(self):
        database.close()
    
    #endregion
    #region Validation
    
    def validateName(self , Fullname : str) -> bool:
        RECORDS = Personal.select()
        
        for iter in RECORDS:
            if iter.prs_username == Fullname:
                return False
        return True

    #endregion
    #region Creation

    def createPerson(self , Obj : prs):
        query = Personal.insert(prs_username= Obj.username,
                                prs_password= Obj.password,
                                prs_age= Obj.age,)
        query.execute()
    
    def createScrapped(self, Obj: scr):
        query = Scrapped.insert(prs_ID = Obj.prsID,
                                sc_text = Obj.scrapped)
        query.execute()
    
    #endregion
    #region Reading

    def readIDPersonal(self) -> list:
        RECORDS = Personal.select()
        IDlist = list()
        
        for iter in RECORDS:
            IDlist.append(iter.id)
        return IDlist
            
    #endregion
    #region Update

    def updatebyID(self , Obj : prs , ID : int):
        query = Personal.update(prs_username= Obj.username,
                                prs_password= Obj.password,
                                prs_age= Obj.age,
                                ).where(Personal.id == ID)
        query.execute()
    
    #endregion
    #region Deleting
    
    def deleteRecord(self, ID : int):
        try:
            Personal.delete_by_id(ID)
        except(...):
            os.system("color 04")
            print("DELETE FAILED")
            return DELETE_FAIL
    
    #endregion
    #region Searching
    
    def searchID(self, username: str) -> int:
        RECORD = Personal.select()
        for iter in RECORD:
            if iter.prs_username == username:
                return iter.id
        return None
    
    def searchPass(self, username: str) -> str:
        RECORD = Personal.select()
        for iter in RECORD:
            if iter.prs_username == username:
                return iter.prs_password
        return None
    #endregion
        