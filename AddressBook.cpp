#include "includes.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
// add contact is complete
void addressBook::addContact() {
    std::string firstName;
    std::string lastName;
    std::string address;
    std::string phone;
    std::string email;

    // getting data from user input
    std::cout << "Enter First Name: ";
    std::cin >> firstName;
    std::cout << std::endl;
    std::cout << "Enter Last Name: ";
    std::cin >> lastName;
    std::cout << std::endl;
    std::cout << "Enter Address: "; 
    std::cin >> address;
    std::cout << std::endl;
    std::cout << "Enter Phone Number: ";
    std::cin >> phone;
    std::cout << std::endl;
    std::cout << "Enter Email: ";
    std::cin >> email;
    std::cout << std::endl;

    // set the entry number
    int entryNumber = addressBook::getRows();

    // adding user data to csv file;
    std::ofstream file("addressBook.csv", std::ios::app);
    
    
    if (file.is_open()) {
        file << entryNumber << "," << firstName << "," << lastName << "," << address << "," << phone << "," << email << "\n";
        file.close();
    }
    
    addressBook::mainMenu();
}

// View Contacts is complete
void addressBook::viewContacts() {
    std::ifstream file("addressBook.csv");
    std::string line;
    std::vector<std::vector<std::string>> lines;
    
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string word;
        while (std::getline(ss, word, ',')) {
            row.push_back(word); // add each word to the row vector
                // std::cout << std::setw(25) << word;
        }
        lines.push_back(row); // add vector containing all user data from each row
    }
    // Display address book and allign data
    for (int row = 0; row < lines.size(); row++) {
        for (int col = 0; col < lines[0].size(); col++) {
                std::cout << std::setw(30) << lines[row][col];
        }
        std::cout << std::endl;
    }
    file.close();
    addressBook::mainMenu();
}

// works except contact numbers get messed up
void addressBook::deleteContact() {
    int rowToDelete;
    std::cout << "Select Contact Number to Delete: ";
    std::cin >> rowToDelete;
    rowToDelete++; // incrementing by one becuase I dont want to count the first row that has the column names
    if (rowToDelete == 0) {
        std::cout << "Invalid Contact Number" << std::endl;
        addressBook::mainMenu();
    }
    std::string line;
    
    std::ifstream inFile("addressBook.csv");
    std::ofstream tempFile("temp.csv");
    std::string filename = "addressBook.csv";
    int currentRow = 1;
    while (getline(inFile, line)) {
        if (currentRow != rowToDelete) {
            tempFile << line << std::endl;
        }
        currentRow++;
    }

    // Close the files
    inFile.close();
    tempFile.close();

    // Delete the original file
    remove(filename.c_str());

    // Rename the temporary file to the original file name
    rename("temp.csv", filename.c_str());

    addressBook::fixOrder(); // will fix the contact numbers that are not arranged after deleting a contact
    addressBook::mainMenu();
}

// SearchContact works correctly and displays contacts found by inputed search namee
void addressBook::searchContact() {
    std::ifstream file("addressBook.csv");
    std::string line;
    std::vector<std::vector<std::string>> lines;
    
    std::string searchName;
    std::cout << "Enter First Name to Search: ";
    std::cin >> searchName;

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string word;
        while (std::getline(ss, word, ',')) {
            row.push_back(word); // add each word to the row vector
                
        }
        lines.push_back(row); // add vector containing all user data from each row
    }
    // Will display the lines that have the searched name if found
    for (int row = 0; row < lines.size(); row++) {
        bool endLine = false;
        for (int col = 0; col < lines[0].size(); col++) {
            if (lines[row][1] == searchName) {
                std::cout << std::setw(30) << lines[row][col];
                endLine = true;
            } else if(row == 0) {
                std::cout << std::setw(30) << lines[row][col];
                endLine = true;
            }
        }
        if (endLine) {
            std::cout << std::endl;
        }
    }
    file.close();
    addressBook::mainMenu();
}

void addressBook::editContact() {
    // user inputs
    int contactNumber;
    std::string columnToEdit;
    std::string newChange;

    std::cout << "Enter Contact Number You Wish To Edit: ";
    std::cin >> contactNumber;
    std::cout << std::endl;
    std::cout << "Enter Column You Would Like To Edit (FirstName lastName etc.): ";
    std::cin >> columnToEdit;
    std::cout << std::endl;
    std::cout << "Enter New Change: ";
    std::cin >> newChange;
    std::cout << std::endl;

    // setting column that user want do edit
    int colToEdit;
    if (columnToEdit == "FirstName") {
        colToEdit = 1;
    } else if (columnToEdit == "LastName") {
        colToEdit = 2;
    } else if (columnToEdit == "Address") {
        colToEdit = 3;
    } else if (columnToEdit == "Phone Number") {
        colToEdit = 4;
    } else if (columnToEdit == "Email") {
        colToEdit = 5;
    }

    std::string filename = "addressBook.csv";
    std::ifstream file(filename);
    std::ofstream tempFile("temp.csv");

    std::string line;
    std::vector<std::vector<std::string>> lines;

    // Creating 2d vector of CSV file
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string word;
        while (std::getline(ss, word, ',')) {
            row.push_back(word); // add each word to the row vector
        }
        lines.push_back(row); // add vector containing all user data from each row
    }
    
    // edits csv file and replaces speficied row and column to the new change the user inputed
    lines[contactNumber][colToEdit] = newChange;

    for (int row = 0; row < lines.size(); row++) {
        for (int col = 0; col < lines[0].size(); col++) {
            tempFile << lines[row][col];
            if (col != lines[row].size() - 1) {
                tempFile << ',';
            }
        }
        tempFile << std::endl;
    }
    // closing csv files
    file.close();
    tempFile.close();

    // Delete the original file
    remove(filename.c_str());
    
    // Rename the temporary file to the original file name
    rename("temp.csv", filename.c_str());
    addressBook::mainMenu();
}
// get rows works
int addressBook::getRows() {
    std::ifstream file("addressBook.csv");
    int rows = 0;
    std::string line;
    while (std::getline(file, line)) {
        rows++;
    }
    return rows;
}

// this function fixes he contact number when it the order gets messed up
void addressBook::fixOrder() { 
    
    std::string filename = "addressBook.csv";

    std::ifstream file(filename);
    std::ofstream tempFile("temp.csv");
    
    std::string line;
    std::vector<std::vector<std::string>> lines;
    int rowNumber = 0;
    while (std::getline(file, line)) {
        int columnNumber = 0;
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string word;
        while (std::getline(ss, word, ',')) {
            if (columnNumber == 0 && rowNumber > 0) {
                row.push_back(std::to_string(rowNumber));
            } else {
                row.push_back(word); // add each word to the row vector
            }
            columnNumber++;
        }
        lines.push_back(row); // add vector containing all user data from each row
        rowNumber++;
    }
    for (int row = 0; row < lines.size(); row++) {
        for (int col = 0; col < lines[0].size(); col++) {
            tempFile << lines[row][col];
            if (col != lines[row].size() - 1) {
                tempFile << ',';
            }
        }
        tempFile << std::endl;
    }
    

    // Close the files
    file.close();
    tempFile.close();

    // Delete the original file
    remove(filename.c_str());

    // Rename the temporary file to the original file name
    rename("temp.csv", filename.c_str());
}

void addressBook::mainMenu() {
    int optionNumber;
    std::cout << "1) Add Contact" << std::endl;
    std::cout << "2) Edit Contact" << std::endl;
    std::cout << "3) View Contacts" << std::endl;
    std::cout << "4) Delete Contact" << std::endl;
    std::cout << "5) Search Contact" << std::endl;
    std::cout << std::endl;
    std::cout << "Choose an Option (type in option number): ";
    std::cin >> optionNumber;
    std::cout << std::endl;
    if (optionNumber == 1) {
        addressBook::addContact();
    } else if (optionNumber == 2) {
        addressBook::editContact();
    } else if (optionNumber == 3) {
        addressBook::viewContacts();
    } else if (optionNumber == 4) {
        addressBook::deleteContact();
    } else if (optionNumber == 5) {
        addressBook::searchContact();
    } else {
        addressBook::mainMenu();
    }

}




