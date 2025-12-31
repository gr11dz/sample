from bs4 import BeautifulSoup
import requests
import re

OK_CONN = 200

class Scrapper:
    
    def __init__(self):
        self._url = str
        self._subString = str
        
    def __setUrl(self, url: str):
        self._url = url
        
    def __getUrl(self) -> str:
        return self._url
    
    def __setSubstring(self, subString : str):
        self._subString = subString
        
    def __getSubstring(self) -> str:
        return self._subString
    
    def __checkResponse(self) -> bool:
        self.__response = requests.get(self._url)
        
        if self.__response.status_code == OK_CONN:
            return True
        
        del self.__response
        return False
            
    def scrapp(self):
        if not self.__checkResponse() or not self._subString:
            return None
        
        soup = BeautifulSoup(self.__response.text, "html.parser")
        
        # print(type(re.findall(rf"([^.]*{self._subString}[^.]*)", soup.text)))
        return re.findall(rf"([^.]*{self._subString}[^.]*)", soup.text)

    url = property(__getUrl, __setUrl)
    subString = property(__getSubstring, __setSubstring)