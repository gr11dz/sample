from Table import *
from User import *
import os

class Crud:
    #region Constructer and Deconstructer
    def __init__(self):
        if database.get_tables() != "Personal":
            create_Personal()
    
    def __del__(self):
        database.close()
    #endregion
    #region Validation
    def validateName(self , Fullname : str) -> bool:
        RECORDS = Personal.select()
        RecFullname = str
        
        for iter in RECORDS:
            RecFullname = iter.prs_fName + iter.prs_lName
            if RecFullname == Fullname:
                return False
        return True
    #endregion

    def create(self , Obj : User):
        query = Personal.insert(prs_fName= Obj.fName, prs_lName= Obj.lName, prs_age= Obj.age, prs_birthPlace = Obj.birthPlace,prs_birthYear= Obj.birthYear)
        query.execute()
        
    def updatebyID(self , Obj : User , ID : int):
        query = Personal.update(prs_fName= Obj.fName, prs_lName= Obj.lName, prs_age= Obj.age, prs_birthPlace = Obj.birthPlace,prs_birthYear= Obj.birthYear).where(Personal.id == ID)
        query.execute()
    #region Reading
    
    def readAll(self):
        RECORDS = Personal.select()
        for iter in RECORDS:
            print("\n{:<10}{:<20}{:<30}{:<10}{:<20}{:<4}"
            .format(iter.id , iter.prs_fName, iter.prs_lName, iter.prs_age, iter.prs_birthPlace, iter.prs_birthYear))

    def readID(self):
        RECORDS = Personal.select()
        IDlist = list()
        
        for iter in RECORDS:
            IDlist.append(iter.id)
        return IDlist
    
    def readRecord(self , ID : int):
        RECORD = Personal.select().where(Personal.id == ID)
        for iter in RECORD:
            print("{:<10}{:<20}{:<30}{:<10}{:<20}{:<4}"
            .format(iter.id , iter.prs_fName, iter.prs_lName, iter.prs_age, iter.prs_birthPlace, iter.prs_birthYear))
    #endregion
    
    def deleteRecord(self, ID : int):
        try:
            Personal.delete_by_id(ID)
        except(...):
            os.system("color 04")
            print("DELETE FAILED")
            os._exit(os.EX_OK)