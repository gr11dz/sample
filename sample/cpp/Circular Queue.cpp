#include <iostream>
using namespace std;
class Queue{
    private:
        string storage[12];
        int size;
        int front;
        int rear;
    public:
        Queue();
        void push();
        void pop();
};
int main()
{
    int option;
    Queue queue;
    while(true){
        system("cls");
        cout << "--------- MAIN MENU ----------\n1. Push\n2. Pop\n3. Exit\nSelect an option: ";
        cin >> option;
        fflush(stdin);
        system("cls");
        switch(option){
            case 1:
                queue.push();
        break;
            case 2:
                queue.pop();
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
Queue::Queue()
{
    front = 0;
    rear = 0;
    size = 12;
}
void Queue::push()
{
//    cout << "REAR : " << rear << "\nFRONT : " << front << endl;
    if((rear+1)%size == front){
        cout << "Your Queue is full!" << endl;
        return;
    }
    cout << "Enter your value : ";
    getline(cin , storage[++rear % size]);
    rear %= size;
}
void Queue::pop()
{
//    cout << "REAR : " << rear << "\nFRONT : " << front << endl;
    if(rear == front){
        cout << "Your Queue is Empty!" << endl;
        return;
    }
    cout << "Your Popped value : " << storage[++front % size] << endl;
    front %= size;
}