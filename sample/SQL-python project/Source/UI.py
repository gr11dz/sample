from os import system
from Link import *
from datetime import date

class UserInterface:
    def __init__(self):
        pass
    
    #region Private Functions
    #region Validating Input
    
    def __intInput(self, str : str):
        while True:
            try:
                return int(input("Enter your {} : ".format(str)))
            except (ValueError):
                print("Invalid input...")
                system("pause & cls")
                
    def __validate_FullName(self, Obj : User) -> bool:
        if Obj.age < 1 :
            return False
        if date.today().year - Obj.birthYear != Obj.age:
            return False
        
        newObj = Crud()
        if newObj.validateName(Obj.fName + Obj.lName): 
            del newObj
            return True
        return False
    
    def __validate_ID(self, ID : int) -> bool:
        newObj = Crud()
        
        for iter in newObj.readID():
            if iter == ID:
                return True
        return False
    #endregion   
     
    #Following function is used for both Updating and Creating.
    def __create(self , update = '' , ID = 0):
        if update:
            print("{0}CURRENT VALUE{0}\n".format('-'*44))
            print("{:<10}{:<20}{:<30}{:<10}{:<20}{:<4}\n".format("ID", "FIRST NAME", "LAST NAME", "AGE" , "BIRTH PLACE" , "BIRTH YEAR"),end='-'*101+'\n')
            crudObj = Crud()
            crudObj.readRecord(ID)
            print('-'*101)
            del crudObj
            
        newObj = User()
        newObj.fName = input("Enter your {} First Name : ".format(update))
        newObj.lName = input("Enter your {} Last Name : ".format(update))
        newObj.age = self.__intInput("{} Age".format(update))
        newObj.birthPlace = input("Enter your {} Birth Place : ".format(update))
        newObj.birthYear = self.__intInput("{} Birth Year".format(update))
        system("cls")

        if self.__validate_FullName(newObj) :
            crudObj = Crud()
            if update:
                crudObj.updatebyID(newObj, ID)
            else:
                crudObj.create(newObj)
                
            del crudObj
        else:
            print("Invalid Values..")
    
    def __readAll(self):
        print("{0}RECORDS{0}\n".format('-'*47))
        print("{:<10}{:<20}{:<30}{:<10}{:<20}{:<4}\n".format("ID", "FIRST NAME", "LAST NAME", "AGE" , "BIRTH PLACE" , "BIRTH YEAR"),end='-'*101)
        
        newObj = Crud()
        newObj.readAll()
        del newObj
        
        print('-'*101)
    
    def __UpdatebyID(self):
        self.__readAll()
        ID= self.__intInput("Desired ID to Update")
        system("cls")
        
        if not(self.__validate_ID(ID)):
            print("Invalid ID...")
            return
        
        self.__create("new" , ID)
        
    def __deleteID(self):
        self.__readAll()
        ID= self.__intInput("Desired ID to Delete")
        system("cls")
        
        if not(self.__validate_ID(ID)):
            print("Invalid ID...")
            return
        
        newObj = Crud()
        newObj.deleteRecord(ID)
        
    #endregion
        
    def Menu(self):
        while True:
            system("cls")
            option = input("{0}MAIN MENU{0}\n1. Create\n2. Read All\n3. Update\n4. Delete\n5. Exit\nSelect an option : ".format('-'*20)) 
            system("cls")
            match option:
                case '1':
                    self.__create()
                case '2':
                    self.__readAll()
                case '3':
                    self.__UpdatebyID()
                case '4':
                    self.__deleteID()
                case '5':
                    return
                case _:
                    print("Invalid input...")
            system("pause")
        
if __name__ == "__main__":
    newUI = UserInterface()
    newUI.Menu()