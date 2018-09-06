/*************************************************************************
 * Description:  This file contains the following routines /classes ......
 * and is responsible for .......
 *
 * Contact:
 * Neil Ashtekar    (nca5096@psu.edu)    (8143213010)
 *
 * Revision History
 *
 * Who         Date     Issue    Description
 * ------       ----     ----      -----------------------
 * nca5096      3-18-18  None      Initial Version
 *
 **********************************************************************/

///////////////////////////////////////////////////////////////
// INCLUDES
///////////////////////////////////////////////////////////////

// #include "stdafx.h" // needed for VS
#include <stdio.h>
#include <string>
//#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////
// CLASS DEFINITION
///////////////////////////////////////////////////////////////
class Stack
{
private:
    struct node
    {
        int data;                      // data
        node* next;                    // pointer to next element (element underneath current element in stack)
    };
    node* top;                         // stack equivalent of head
    node* curr;                        // current node
    node* temp;                        // temporary node
    
public:
    Stack()                             // constructor
    {
        temp = curr = top = NULL;       // starts w nothing on stack
    }
    void push(int onto);                // to push element onto stack
    int pop();                          // to pop top element off of stack
    void printTop();                    // to print elements in stack
    int size();
};

///////////////////////////////////////////////////////////////
// FUNCTION DEFINITIONS (in stack class)
///////////////////////////////////////////////////////////////

//
// pushes element onto stack
//
void Stack::push (int onto)
{
    temp = top;                    // temporarily hold the top value in temp
    
    top = new node;                // top points to newly created node
    
    top -> data = onto;            // data stored in top: data pushed onto stack
    
    top -> next = temp;            // the next pointer in top points to the previous top (previous top is now the second element)
}

//
// pops element off of stack
//
int Stack::pop()
{
    int popped = top -> data;     // get data in top (number to be taken off of stack)
    
    temp = top;                   // create temp node pointer, so we can delete address
    
    top = top -> next;            // reassign top
    
    delete temp;                  // delete old address
    
    return popped;                // return number taken off of stack
}

//
// prints top of stack
//
void Stack::printTop()
{
    cout << top -> data << endl;
}

//
// returns size (how many elements) in stack, for error checking
//
int Stack::size()
{
    int count = 0;
    
    if (top == NULL)        // if there is no first element -- list is empty (note: no else after, because nothing wil print regardless)
    {
        return count;
    }
    
    curr = top;             // initialize curr to point to start of list
    
    while (curr != NULL)     // while not the end of the list, print the data in the node and then move to next node
    {
        count ++;
        
        curr = curr -> next; // moves to next element
    }
    
    return count;
}

///////////////////////////////////////////////////////////////
// FUNCTION DEFINITIONS (not in stack class)
///////////////////////////////////////////////////////////////

//
// function not in stack class, to be used in main to test if a string is an int
//
bool isNumeric(string input)
{
    string num = "0123456789";
    
    int count = 0;
    
    for (int i = 0; i < input.length(); i ++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (input[i] == num[j])
            {
                count ++;
            }
        }
    }
    if (count == input.length())
    {
        return true;
    }
    else
    {
        return false;
    }
}
///////////////////////////////////////////////////////////////
// MAIN FUNCTION
///////////////////////////////////////////////////////////////
int main()
{
    Stack st;
    
    cout << "Please enter your operands or operators with spaces between each, and hit enter when done. Type 'exit' to exit.\n";
    cout << "For example: 5 6 +\n\n";
    
    string input;
    
    //
    // loop always running until user enters exit, in which case just return 0
    //
    while (true)
    {
        cout << "Equation: ";
        
        bool end = false;              // flag to end inner while loop
        
        bool invalid = false;          // flag for invalid input
        
        while (end == false)
        {
            cin >> input;
            
            //
            // if the user enters 'exit', end program
            //
            if (input == "exit" || input == "Exit")
            {
                return 0;
            }
            
            //
            // if input string is an int
            //
            if (isNumeric(input))
            {
                st.push(int(stoi(input)));
            }
            //
            // else if input string is an operator
            //
            else if (input == "+" || input == "-" || input == "*" || input == "/" || input == "^")
            {
                if (st.size() < 2)
                {
                    cout << "Invalid input!\n";
                    
                    invalid = true;
                }
                else
                {
                    int left, right, result;
                    
                    right = st.pop();   // right is first one to be popped (1 higher on stack than right)
                    left = st.pop();    // left is second to be popped
                    
                    if (input == "+")
                    {
                        result = left + right;
                    }
                    else if (input == "-")
                    {
                        result = left - right;
                    }
                    else if (input == "*")
                    {
                        result = left * right;
                    }
                    else if (input == "/")
                    {
                        if (right != 0)
                        {
                            result = left/right;
                        }
                        else
                        {
                            cout << "Invalid input -- can't divide by 0!\n";
                            
                            invalid = true;
                        }
                    }
                    else if (input == "^")
                    {
                        result = pow(left, right);
                    }
                    st.push(result);    // push result onto stack, result will be only one remaining
                }
            }
            //
            // else the user has entered something invalid, not enter key
            //
            else if (cin.get() != '\n')
            {
                cout << "Invalid input!\n";
            }
            
            //
            // if user hits return, end equation line
            //
            if (cin.get() == '\n')
            {
                if (invalid == false)
                {
                    cout << "Result: ";
                    st.printTop();
                }
                end = true;
            }
        }
    }
}

/*************************************************************************************************************************
 LIMITATIONS
 - error checked for starting cases (ex: dividing by 0, entering operator before operand initially) but did not check all
 extended cases (ex: multiple lines entered, then entering possibly invalid input)
 **************************************************************************************************************************/

