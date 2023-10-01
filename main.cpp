#include "includes.hpp"
#include "AddressBook.cpp"
#include <fstream>
using namespace std;

int main() {
    // ofstream file;
    // file.open("addressBook.csv");
    std::cout << "=================AddressBook=================" << std::endl;
    addressBook book;
    book.mainMenu();
    // book.viewContacts();
    // book.editContact();
    // book.addContact();
    // book.deleteContact();
    // book.searchContact();
    return 0;
}