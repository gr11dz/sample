
class Personal:
    
    def __init__(self):
        
        self.__username = str
        self.__password = str
        self.__age = int
        
    def __getUsername(self):
        return self.__username
    
    def __getPassword(self):
        return self.__password
    
    def __getAge(self):
        return self.__age
    
    def __setUsername(self, username: str):
        self.__username = username
        
    def __setPassword(self, password:str):
        self.__password = password
        
    def __setAge(self, age: int):
        self.__age = age
        
    username = property(__getUsername , __setUsername)
    password = property(__getPassword, __setPassword)
    age = property(__getAge, __setAge)
    
class Scrapped:
    
    def __init__(self):
        
        self.__prsID = int
        self.__scrapped = str
        
    def __getPrsID(self):
        return self.__prsID
    
    def __getScrapped(self):
        return self.__scrapped
    
    def __setPrsID(self, ID: int):
        self.__prsID = ID
        
    def __setScrapped(self, scrape: str):
        self.__scrapped = scrape
    
    prsID = property(__getPrsID, __setPrsID)
    scrapped = property(__getScrapped, __setScrapped)