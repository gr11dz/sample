from os import system
import User
class FileHandle:
    def __init__(self):
        self.read_All()
    def read_All(self, newList = list()):
        newList.clear()
        try:
            file = open("users.txt" , 'r+')
        except:
            file = open("users.txt" , 'w+')
            file.write("1,Admin,admin\n")
            file.close()
            file = open("key.txt" , 'w')
            file.close()
            return
        while fcontent := file.readline() :
            if fcontent == 'l0\b':
                break
            temp = fcontent.replace('\n' , '\0').split(',')
            newObj = User.User()
            newObj.ID = int(temp[0])
            newObj.username = temp[1]
            if temp[2][len(temp[2])-1] == '\x00':
                newObj.password = temp[2][:len(temp[2])-1]
            else:
                newObj.password = temp[2]
            if not(newObj.username == 'Admin'):
                try:
                    # value = str()
                    newObj.score = float(temp[3][:len(temp[3])-4])
                except:
                    newObj.score = float(0)
            newList.append(newObj)
        file.close()
        return newList
    def saveAll(self , users = list()):
        with open("users.txt" , 'w+' , encoding="utf-8") as fUser:
            for iter in users:
                fUser.write("{},{},{},{}\n".format(iter.ID , iter.username , iter.password , iter.score))
        if len(users) <= 1:
            file = open("key.txt" , 'w')
            file.close()
    def append_user(self , obj : User.User) -> None:        
        with open("users.txt" , 'a' , encoding="utf-8") as file:
            file.write("{},{},{},{}\n".format(obj.ID , obj.username , obj.password , obj.score))
    def append_key(self , key : list):
        with open("key.txt" , 'a') as fKey:
            for i in key:
                fKey.write("{} ".format(i))
            fKey.write('\n')
    def find_key(self , ID : int):
        key = list()
        key.clear()
        with open("key.txt" , 'r') as fKey:
            count = 1
            while fContent := fKey.readline():
                count +=1
                if count == ID:
                    # break
                    temp = fContent.replace('\n' , '').split(' ')
                    temp.remove('')
                    for iter in temp:
                        key.append(int(iter))
        return key
        # key = list()
        # key.clear()
        # for iter in fContent:
    def get_settings(self):
        settings = dict()
        try:
            fSett = open("settings.txt" , 'r')
        except:
            fSett = open("settings.txt" , 'w+')
            system("pause")
            fSett.write("Unique = 0\nHistory = 1\nlength = 5")
            fSett.close()
            settings[0] = False
            settings[1] = True
            settings[2] = 5
            return settings
        fContent = fSett.readlines()
        fSett.close()
        count = 0
        for iter in fContent:
            if count == 0:
                if iter[iter.index('=')+2] == 'True':
                    settings[count] = True
                else:
                    settings[count] = False
                # settings[count] = bool(iter[iter.index('=')+2])
            elif count == 1:
                if iter[iter.index('=')+2] == 'True':
                    settings[count] = True
                else:
                    settings[count] = False
            else:
                settings[count] = int(iter[iter.index('=')+2])
                return settings
            count+=1
    def set_settings(self , settings : dict):
        with open("settings.txt", 'w+') as fSett:
            fSett.write("Unique = {}\nHistory = {}\nLength = {}".format(settings[0] , settings[1] , settings[2]))
            