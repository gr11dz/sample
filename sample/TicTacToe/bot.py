from map import Map, Coordinates

class Bot:
    def __init__(self, player_mark: str, bot_difficulty: int):
        self.__botMark = str
        self.__set_bot_mark(player_mark)

        self.__bot_difficulty = bot_difficulty

    def __set_bot_mark(self, player_mark : str):
        if player_mark == 'x':
            self.__botMark = 'o'
        else:
            self.__botMark = 'x'

    def get_bot_mark(self) -> str:
        return self.__botMark

    def __easyBot(self, grid : list) -> Coordinates:
        priority_coords = [(1, 1), (1, 0), (0, 1), (2, 1), (1, 2),
                           (0, 0), (2, 0), (0, 2), (2, 2)]
        
        for i in priority_coords:
            occured = False
            for cell in grid:
                x_str, y_str, mark = cell.split(',')
                # if mark == self.__botMark:
                #     continue
                x, y = int(x_str), int(y_str)
                
                if (x, y) == i:
                    occured = True
                    break
            if not occured:
                return Coordinates(i[0], i[1])
        
    def __mediumBot(self, grid : list):
        pass

    def __hardBot(self, grid : list):
        pass

    def ini_bot(self, map: list) -> Coordinates:
        match self.__bot_difficulty:
            case 1:
                return self.__easyBot(map)
            case 2:
                return self.__mediumBot(map)
            case 3:
                return self.__hardBot(map)