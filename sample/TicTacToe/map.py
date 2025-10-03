from coordinates import *

class Map:
    def __init__(self, default_value = '0', column = 3, row = 3):
        self.__default_value = str(default_value)
        self.__row = int(column)
        self.__column = int(row)
        self.__size = int(9)
        self.__grid = [[default_value for _ in range(column)] for _ in range(row)]
        self.__lastPlaced = list()

    def setPiece(self, mark: str, coords: Coordinates) -> int:
        if self.__grid[coords.y][coords.x] != '0':
            return 0
        self.__grid[coords.y][coords.x] = mark
        self.__lastPlaced.append(f"{coords.x},{coords.y},{mark}")
        if self.__checkWin(mark):
            return 1
        elif self.__checkTie():
            return 2
        else:
            return 3
    
    def getPlayer(self, coords: Coordinates) -> str:
        return self.__grid[coords.y][coords.x]
    
    def getLastPlaced(self) -> list:
        return self.__lastPlaced

    def getGrid(self) -> list:
        return self.__compress_grid()

    def showGrid(self):
        for i in range(self.__column):
            for j in range(self.__row):
                print(self.__grid[i][j],end=' ')
            print()

    def __checkDiagonal(self, playerMark: str) -> bool:
        counter = 0
        if self.__grid[1][1] == playerMark:
            for i in range(self.__column):
                if self.__grid[i][i] == playerMark:
                    counter += 1
            if counter == 3:
                return True
            else:
                counter = 0
            for i in range(self.__column):
                if self.__grid[i][-i] == playerMark:
                    counter += 1
            if counter == 3:
                return True
            else:
                counter = 0
    def __checkColumn(self, playerMark: str) -> bool:
        counter = 0
        if any(cell == playerMark for cell in self.__grid[1]) :
            for i in range(self.__column):
                for j in range(self.__column):
                    if self.__grid[j][i] == playerMark:
                        counter += 1
                if counter == 3:
                    return True
                else:
                    counter = 0
    def __checkRow(self, playerMark: str) -> bool:
        counter = 0
        if any(row[1] == playerMark for row in self.__grid):
            for i in range(self.__column):
                for j in range(self.__column):
                    if self.__grid[i][j] == playerMark:
                        counter += 1
                if counter == 3:
                    return True
                else:
                    counter = 0

    def __checkWin(self, playerMark: str) -> bool:
        if self.__checkDiagonal(playerMark):
            return True
        elif self.__checkColumn(playerMark):
            return True
        elif self.__checkRow(playerMark):
            return True
        else:
            return False
    
    def __checkTie(self) -> bool:
        for i in range(self.__column):
            for j in range(self.__column):
                if self.__grid[j][i] == '0':
                    return False
        return True

    def __compress_grid(self) -> list:
        comp_list = list()
        for i in range(self.__column):
            for j in range(self.__column):
                if (mark:=self.__grid[j][i]) != '0':
                    comp_list.append(f"{i},{j},{mark}")
        return comp_list
