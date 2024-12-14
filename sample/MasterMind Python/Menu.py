from Profile import *
class Menu:
    def __init__(self):
        self.__profileObj = Profile()
        self.__settingObj = Settings()
    def __alterSettings(self , str):
        value = bool
        value2 = int
        match str:
            case "Unique":
                try:
                    temp = input("Current {0} Value : {1}\nEnter your new {0} Value (Enter 1 for True & 0 for False): ".format(str , self.__settingObj.unique))
                    if temp == '0':
                        value = False
                    elif temp == '1':
                        value = True
                    else:
                        raise ValueError
                except:
                    print("Invalid input...")
                    return
                self.__settingObj.unique=value
            case "History":
                try:
                    temp = input("Current {0} Value : {1}\nEnter your new {0} Value (Enter 1 for True & 0 for False): ".format(str , self.__settingObj.history))
                    if temp == '0':
                        value = False
                    elif temp == '1':
                        value = True
                    else:
                        raise ValueError
                except:
                    print("Invalid input...")
                    return
                self.__settingObj.history=value
            case 'Length':
                try:
                    value2 = int(input("Current {0} Value : {1}\nEnter your new {0} Value (Enter a number from 1 to 9): ".format(str , self.__settingObj.length)))
                    if value2 > 9 or value2 < 1:
                        raise ValueError
                except:
                    print("Invalid input...")
                    return
                self.__settingObj.length=value2
        print(self.__settingObj.history)
        system("pause")
        self.__settingObj.save_settings()
        print("Changes were saved!")
    def __settings(self):
        while True:
            system("cls")
            print("{0}CURRENT SETTINGS{0}\n1. Unique : {1}\n2. History : {2}\n3. Length : {3}\n{0}{0}{0}"
                  .format('-'*16, self.__settingObj.unique , self.__settingObj.history , self.__settingObj.length))
            option = input("{}OPTIONS{}\n1. Change Unique\n2. Change History\n3. Change Length\n4. Return\nSelect an option : ".format('-'*21 , '-'*20))
            system("cls")
            match option:
                case '1':
                    self.__alterSettings("Unique")
                case '2':
                    self.__alterSettings("History")
                case '3':
                    self.__alterSettings("Length")
                case '4':
                    return
                case _:
                    print("Invalid input...")
            system("pause")
    def __admin_menu(self):
        option = int()
        while True:
            system("cls")
            option = input("{0}ADMIN MENU{0}\n1. Remove Player\n2. Set Default Settings\n3. Return to Main Menu\nSelect an option : ".format('-'*30))
            system("cls")
            match option:
                case '1':
                    self.__profileObj.Remove_User()
                case '2':
                    self.__settingObj.defaultSetting()
                    print("Default settings were implemented!")
                case '3':
                    return
            system("pause")
    def main(self):
        option = int()
        while True:
            system("cls")
            option = input("{0}MAIN MENU{0}\n1. Sign Up\n2. Settings\n3. Play\n4. LeaderBoard\n5. Exit\nSelect an option : ".format('-'*20))
            system("cls")
            match option:
                case '1':
                    self.__profileObj.addUser()
                case '2':
                    self.__settings()
                case '3':
                    if self.__profileObj.login(self.__settingObj) == True:
                        self.__admin_menu()
                case '4':
                    self.__profileObj.sortScore()
                case '&&':
                    self.__profileObj.show()
                case '5':
                    return
                case _:
                    print("Invalid input...")
            system("pause")


if "__main__" == __name__:
    obj = Menu()
    obj.main() 