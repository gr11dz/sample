class User:
    def __init__(self):
        self.__fName = str
        self.__lName = str
        self.__age = int
        self.__birthPlace = str
        self.__birthYear = int
    def __get_fName(self):
        return self.__fName
    def __get_lName(self):
        return self.__lName
    def __get_age(self):
        return self.__age
    def __get_birthPlace(self):
        return self.__birthPlace
    def __get_birthYear(self):
        return self.__birthYear
    def __set_fName(self, fName):
        self.__fName = fName
    def __set_lName(self, lName):
        self.__lName = lName
    def __set_age(self, age):
        self.__age = age
    def __set_birthPlace(self, birthPlace):
        self.__birthPlace = birthPlace
    def __set_birthYear(self, birthYear):
        self.__birthYear = birthYear
        
    fName = property(__get_fName , __set_fName)
    lName = property(__get_lName , __set_lName)
    age = property(__get_age, __set_age)
    birthPlace = property(__get_birthPlace , __set_birthPlace)
    birthYear = property(__get_birthYear , __set_birthYear)