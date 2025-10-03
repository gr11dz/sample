from os import system
from map import Map, Coordinates
from bot import Bot

class Menu:
    def __init__(self):
        # self.__map = Map()
        # self.__bot = Bot()
        self.__playerMark = str

    def __gridInput(self, input: str) -> Coordinates:
        x, y = map(int, input.split())
        return Coordinates(x, y)

    def __select_player(self) -> bool:
        self.__player_mark = None
        while True:
            system("cls")
            option = input(f"{'-'*10}Player Mark{'-'*10}\n1. x\n2. o\n3. Return\nSelect an option: ")
            match option:
                case '1':
                    self.__player_mark = 'x'
                case '2':
                    self.__player_mark = 'o'
                case '3':
                    return False
                case _:
                    print("Invalid input...")
                    system("pause")
                    continue
            return True
            
    def __select_bot_difficulty(self) -> int:
        
        while True:
            system('cls')
            option = input(f"{'-'*10}Bot Difficulty{'-'*10}\n1. Easy\n2. Medium\n3. Hard\n4. Return\nSelect an option: ")
            match option:
                case '1':
                    return 1
                case '2':
                    return 2
                case '3':
                    return 3
                case '4':
                    return 0
                case _:
                    print("Invalid input...")
                    continue

    def __matchConclusion(self, result: int, mark: str) -> bool:
        match result:
            case 0:
                print("Invalid input...")
                return None
            case 1:
                # print(f"Player {mark} has won!")
                return True
            case 2:
                print("Its a Tie!")
                return True
            case 3:
                return False

    def ini_1v1_game(self):
        counter = 0
        playerMark = ''
        result = None
        map = Map()
        while True:
            system("cls")
            if counter % 2 == 0:
                playerMark = 'x'
            else:
                playerMark = 'o'
            map.showGrid()
            usr_input = input(f"select a Grid number for player {playerMark} : ")

            result = self.__matchConclusion(map.setPiece(playerMark, self.__gridInput(usr_input)),
                                            playerMark)
         
            if result == None:
                print("Invalid Input...")
                continue
            elif result == True:
                system("cls")
                map.showGrid()
                print("You've Won!")
                system("pause")
                return
            else:
                counter +=1

    def ini_PvE_game(self):
        if not self.__select_player():
            return
        
        if (bot_difficulty := self.__select_bot_difficulty()) == 0:
            return
        bot = Bot(self.__player_mark, bot_difficulty)
        map = Map()
        counter = 0
        if self.__player_mark == 'o':
            counter+=1

        while True:
            if counter %2 != 0:
                #bot's turn.
                print(f"map : {map.getGrid()}")
                coords = bot.ini_bot(map.getLastPlaced())
                print(f"Bots Coords: {coords.x}, {coords.y}")
                system("pause")
                result = self.__matchConclusion(map.setPiece(bot.get_bot_mark(), coords),
                                                bot.get_bot_mark())
                if result == True:
                    system("pause")
                    return
                del coords
                counter+=1
                continue
            #Player's turn.
            system("cls")
            map.showGrid()
            coords = self.__gridInput(input("Enter a Coordinates : "))
            result = self.__matchConclusion(map.setPiece(self.__player_mark, coords),
                                            self.__playerMark)
            if result == True:
                system("cls")
                map.showGrid()
                print("You've Won!")
                system("pause")
                return
            elif result == None:
                continue
            counter+=1
 
    def main_menu(self):
        while True:
            system("cls")
            option = input(f"{'='*10}Main Menu{'='*10}\n1. PvP\n2. PvE\n3. Exit\nSelect an option: ")
            match option:
                case '1':
                    self.ini_1v1_game()
                case '2':
                    self.ini_PvE_game()  
                case '3':
                    return
                case _:
                    print("Invalid input...")
            system("pause")
    
if __name__ == "__main__":
    menu = Menu()
    menu.main_menu()