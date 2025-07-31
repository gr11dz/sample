#include <iostream>
using namespace std;
class Stack{
    private:
        string storage[12];
        int top;
        int size;
    public:
        Stack();
        void pop();
        void push();
};
int main()
{
    int option;
    Stack stck;
    while(true){
        system("cls");
        cout << "------- MAIN MENU -------\n1. Push\n2. Pop\n3. Exit\nSelect an option : ";
        cin >> option;
        fflush(stdin);
        system("cls");
        switch(option){
            case 1:
                stck.push();
        break;
            case 2:
                stck.pop();
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
Stack::Stack()
{
    top = -1;
    size = 12;
}
void Stack::pop()
{
    if(top == -1){
        cout << "Your stack is empty!\n";
        return;
    }
    cout << "Value : " << storage[top--] << endl;
}
void Stack::push()
{
    if(top == 11){
        cout << "Your stack is full!\n";
        return;
    }
    cout << "Enter a value : ";
    getline(cin , storage[++top]);

}