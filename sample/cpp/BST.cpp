#include <iostream>
#include <queue>
#include <vector>
using namespace std;
template<typename T>
class Node{
    public:
        T data;
        Node* right;
        Node* left;
        Node(T data) : data(data) , right(nullptr) , left(nullptr){}
};
template<typename T>
class Tree{
    private:
        Node<T>* root;
        Node<T>* insert(Node<T>* root , T input_data){
            if(!root)
                return new Node<T>(input_data);
            queue<Node<T>*> que;
            que.push(root);
            for(; !que.empty() ;){
                Node<T>* node = que.front();
                que.pop();
                if(!node->left){
                    node->left = new Node<T>(input_data);
                    break;
                }else{
                    que.push(node->left);
                }
                if(!(node->right)){
                    node->right = new Node<T>(input_data);
                    break;
                }else{
                    que.push(node->right);
                }
            }
            return root;
        }
        Node<T>* sort_insert(Node<T>*  node, T input_data){
            if(!node)
                return new Node<T>(input_data);
            if(input_data < node->data)
                node->left = insert(node->left , input_data);
            else
                node->right = insert(node->right , input_data);
            return node;
        }
        void vec_store(Node<T>* node , vector<T>& container, int &i){
            if(node){
                container.push_back(node->data);
                vec_store(node->left , container, i);
                vec_store(node->right, container, i);
            }
        }
        void pre_order(Node<T>* node){
            if(node){
                cout << node->data << '\t';
                pre_order(node->left);
                pre_order(node->right);
            }
        }
        void in_order(Node<T>* node){
            if(node){
                in_order(node->left);
                cout << node->data << '\t';
                in_order(node->right);
            }
        }
        void post_order(Node<T> *node){
            if(node){
                post_order(node->left);
                post_order(node->right);
                cout << node->data << '\t';
            }
        }
        auto find_median(vector<T>& container , int size){
            int i,j,min_index;
            for(i = 0 ; i < size -1 ; i++){
                min_index = i;
                for(j = i+1 ; j < size ; j++){
                    if(container[j] < container[min_index])
                        min_index = j;
                }
                if(min_index != i)
                    swap(container[min_index] , container[i]);
            }
            if(size%2 != 0)
                return container[size/2];
            else
                return container[(size+1)/2];
        }
        void search(Node<T>* root , T srch){
            vector<T> container;
            int i = 0;
            vec_store(root , container , i);
            for(auto iter : container){
                if(iter == srch){
                    system("color 0a");
                    cout << "Value has been found!" << endl;
                    return;
                }
            }
            cout << "Your value was NOT found!" << endl;
            system("color 0c");
        }
        Node<T>* sort(Node<T> *root){
            vector<T> container;
            int i = 0;
            vec_store(root , container , i);
            auto size = container.size();
            Tree<T> newtree;
            newtree.root = sort_insert(newtree.root , find_median(container , size));
            for(auto iter : container){
                if(iter == newtree.root->data)
                    continue;
                else
                    newtree.root = sort_insert(newtree.root , iter);
            }
            return newtree.root;
        }
        Node<T>* delete_node(Node<T> *root, T value){
            vector<T> container;
            int i = 0;
            vec_store(root , container , i);
            //checks if the value was in the container or not( 1 : True , 0 : False)
            i = 0;
            for(unsigned int iter = 0 ; iter < container.size() ; iter++){
                if(container[iter] == value){
                    i = 1;
                    container.erase(container.begin() + iter);
                }
            }
            if(i){
                system("color 0a");
                cout << "Element was found and Deleted!" << endl;
                Tree<T> newtree;
                for(auto iter : container){
                    newtree.root = insert(newtree.root , iter);
                }
                return newtree.root;
            }else{
                system("color 0c");
                cout << "Element was NOT found!" << endl;
                return root;    
            }
        }
    public:
        Tree() : root(nullptr){}
        void insert(){
            cout << "Enter your data : ";
            try{
                T input_data;
                cin >> input_data;
                fflush(stdin);
                if(cin.fail()){
                    cin.clear();
                    throw input_data;
                }
                system("color 0a");
                root = insert(root , input_data);
            }catch(...){
                system("color 0c");
                cout << "Invalid input...Returning to main menu..." << endl;
            }
        }
        void show(){
            if(!root){
                cout << "Your Tree is Empty!" << endl;
                system("color 0c");
                return;
            }
            int option;
            while(true){
                system("cls & color 0d");
                cout << "------------ DISPLAY ------------\n1. PreOrder (VLR)\n2. InOrder (LVR)\n3. PostOrder (LRV)\n4. Return\nSelect an option : ";
                cin >> option;
                fflush(stdin);
                system("cls");
                switch(option){
                    case 1:
                        pre_order(root);
                break;
                    case 2:
                        in_order(root);
                break;
                    case 3:
                        post_order(root);
                break;
                    case 4:
                        return;
                break;
                    default:
                        cout << "Invalid input..." << endl;
                }
                cout << endl;
                system("color 0a & pause");
            }
        }
        void search(){
            system("color 0e");
            if(!root){
                cout << "Your Tree is Empty!" << endl;
                return;
            }
            T srch;
            try{
                cout << "Enter the Value you'd like to search for : ";
                cin >> srch;
                fflush(stdin);
                if(cin.fail()){
                    cin.clear();
                    throw srch;
                }
            }catch(T srch){
                system("color 0c");
                cout << "Invalid input...Returning to main menu..." << endl;
                return;
            }
            system("cls");
            search(root, srch);
        }
        void sort(){
            //I sorted the tree by setting the midian of the values in root and everything else gets inserted as if its a Binary Search Tree.
            if(!root){
                cout << "Your Tree is Empty!" << endl;
                return;
            }else if(!root->right && !root->left){
                cout << "Please add more data to your tree!" << endl;
                return;
            }
           root = sort(root);
        }
        void delete_node(){
            if(!root){
                system("color 0c");
                cout << "Your Tree is Empty!" << endl;
            }
            T value;
            system("color 09");
            cout << "Enter the Value you'd like to remove from your Tree : ";
            try{
                cin >> value;
                fflush(stdin);
                if(cin.fail())
                    throw value;
            }catch(T value){
                system("color 0c");
                cout << "Invalid input...Returning to main menu..." << endl;
            }
            system("cls");
            root = delete_node(root , value);
        }
};
template<typename T>
void main_menu(Tree<T> tree);
int main()
{
    int option;
    while(true){
        system("cls & color 02");
        cout << "------------- TYPE MENU -------------\n1. INT\n2. DOUBLE\n3. FLOAT\n4. STRING\n5. CHAR\nselect an option : ";
        cin >> option;
        fflush(stdin);
        system("cls & color 07");
        switch(option){
            case 1:{
                Tree<int> tree;
                main_menu(tree);
            }
        break;
            case 2:{
                Tree<double> tree;
                main_menu(tree);
            }
        break;
            case 3:{
                Tree<float> tree;
                main_menu(tree);
            }
        break;
            case 4:{
                Tree<string> tree;
                main_menu(tree);
            }
        break;
            case 5:{
                Tree<char> tree;
                main_menu(tree); 
            }
        break;
            default:
                cout << "Invalid input..." << endl;
        }
        system("pause");
    }
}
template<typename T>
void main_menu(Tree<T> tree){
    int option;
    while(true){
        system("cls & color 0b");
        cout << "------------- MAIN MENU -------------\n1. Insert\n2. Display\n3. Search\n4. sort\n5. Delete\n6. Return\nselect an option : ";
        cin >> option;
        fflush(stdin);
        system("cls & color 07");
        switch(option){
            case 1:
                tree.insert();
        break;
            case 2:
                tree.show();
        break;
            case 3:
                tree.search();
        break;
            case 4:
                tree.sort();
        break;
            case 5:
                tree.delete_node();
        break;
            case 6:
                return;
         break;
            default:
                cout << "Invalid input..." << endl;
        }
        fflush(stdin);
        system("pause");
    }
}
