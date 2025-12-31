#include <iostream>
#include <ctime>
#include <vector>
using namespace std;
class People{
    private:
        string name;
        int year;
        string month;
        int day;
        string gender;
        int age;
    public:
        string get_name();
        int get_name_first();
        int get_year();
        string get_month();
        int get_day();
        string get_gender();
        int get_age();
        void set_name(string name);
        void set_year(int year);
        void set_month(string month);
        void set_day(int day);
        void set_gender(string gender);
        void set_age(int age);
        void add();
        void search(int option);
        void sort_by_name(int option);
};
class Stack{
    protected:
        vector<People> data;
        int last;
        int first;
    public:
        Stack();
        void set_data(vector<People> data);
        vector<People> get_data();
        void add(People str);
        bool check_empty();
        bool check_full();
};
class Queue : public Stack{
    public:
        void pop();
        void search(string str , int option);
        void show();  
};
Queue males;
Queue females;
int main()
{
    People p1;
    int option;
    while(true){
        system("cls");
        cout << "------------ MAIN MENU ------------\n1. Add\n2. Search By Name\n3. Seach By Month\n4. Sort by Name\n5. show ALL\n6. Exit\nSelect an option : ";
        cin >> option;
        fflush(stdin);
        system("cls");
        switch(option){
            case 1:
                p1.add();
        break;
            case 2:
                p1.search(1);
        break;
            case 3:
                p1.search(2);
        break;
            case 4:
                p1.sort_by_name(1);
                p1.sort_by_name(2);
                males.show();
                females.show();
        break;
            case 5:
                males.show();
                females.show();
        break;
            case 6:
                cout << "Terminating programm" << endl;
                return 0;
        break;
            default:
                cout << "Invalid input..." << endl;
        }
        system("pause");
    }
}
Stack::Stack()
{
    last = 0;
}
vector<People> Stack::get_data()
{
    return data;
}
void Stack::set_data(vector<People> data)
{
    this->data = data;
}
void Stack::add(People str)
{
    if(check_full()){
        cout << "Your Space is Full!" << endl;
        return;
    }
    data.push_back(str);
    last++;
}
string People::get_name()
{
    return name;
}
int People::get_name_first()
{
    return int(name[0]);
}
int People::get_year()
{
    return year;
}
string People::get_month()
{
    return month;
}
int People::get_day()
{
    return day;
}
string People::get_gender()
{
    return gender;
}
int People::get_age()
{
    return age;
}
void People::set_name(string name)
{
    this->name = name;
}
void People::set_year(int year)
{
    this->year = year;
}
void People::set_month(string month)
{
    this->month = month;
}
void People::set_day(int day)
{
    this->day = day;
}
void People::set_gender(string gender)
{
    this->gender = gender;
}
void People::set_age(int age)
{
    this->age = age;
}
void People::add()
{
    string str , temp;
    cout << "Enter your Details with this Format ( Name:/Year/Month/Day/Gender ) : ";
    getline(cin , str);
    unsigned int check = -1;
    if(str.find(":") == check || str.find("/") == check){
        cout << "Invalid input.. Returning..." << endl;
        return;
    }   
    int i;
    name.clear();
    for(i = 0 ; ; i++){
        if(str[i] == ':')
            break;
        name+=str[i];
    }
    i++;
    temp.clear();
    for(int count = 1; str[i-1] ; i++){
        if(str[i] == '/' || !str[i]){
            if(count == 1)
                year = stoi(temp);
            else if(count == 2)
                month = temp;
            else if(count == 3)
                day = stoi(temp);
            else
                gender = temp;
            count++;
            temp.clear();
            continue;
        }
        temp+=str[i];
    }
    time_t time_second;
    time_second = time(NULL);
    int time_year = 1970 + time_second / 31537970;
    age = time_year - year;
    People obj;
    obj.set_name(name);
    obj.set_year(year);
    obj.set_month(month);
    obj.set_day(day);
    obj.set_age(age);
    obj.set_gender(gender);
    if(gender == "female" || gender == "FEMALE" || gender == "Female"){
        females.add(obj);
        cout << "User has been added to Females" << endl;
    }else{
        males.add(obj);
        cout << "User has been Added to Males" << endl;
    }
    cout << "Adding Process Complete!" << endl;
}
void People::search(int option)
{
    if(males.check_empty() && females.check_empty()){
        cout << "Both of your Queues are Empty!" << endl;
        return;
    }
    string name;
    if(option == 1)
        cout << "Enter the Name you'd like to Search for : ";
    else
        cout << "Enter the Month you'd like to Search for : ";
    getline(cin , name);
    system("cls");
    cout << "Searching Males..." << endl;
    males.search(name, option);
    cout << "Searching Females..." << endl;
    females.search(name, option);
}
void People::sort_by_name(int option)
{
    vector <People> temp;
    if(option == 1){
        cout << "SORTING MALES!" << endl;
        temp = males.get_data();
    }else{
        cout << "SORTING FEMALES!" << endl;
        temp = females.get_data();
    }
    if(temp.size() <= 1){
        cout << "Theres Nothing to Sort!" << endl;
        return;
    }
    int i , j , min , size = temp.size();
    for(i = 0 ; i < size -1 ; i++){
        min = i;
        for(j = i+1 ; j < size ; j++){
            if(temp[min].get_name_first() > temp[j].get_name_first())
                min = j;
        }
        if(min != i)
            swap(temp[min] , temp[i]);
    }
    cout << "Sorting Complete!" << endl;
    if(option == 1)
        males.set_data(temp);
    else
        females.set_data(temp);
    // males.show();
}
bool Stack::check_empty()
{
    return data.empty();
}
bool Stack::check_full()
{
    int max = data.max_size();
    if(last >= max)
        return true;
    else
        return false;
}
void Queue::pop()
{
    if(check_empty()){
        cout << "Your Queue is Empty..Returning.." << endl;
        return;
    }
    People temp = data[first];
    data.erase(data.begin() + first);
    first++;
    cout << "-------- POPPED OBJECT --------\nName : " << temp.get_name() << "\nBirth Date : "<< temp.get_year() << " / " << temp.get_month() << " / " << temp.get_day() << "\nGender : " << temp.get_gender() 
        << "\nAge : " << temp.get_age() << endl;
}
void Queue::search(string str , int option)
{
    bool check_found = false;
    for(People value : data){
        if(option == 1){
            if(value.get_name() == str){
                check_found = true;
                cout << "-------- FOUND PERSON --------\nName : " << value.get_name() << "\nBirth Date : "<< value.get_year() << " / " << value.get_month() << " / " << value.get_day() << "\nGender : " << value.get_gender() 
                    << "\nAge : " << value.get_age() << "\n----------------------------" << endl;
            }
        }else{
            if(value.get_month() == str){
                check_found = true;
                cout << "-------- FOUND PERSON --------\nName : " << value.get_name() << "\nBirth Date : "<< value.get_year() << " / " << value.get_month() << " / " << value.get_day() << "\nGender : " << value.get_gender() 
                    << "\nAge : " << value.get_age() << "\n----------------------------" << endl;
            }
        }
    }
    if(!check_found)
        cout << "No user with such prompt was found!" << endl;
}
void Queue::show()
{
    for(People value : data){
        cout << "----------------------------\nName : " << value.get_name() << "\nBirth Date : "<< value.get_year() << " / " << value.get_month() << " / " << value.get_day() << "\nGender : " << value.get_gender() 
            << "\nAge : " << value.get_age() << "\n----------------------------" << endl;   
    }
}
