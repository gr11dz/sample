#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

#include "Population.h"
#include "LinkedQueue.h"

using namespace std;

class FileHandler
{
    private:

        vector<string> getParents()
        {
            ifstream file;
            file.open("../File/parents.txt");

            if (!file.is_open())
            {
                cout << "Error : " << strerror(errno) << endl;
                exit(0);
            }

            string text;
            vector<string> parents;
            parents.clear();

            while (getline(file, text))
            {
                parents.push_back(text);
            }

            file.close();
            return parents;
        }

    public:

        void truncOrder()
        {
            ofstream file;
            file.open("../File/order.txt");
            file.close();
        }

        Population setPopulation()
        {
            vector<string> parents = getParents();
            
            int queenAmount = stoi(parents[0].substr(0, parents[0].find(' ')));

            Population newpop;

            int iter;
            for(iter = 1; iter <= queenAmount; iter++){
                newpop.setQueen(parents[iter]);
            }

            for(; iter < parents.size(); iter++){
                newpop.setWorker(parents[iter]);
            }
            return newpop;
        }

        void orderWrite(int queenNumber, int startIndex, int strLength)
        {
            ofstream file;
            file.open("../File/order.txt", ios::app);

            file << queenNumber << '/' << startIndex << '/' << strLength << '\n';
            file.close();
        }
        
        LinkedList<string> getOrder()
        {
            ifstream file;
            file.open("../File/order.txt");
            if (!file.is_open())
            {
                cout << "Error : " << strerror(errno) << endl;
                exit(0);
            }

            LinkedList<string> Orderlist;
            string temp;
            while(getline(file, temp))
            {
                Orderlist.push_back(temp);
            }
            file.close();
            return Orderlist;
        }


};
