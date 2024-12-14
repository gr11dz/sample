#include <iostream>
#include <vector>
#include "Cordinates.h"
using namespace std;
#define RIGHT Cordinates(1 , 0)
#define LEFT Cordinates(-1 , 0)
#define UP Cordinates(0 , -1)
#define DOWN Cordinates(0 , 1);
enum Pieces{
    PLAYER1 = 4,PLAYER2 = 3,
};
class Grid{
	private:
        vector<vector<int>> grid;
        int last_placed;
    public:
        Grid(){
            vector<int> temp;
            for(int i = 0 ; i < 8 ; i++){
                for(int j = 0 ; j < 8 ; j++){
                    temp.push_back(0);
                }
                grid.push_back(temp);
            }
            grid[3][3] = PLAYER1;
            grid[4][4] = PLAYER1;
            grid[3][4] = PLAYER2;
            grid[4][3] = PLAYER2;
            last_placed = PLAYER2;
        }
        int get_last_placed(){
            return last_placed;
        }
        bool check_placeable(Cordinates cord){
            if(grid[cord.get_y()][cord.get_x()] != 0)
                return false;
            int last;
            if(last_placed == PLAYER1)
                last = PLAYER2;
            else
                last = PLAYER1;
            Cordinates check;
            for(int iter = 0 ; iter < 8 ; iter++){
                switch(iter){
                    case 0:
                        check = RIGHT;
                break;
                    case 1:
                        check = RIGHT + UP;
                break;
                    case 2:
                        check = RIGHT + DOWN;
                break;
                    case 3:
                        check = DOWN;
                break; 
                    case 4: 
                        check = UP;
                break;
                    case 5:
                        check = LEFT + UP;
                break; 
                    case 6:
                        check = LEFT;
                break;  
                    case 7:
                        check = LEFT + DOWN;
                break;
                }
                check = cord + check;
                if(check.get_x() > 0 && check.get_x() < 8 && check.get_y() > 0 && check.get_y() < 8){
                    if(grid[check.get_y()][check.get_x()] == last){
                        last_placed = last;
                        grid[cord.get_y()][cord.get_x()] =last_placed;
                        return true;
                    }
                }
            }
            return false;
        }
        bool check_end(){
            int i,j;
            for(i = 0 ; i < 8 ; i++){
                for(j = 0 ; j < 8 ; j++){
                    if(grid[i][j] == 0)
                        return false;
                }
            }
            return true;
        }
};
