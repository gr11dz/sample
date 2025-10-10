import re
from os import system

from tabulate import tabulate

from modelConn import Conn
from task import Task


class Ui:
    def __init__(self):
        self.__model = Conn()

    def __tokenize(self, code):
        tokens = re.findall(r"[a-zA-Z_]\w*|==|!=|<=|>=|[0-9]+|[+\-*/=()]|\".*?\"|'.*?'|\n", code)
        return tokens
    
    def __list(self, option: str) -> bool:
        try:
            match option:
                case '1':
                    records = self.__model.read_by_progress("done")
                case '2':
                    records = self.__model.read_by_progress("todo")
                case '3':
                    records = self.__model.read_by_progress("in-progress")
                case '4':
                    records = self.__model.readAll()
        except(...):
            print("SQL Read Exception...")
            return False
        finally:
            table = [[i+1, records[i].name, records[i].progress] for i in range(len(records))]
            headers = ["ID", "Name", "Progress"]        
            print(tabulate(table, headers= headers, tablefmt='grid'))

    def __parse(self, tokens) -> bool:
        
        for i in range(len(tokens)):
            match tokens[i]:
                case "add": 
                    if self.__model.insert(Task(tokens[i+1])):
                        print(f"Task has been added! (id={self.__model.getID(tokens[i+1])})")
                    else:
                        print("Task has not been added!")
                case "delete":
                    if self.__model.delete_by_id(tokens[i]):
                        print("Task Deleted Successfully!")
                    else:
                        print("Task was not found!")
                case "update":
                    if self.__model.update_name(name= tokens[i+2], id= tokens[i+1]):
                        print("Task has been updated")
                    else:
                        print("Task has not been updated!")
                case "mark-in-progress":
                    if self.__model.update_progress(id= id, progress="IN-PROGRESS"):
                        print("Task has been updated")
                    else:
                        print("Task has not been updated!")
                case "mark-done":
                    if self.__model.update_progress(id= id, progress="DONE"):
                        print("Task has been updated")
                    else:
                        print("Task has not been updated!")
                case "list":
                    try:
                        if tokens[i+1] == "done":
                            self.__list(option= "1")
                        elif tokens[i+1] == "todo":
                            self.__list(option= "2")
                        elif tokens[i+1] == "in-progress":
                            self.__list(option= "3")
                    except(IndexError):
                        self.__list(option= '4')
                
    def main_menu(self):

        while True:
            system("cls")
            usr_input = input("Task-Cli > Enter your Command >")
            token = self.__tokenize(usr_input)
            self.__parse(token)
            system("pause")

if __name__ == "__main__":
    ui = Ui()
    ui.main_menu()
