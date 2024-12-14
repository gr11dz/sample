from Astring import *
from Game import *
from os import system
class Profile:
    def __init__(self):
        self.__users = list()
        self.__fileObj = FileHandle()
        self.__fileObj.read_All(self.__users)
    def show(self):
        print("{0}PLAYER LIST{0}\n{1:<20}{2:<30}{3:30}{4:<10}".format('-'*50 , "ID" , "USERNAME", "PASSWORD" , "SCORE"))
        for iter in self.__users:
            print("{:<20}{:<30}{:<30}{:<10}".format(iter.ID, iter.username, iter.password, iter.score))
    def addUser(self):
        system("cls")
        newUser = User.User()
        newUser.username = input("Please Enter your Username : ")
        for iter in self.__users:
            if iter.username == newUser.username:
                system("cls")
                print("This Username Already Exists!")
                del newUser
                return
        newUser.ID = self.__users[-1].ID + 1
        oAstring = Astring()
        newUser.password = oAstring.encrypt(input("Enter your Password : "))
        newUser.score = 0
        self.__users.append(newUser)
        self.__fileObj.saveAll(self.__users)
        del newUser
    def Remove_User(self):
        while True:
            print("{0}USERS{0}\n0. EXIT".format('-'*30))
            for iter in self.__users:
                print("{}. {}".format(iter.ID , iter.username))
            print(end='-'*65+'\n')
            try:
                ID = int(input("Enter the ID of the Player you'd like to Remove : "))
                if ID == 1:
                    print("YOU CANNOT REMOVE YOURSELF!!")
                    raise ValueError
                elif ID == 0:
                    return
                for iter in range(len(self.__users)):
                    if self.__users[iter].ID == ID:
                        del self.__users[iter]
                        self.__fileObj.saveAll(self.__users)
                        print("User has been Deleted!")
                        return
                raise NameError    
            except ValueError:
                print("Invalid input...")
                system("pause")
            except NameError:
                print("ID was NOT found!")
                system("pause")
            finally:
                system("cls")
    def login(self , settings : Settings) -> bool:
        system("cls")
        found = False
        username = input("Enter your Username : ")
        # matched = User.User()
        for iter in range(len(self.__users)):
            if self.__users[iter].username == username:
                found = True
                matched = iter
                break
        if not(found):
            print("User does NOT exist!")
            return
        system("cls")
        password = input("Enter your password : ")
        oAstring = Astring()
        if username == 'Admin':
            dPass = matched.password
        else:
            dPass = oAstring.decrypt(self.__users[matched])
        del oAstring
        if password == dPass :
            system("cls")
            print("{0}WELCOME {1}{0}".format('-'*30 , self.__users[matched].username))
            if username == 'Admin':
                system("pause & cls")
                return True
        newGame = Game(self.__users[matched] , settings)
        self.__users[matched] = newGame.play()
        oFile = FileHandle()
        oFile.saveAll(self.__users)
        return False
    def sortScore(self):
        for i in range(1, len(self.__users)-1):
            min = i
            for j in range(i+1 , len(self.__users)):
                if self.__users[min].score > self.__users[j].score:
                    min = j
            if min != i:
                temp = self.__users[min]
                self.__users[min] = self.__users[i]
                self.__users[i] = temp
        print("{0}PLAYER LIST{0}\n{1:<20}{2:<30}{3:30}{4:<10}".format('-'*50 , "ID" , "USERNAME", "PASSWORD" , "SCORE"))
        for iter in self.__users:
            print("{:<20}{:<30}{:<30}{:<10}".format(iter.ID, iter.username, iter.password, iter.score))