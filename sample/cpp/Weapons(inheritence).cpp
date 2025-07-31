#include<iostream>
using namespace std;
class Player{
	private:
		string username;
		double health;
		double range;
	public:
		Player();
		string get_username();
		double get_health();
		double get_range();
		void set_range(double range);
		void set_health(double health);
};
class Weapons{
	protected:
		string name;
		int damage;
		double range;
		double range_mul;
	public:
		void show_details();
		bool check_range();
		void fire();
};
class AK : public Weapons{
	public:
		AK();
};
class Bomb : public Weapons{ 
	public:
		Bomb();
};
class M5 : public Weapons{
	private:
		int damage2;
		double range2;

		double range2_mul;
	public:
		M5();
		bool check_range_bomb();
		void fire_bomb();
		void show_exp_detail();
};
bool weapon_select();
void weapon_details();
Player player;
void select_range();
int main(){
	int option;
	while(true){
		system("cls");
		cout << "---------- MAIN MENU ----------\n1. Weapon Try Outs\n2. Weapons Detail\n3. Exit\nSelect an option : ";
		cin >> option;
		fflush(stdin);
		system("cls");
		switch(option){
			case 1:
				if(weapon_select())
					return 0;
		break;
			case 2:
				weapon_details();
		break;
			case 3:
				return 0;
		break;
			default:
				cout << "Invalid input.." << endl;
		}
		system("pause");
	}
}
Player::Player()
{
	system("cls");
	cout << "Enter a username : ";
	getline(cin , username);
	system("cls");
	cout << "------------ Welcome " << username << " ------------" << endl;
	health = 100;
	system("pause");
}
string Player::get_username()
{
	return username;
}
double Player::get_health()
{
	return health;
}
double Player::get_range()
{
	return range;
}
void Player::set_health(double health)
{
	this->health = health;
}
void Player::set_range(double range)
{
	this->range = range;
}
bool M5::check_range_bomb()
{
	if(player.get_range() <= range2){
		range2_mul = 1;
		return true;
	}else if(player.get_range() <= range2){
		range2_mul = range2 / player.get_range();
		return true;
	}else{
		return false;
	}
}
bool Weapons::check_range()
{
	if(player.get_range() <= range){
		range_mul = 1;
		return true;
	}else if(player.get_range() <= 2*range){
		range_mul = range / player.get_range();
		return true;
	}else{
		return false;
	}
}
void Weapons::fire()
{
    select_range();
	double hp = player.get_health();
	if(check_range()){
		cout << "You've been SHOT!" << endl;
		hp-=damage * range_mul;
		player.set_health(hp);
	}else{
		cout << "You were too far!" << endl;
	}
}
void Weapons::show_details()
{
	cout << "------------ " << name << " ------------\nRange : " << range << "\nDamage : " << damage << endl;
}
AK::AK()
{
	name = "AK-47";
	damage = 15;
	range = 2000;
	range_mul = 1;
}
Bomb::Bomb()
{
	name = "BOMB";
	damage = 100;
	range = 50;
	range_mul = 1;
}
M5::M5()
{
	name = "M5";
	damage2 = 80;
	range2 = 300;
	range2_mul = 1;
	damage = 10;
	range = 1500;
}
void M5::fire_bomb()
{
    select_range();
	double hp = player.get_health();
	if(check_range_bomb()){
		cout << "You've been shot!\nDamage taken : " << damage2 << endl;
		hp-=damage2 * range2_mul;
		player.set_health(hp);
    }
	else{
		cout << "You were too far!" << endl;
 	}
}
bool weapon_select()
{
	int option;
	while(true){
		system("cls");
		cout << "------- WEAPON SELECT -------\n1. AK-47\n2. M5\n3. BOMB\n4. Return to main menu\nSelect an option : ";
		cin >> option;
		fflush(stdin);
		system("cls");
		switch(option){
			case 1:
			{
				AK weapon;
				weapon.fire();
		 	}
		break;
		 	case 2:
		 	{
		 		cout << "------------ Fire Mode ------------\n1. Bullet\n2. Grenade Launcher\nSelect an option : ";
				cin >> option;
				fflush(stdin);
				system("cls");
				M5 weapon2;
				if(option == 1)
					weapon2.fire();
				else if(option == 2)
					weapon2.fire_bomb();
				else
					cout << "Invalid input.." << endl;	
			}
		break;
			case 3:
			{
				Bomb weapon3;
				weapon3.fire();
			}
		break;
			case 4:
				return false;
		break;
			default:
				cout << "Invalid input...";		 		
		}

		if(player.get_health() <= 0){
			cout << "------------ GAME OVER ------------\n\t" <<player.get_username() << " , You've Died!" << endl;
			system("pause");
			return true;
		}else{
			cout << "\nCurrent Health : " << player.get_health() << endl;
		}
		system("pause");
	}
}
void select_range()
{
	double temp;
	cout << "Enter the distance of you and the Weapon : ";
	cin >> temp;
	fflush(stdin);
	player.set_range(temp);
}
void M5::show_exp_detail()
{
	cout << "Explosive Range : " << range2 << "\nExplosive Damage : " << damage2 << endl;
}
void weapon_details()
{
	int option;
	while(true){
		system("cls");
		cout << "------------- DETAILS -------------\n1. AK-47\n2. M5\n3. BOMB\n4. Return\nSelect an option : ";
		cin >> option;
		fflush(stdin);
		system("cls");
		switch(option){
			case 1:
			{
				AK weapon1;
				weapon1.show_details();
			}
		break;
			case 2:
			{
				M5 weapon2;
				weapon2.show_details();
				weapon2.show_exp_detail();
			}
		break;
			case 3:
			{
				Bomb weapon3;
				weapon3.show_details();
			}
		break;
			case 4:
				return;
		break;
			default:
				cout << "Invalid input..." << endl;
		}
		system("pause");
	}
}
