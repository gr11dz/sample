class User:
    def __init__(self):
        self.__ID = int()
        self.__username = str()
        self.__password = str()
        self.__score = float()
    def __get_ID(self):
        return self.__ID
    def __get_username(self):
        return self.__username
    def __get_passsword(self):
        return self.__password
    def __get_score(self):
        return self.__score
    def __set_ID(self , ID : int) -> None:
        self.__ID = ID
    def __set_username(self , username : str) -> None:
        self.__username = username
    def __set_password(self , password : str) -> None:
        self.__password = password
    def __set_score(self , score : float) ->None:
        self.__score = score
    ID = property(__get_ID , __set_ID)
    username = property(__get_username , __set_username)
    password = property(__get_passsword , __set_password)
    score = property(__get_score , __set_score)    