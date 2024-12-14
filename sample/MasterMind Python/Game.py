from Settings import *
import time
import random
class Game:
    def __init__(self, player : User.User , settings : Settings):
        self.__player = player
        self.__settings = settings
        self.__startTime = float
        self.__endTime = float
    def play(self):
        system("cls")
        values = list()
        if self.__settings.unique:
            temp = list(range(1 , 10))
            random.shuffle(temp)
            values = temp[:self.__settings.length]
        else:
            for iter in range(self.__settings.length):
                values.append(random.randint(1 , 9))
        guessed = list()
        for i in range(len(values)):
            guessed.append(0)
        print("{0}MASTER MIND{0}\nAre you Ready?".format('-'*30))
        system("pause")
        print("GAME STARTING IN....")
        for counter in range(3,0,-1):
            print(counter)
            time.sleep(1)
        self.__startTime = time.time()
        checkEnd = True
        while True:
            system("cls")
            checkEnd = True
            if self.__settings.history:
                for i in range(len(values)):
                    if guessed[i] == values[i]:
                        print(' ',values[i],end=' \0')
                    else:
                        print(end=' _ ')
                        checkEnd = False
            if checkEnd:
                self.__endTime = time.time()
                print("\nYOU'VE WON!!")
                break
            try:    
                guess = int(input("\n\nEnter your Guess : "))
            except:
                print("Invalid input..")
                system("pause")
                continue
            for iter in range(len(values)):
                if guess == values[iter]:
                    guessed[iter] = values[iter]
                    print("NUMBER EXISTS!")
        self.__player.score = (self.__startTime - self.__endTime)+ self.__settings.length* 10
        if self.__player.score < 0:
            self.__player.score = 0
            
        if self.__settings.history:
            self.__player.score -=10
            
        if self.__settings.unique:
            self.__player.score +=20
        return round(self.__player.score , 2)