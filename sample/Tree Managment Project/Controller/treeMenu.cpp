#include "../src/View/manager.cpp"
using namespace std;

class MainMenu
{
    private:
        Manager<int> treeManager;

        void insert()
        {
            int data;
            system("cls");
            cout << "Enter your Data(integer!) : ";
            cin >> data;
            system("cls");
            treeManager.insert(data);
        }
    public:
        MainMenu()
        {
            startMenu();
        }

        void startMenu()
        {
            int option;
            while (true)
            {
                system("cls");
                cout << "----------MAIN MENU----------\n1. Create\n2. Delete Children\n3. Details\n4. Inverse Nodes\n5. Show Contents\n6. Exit\nSelect an option : ";
                cin >> option;
                system("cls");

                switch (option)
                {
                    case 1:
                        insert();
                    break;

                    case 2:
                        treeManager.deleteNodes();
                    break;

                    case 3:
                        treeManager.countNodes();
                    break;

                    case 4:
                        treeManager.inverseNodes();
                    break;

                    case 5:
                        treeManager.showAll();
                    break;
    
                    case 6:
                        return;
                    break;

                    default:
                        cout << "Invalid Input..." << endl;

                } 
                system("pause");
            }
        }
};

int main()
{
    MainMenu menu;
    menu.startMenu();
}