/**************************************************************
 * Description:  This file contains the following routines /
 * classes ......  and is responsible for .......
 *
 * Contact:
 * Neil Ashtekar    (nca5096@psu.edu)    (8143213010)
 *
 *
 * Functions declared in file
 *    Email: Constructor with no body
 *    setName: Sets the email address string to name
 *    getName: Gets email address string (returns name string)
 *    correctLength: Returns true if address is shorter than or
 *                   equal to 31 characters, false if otherwise
 *    charCheck: Returns true if address contains necessary
 *                   characters in the correct locations and
 *                   does not contain spaces, false if
 *                   otherwise
 *
 *
 * Revesion History
 *
 * Who         Date     Issue    Description
 * ------       ----     ----      -----------------------
 * nca5096      1-20-18  None      Initial Version
 * nca5096      1-22-18  Classes   Edited class structure
 **************************************************************/

//
// Includes:
//
#include <stdio.h>                            // File for standard Input/Output
#include <iostream>                         // Input/Output stream
#include <string>                           // Use of strings
using namespace std;                        // Set of identifiers


/////////////////////////////////////////////////////////////////////////
// CLASS DEFINITION
////////////////////////////////////////////////////////////////////////

//
// define class for email
//
class Email
{
private:
    string name;                    // Email adress as string
    int length;                     // Number of characters in address
    
public:
    Email() {}                       // Constructor
    void setName(string);           // Sets address string
    string getName() const;         // To access adress string
    bool correctLength();           // To ensure correct number of characters
    bool charCheck() const;         // To ensure correct characters/locations
};


/////////////////////////////////////////////////////////////////////////
// FUNCTION DEFINITIONS
////////////////////////////////////////////////////////////////////////

//
// Sets name of address
//
void Email::setName(string a)
{
    name = a;
}

//
// Returns (gets) name of address
//
string Email::getName() const
{
    return name;
}

//
// Function to check length of address
//
bool Email::correctLength()
{
    length = name.length();                 // Sets length or string, also used in charCheck (thus function not const)
    
    if (length <= 30 && length >= 7)        // String must be at least 7 characters long: _@_.___ but not excessively long
    {
        return true;
    }
    else
    {
        return false;
    }
}

//
// Function to check that address contains all necessary characters and does not contain invalid spcae character
//
bool Email::charCheck() const
{
    int i, atspot = 30, dotspot = 0, atcount = 0, dotafterat = 0;  // Intergers used to count characters, mark character locations
    bool space = false;                                            // Used to mark presence of a space
    
    for (i = 0; i <= length; i++)                                  // Iterates over each character in string
    {
        
        if (name[i] == '@')                                        // Must have a single @
        {
            atspot = i;
            
            atcount++;
        }
        
        if (name[i] == '.')                                        // Must have a single . after @, . before @ irrelevant
        {
            dotspot = i;
            
            if (dotspot > atspot)
            {
                dotafterat++;
            }
        }
        
        if (name[i] == ' ')                                         // Cannot have spaces
        {
            space = true;
        }
    }
    
    if (atcount == 1 && dotafterat == 1 && space == false && (atspot + 1) < dotspot && dotspot == (length - 4))   // Must meet all conditions to have all valid characters
    {
        return true;
    }
    else
    {
        return false;
    }
}


/////////////////////////////////////////////////////////////////////////
// MAIN FUNCTION
////////////////////////////////////////////////////////////////////////

int main()
{
    Email em;
    string tempEntry = "a";
    
    while (tempEntry != "x" && tempEntry != "X")
    {
        cout << "Please enter an email address for validation or type X to cancel: ";
        cin >> tempEntry;                                                                // Ask user for entry
        
        if (tempEntry != "x" && tempEntry != "X")
        {
            em.setName(tempEntry);                                                      // Set name string as email address
            
            if (em.correctLength() == true && em.charCheck() == true)                   // If address has correct length and correct characters, it is valid
            {
                cout << "\nThe email address '" << em.getName() << "' is valid!\n\n";  // Display address and its validity
            }
            else
            {
                cout << "\nThe email address '" << em.getName() << "' is invalid!\n\n";
            }
        }
    }
    return 0;
}

/************************************************************************************************************
 * LIMITATIONS
 *
 * - Does not filter out characters like ", ', +, = (I was unsure where these characters were/were not allowed)
 * - Assumes address ends in .edu/.org/.com, etc. (three letters after period -- I believe all addresses do)
 * - If address fails, does not display why
 * - Caps address length at 30 characters -- somewhat arbitruary
 * - Treats whitespace as end of address in user entry (does not change validation of a single address)
 *************************************************************************************************************/
