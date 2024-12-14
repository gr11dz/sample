#include <graphics.h>
#include <windows.h>
#include "Grid.h"
using namespace std;
class Graphical{
	private:
		const int HEIGHT;
		const int WIDTH;
		const int SIZE;
		void show_main(vector<string> texts){
			initwindow(WIDTH , HEIGHT);
			int iter , iter2;
			int last = 0 , midx , midy;
			int textx , texty;
			readimagefile("bk_image.jpg" , 0 , 0 , WIDTH , HEIGHT);	
			midx = WIDTH /2 ;
			setfillstyle(SOLID_FILL , BLACK);
			for(iter = 50 , iter2 = 0 ; iter2 < texts.size() ; iter+= 70 ,iter2++){
				setcolor(CYAN);
				rectangle(2*WIDTH / 5 , (HEIGHT / 4) + last , 3*WIDTH / 5 , (HEIGHT / 4) + iter);
				midy = (HEIGHT /4) + (iter + last)/2;
				string temp = texts[iter2];
				textx = textwidth((char*)temp.c_str());
				texty = textheight((char*)temp.c_str());
				setcolor(WHITE);
				floodfill(midx , midy , CYAN);
				outtextxy(midx - textx/2 , midy - texty/2, (char*)temp.c_str());
				last = iter + 20;
			}			
		}
		int cursor_find(vector<string> texts){
			show_main(texts);
			POINT cursor;
			setcolor(WHITE);
			int iter , iter2 , last;
			while(true){
				GetCursorPos(&cursor);
				if(GetAsyncKeyState(VK_LBUTTON) < 0){
					if(cursor.x >= 2*WIDTH /5 && cursor.x <= 3*WIDTH / 5){
						last = 0;
						for(iter = 50 ,iter2 = 1 ; iter2 <= texts.size() ; iter+= 70 ,iter2++){
							if((cursor.y >= HEIGHT /4 + last && cursor.y <= HEIGHT / 4 + iter)){
								closegraph();
								return iter2;
							}
							last = iter + 20;
						}		
					}	
				}	
			}
		}
		void game_show(string username1 , string username2){
			initwindow(WIDTH , HEIGHT);
			setcolor(CYAN);
			circle(7*SIZE / 24 , 7*SIZE / 24 , SIZE / 30 );
			circle(9*SIZE / 24 , 9*SIZE / 24 , SIZE / 30 );
			setcolor(RED);
			circle(9*SIZE / 24 , 7*SIZE / 24 , SIZE / 30 );
			circle(7*SIZE / 24 , 9*SIZE / 24 , SIZE / 30 );
			int i,j;
			setcolor(LIGHTGREEN);
			for(i = 1 ; i < 9 ; i++){
				for(j = 1 ; j < 9 ; j++){
					rectangle(0 + i , 0 + j , i * SIZE /12 , j * SIZE / 12);
				}
			}
			setcolor(WHITE);
			rectangle(WIDTH / 2 , HEIGHT / 8 , 3 * WIDTH /4 , HEIGHT / 8 + 150);
			outtextxy(2.5 * WIDTH / 4 - textwidth((char*)username1.c_str())/2 , HEIGHT / 8 + textheight((char*)username1.c_str())/2 , (char*)username1.c_str());
			rectangle(WIDTH / 2 , HEIGHT / 8 + 200 , 3 * WIDTH /4 , HEIGHT / 8 + 350);
			outtextxy(2.5 * WIDTH / 4 - textwidth((char*)username2.c_str())/2 , HEIGHT / 8 + textheight((char*)username2.c_str())/2 + 200 , (char*)username2.c_str());
		}
		Grid game_cursor(Grid map){
			POINT cursor;
			bool check_break = false;
			int i ,j , iter = 0;
			while(true){
				GetCursorPos(&cursor);
				if(map.check_end()){
					return map;
				}
				if(GetAsyncKeyState(VK_LBUTTON) < 0){
					for(i = 1 ; i < 9 ; i++){
						for(j = 1 ; j < 9 ; j++){
							if(cursor.x >= i && cursor.x <= i*SIZE/12){
								if(cursor.y >= j && cursor.y <= j*SIZE/12){
									if(map.check_placeable(Cordinates(i-1 , j-1))){
										setcolor(map.get_last_placed());
										circle((2*i -1)* SIZE/24 , (2*j -1)* SIZE/24 , SIZE/30);
									}
									check_break = true;
									break;
								}
							}
						}
						if(check_break){
							check_break = false;
							break;
						}
					}	
				}
				iter++;
			}
		}
	public:
		Graphical() : HEIGHT(GetSystemMetrics(SM_CYSCREEN)) , WIDTH(GetSystemMetrics(SM_CXSCREEN)) , SIZE((HEIGHT > WIDTH)? WIDTH : HEIGHT){}
		int main_menu(){
			vector<string> texts;
			texts.push_back("SIGN UP");
			texts.push_back("PLAY");
			texts.push_back("HISTORY");
			texts.push_back("LEADERBOARD");
			texts.push_back("EXIT");
			return cursor_find(texts);
		}
		int game_menu(){
			vector<string> texts;
			texts.push_back("TWO PLAYER");
			texts.push_back("SINGLE PLAYER");
			return cursor_find(texts);
		}
		int continue_menu(){
			vector<string> texts;
			texts.push_back("NEW GAME");
			texts.push_back("CONTINUE");
			return cursor_find(texts);
		}
		Grid game(string username1 , string username2 , Grid& map){
			game_show(username1, username2);
			return game_cursor(map);
		}
};
