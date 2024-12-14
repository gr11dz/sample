from File import *
class Settings:
    def __init__(self):
        oFile = FileHandle()
        self.__settings = oFile.get_settings()
        del oFile
    def set_unique(self, unique : bool):
        self.__settings[0] = unique
    def set_history(self , history : bool):
        self.__settings[1] = history
    def set_length(self , length : int):
        self.__settings[2] = length
    def get_unique(self):
        return self.__settings[0]
    def get_history(self):
        return self.__settings[1]
    def get_length(self):
        return self.__settings[2]
    def save_settings(self):
        oFile = FileHandle()
        oFile.set_settings(self.__settings)
        del oFile   
    # def save_all(self , settings : dict):
    #     self.__settings = settings
    def defaultSetting(self):
        self.__settings[0] = 1
        self.__settings[1] = 1
        self.__settings[2] = 5
        oFile = FileHandle()
        oFile.set_settings(self.__settings)
        del oFile
    unique = property(get_unique , set_unique)
    history = property(get_history , set_unique)
    length = property(get_length , set_length)