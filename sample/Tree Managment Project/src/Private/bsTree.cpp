#include <vector>

namespace Codes
{
    enum codes
    {
        //error Codes
        TREE_FULL = 101,
        TREE_EMPTY = 102,
        INSERT_FAIL = 103,
        INSERT_AlEXISTS = 104,
        //success codes
        INSERT_SUCCESS = 201,
    };
}

using namespace std;

template <typename Type>
class Node
{
    public:
        Type data;
        Node* left;
        Node* right;

        Node(): left(nullptr), right(nullptr){}
        Node(Type data): data(data), left(nullptr), right(nullptr){}
};

template <typename Type>
class Bst
{
    private:
        Node<Type>* root;

        Node<Type>* createNode(Type const DATA)
        {
            Node<Type>* newNode = new Node<Type>(DATA);
            return newNode;
        }
        
        Node<Type>* insertNode(Node<Type>* node, Type const DATA, bool reverse)
        {
            if (!node)
                return createNode(DATA);
            if (reverse)
            {
                if (DATA > node->data)
                    node->right = insertNode(node->right, DATA, reverse);
                else
                    node->left = insertNode(node->left, DATA, reverse);
            }

            return node;
        }
        


        bool SearchNodes(Node<Type>*node, Type const KEYWORD, bool check)
        {
            if (!node)
                return false;

            if (node->data == KEYWORD)
                return true;
            
            if (KEYWORD > node->data)
                return SearchNodes(node->right, KEYWORD, true);
            else
                return SearchNodes(node->left, KEYWORD, true);
        }

        Node<Type>* SearchNodes(Node<Type>* node, Type const KEYWORD)
        {
            if (!node || node->data == KEYWORD)
                return node;
            
            if (KEYWORD > node->data)
                return SearchNodes(node->right, KEYWORD);
            else
                return SeachNodes(node->left, KEYWORD);
        }

        void inOrder(Node<Type>* node, vector<Type>& container)
        {
            if (node)
            {
                inOrder(node->left, container);
                container.push_back(node->data);
                inOrder(node->right, container);
            }
        }
        void inOrder(Node<Type>* node, int& counter)
        {
            if (node)
            {
                inOrder(node->left, counter);
                counter++;
                inOrder(node->right, counter);
            }
        }
        
        #pragma region Deleting Nodes Algorithms
        void evictChildren(Node<Type>* node)
        {
            if(!node)
                return;
            
            evictChildren(node->right);
            evictChildren(node->left);

            node->right = nullptr;
            node->right = nullptr;
            node = nullptr;
        }

        void deleteNodes()
        {
            root->right = nullptr;
            root->left = nullptr;
        }

        #pragma endregion
    public:
        Bst(): root(nullptr){}

        Bst(Node<Type>* root): root(root){}

        ~Bst()
        {
            delete root;
        }
        
        Node<Type>* get_root()
        {
            return root;
        }

        Codes::codes insert(Type const DATA, bool reverse)
        {
            if (SearchNodes(root, DATA, true))
                return Codes::INSERT_AlEXISTS;

            root = insertNode(root, DATA, reverse);
            return Codes::INSERT_SUCCESS;
        }

        vector<Type> show()
        {
            vector<Type> container;
            container.clear();

            if (!root)
                return container;

            inOrder(root, container);
            return container;
        }

        int countNodes()
        {
            if (!root)
                return -1;

            int counter = 0;
            inOrder(root, counter);
            return counter;
        }
        
        void deleteChildren()
        {
            if (!root)
                return;
            evictChildren(root->right);
            root->right = nullptr;

            evictChildren(root->left);
            root->left = nullptr;
        }

};