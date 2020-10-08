#include <iostream>
#include<fstream>
#include<sstream>
#include <stack>
#include <string>
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
    int size;
    
public:
    //Constructor
    digitList()
    {
        head = nullptr;
        size = 0;
    }

    //Getter function
    digit* getHead()
    {
        return head;
    }
    
    //Add digit at the end of linked list using recursion
    void addAtEndRecursively(digit* curr, int info)
    {
        if (head == nullptr)
        {
            digit* temp = new digit;
            temp->info = info;
            temp->next = nullptr;

            head = temp;
            size++;
            return;
        }

        if (curr->next == nullptr)
        {
            digit* temp = new digit;
            temp->info = info;
            temp->next = nullptr;

            curr->next = temp;
            size++;
            return;
        }

        addAtEndRecursively(curr->next, info);
    }

    //Search if the linked list contains negative number (return the first negative number)
    int searchNegative(digit* curr)
    {
        //If linked list is empty or reach the end of the linked list
        if (curr == nullptr)
        {
            return 0;
        }

        //If the number is negative, return the number
        if (curr->info < 0)
        {
            return curr->info;
        }

        return searchNegative(curr->next);
    }

    //Delete specific value by index in the linked list
    bool deleteByPos(digit* curr, int index)
    {
        //If index is invalid
        if (index < 0 || index >= size)
        {
            return false;
        }

        //If linked list is empty or reach the end of the linked list
        if (curr == nullptr)
        {
            return false;
        }

        //Special case: digit to be deleted is the first digit
        if (index == 0)
        {
            head = head->next;
            delete curr;
            size--;
            return true;
        }

        //Normal case: degit to be deleted is not the first digit
        if (curr->next != nullptr && index == 1)
        {
            //Update the pointer
            digit* temp = new digit;
            temp = curr->next;
            curr->next = temp->next;
            delete temp;
            size--;
            return true;
        }

        return deleteByPos(curr->next, index - 1);
    }

    //Delete specific value by value in the linked list
    bool deleteByValue(digit* curr, int info)
    {
        //If linked list is empty or reach the end of the linked list
        if (curr == nullptr)
        {
            return false;
        }

        //Special case: digit to be deleted is the first digit
        if (curr->info == info)
        {
            head = head->next;
            delete curr;
            size--;
            return true;
        }

        //Normal case: degit to be deleted is not the first digit
        if (curr->next != nullptr && curr->next->info == info)
        {
            //Update the pointer
            digit* temp = new digit;
            temp = curr->next;
            curr->next = temp->next;
            delete temp;
            size--;
            return true;
        }

        return deleteByValue(curr->next, info);
    }

    //Using insertion sort to sort sub list
    void insertionSort()
    {
        //If the list is empty or has only one digit, no need to sort
        if (head == nullptr || head->next == nullptr)
        {
            return;
        }

        //Create a dummy pointer (before head)
        digit* dummy = new digit;
        dummy->next = head;

        digit* curr = head;           //For unsorted list
        digit* prev = nullptr;        //For sorted list
        digit* temp = nullptr;        //For storing digit that need to be moved

        //Check the condition (make sure curr digit can compare to next digit)
        while (curr != nullptr && curr->next != nullptr)
        {
            //If these two digits are in the right order, move to next digit
            if (curr->info <= curr->next->info)
            {
                curr = curr->next;
            }
            else
            {
                //Use temp to store the digit that need to move
                temp = curr->next;
                curr->next = curr->next->next;

                //Traverse the sorted list to see where to stop
                prev = dummy;
                while (prev->next->info <= temp->info)
                {
                    prev = prev->next;
                }

                //If the prev pointer ddin't move, temp will be insert at the beginning of the list
                if (prev == dummy)
                {
                    temp->next = head;
                    head = temp;
                    dummy->next = head;
                }
                else
                {
                    //Update the link
                    temp->next = prev->next;
                    prev->next = temp;
                }
            }
        }
    }

    void mergeSortedList(digit* first, digit* second)
    {
        //Make sure both lists are not empty
        while (first != nullptr && second != nullptr)
        {
            if (first->info <= second->info)
            {
                addAtEndRecursively(this->getHead(), first->info);
                first = first->next;
            }
            else if (first->info > second->info)
            {
                addAtEndRecursively(this->getHead(), second->info);
                second = second->next;
            }
        }

        //If the first list is not empty
        while (first != nullptr)
        {
            addAtEndRecursively(this->getHead(), first->info);
            first = first->next;
        }

        //If the second list is not empty
        while (second != nullptr)
        {
            addAtEndRecursively(this->getHead(), second->info);
            second = second->next;
        }
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
        cout << "YEA" << endl;
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

//Remove space from a string
string removeSpace(string line)
{
    string newStr = "";

    for (unsigned int i = 0; i < line.length(); i++)
    {
        if (line[i] != ' ')
        {
            newStr += line[i];
        }
    }

    return newStr;
}

// ------------------------------------------------ MAIN FUNCTION ----------------------------------------------------

int main(int argc, char* argv[])
{
    ArgumentManager am(argc, argv);

    //Get the filename of argument name "input" and "output"
    //string input = am.get("input");
    //string output = am.get("output");

    //Test
    string input = "input19.txt";
    string output = "output19.txt";

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

        string line = "";
        string currentUser = "";
        string bin = "";
        string password = "";
        int numOfInvalid = 0;
        int result = 0;
        int negativeNum = 0;
        digitList ScarletList;
        digitList TravisList;

        // ----------------------------------------------------------- ADD DIGIT -----------------------------------------------------

        while (getline(inFS, line))
        {
            //Check if the line is empty
            if (line.empty())
            {
                continue;
            }

            //Remove space in the line
            line = removeSpace(line);

            //Only password line contains colon
            if (hasColon(line))
            {
                //Clear input string stream
                inSS.clear();

                //Using input string stream to read password line
                inSS.str(line);

                //Get rid of the useless infomation
                getline(inSS, bin, ':');

                //Read password
                getline(inSS, password);
            }

            else if (line == "Scarlet")
            {
                currentUser = "Scarlet";
            }

            else if (line == "Travis")
            {
                currentUser = "Travis";
            }
            else
            {
                //If the expression is balanced, then evaluate the expression
                if (checkBalanced(line))
                {
                    cout << line << endl;

                    for (int i = 0; i < line.length(); i++)
                    {
                        cout << i << " " << line[i] << endl;
                    }

                    line = infixToPostfix(line);
                    cout << line << endl;
                    cout << line.length() << endl;


                    for (int j = 0; j < line.length(); j++)
                    {
                        cout << j << " " << line[j] << endl;
                    }



                    result = evaluatePostfix(line);

                    if (currentUser == "Scarlet")
                    {
                        ScarletList.addAtEndRecursively(ScarletList.getHead(), result);
                    }
                    else if (currentUser == "Travis")
                    {
                        TravisList.addAtEndRecursively(TravisList.getHead(), result);
                    }
                }
                else
                {
                    numOfInvalid++;
                }
            }
        }

        // ---------------------------------------------------- DELETE NEGATIVE ---------------------------------------------------

        bool isDelete = false;

        negativeNum = ScarletList.searchNegative(ScarletList.getHead());

        //If the searchNegative function return 0, it means there is no negative number in the linked list 
        while (negativeNum != 0)
        {
            //Delete negative number
            ScarletList.deleteByValue(ScarletList.getHead(), negativeNum);

            //Delete correspond positive number
            isDelete = ScarletList.deleteByValue(ScarletList.getHead(), abs(negativeNum));

            //If can not find number in Scarlet's list, try to find it in Travis's list 
            if (!isDelete)
            {
                TravisList.deleteByValue(TravisList.getHead(), abs(negativeNum));
            }

            negativeNum = ScarletList.searchNegative(ScarletList.getHead());
        }

        negativeNum = TravisList.searchNegative(TravisList.getHead());

        //If the searchNegative function return 0, it means there is no negative number in the linked list 
        while (negativeNum != 0)
        {
            //Delete negative number
            TravisList.deleteByValue(TravisList.getHead(), negativeNum);

            //Delete correspond positive number
            isDelete = TravisList.deleteByValue(TravisList.getHead(), abs(negativeNum));

            //If can not find number in Travis's list, try to find it in Scarlet's list 
            if (!isDelete)
            {
                ScarletList.deleteByValue(ScarletList.getHead(), abs(negativeNum));
            }

            negativeNum = TravisList.searchNegative(TravisList.getHead());
        }

        // -------------------------------------------------------- PRINT ORIGINAL -----------------------------------------------
        digit* temp = new digit;
        temp = ScarletList.getHead();

        //If the list is empty
        if (temp == nullptr)
        {
            outFS << "Scarlet: []" << endl;
        }
        else
        {
            outFS << "Scarlet: [";

            while (temp->next != nullptr)
            {
                outFS << temp->info << ", ";
                temp = temp->next;
            }

            outFS << temp->info << "]" << endl;
        }

        //Print Travis's list to the output file
        temp = TravisList.getHead();

        //If the list is empty
        if (temp == nullptr)
        {
            outFS << "Travis: []" << endl;
        }
        else
        {
            outFS << "Travis: [";

            while (temp->next != nullptr)
            {
                outFS << temp->info << ", ";
                temp = temp->next;
            }

            outFS << temp->info << "]" << endl;
        }

        // -------------------------------------------------------------- SORT LIST ----------------------------------------------------------

        ScarletList.insertionSort();
        TravisList.insertionSort();

        // -------------------------------------------------------------- MERGE LIST ----------------------------------------------------------

        digitList mergeList;
        mergeList.mergeSortedList(ScarletList.getHead(), TravisList.getHead());

        //Do not delete if no expression is invalid
        if (numOfInvalid > 0)
        {
            mergeList.deleteByPos(mergeList.getHead(), numOfInvalid);
        }

        // ------------------------------------------------------------PRINT SORTED LIST ---------------------------------------------------
        
        string decodedPassword = "";

        temp = mergeList.getHead();

        while (temp != nullptr)
        {
            decodedPassword += to_string(temp->info);
            temp = temp->next;
        }

        outFS << "Decoded passcode: ";

        for (int i = 0; i < decodedPassword.length(); i++)
        {
            outFS << "| " << decodedPassword[i] << " ";
        }

        outFS << "|" << endl;

        outFS << "Actual passcode: ";

        for (int i = 0; i < password.length(); i++)
        {
            outFS << "| " << password[i] << " ";
        }

        outFS << "|" << endl;

        if (decodedPassword == password)
        {
            outFS << "Treasure unlocked!";
        }
    }
    catch (runtime_error & e)
    {
        outFS << e.what() << endl;
    }

    inFS.close();
    outFS.close();

    return 0;
}

