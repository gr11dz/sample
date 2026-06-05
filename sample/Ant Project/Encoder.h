#include <math.h>

#include "FileHandler.h"

using namespace std;
#define INPUT_CHARACTER 256

class Encoder
{
    private:

        int rabinKarpSearch(string pat, string txt, int primeNum = INT_MAX)
        {
            int patSize = pat.length();
            int txtSize = txt.length();
            int i, j;
            int pattI = 0; 
            int txtI = 0; 
           
            int h = int(pow(INPUT_CHARACTER, patSize-1))%primeNum;
            for (i = 0; i < patSize; i++) {
                pattI = (INPUT_CHARACTER * pattI + pat[i]) % primeNum;
                txtI = (INPUT_CHARACTER * txtI + txt[i]) % primeNum;
            }
            for (i = 0; i <= txtSize - patSize; i++) {

                if (pattI == txtI) {
                    for (j = 0; j < patSize; j++) {
                        if (txt[i + j] != pat[j]) {
                            break;
                        }
                    }
                    if (j == patSize)
                        return i;
                }
                if (i < txtSize - patSize) {
                    txtI = (INPUT_CHARACTER * (txtI - txt[i] * h) + txt[i + patSize]) % primeNum;

                    if (txtI < 0)
                        txtI = (txtI + primeNum);
                }
            }
            return -1;
        }

    public:

        void encode(LinkedList<string> inputList, Population ants)
        {
            for(auto iter : ants.getWorker())
            {
               inputList.checkValue(iter);
            }

            for(auto iter : ants.getQueen())
            {
                inputList.checkValue(iter);
            }

            int startIndex;
            int queenNumber;
            string pattern;
            FileHandler newFile;
            newFile.truncOrder();

            while (!inputList.is_empty())
            {
                pattern = inputList.popFirst();
                
                queenNumber = 0;
                startIndex = -1;
                for(auto iter : ants.getQueen())
                {
                    startIndex = rabinKarpSearch(pattern, iter);
                    if (startIndex != -1)
                        break;
                    queenNumber++;
                }
                if (startIndex == -1)
                    continue;
                newFile.orderWrite(queenNumber, startIndex, pattern.length());
            }
        }

};

class Decoder
{
    private:
        LinkedList<string> orderList;

        string createSub(string queen, int startIndex, int strlength)
        {
            return queen.substr(startIndex, strlength);
           
        }

    public:
        Decoder()
        {
            FileHandler newFile;
            orderList = newFile.getOrder();
        }

        void decode(Population ants)
        {   
            while (!orderList.is_empty())
            {
                string temp = orderList.popFirst();

                int firstComma = temp.find('/');
                int queenNumber = stoi(temp.substr(0, firstComma));

                int secondComma = temp.find('/', firstComma+1);
                int startIndex = stoi(temp.substr(firstComma+1, secondComma - firstComma -1));

                int strlength = stoi(temp.substr(secondComma+1, temp.length()-secondComma-1));
                
                string queen;
                for(auto iter : ants.getQueen())
                {
                    queenNumber--;
                    if (queenNumber < 0)
                    {
                        queen = iter;
                        break;
                    }
                }
                cout << createSub(queen, startIndex, strlength) << endl;
            }
            FileHandler newfile;
            newfile.truncOrder();
        }
};