#include "Graphical.h"
#include "Profile.h"
using namespace std;
int main()
{
	Graphical display;
	Profile profile;
	User player1;
	User player2;
	Grid map;
	int ID;
	int option;
	while(true){
		system("cls");
		option = display.main_menu();
		switch(option){
			case 1:
				profile.user_add();
		break;
			case 2:
				player1 = profile.sign_in();
				if(player1.get_id() == -1)
					break;
				if(display.game_menu() == 1){
					player2 = profile.sign_in();
					if(player2.get_id() == -1)
						break;
				}
				map = display.game(player1.get_username() , player2.get_username() , map);
		break;
			case 5:
				return 0;
		break;
		}
	}
}

