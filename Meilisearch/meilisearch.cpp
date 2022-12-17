#include <iostream>
#include <vector>
#include <string>
#include <fstream>
struct Node
{
    Node() : value(),  left(nullptr), right(nullptr){}
    Node(std::string v) : value(v), left(nullptr), right(nullptr){}
    ~Node()
    {
        delete left;
        delete right;
    }

    std::string value;
    Node* left;
    Node* right;
};

void insert(Node* node, const std::string& name, std::string_view place)
{
    if(!(place.length() > 0))
    {
        node->value = name;
        //if(place[0] == 'L')
            //node->left = new Node(name);
        //else if(place[0] == 'R')
            //node->right = new Node(name);
        // else 
        // {
        //     std::cout << "1invalid input : \"" << place << "\"" << place[0] << "\"\n";
        //     abort();
        // }
        return;
    }
    else
        switch(place[0])
        {
            case 'L':
                if(!node->left)
                    node->left = new Node();
                insert(node->left, name, std::string_view(place.begin()+1, place.end()));
                return;
            case 'R':
                if(!node->right)
                    node->right = new Node();
                insert(node->right, name, std::string_view(place.begin()+1, place.end()));
                return;
            default:
            std::cout << "2invalid input : \"" << place << "\"" << place[0] << "\"\n";
                abort();
        }
}


void optimize(Node* node)
{
    if(node->left && !node->right && node->left->value.length() == 0)
    {
        Node* tmp = node->left;
        node->left = tmp->left;
        node->right = tmp->right;
        tmp->left = nullptr;
        tmp->right = nullptr;
        delete tmp;
    }    
    else if(node->right && !node->left && node->right->value.length() == 0)
    {
        Node* tmp = node->right;
        node->left = tmp->left;
        node->right = tmp->right;
        tmp->left = nullptr;
        tmp->right = nullptr;
        delete tmp;
    }
    else
    {
        if(node->left)
            optimize(node->left);
        if(node->right)
            optimize(node->right);
    }

}


void printBT(const std::string& prefix, const Node* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "\303\304\304" : "\300\304\304" );

        // print the value of the node
        std::cout << node->value << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "\263  " : "   "), node->left, true);
        printBT( prefix + (isLeft ? "\263  " : "   "), node->right, false);
    }
}

std::string find_first(Node* node, int& dist)
{
    if(node->value.length() > 0)
        return node->value;
    
    int leftD = dist+1;
    int rightD = dist + 1;
    std::string vl;
    std::string vr;
    
    if(node->left)
    {
        vl = find_first(node->left,leftD);
        std::cout << vl << " - " << leftD << "\n";
    }
    if(node->right)
    {
        vr = find_first(node->right, rightD);
        std::cout << vr << " - " << rightD << "\n";
    }

    if(rightD < leftD)
    {
        dist = rightD;
        return vr;
    }
    
    dist = leftD;
    return vl;
}

int main()
{
    std::ifstream file("input");
    if (!file.is_open())
    {
        std::cout << "file not found\n";
        return -1;
    }

    Node root;
    
    std::string line = "";
    while (std::getline(file, line))
    {
        auto dash = line.find_first_of("-");
        auto name = line.substr(0, dash - 1);
        auto path = line.substr(dash + 2);
        
        insert(&root, name, path);
    }

    optimize(root.left);
    optimize(root.right);

    int d = 0;
    //printBT("", &root, false);
    auto found = find_first(&root, d);
    std::cout << "found : " << found << "\n";
}