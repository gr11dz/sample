#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>
using namespace std;
class Cordinates{
    private:
        int x;
        int y;
    public:
        Cordinates(): x(0) , y(0){}
        Cordinates(int x, int y): x(x) , y(y){}
        void set_x(int x){
            this->x = x;
        }
        void set_y(int y){
            this->y = y;
        }
        int get_x(){
            return x;
        }
        int get_y(){
            return y;
        }
        Cordinates operator+(Cordinates const& obj){
            Cordinates temp(x + obj.x , y + obj.y);
            return temp;
        }
        Cordinates operator-(Cordinates const& obj){
            Cordinates temp(x - obj.x , y - obj.y);
            return temp;
        }
};
#define RIGHT Cordinates(1 , 0)
#define LEFT Cordinates(-1 , 0)
#define UP Cordinates(0 , -1)
#define DOWN Cordinates(0 , 1)
class Map{
    private:
        vector<vector<int>> grid;
        bool file_read(string file_name , vector<vector<int>>& grid){
            ifstream file(file_name);
            if(!file){
                cout << "File was NOT found..." << endl;
                return false;
            }
            auto column = 0;
            string str;
            while(getline(file , str)){
                if(str.empty())
                    break;  
                vector<int> temp;
                for(auto iter : str){
                    temp.push_back(int(iter) - 48);
                }
                grid.push_back(temp);
                cout << endl;
                column++;
            }
            file.close();
            return true;
        }
        Cordinates find_start(vector<vector<int>> grid){
            int iter;
            int main_size = grid.size();
            Cordinates start;
            for(iter = 0 ; iter < main_size ; iter++){
                vector<int> temp = grid[iter];
                if(iter == 0){
                    int size = temp.size();
                    for(int iter2 = 0 ; iter2 < size ; iter2++){
                        if(temp[iter2] == 8){
                            start.set_x(iter2);
                            start.set_y(0);
                            return start;
                        }
                    }
                }else if(temp[0] == 8){
                    start.set_x(0);
                    start.set_y(iter);   
                    return start;
                }else if(temp[main_size-1] == 8){
                    start.set_x(main_size-1);
                    start.set_y(iter);
                    return start;
                }
            }
            start.set_x(-1);
            start.set_y(-1);
            return start;
        }
        Cordinates movement(Cordinates location , vector<vector<int>>& grid){
            Cordinates temp;
            bool check_reverse = false;
            for(auto iter = 0 ; iter < 5 ; iter++){
                if(iter == 0)
                    temp = location + RIGHT;
                else if(iter == 1)
                    temp = location + DOWN;
                else if(iter == 2)
                    temp = location + LEFT;
                else if(iter == 3)
                    temp = location + UP;
                else{
                    check_reverse = true;
                    iter = 0;
                }
                if(temp.get_x() < 0 || temp.get_y() < 0){
                    continue;
                }else{
                    auto place = grid[temp.get_y()][temp.get_x()];
                    if(place == 8){
                        temp.set_y(-1);
                        //cout << "END";
                        //system("pause");
                        return temp;
                    }
                    if(place == 1){
                        check_reverse = false;
                        grid[temp.get_y()][temp.get_x()] = 9;
                        grid[location.get_y()][location.get_x()] = 3;
                        return temp;
                    }else if(check_reverse && place == 3){
                        grid[location.get_y()][location.get_x()] = 7;
                        grid[temp.get_y()][temp.get_x()] = 9;
                        return temp;
                    }
                }
            }
            temp.set_x(-1);
            return temp;
        }
    public:
        Map(){
            system("cls");
            string file_name;
            do{
                cout << "Enter The File Name with the maze : ";
                getline(cin , file_name);
                system("cls");
                if(file_name.length() <= 4 || file_name.substr(file_name.length()-4 , file_name.length()) != ".txt")
                    file_name+=".txt";
            }while(!file_read(file_name , grid));
        }
        void find_start(Cordinates& start){
            start = find_start(grid);
            if(start.get_x() == -1 && start.get_y() == -1){
                cerr << "Could not find start position!\nMake sure to put 8 at the start and end position!" << endl;
                return;
            }
        }
        Cordinates movement(Cordinates location){
            return movement(location , grid);
        }
        void show_map(){
            vector<int> temp;
            for(auto iter : grid){
                temp = iter;
                for(auto iter2 : temp){
                    if(iter2 == 0)
                        cout << "#";
                    else if(iter2 == 1 || iter2 == 3 || iter2 == 7)
                        cout << " ";
                    else if(iter2 == 9)
                        cout << "M";
                    else if(iter2 == 8)
                        cout << '!';
                    cout << " ";
                }
                cout << endl;
            }
        }
};
class Mouse{
    private:
        Cordinates location;
    public:
        Mouse(Map map){
            map.find_start(location);
            if(location.get_x() == -1)
                return;
        }
        void move(Map& map){
            Cordinates temp;
            while(true){
                temp = map.movement(location);
                if(temp.get_x() != -1 && temp.get_y() != -1){
                    location = temp;
                    cout << "LOCATION : " << location.get_x() << ':' << location.get_y() << endl;
                }else if(temp.get_y() == -1){
                    system("cls");
                    cout << "THE MOUSE HAS REACHED THE END!" << endl;
                    system("pause");
                    return;
                }else{
                    cout << "THE MOUSE HAS RAN INTO A PROBLEM!" << endl;
                    system("pause");
                    return;
                }
                map.show_map();
                sleep(1);
                system("cls");
            }
        }
};
int main()
{
    Map map;
    Mouse mouse(map);
    mouse.move(map);
}