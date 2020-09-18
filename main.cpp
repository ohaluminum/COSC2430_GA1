#include <iostream>
#include<fstream>
#include <stack>
#include "ArgumentManager.h"

using namespace std;

struct digit
{
    int info = 0;
    digit* next = nullptr;
};

class digitList
{
private:
    digit* head;
    
public:
    //Constructor
    digitList()
    {
        head = nullptr;
    }



};

//Creat a function to check if the expression is balanced
bool checkBalanced(string expression)
{
    stack<char> st;











}




int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output"
    //string input = am.get("input");
    //string output = am.get("output");

    //Test
    string input = "input13.txt";
    string output = "output13.txt";

    ifstream inFS;
    ofstream outFS;

    inFS.open(input);
    outFS.open(output);



}

