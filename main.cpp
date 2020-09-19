#include <iostream>
#include<fstream>
#include<sstream>
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

//Create a function to return the operator precedence
int precedence(char operators)
{
    switch (operators)
    {
    case '+':
        return 1;
        break;

    case '-':
        return 1;
        break;

    default:
        return 0;
    }
}

//Creat a function to check if the expression is balanced
bool checkBalanced(string expression)
{
    stack<char> st;

    //Traversing the Expression
    for (unsigned int i = 0; i < expression.length(); i++)
    {
        //Push the opening bracket in the stack
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[')
        {
            st.push(expression[i]);
        }
        else if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']')
        {
            //If the stack is empty, the top does not pair with expression[i]
            if (st.empty())
            {
                return false;
            }
            
            //Check if the parenthesis is balanced
            if (expression[i] == ')')
            {
                if (st.top() == '(')
                {
                    st.pop();
                }
                else
                {
                    return false;
                }
            }
            else if (expression[i] == '}')
            {
                if (st.top() == '{')
                {
                    st.pop();
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if (st.top() == '[')
                {
                    st.pop();
                }
                else
                {
                    return false;
                }
            }
        }
    }

    //Check if the stack is empty (if so the expression is balanced)
    if (!st.empty())
    {
        return false;
    }

    return true;
}

//Create a function to convert infix to postfix expression
string infixToPostfix(string infix)
{
    stack<char> st;
    string postfix = "";

    //Traversing the Expression
    for (unsigned int i = 0; i < infix.length(); i++)
    {
        //If infix[i] is a digit, add it to the string
        if (isdigit(infix[i]))
        {
            postfix += infix[i];
        }

        //If the infix[i] is the opening bracket, push it to the stack
        else if (infix[i] == '(' || infix[i] == '{' || infix[i] == '[')
        {
            st.push(infix[i]);
        }

        //If the infix[i] is the closing bracket, check the stack
        else if (infix[i] == ')')
        {
            while (st.top() != '(')
            {
                postfix += st.top();
                st.pop();
            }

            //Pop the opening bracket
            st.pop();
        }
        else if (infix[i] == '}')
        {
            while (st.top() != '{')
            {
                postfix += st.top();
                st.pop();
            }

            //Pop the opening bracket
            st.pop();
        }
        else if (infix[i] == ']')
        {
            while (st.top() != '[')
            {
                postfix += st.top();
                st.pop();
            }

            //Pop the opening parenthesis
            st.pop();
        }
        else
        {
            while (!st.empty() && (precedence(st.top()) >= precedence(infix[i])))
            {
                postfix += st.top();
                st.pop();
            }

            st.push(infix[i]);
        }
    }

    while (!st.empty())
    {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

//Create a function to execute operation
int operation(int first, int second, char operand)
{
    if (operand == '+')
    {
        return first + second;
    }
    else
    {
        return first - second;
    }
}

//Create a function to evaluate the postfix expression
int evaluatePostfix(string postfix)
{
    stack<int> st;
    int left;
    int right;
    int result;

    //Traversing the Expression
    for (unsigned int i = 0; i < postfix.length(); i++)
    {
        //If postfix[i] is a digit, push it to the stack
        if (isdigit(postfix[i]))
        {
            st.push(int(postfix[i]) - 48);
        }
        //If the postfix[i] is a operand, continue to do the operation
        else
        {
            //Read the second operand and pop
            right = st.top();
            st.pop();
            //Read the first operand and pop
            left = st.top();
            st.pop();

            //Call function operation to get the result
            result = operation(left, right, postfix[i]);
            //Push it to the stack
            st.push(result);
        }
    }

    return st.top();
}

//Create a function to check for colon
bool hasColon(string str)
{
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (str[i] == ':')
        {
            return true;
        }
    }
    return false;
}

//Create a function to read password
int readPassword(string str, istringstream& inSS)
{
    string bin;
    string password_str;
    int password;

    //Clear input string stream
    inSS.clear();

    //Using input string stream to read password line
    inSS.str(str);

    //Get rid of the useless infomation
    getline(inSS, bin, ':');

    //Read password
    getline(inSS, password_str);
    password = stoi(password_str);

    return password;
}

//Create a function to read expression to Scarlet Linked list



// ------------------------------------------------ MAIN FUNCTION ----------------------------------------------------
int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output"
    //string input = am.get("input");
    //string output = am.get("output");

    //Test
    string input = "input11.txt";
    string output = "output11.txt";

    ifstream inFS;
    ofstream outFS;
    istringstream inSS;

    inFS.open(input);
    outFS.open(output);

    try 
    {
        //Throw exception if the file doesn't exist
        if (!inFS.is_open())
        {
            throw runtime_error("ERROR: File not found");
        }

        //Throw exception if the file is empty
        if (inFS.peek() == EOF)
        {
            throw runtime_error("ERROR: File is empty");
        }

        string line;
        string expression;
        int password;
        digitList Scarlet;
        digitList Travis;

        while (getline(inFS, line))
        {
            //Check if the line is empty
            if (line.empty())
            {
                continue;
            }

            //Only password line contains colon
            if (hasColon(line))
            {
                password = readPassword(line, inSS);
            }

            else if (line == "Scarlet")
            {
                while (getline(inFS, expression))
                {
                    //Check if the line is empty
                    if (line.empty())
                    {
                        continue;
                    }

                    if (expression == "Travis" || expression == "Scarlet")
                    {
                        break;
                    }

                    //If the line contains colon, read the password directly
                    if (hasColon(expression))
                    {
                        password = readPassword(expression, inSS);
                        break;
                    }

                    //Read in the linked list
                    cout << "Scarlet" << endl;

                }
            }

            else if (line == "Travis")
            {
                while (getline(inFS, expression))
                {
                    if (expression == "Scarlet" || expression == "Travis")
                    {
                        break;
                    }

                    //If the line contains colon, read the password directly
                    if (hasColon(expression))
                    {
                        password = readPassword(expression, inSS);
                        break;
                    }

                    //Read in the linked list
                    cout << "Travis" << endl;
                }
            }
        }






    }
    catch (runtime_error & e)
    {
        outFS << e.what() << endl;
    }

    //string check = "8-{(7+0-1)}-3";
    //string postfix;
    //int result;

    //if (!checkBalanced(check))
    //{
    //    cout << "Not balanced" << endl;
    //}
    //else
    //{
    //    postfix = infixToPostfix(check);
    //}

    //result = evaluatePostfix(postfix);
    //cout << postfix << ": " << result << endl;


    //string test = "1234:";
    //cout << hasColon(test) << endl;


    //Close all files
    inFS.close();
    outFS.close();

    return 0;

}

