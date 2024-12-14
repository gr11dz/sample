#include <iostream>
using namespace std;
class User{
    private:
        int id;
        string username;
        string password;
        int score;
    public:
        User(int id , string username , string password , int score) : id(id) , username(username) , password(password) , score(score){}
        User() :  score(0){}
        void set_id(int id){
            this->id = id;
        }
        void set_username(string username){
            this->username = username;
        }
        void set_password(string password){
            this->password = password;
        }
        void set_score(int score){
            this->score = score;
        }
        int get_id(){
            return id;
        }
        string get_username(){
            return username;
        }
        string get_password(){
            return password;
        }
        int get_score(){
            return score;
        }
        User operator+(User const& obj){
            User newuser(id , username , password , score + obj.score);
            return newuser;
        }
        User operator-(User const& obj){
            User newuser(id , username , password , score - obj.score);
            return newuser;
        }
};
