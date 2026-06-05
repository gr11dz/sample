#include "Encoder.h"

using namespace std;

class GUI
{
    private:
        FileHandler File;
        Population population;

        void showPop()
        {
            cout << "---------QUEENS---------" << endl;
            population.printQueen();
            cout << "---------WORKERS---------" << endl;
            population.printWorker();
        }
        
        void encode()
        {
            LinkedList<string> list;
            while (true)
            {
                system("cls");
                fflush(stdin);
                string input;

                cout << "Enter 0 to End input process!" << endl;
                if (!list.is_empty())
                {
                    cout << "Current Values : ";
                    list.printAll();
                }
                cout << "Enter your new Value : ";
                getline(cin, input);
                
                if(input == "0")
                    break;
                list.push_back(input);
            }
            Encoder newEncoder;
            newEncoder.encode(list, population);
        }
        
        void decode()
        {
            Decoder decode;
            decode.decode(population);
        }
    public:

        GUI()
        {
            population = File.setPopulation();
        }
        
        void mainMenu()
        {
            int option;

            while (true)
            {
                system("cls");
                cout << "---------------MAIN MENU---------------\n1. Encode\n2. Decode\n3. Show Current population\n4. Exit\nSelect an option : ";
                cin >> option;
                system("cls");
                switch (option)
                {
                    case 1:
                        encode();
                break;
                    case 2:
                        decode();
                break;
                    case 3:
                        showPop();
                break;
                    case 4:
                        return;
                break;
                    default:
                        cout << "Invalid Value..." << endl;
                }
                system("pause");
            }

        }  
};


int main()
{

    GUI newGUI;
    newGUI.mainMenu();
    return 0;
}