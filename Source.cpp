#include<iostream>
#include<string>
#include<fstream>

using namespace std;




class person
{

public:
    string Name;
    string parent;
    string sex;
    person* left;
    person* right;
    person()
    {
        left = right = nullptr;
        Name = "";
        parent = "";
        sex = "";
    }

    ~person() = default;


    void getData() 
    {
        string fn;
        cout << "enter the name of file: ";
        cin >> fn;
        ifstream fin(fn);
        if (fin.is_open()) {
            fin >> Name;
            fin >> parent;
            fin >> sex;

        }
        else {
            cout << "file no found" << endl;
        }



    }





};


void ignoreLine()
{
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}


class familyTree
{
private:
public:

    person* root;
 

    familyTree()
    {
        root = nullptr;
    }

  

    person* traverseLeft(person* ptr, const string& person)
    {
        ptr = ptr->left;

        while (ptr != nullptr)
        {
            if ((ptr->Name) == person) {
                return ptr;
            }

            else if (traverseRight(ptr, person) != nullptr)
            {
                return traverseRight(ptr, person);
            }
            else
            {
                ptr = ptr->left;
            }
        }
        return nullptr;
    }

    person* traverseRight(person* ptr, const string& person)
    {

        ptr = ptr->right;

        while (ptr != nullptr)
        {
            if ((ptr->Name) == person)
            {
                return ptr;
            }
            else if (traverseLeft(ptr, person) != nullptr)
            {
                return traverseLeft(ptr, person);
            }
            else
                ptr = ptr->right;
        }
        return nullptr;
    }


    void addNewPerson()
    {
        person* p = new person;
        p->getData();


        if (root == nullptr)
        {
            cout << "\nFirst person added to the family!" << endl;
            root = p;
        }

        else // if there exists a person in the tree, add the new person as a relative to a previous
        {

            person* parent = search(p->parent);
            if (parent != NULL)  //tests if the person entered is found int the tree, if yes it continues.
            {
                if (parent->left != NULL && parent->right != NULL) {
                    cout << parent->Name << " has already both childs" << endl;
                    return;
                }
                if (parent->left == NULL) {
                    parent->left = p;
                    cout << p->Name << " is added as a child of " << parent->Name << endl;
                }
                else {
                    parent->right = p;
                    cout << p->Name << " is added as a child of " << parent->Name << endl;
                }


            }

            else {
                cout << "parent not found" << endl;
            }
        }
    }

    void printInOrder(person* person,int space) //print its persons using in order traversal
    {
        auto count = 7; //using count for how much space between generations (horizontal)
        space =space + count;

        if (person != nullptr)
        {
            if (person->left != nullptr)
            {
                printInOrder(person->left,space);
            }

            cout << endl;
            for (int i = count; i < space; i++)
                cout << " ";

            cout << person->Name << "\n";
       
            if (person->right != nullptr)
            {
                printInOrder(person->right,space);
            }
        }

        else
        {
            cout << "No tree exist!" << endl;
            ignoreLine(); // "pause" the program until the user press "Enter"
            return;
        }
    }

    person* search(string  per) // to search for a person
    {
        person* ptr = root;

        if ((ptr->Name) == per)
        {
            return ptr;
        }

        else if (traverseRight(root, per) != nullptr)
        {
            return traverseRight(root, per);
        }

        else if (traverseLeft(root, per) != nullptr)
        {
            return traverseLeft(root, per);
        }

        else
        {
            cout << "\nNo person found with the given name" << endl;
            ignoreLine(); // "pause" the program until the user press "Enter"
            return nullptr;
        }
    }

    void show(person* ptr) // to show the information of a particular person
    {
        cout << "Name: " << ptr->Name << endl;
        cout << "Sex: " << ptr->sex << endl;
        cout << "Parent: " << ptr->parent << endl;
        if (ptr->left != NULL) {

            cout << "child 1: " << ptr->left->Name << endl;
        }
        else if (ptr->right != NULL) {
            cout << "child 2: " << ptr->right->Name << endl;
        }
    }
};



void showMainMenu()
{
    cout << "Welcome" << endl;
    cout << "Please enter a number for your choice below:\n" << endl;
    cout << "(1) Add new person to tree" << endl;
    cout << "(2) Find relationShip for a person" << endl;
    cout << "(3) Print complete family-tree" << endl;
    cout << "(4) Search" << endl;
    cout << "(0) Quit" << endl;
    cout << "\nYour choice: " << endl;
}

int main()
{
    familyTree fT;

    int option, exit = 0;
    string temp, str;
    person* p;

    while (exit == 0)
    {
        showMainMenu();
        cin >> option;

        while (cin.fail())
        {
            ignoreLine();
            cout << "\nOnly a number between 0 and 10 is allowed: ";
            cin >> option;
        }

        switch (option)
        {
        case 1:
            fT.addNewPerson();
            break;
        case 2:
            cin.ignore();
            cout << "Enter name of person to show information: ";
            cin >> temp;
           fT.show(fT.search(temp));
            break;
        case 3:
            fT.printInOrder(fT.root,0);
            break;
        case 4:
            cin.ignore();
            cout << "Enter name of person to show information: ";
            cin >> temp;
            fT.show(fT.search(temp));
            break;
        case 0:
            exit = 1;
            break;
        }
        cout << "\nPress enter to continue.." << endl;
        ignoreLine();
    }
    return 0;
}