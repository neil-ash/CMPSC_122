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
 * nca5096      3-16-18  None      Initial Version
 * nca5096      3-17-18  Edits     Added List class functions
 * nca5096      3-18-18  Edits     Added main function, debugged
 **********************************************************************/

///////////////////////////////////////////////////////////////
// INCLUDES
///////////////////////////////////////////////////////////////

// #include "stdafx.h" // needed for VS
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

///////////////////////////////////////////////////////////////
// CLASS DEFINITION
///////////////////////////////////////////////////////////////
class List
{
//
// variables in private
//
private:
    struct node                         // creates node data type; includes element data and pointer to next element (singly linked)
    {
        int data;
        node* next;
    };
    
    node* head;
    node* curr;
    node* temp;
    
//
// functions in public (only names, not definitions)
//
public:
    List()                              // constructor
    {
        head = curr = temp = NULL;      // initialize all variables as null
    }
    void addElementFront(int addData);
    void addElementBack(int addData);
    void insertElement(int insertIndex, int insertData);
    void deleteElement(int delData);
    void removeFront();
    void removeBack();
    int size();
    void print();
};


///////////////////////////////////////////////////////////////
// FUNCTION DEFINITIONS
///////////////////////////////////////////////////////////////

//
// adds element to front of list
//
void List::addElementFront(int addData)
{
    temp = new node;               // temp points to newly created node
    
    temp -> next = head;           // the next pointer points to head
    
    head = temp;                   // head is reassigned to point to the added element, now first in the list
    
    head -> data = addData;        // store user input as data in head
    
    cout << "The value " << addData << " was added";
}

//
// adds element to end (back) of list
//
void List::addElementBack(int addData)
{
    temp = new node;              // pointer n points to newly created node
    
    temp -> next = NULL;          // its next pointer doesn't point to anything
    
    temp  -> data = addData;      // assigns function input to data contents
    
    if (head != NULL)             // if head is pointing to something, then we have a list
    {
        curr = head;              // start at head
        
        while (curr -> next != NULL)
        {
            curr = curr -> next;  // while we aren't at the end of the list, the current pointer points to next
                                  // takes to last element in list
        }
        curr -> next = temp;      // end of list: where element to be added goes
    }
    else
    {
        head = temp;              // if head isn't pointing to anything (head points to nothing) then head points to element to be added
    }
    
    cout << "The value " << addData << " was added";
}

//
// inserts element in list
//
void List::insertElement(int insertIndex, int insertData)
{
    node* insPtr = new node;           // insPtr points to newly created node
    
    temp = curr = head;                // temp and curr pointer point to head (start of list)
    
    if (head == NULL)                  // if the list is empty
    {
        head = insPtr;                 // the head of the empty list is newly created node
        
        head -> data = insertData;     // data in head is inserted data
        
        head -> next = NULL;           // next entry is null
    }
    else                               // otherwise (if list is not empty)
    {
        int count = 0;                 // counts number of elements in list, starts at 0
        
        //
        // while we haven't reached index to insert element
        //
        while (count < insertIndex && curr -> next != NULL)
        {
            count++;                   // tally elements
            
            temp = curr;               // temp trails curr by one element
            
            curr = curr -> next;       // move to next element
        }
        
        temp -> next = insPtr;         // the trailing element's next pointer will now point to added element
        
        insPtr -> data = insertData;  // sets data in added element
        
        insPtr -> next = curr;        // sets added element's next pointer to leading element
    }
    
    cout << insertData << " was added at index " << insertIndex;
}

//
// deletes element
//
void List::deleteElement(int delData)
{
    node* delPtr = NULL;        // creates pointer to a node, intitilize as null
    
    temp = curr = head;         // temp and curr pointer point to head (start of list)
    
    while (curr != NULL && curr -> data != delData)
    {
        temp = curr;            // temp trails one element behind curr
        
        curr = curr -> next;    // loop iterates thru until the curr pointer points to the data to be deleted
    }
    if (curr == NULL)           // if the curr pointer points to nothing, then delData wasn't found
    {
        cout << delData << " was not in the list";
        
        delete delPtr;          // deletes node delPtr points to
    }
    else
    {
        delPtr = curr;          // delPtr points to what curr pointer points to (same as what we want to delete)
        
        curr = curr -> next;    // moves curr to point to next node
        
        temp -> next = curr;    // patches list
        
        if (delPtr == head)    // if deleting the first element in the list (the head), then the head is the next node
        {
            head = head -> next;
            
            temp = NULL;
        }
        
        delete delPtr;         // deletes node delPtr points to
        
        cout << "The value " << delData << " was deleted";
    }
}

//
// removes first element
//
void List::removeFront()
{
    if (head == NULL)              // if the list is empty (there is no first element) then doesn't work
    {
        cout << "There is nothing to delete in the front of the list";
    }
    else
    {
        cout << "The value of "<< head -> data << " was removed";
        
        head = head -> next;       // reassigns head to the (previously) second element
    }
}

//
// removes last element
//
void List::removeBack()
{
    if (head != NULL)
    {
        if (head -> next == NULL)
        {
            cout << "The value of " << head -> data << " was removed";
            
            delete head;               // modification to prevent memory leak (?)
            
            head = NULL;
        }
        else
        {
            curr = temp = head;
            
            while (curr -> next != NULL)
            {
                temp = curr;            // temp trails one element behind curr
                
                curr = curr -> next;    // loop iterates thru until the curr pointer points to last element
            }
            
            delete curr;                // necessary (?)
            
            cout << "The value of " << curr -> data << " was removed";
            
            curr = temp;                // now, set curr back one element to temp, which is now the last element
            
            curr -> next = NULL;        // the next pointer of the last element points to nothing
        }
    }
    else
    {
        cout << "There is nothing to delete at the end of the list";
    }
}

//
// prints number of elements
//
int List::size()
{
    int count = 0;             // counts number of elements in list, starts at 0
    
    curr = head;               // initializes curr to point to start of list
    
    while (curr != NULL)       // while there are still elements in the list
    {
        count++;               // tally elements
        
        curr = curr -> next;   // move to next element
    }
    
    return count;              // value returned since function called in other functions for input validation
}

//
// prints all elements in list
//
void List::print()
{
    if (head == NULL)        // if there is no first element -- list is empty (note: no else after, because nothing wil print regardless)
    {
        cout << "The list is empty -- there is nothing to print\n";
    }
    
    curr = head;             // initialize curr to point to start of list
    
    while (curr != NULL)     // while not the end of the list, print the data in the node and then move to next node
    {
        cout << curr -> data << endl;
        
        curr = curr -> next; // moves to next element
    }
}

///////////////////////////////////////////////////////////////
// MAIN FUNCTION
///////////////////////////////////////////////////////////////
int main()
{
    List ls;                  // constructor
    
    string command;           // user entry
    
    int arg;                  // element to add/delete/index: when value required
    
    cout<<"Command: ";
    cin>>command;
    
    //
    // while user does not enter exit, ask for next command, and run corresponding function
    //
    while (command != "Exit" && command != "exit")
    {
        if (command == "addFront" || command == "addfront")
        {
            cin >> arg;
            
            ls.addElementFront(arg);
        }
        else if (command == "addBack" || command == "addback")
        {
            cin >> arg;
            
            ls.addElementBack(arg);
        }
        else if (command == "Insert" || command == "insert")
        {
            int arg1;
            
            cin >> arg;
            
            //
            // if user tries to insert at index outside list length, or tries to insert at negative index
            //
            if (arg > ls.size() || arg < 0)
            {
                cout << "Invalid index.";
            }
            else
            {
                cin >> arg1;
                
                ls.insertElement(arg, arg1);
            }
        }
        else if (command == "Del" || command == "del")
        {
            cin >> arg;
            
            ls.deleteElement(arg);
        }
        else if (command == "delFront" || command == "delfront")
        {
            ls.removeFront();
        }
        else if (command == "delBack" || command == "delback")
        {
            ls.removeBack();
        }
        else if (command == "Size" || command == "size")
        {
            cout << "Size is " << ls.size() << endl;
            
        }
        else if (command == "Print" || command == "print")
        {
            cout << endl;
            ls.print();
        }
        else if (command != "exit" && command != "Exit")
        {
            cout<<"Invalid command. ";
        }
        
        //
        // As long as user does not enter exit, ask user for next command
        //
        if (command != "Exit" && command != "exit")
        {
            cout<<"\nCommand: ";
            cin>>command;
        }
    }
    return 0;
}

/*************************************************************************************************************************
 LIMITATIONS
 - No "Create" function -- instead, starts with empty list and user must add elements to fill list
    - Otherwise, no commands would make sense before the create function
 **************************************************************************************************************************/
