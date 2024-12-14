from File import *
import random as rand
class Astring:
    def __init__(self):
       pass 
    def encrypt(self, password : str):
        key = list()
        key.clear()
        length = len(password)
        for iter in range(length):
            key.append(rand.randint(1 , 20))
        newPass = str()
        for iter in range(length):
            newPass += chr(ord(password[iter]) + key[iter])
        oFile = FileHandle()
        oFile.append_key(key)
        return newPass
    def decrypt(self , player : User.User):
        oFile = FileHandle()
        key = oFile.find_key(player.ID)
        newPass = str()
        for iter in range(len(key)):
            newPass += chr(ord(player.password[iter]) - key[iter])
        return newPass