#pragma once

#include <iostream>
#include "../Private/bsTree.cpp"

using namespace std;

template <typename Type>
class Manager
{
    private:
        Bst<Type> tree;

        vector<Type> getValues()
        {
            return tree.show();
        }

    public:
        void insert(Type const DATA)
        {
            try
            {
                Codes::codes result = tree.insert(DATA, false);
                if (result != Codes::INSERT_SUCCESS)
                    throw result;
                cout << "Insertion Succeeded!" << endl;
            }catch(Codes::codes result)
            {
            
                if (result == Codes::INSERT_AlEXISTS)
                    cout << "Data Already Exists in Tree!" << endl;
                else
                    cout << "Insertion Failed!" << endl;
            }
        }

        void showAll()
        {
            vector<Type> container = getValues();
            if (container.empty())
            {
                cout << "Tree is Empty!" << endl;
                return;
            }
                
            for(Type iter : container)
            {
                cout << iter << "\t";
            }
            cout << endl;
        }

        void countNodes()
        {
            int counter = tree.countNodes();
            
            if (counter == -1)
                cout << "Tree is empty!" << endl;
            else
                cout << "Your Tree has " << counter << " amount(s) of Nodes!" << endl;
        }

        void deleteNodes()
        {
            tree.deleteChildren();
            
            // Another form of deleting everything that wont work because root isn't a pointer.

            // Bst<Type> newTree(tree.get_root());
            // delete tree 
            // tree = newTree;
        }

        void inverseNodes()
        {
            vector<Type> container = getValues();

            for(Type iter : container)
            {
                tree.insert(iter, true);
            }
        }

};