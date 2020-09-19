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
    for (int i = 0; i < expression.length(); i++)
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
    for (int i = 0; i < infix.length(); i++)
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
    for (int i = 0; i < postfix.length(); i++)
    {
        if (isdigit(postfix[i]))
        {
            st.push(int(postfix[i]) - 48);
        }
        else
        {
            //Read the second operand and pop
            right = st.top();
            st.pop();
            //Read the first operand and pop
            left = st.top();
            st.pop();
            result = operation(left, right, postfix[i]);
            st.push(result);
        }
    }
    return st.top();
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

    string check = "8-{(7+0-1)}-3";
    string postfilx;

    if (!checkBalanced(check))
    {
        cout << "Not balanced" << endl;
    }
    else
    {
        postfilx = infixToPostfix(check);
    }


    cout << postfilx << endl;





    inFS.close();
    outFS.close();

    return 0;

}

