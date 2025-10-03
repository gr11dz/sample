class Coordinates:
    def __init__(self, x= 0, y= 0):
        self.__x = int(x)
        self.__y = int(y)

    def __getX(self):
        return self.__x
    def __getY(self):
        return self.__y
    def __setX(self, x :int):
        self.__x = x
    def __setY(self, y :int):
        self.__y = y

    def __add__(self, object):
        result = Coordinates()
        result.x = self.__x + object.x
        result.y = self.__y + object.y
        return result

    def __sub__(self, object):
        result = Coordinates()
        result.x = self.__x - object.x
        result.y = self.__y - object.y
        return result
    
    def __repr__(self):
        return f"{self.__str__()}(x= {self.__x}, y={self.__y})"

    x = property(__getX, __setX)
    y = property(__getY, __setY)




if __name__ == "__main__":
    coord1 = Coordinates(1, 2)
    coord2 = Coordinates(2, 3)

    print((coord1 - coord2).x, (coord1 - coord2).y)
    print(coord1)