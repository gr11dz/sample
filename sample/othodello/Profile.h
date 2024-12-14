#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include "User.h"
using namespace std;
class Profile{
    private:
        vector<User> users;
        void file_read(){
            ifstream file("users.txt");
            if(!file.is_open()){
                ofstream file("users.txt");
                file << "1,Admin,admin\n";
                User newuser;
                newuser.set_id(1);
                newuser.set_username("Admin");
                newuser.set_password("admin");
                newuser.set_score(0);
                file.close();
                users.push_back(newuser);
                return;
            }
            string fcontent;
            int index = 0 , last = 0;
            int temp;
            while(getline(file , fcontent)){
                User newuser;
                last = 0;
                index = 0;
                for(int iter = 0; iter < 4 ; iter++){
                    last = index;
                    index = fcontent.find(',' , index+1);
                    if(index == -1)
                        index = fcontent.length();
                    if(iter == 0){
                        newuser.set_id(stoi(substr(fcontent , last , index)));
					}else if(iter == 1)
                        newuser.set_username(substr(fcontent , last+1 , index));
                    else if(iter == 2){
                        newuser.set_password(substr(fcontent , last+1 , index));
                        if(newuser.get_username() == "Admin"){
                            newuser.set_score(0);
                            break;
                        }
                    }else{
                        newuser.set_score(stoi(substr(fcontent , last+1 , index)));
                    }
                }
                users.push_back(newuser);
            }
            file.close();
        }
        void file_save_all(){
            fstream file;
            file.open("users.txt" , ios::trunc);
            for(int iter = 0 ; iter < users.size() ; iter++){
                file << users[iter].get_id() << ',' << users[iter].get_username() << ',' << users[iter].get_password() << ',' << users[iter].get_score() << '\n';
            }
            file.close();
        }
        void file_append(User newuser){
            fstream file;
            file.open("users.txt" , ios::app);
            file << newuser.get_id() << ',' << newuser.get_username() << ',' << newuser.get_password() << ',' << newuser.get_score() << '\n';
            file.close();
        }
        string substr(string str , int start , int end){
            string temp;
            for(int index = start ; index < end ; index++){
                temp+=str[index];
            }
            return temp;
        }
        bool check_username(string username){
            for(int iter = 0 ; iter < users.size() ; iter++){
            	if(users[iter].get_username() == username)
            		return false;
			}
            return true;
        }
        vector<int> encrypt(string& password){
            srand(time(0));
            vector<int> key;
            key.empty();
            for(int iter = 0 ; iter < password.length() ; iter++){
                key.push_back(rand());
                password[iter] ^= key[iter];
            }
            return key;
        }
        bool remove_user(int ID){
            for(int iter = 0 ; iter < users.size() ; iter++){
                if(users[iter].get_id() == ID){
                    users.erase(users.begin() + iter);
                    return true;
                }
            }
            return false;
        }
        void admin_menu(){
            int size = users.size();
            if(size < 2){
                system("color 0c");
                cout << "Not many users detected! Returning..." << endl;
                system("pause & color 07 & cls");
                return;
            }
            int ID;
            cout << "------------Profiles------------" << endl;
            for(int iter= 1 ; iter < size ; iter++){
                cout << users[iter].get_id() << ". " << users[iter].get_username() << endl;
            }
            while(true){
                try{
                    cout << "\nEnter the ID of the user you'd like to remove : ";
                    cin >> ID;
                    if(cin.fail() || ID == 1){
                        cin.clear();
                        throw ID;
                    }
                    break;
                }catch(...){
                    system("color 0c");
                    cout << "Invalid input..." << endl;
                    system("pause & color 07 & cls");
                }
            }
            if(remove_user(ID)){
                system("color 02");
                cout << "User was Found and Deleted!" << endl;
                file_save_all();
                system("pause & color 07 & cls");
            }else{
                system("color 0c");
                cout << "Deleting Process Failed!" << endl;
                system("pause & color 07 & cls");
            }
        }
        string decrypt(int ID , string password){
            ifstream file("keys.txt");
            if(!file)
                return " ";
            string key , temp ,temp2;
            int file_ID, index;
            vector<int> key_int;
            while(getline(file , temp)){
                index = temp.find(',');
                file_ID = stoi(substr(temp , 0 , index));
                if(file_ID == ID){
                    key = substr(temp , index+1 , temp.length());
                    for(int iter = 0 ; iter < key.length() ; iter++){
                        if(key[iter] == ' '){
                            key_int.push_back(stoi(temp2));
                            temp2.clear();
                        }
                        temp2 += key[iter];
                    }
                    break;
                }
            }
            if(key_int.empty())
                return " ";
            for(int iter = 0 ; iter < password.length() ; iter++){
                password[iter] ^= key_int[iter];
            }
            return password;
        }
        void key_append(vector<int> key , const int ID){
            fstream file("keys.txt" , ios::app);
            if(!file)
                fstream file("keys.txt" , ios::out);
            file << ID << ',';
            for(int iter = 0 ; iter < key.size() ; iter++){
                file << key[iter] << ' ';
            }
            file << '\n';
            file.close();
        }
    public:
        Profile(){
            users.empty();
            file_read();
        }
        void user_add(){
            string username , password;
            const int ID = users.back().get_id()+1;
            while(true){
                system("cls");
                cout << "Enter your Username : ";
                getline(cin , username);
                system("cls");
                if(check_username(username))
                    break;
                else
                    cout << "Username already taken!" << endl;
                system("pause");
            }
            cout << "Enter a Password : ";
            getline(cin , password);
            key_append(encrypt(password) , ID);
            User newuser(ID , username , password , 0);
            file_append(newuser);
            users.push_back(newuser);
        }
        User sign_in(){
            string username , password;
            int check_return = 0 , iterable = 0;
            User user;
            while(true){
                system("cls");
                cout << "Enter your Username : ";
                getline(cin , username);
                for(int iter = 0 ; iter < users.size() ; iter++){
                    if(username == users[iter].get_username()){
                        user = users[iter];
                        check_return = 1;
                        break;
                    }
                }
                if(check_return == 1)
                    break;
                else{
                    user.set_id(-1);
                    return user;
                }
                system("cls");
                cout << "Invalid username...";
                iterable++;
                if(iterable >= 2){
                    cout << "\nWould you like to return? (Enter 1 to Return) : ";
                    try{
                        cin >> check_return;
                        if(cin.fail()){
                            cin.clear();
                            throw check_return;
                        }
                        if(check_return == 1){
                            user.set_id(-1);
                            return user;
                        }
                    }catch(...){
                        system("color 0c");
                        cout << "Invalid input...";
                        system("pause & color 07");
                    }
                }
            }
            string new_password;
            if(user.get_username() != "Admin"){
                new_password = decrypt(user.get_id() , user.get_password());
                if(new_password == " "){
                    system("color 0c");
                    cout << "Invalid Arguement..." << endl;
                    system("pause & color 07");
                    user.set_id(-1);
                    return user;
                }
            }else
                new_password = user.get_password();
            for(iterable = 0 ; ;iterable++){
                system("cls");
                cout << "Enter your password : ";
                getline(cin , password);
                system("cls");
                if(password == "admin"){
                    admin_menu();
                    user.set_id(-1);
                    return user;
                }else if(password != new_password){
                    system("color 0c");
                    cout << "\nInvalid password...Please try again.." << endl;
                    system("pause");
                }else{
                    system("color 0a");
                    cout << "---------------WELCOME " << user.get_username() << "---------------" << endl;
                    system("pause & color 07");
                    return user;

                }
                if(iterable >= 2){
                    cout << "Too many tries...Returning to Main Menu..." << endl;
                    system("pause & color 07");
                    user.set_id(-1);
                    return user;
                }
                system("color 07");
            }
        }
};
