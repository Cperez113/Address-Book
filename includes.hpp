#ifndef INCLUDES_HPP
#define INCLUDES_HPP
#include <iostream> 

class addressBook {
    public:
        void addContact(); // allows user to enter person information and save it to the address book

        void viewContacts(); // allows user to see all added contacts

        void editContact(); // allows user to edit an existing contacts information

        void deleteContact(); // allows a user to remove an existing contact in the address book
        
        void searchContact(); // Allows user to search for an already added contact by name

        void fixOrder(); // will fix the order of the csv file and correct and Contact numbers that may be messed up by deleting a contact

        void mainMenu(); // allows user to pick an option in the addressBook

        int getRows(); // will output number of rows in csv file
        

};

#endif
