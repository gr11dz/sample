#include <vector>

using namespace std;

class Population
{
    private:
        vector<string> queens;
        vector<string> workers;

    public:

        Population()
        {
            queens.clear();
            workers.clear();
        }
        //Getters
        vector<string> getQueen()
        {
            return queens;
        }

        vector<string> getWorker()
        {
            return workers;
            
        }
        //Setters
        void setQueen(string queen)
        {
            queens.push_back(queen);
        }

        void setWorker(string worker)
        {
            workers.push_back(worker);
        }
        //printing
        void printQueen()
        {
            if (queens.empty())
                return;

            for (auto iter : queens)
            {
                cout << iter << endl;
            }
        }

        void printWorker()
        {
            if (workers.empty())
                return;

            for(auto iter : workers)
            {
                cout << iter << endl;
            }
            
        }
        

};