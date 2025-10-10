class Task:
    def __init__(self, name = '', progress = ''):
        self.__name = name
        self.__progress = progress
    
    def __get_name(self) -> str:
        return self.__name
    def __get_progress(self) -> str:
        return self.__progress
    
    def __set_name(self, name: str):
        self.__name = name
    def __set_progress(self, progress: str):
        self.__progress = progress

    name = property(__get_name, __set_name)
    progress = property(__get_progress, __set_progress)


    