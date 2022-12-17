#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <ranges>
#include <algorithm>


struct Node
{
    enum class Type
    {
        dir,
        file
    };

    Type type;
    std::string name;
    mutable size_t size;
    Node* parent;
    std::vector<std::unique_ptr<Node> > nodes;

    Node(std::string n, Type t, Node* p = nullptr): name(n), type(t), parent(p), size(0){}
    virtual size_t getSize() const = 0;
    virtual ~Node() = default;
};

struct Dir : public Node
{

    Dir(std::string name, Node* p = nullptr): Node(name, Type::dir, p){}
    virtual ~Dir() override = default;

    virtual size_t getSize() const override
    {
        if(size == 0)
            for(const auto& it : nodes)
                size += it->getSize();
        return size;
    }
};

struct File: public Node
{

    File(std::string n, size_t s, Node* p = nullptr): Node(n, Type::file, p){size = s;}
    virtual ~File() override = default;

    virtual size_t getSize()const  override
    {
        return size;
    }
};



void getList(Node* n, std::vector<Node*>& list)
{
    if(n->type == Node::Type::file)
        return;

    for(auto& i : n->nodes)
    {
        list.emplace_back(i.get());
    }
    
    for(auto& i : n->nodes)
    {
        getList(i.get(), list);
    }
}


size_t search(Node* n)
{
    if(n->type == Node::Type::file)
        return 0;

    auto size = n->getSize();
    size_t sumOfSizes = 0;
    
    for(const auto & it : n->nodes)
    {
        sumOfSizes += search(it.get());
    }
    if(size <= 100000)
        return sumOfSizes + size;

    return sumOfSizes;
}


int main()
{
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cout << "file not found\n";
        return -1;
    }

    std::unique_ptr<Node> root = std::make_unique<Dir>("/");
    Node* currentNode = root.get();;

    std::string line;
    while(file >> line)
    {
        if(line == "$")
        {
            std::string command;
            file >> command;
            if(command == "cd")
            {
                std::string dir;
                file >> dir;
                if(dir == "/")
                    currentNode = root.get();
                else if(dir == "..")
                    currentNode = currentNode->parent;
                else
                {
                    for(const auto& it : currentNode->nodes)
                    {
                        if(it->name == dir)
                            currentNode = it.get();
                    }
                }

            }
            else if(command == "ls")
            {
                continue;
            }
        }
        else
        {
            std::string name;
            if(line == "dir")
            {
                file >> name;
                currentNode->nodes.emplace_back(std::make_unique<Dir>(name, currentNode));
            }
            else
            {
                size_t size = std::stoll(line);
                file >> name;
                currentNode->nodes.emplace_back(std::make_unique<File>(name, size, currentNode));
            }
        }
    }

    auto result = search(root.get());

    std::cout << "niestety : " << result << "\n";

    auto size = root->getSize();
    std::cout << "size of / : " << size << "\n"; 
    std::cout << "free space : " << 70000000 - size << "\n";
    std::cout << "need to free : " << 30000000 - (70000000 - size) << "\n";

    size = 30000000 - (70000000 - size);

    std::vector<Node*> list;
    getList(root.get(), list);

    std::ranges::sort(list, [](const Node* l, const Node* r){return l->getSize() < r->getSize();});

    for(auto& it : list)
        std::cout << it->name << " | " << it->getSize() << "\n";

}
