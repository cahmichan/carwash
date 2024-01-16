#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cctype>
#include <chrono>
#include <thread>
#include <vector>
#include <Windows.h>
#include <mmsystem.h>
#include <windows.graphics.h>
#include "graphics.h"

#pragma comment(lib,"graphics.lib")
#pragma comment(lib, "winmm.lib")

using namespace std;

// Function declarations
bool doesUserExist(const unordered_map<string, string>& users, const string& username);
bool authenticateUser(const unordered_map<string, string>& users, const string& username, const string& password);
void registerUser(unordered_map<string, string>& users, const string& username, const string& password);
void customerProcess(unordered_map<string, string>& users);
void staffProcess(unordered_map< string, string>& staffCredentials);
void adminProcess();
void displayMenu();
int handleCustomerChoice(const unordered_map<string, string>& users);
int handleCarWashChoice(int carOption);
bool customerLogin(const unordered_map<string, string>& users);
bool staffLogin(const unordered_map<string, string>& staffCredentials);
bool adminLogin(const unordered_map<string, string>& adminCredentials);
double handleCarWashPrice(int washOption, int carOption);
double handleCarMerchandise(double& price, char& itemOption, int& quantity, int& tShirtSold, int& mugSold, int& towelSold, int& actionFigureSold);
double generateReceipt(double totalPrice, char itemOption, int quantity, double itemPrice);
void validateCardNumber(string cardNumber);
void validateExpiryDate(int expiryDate);
void validateSecurityCode(int securityCode);
void paymentMethod();
int handleStaffChoice(const unordered_map<string, string>& staffCredentials);
int handleAdminOption(const unordered_map<string, string>& adminCredentials);
double DetDiscountCode(double& carWashPrice, double& price, string& discountCode);
void createStaffAccount(unordered_map<string, string>& staffCredentials);
void deleteStaffAccount(unordered_map<string, string>& staffCredentials);
void modifyStaffAccount(unordered_map<string, string>& staffCredentials);
void displayAllStaff(const unordered_map<string, string>& staffCredentials);
void changeDiscountCode(string& discountCode);
void displaySalesSummary(int carWashCustomers, int tShirtSold, int mugSold, int towelSold, int actionFigureSold);
void staffWage(unordered_map<string, string>& staffCredentials);
void carDetail(unordered_map<string, string>& staffCredentials);
void editCarDetail(unordered_map<string, string>& staffCredentials);
void displayAllCars(unordered_map<string, string>& staffCredentials);
void modifyCustomerPassword(unordered_map<string, string>& users);
void toLowercase(string& str);
int invalidCarChoice();


char choice;
string discountCode = "THEGUYS";
int carWashCustomers = 0;      // Number of customers using the car wash service
int tShirtSold = 0;            // Number of T-Shirts sold
int mugSold = 0;               // Number of Ceramic Mugs sold
int towelSold = 0;             // Number of Towels sold
int actionFigureSold = 0;      // Number of Action Figures sold

void registerUser(unordered_map<string, string>& users) {
    string username, password;

    cout << "\nEnter new username: ";
    cin >> username;

    // Check for duplicate usernames
    while (doesUserExist(users, username)) {
        cout << "Username already exists. Please choose a different one: ";
        cin >> username;
    }

    cout << "Enter password: ";
    cin >> password;

    users[username] = password;
    cout << "Registration successful!" << endl;
}

void displayMenu() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");
    cout << "==========================" << endl;
    cout << "=   CHOOSE YOUR PROGRAM  =" << endl;
    cout << "==========================" << endl;
    cout << "=      1. Customer       =" << endl;
    cout << "=      2. Staff          =" << endl;
    cout << "=      3. Admin          =" << endl;
    cout << "=      4. Exit           =" << endl;
    cout << "==========================" << endl;
    cout << "\nEnter your option: ";
}

bool doesUserExist(const unordered_map<string, string>& users, const string& username) {
    return users.find(username) != users.end();
}

bool authenticateUser(const unordered_map<string, string>& users, const string& username, const string& password) {
    auto it = users.find(username);
    if (it != users.end()) {
        return it->second == password;
    }
    return false;
}

void registerUser(unordered_map<string, string>& users, const string& username, const string& password) {
    users[username] = password;
}

void customerProcess(unordered_map<string, string>& users) {
    handleCustomerChoice(users);
}

void staffProcess(unordered_map< string, string>& staffCredentials) {
    handleStaffChoice(staffCredentials);
}

void adminProcess() {
    cout << "Admin is adminining" << endl;
}

bool customerLogin(const unordered_map<string, string>& users) {
    string username, password;
    cout << "\n===============================" << endl;
    cout << "Enter Username:";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;
    cout << "===============================" << endl;

    if (authenticateUser(users, username, password)) {
        cout << "Authentication successful. Welcome, " << username << "!" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        system("cls");
        return true;
    }
    else if (!authenticateUser(users, username, password)) {
        cout << "Invalid username or password. Would you like to register (y/n)? ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            cout << "\nWelcome " << username << " to THE GUYS Car Wash!";
            this_thread::sleep_for(chrono::milliseconds(1000));
            system("cls");
            return true;
        }
        else if (choice != 'y' && choice != 'Y')
        {
            cout << "\nRegistration cancelled.";
            return false;
        }
    }
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");
    return false;  // If authentication succeeded, proceed as usual
}

bool staffLogin(const unordered_map<string, string>& staffCredentials) {
    string username, password;
    cout << "\nEnter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    if (authenticateUser(staffCredentials, username, password)) {
        cout << "Authentication successful. Welcome, " << username << "!" << endl;
        return true;
    }
    else
    {
        cout << "Invalid username or password. Access denied." << endl;
        return false;
    }
}

bool adminLogin(const unordered_map<string, string>& adminCredentials) {
    string username, password;
    cout << "\nEnter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    if (authenticateUser(adminCredentials, username, password)) {
        cout << "Authentication successful. Welcome, " << username << "!" << endl;
        return true;
    }
    else
    {
        cout << "Invalid username or password. Access denied." << endl;
        return false;
    }
}

int invalidCarChoice() {
     cout << "Invalid option. Please choose 1, 2, 3, or 4." << endl;
     return 0;
     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
     system("cls");
}

int handleAdminOption(const unordered_map<string, string>& adminCredentials) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");
    int adminOption;
    cout << "\n===================================================" << endl;
    cout << "=       Admin Option          | Press the Number  =" << endl;
    cout << "===================================================" << endl;
    cout << "=    Create Staff Account     |        1          =" << endl;
    cout << "=    Delete Staff Account     |        2          =" << endl;
    cout << "=    Modify Staff Account     |        3          =" << endl;
    cout << "=    Change Discount Code     |        4          =" << endl;
    cout << "=       Sales Summary         |        5          =" << endl;
    cout << "=       List Of Staff         |        6          =" << endl;
    cout << "=           Exit              |        7          =" << endl;
    cout << "===================================================" << endl;
    cout << "Please choose option you want to do: ";
    cin >> adminOption;
    cout << "loading.....";
    return adminOption;
}

int handleStaffChoice(const unordered_map<string, string>& staffCredentials) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");
    int staffOption;
    cout << "\n===========================================" << endl;
    cout << "=     Task          |  Press the Number   =" << endl;
    cout << "===========================================" << endl;
    cout << "= 1. Customer Acc   |        1            =" << endl;
    cout << "= 2. Calc Wage      |        2            =" << endl;
    cout << "= 3. Car  Detail    |        3            =" << endl;
    cout << "= 4. Edit Detail    |        4            =" << endl;
    cout << "= 5. Exit           |        5            =" << endl;
    cout << "===========================================" << endl;
    cout << " Please enter number ";
    cin >> staffOption;
    return staffOption;
}

int handleCustomerChoice(const unordered_map<string, string>& users) {
    int carOption;
    cout << "\n======================================" << endl;
    cout << "= Type of Car     | Press the Number =" << endl;
    cout << "======================================" << endl;
    cout << "=      MPV        |        1         =" << endl;
    cout << "=      SUV        |        2         =" << endl;
    cout << "=   HATCHBACK     |        3         =" << endl;
    cout << "=     SEDAN       |        4         =" << endl;
    cout << "======================================" << endl;
    cout << "Please choose what type of car you have: ";
    cin >> carOption;
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");
    return carOption;
}

int handleCarWashChoice(int carOption) {
    int washOption;
    cout << "\n===================================================" << endl;
    cout << "= Type of Wash                | Press the Number  =" << endl;
    cout << "===================================================" << endl;
    cout << "=      Interior               |        1          =" << endl;
    cout << "=      Exterior               |        2          =" << endl;
    cout << "=   Interior and Exterior     |        3          =" << endl;
    cout << "===================================================" << endl;
    cout << "Please choose what type of wash you want: ";
    cin >> washOption;
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");
    return washOption;
}

double handleCarMerchandise(double& price, char& itemOption, int& quantity, int& tShirtSold, int& mugSold, int& towelSold, int& actionFigureSold)
{
    char buyOption;
    cout << "Would you like to buy our merchandise? (y/n)" << endl;
    cin >> buyOption;
    if (buyOption == 'y' || buyOption == 'Y')
    {
        system("cls");
        cout << "\n=========================================" << endl;
        cout << "= Items                    | Price      =" << endl;
        cout << "=========================================" << endl;
        cout << "= A. THE GUYS Car T-Shirt  |   RM20.00  =" << endl;
        cout << "= B. THE GUYS Ceramic Mug  |   RM15.00  =" << endl;
        cout << "= C. THE GUYS Towel        |   RM12.00  =" << endl;
        cout << "= D. THE GUYS Action Figure|   RM25.00  =" << endl;
        cout << "=========================================" << endl;
        cout << "Enter the item letter (A/B/C/D): ";
        cin >> itemOption;

        cout << "Enter the quantity: ";
        cin >> quantity;

        switch (itemOption)
        {
        case 'A':
        case 'a':
            price = 20.00 * quantity;
            cout << "Total price for THE GUYS Car T-Shirt (quantity: " << quantity << "): RM" << price << endl;
            tShirtSold += quantity;  // Increment the count of T-Shirts sold
            break;
        case 'B':
        case 'b':
            price = 15.00 * quantity;
            cout << "Total price for THE GUYS Ceramic Mug (quantity: " << quantity << "): RM" << price << endl;
            mugSold += quantity;  // Increment the count of Ceramic Mugs sold
            break;
        case 'C':
        case 'c':
            price = 12.00 * quantity;
            cout << "Total price for THE GUYS Towel (quantity: " << quantity << "): RM" << price << endl;
            towelSold += quantity;  // Increment the count of Towels sold
            break;
        case 'D':
        case 'd':
            price = 25.00 * quantity;
            cout << "Total price for THE GUYS Action Figure (quantity: " << quantity << "): RM" << price << endl;
            actionFigureSold += quantity;  // Increment the count of Action Figures sold
            break;
        default:
            cout << "Invalid option selected." << endl;
            return price; // Return the price
        }
    }
    else
    {
        cout << "Thank you for washing with THEGUYS Car Wash!" << endl;
        price = 0.0;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        system("cls");
        return 0; // Return 0 if no merchandise is bought
    }
    return price;
}

double handleCarWashPrice(int washOption, int carOption) {
    double basePrice = 10.00;  // Set base price for all car types
    double additionalFee = 0.00;  // Initialize additional fee

    switch (carOption) {
    case 1:  // MPV
        additionalFee = 5.00;  // Example additional fee for MPV
        break;
    case 2:  // SUV
        additionalFee = 8.00;  // Example additional fee for SUV
        break;
    case 3:  // HATCHBACK
        // No additional fee for hatchback
        break;
    case 4:  // SEDAN
        // No additional fee for sedan
        break;
    default:
        
        return 0;  // Exit the function if invalid option
    }

    // Update additionalFee based on washOption
    switch (washOption) {
    case 1:  // Interior only
        additionalFee += 2.00;  // Example fee for interior wash
        break;
    case 2:  // Exterior only
        additionalFee += 4.00;  // Example fee for exterior wash
        break;
    case 3:  // Interior and exterior
        additionalFee += 6.00;  // Example fee for both interior and exterior
        break;
    default:
        
        return 0;  // Exit the function if invalid option
    }

    double totalPrice = basePrice + additionalFee;
    cout << "\nTotal price for the car wash: RM" << fixed << setprecision(2) << totalPrice << endl;
    return totalPrice; // Return the total price
}

double DetDiscountCode(double& carWashPrice, double& price, string& discountCode) {
    string code;
    cout << "Do you have a discount code? (y/n): ";
    cin >> code;

    if (code == "y" || code == "Y") {
        string discountCodeEntered;
        cout << "Enter your discount code: ";
        cin >> discountCodeEntered;

        if (discountCodeEntered == discountCode) {
            carWashPrice *= 0.9; // Apply a 10% discount to car wash price
            price *= 0.9; // Apply a 10% discount to merchandise price
            cout << "Discount code applied! 10% off car wash and merchandise prices." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            system("cls");
        }
        else {
            cout << "Invalid discount code. No discount applied." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            system("cls");
        }
    }
    else {
        cout << "No discount code entered." << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        system("cls");
    }
    return carWashPrice, price;
}

double generateReceipt(double totalPrice, char itemOption, int quantity, double itemPrice) {
    cout << "\nGenerating receipt..." << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    system("cls");
    cout << "======================" << endl;
    cout << "THE GUYS Car Wash" << endl;
    cout << "======================" << endl;
    cout << "Car Wash: RM" << fixed << setprecision(2) << totalPrice << endl;
    cout << "Merchandise: RM" << fixed << setprecision(2) << itemPrice << endl;
    cout << "======================" << endl;
    cout << "Total: RM" << fixed << setprecision(2) << totalPrice + itemPrice << endl;
    cout << "======================" << endl;
    cout << "Thank you for choosing THE GUYS Car Wash!" << endl;
    return totalPrice + itemPrice;
}

void validateCardNumber(string cardNumber) {
    if (cardNumber.length() < 16 || cardNumber.length() > 19) {
        cout << "Invalid Card Number!" << endl;
        cout << "Payment Failed!" << endl;
        exit(0);
    }

    for (char c : cardNumber) {
        if (!isdigit(c)) {
            cout << "Invalid Card Number!" << endl;
            cout << "Payment Failed!" << endl;
            exit(0);
        }
    }
}

void validateExpiryDate(int expiryDate) {
    if (expiryDate < 1000 || expiryDate > 9999) {
        cout << "Invalid Expiry Date!" << endl;
        cout << "Payment Failed!" << endl;
        exit(0);
    }
}

void validateSecurityCode(int securityCode) {
    if (securityCode < 100 || securityCode > 999) {
        cout << "Invalid Security Code!" << endl;
        cout << "Payment Failed!" << endl;
        exit(0);
    }
}

void paymentMethod() {
    int choice;
    cout << "\nChoose Payment Method:\n";
    cout << "1. Credit/Debit Card\n";
    cout << "2. QR Code\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        // Credit/Debit Card payment
        string cardNumber;
        int expiryDate, securityCode;

        cout << "\nEnter Card Number: ";
        cin >> cardNumber;
        validateCardNumber(cardNumber);

        cout << "Enter Expiry Date (MMYY): ";
        cin >> expiryDate;
        validateExpiryDate(expiryDate);

        cout << "Enter Security Code (3 digits): ";
        cin >> securityCode;
        validateSecurityCode(securityCode);

        // Process card information (you can add further processing or validation here)
        cout << "\nProcessing Credit/Debit Card Payment..." << endl;
        cout << "Card Number: " << cardNumber << endl;
        cout << "Expiry Date: " << expiryDate << endl;
        cout << "Security Code: " << securityCode << endl;
        cout << "Payment Successful!" << endl;
        carWashCustomers++;

    }
    else if (choice == 2) {
        // QR Code payment
        initwindow(600,600, "QR");
        readimagefile("QR.jpg", 0, 0, 600, 600);
        getch();
        closegraph();
        // Process QR Code information (you can add further processing or validation here)
        cout << "\nProcessing QR Code Payment..." << endl;
        cout << "Payment Successful!" << endl;
        carWashCustomers++;
    }
    else {
        cout << "Invalid choice. Please choose 1 or 2." << endl;
    }
}

// Function to create a new staff account
void createStaffAccount(unordered_map<string, string>& staffCredentials) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");
    string username, password;

    for (int i = 0; i < 15; i++)
        cout << "-";
    cout << " Create New Staff ";
    for (int i = 0; i < 15; i++)
        cout << "-";
    cout << endl;

    do {

        cout << "\nEnter new username: ";
        cin >> username;

        // Check if the username already exists
        if (staffCredentials.find(username) == staffCredentials.end()) {
            cout << "Enter new password: ";
            cin >> password;

            // Add the new staff account to the credentials map
            staffCredentials[username] = password;

            cout << "Staff account created successfully." << endl;
        }
        else {
            cout << "Username already exists. Please choose a different username." << endl;
        }
        cout << "\nDo you want to continue this process (Y-Yes,N-No): ";
        cin >> choice;
        for (int i = 0; i < 10; i++)
            cout << "-";
        cout << endl;
    } while (choice == 'y' || choice == 'Y');
    cout << "\nloading.....";
}

// Function to delete a staff account
void deleteStaffAccount(unordered_map<string, string>& staffCredentials) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");
    string username;

    for (int i = 0; i < 15; i++)
        cout << "-";
    cout << " Delete Staff Account ";
    for (int i = 0; i < 15; i++)
        cout << "-";
    cout << endl;

    do {
        cout << "\nEnter the username to delete: ";
        cin >> username;

        // Check if the username exists in the credentials map
        auto it = staffCredentials.find(username);
        if (it != staffCredentials.end()) {
            // Erase the staff account
            staffCredentials.erase(it);
            cout << "Staff account deleted successfully." << endl;
        }
        else {
            cout << "Username not found. Deletion failed." << endl;
        }
        cout << "\nDo you want to continue this process (Y-Yes,N-No): ";
        cin >> choice;
        for (int i = 0; i < 10; i++)
            cout << "-";
        cout << endl;
    } while (choice == 'y' || choice == 'Y');
    cout << "\nloading.....";
}

// Function to modify the username and password of a staff account
void modifyStaffAccount(unordered_map<string, string>& staffCredentials) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");
    string oldUsername, newUsername, newPassword;

    for (int i = 0; i < 15; i++)
        cout << "-";
    cout << " Modify Staff Account ";
    for (int i = 0; i < 15; i++)
        cout << "-";
    cout << endl;

    do {
        cout << "\nEnter the current username to modify: ";
        cin >> oldUsername;

        // Check if the old username exists in the credentials map
        auto it = staffCredentials.find(oldUsername);
        if (it != staffCredentials.end()) {
            cout << "Enter the new username: ";
            cin >> newUsername;

            // Check if the new username already exists
            if (staffCredentials.find(newUsername) == staffCredentials.end()) {
                cout << "Enter the new password: ";
                cin >> newPassword;

                // Modify the username and password for the staff account
                staffCredentials.erase(it);  // Remove the entry with the old username
                staffCredentials[newUsername] = newPassword;  // Add a new entry with the new username and password

                cout << "Username and password modified successfully." << endl;
            }
            else {
                cout << "New username already exists. Modification failed." << endl;
            }
        }
        else {
            cout << "Old username not found. Modification failed." << endl;
        }
        cout << "\nDo you want to continue this process (Y-Yes,N-No): ";
        cin >> choice;
        for (int i = 0; i < 10; i++)
            cout << "-";
    } while (choice == 'y' || choice == 'Y');
    cout << "\nloading.....";
}

// Function to change discount code
void changeDiscountCode(string& discountCode) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");

    for (int i = 0; i < 15; i++)
        cout << "-";
    cout << " Change Discount Code ";
    for (int i = 0; i < 15; i++)
        cout << "-";
    cout << endl;

    do {

        cout << "\nExisting discount code: " << discountCode;
        cout << "\nEnter a new discount code: ";
        cin >> discountCode;
        cout << "Discount code updated successfully." << endl;
        cout << "New discount code: " << discountCode;
        cout << "\n\nDo you want to continue this process (Y-Yes,N-No): ";
        cin >> choice;
        for (int i = 0; i < 10; i++)
            cout << "-";
        cout << endl;
    } while (choice == 'y' || choice == 'Y');
    cout << "\nloading.....";
}

// Function to display the sales summary
void displaySalesSummary(int carWashCustomers, int tShirtSold, int mugSold, int towelSold, int actionFigureSold)
{
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");

    cout << "\n=========================================" << endl;
    cout << "=           Sales Summary               =" << endl;
    cout << "=========================================" << endl;
    cout << "= Number of car wash customers:   " << setw(5) << left << carWashCustomers << " =" << endl;
    cout << "= Number of T-Shirts sold:        " << setw(5) << left << tShirtSold << " =" << endl;
    cout << "= Number of Ceramic Mugs sold:    " << setw(5) << left << mugSold << " =" << endl;
    cout << "= Number of Towels sold:          " << setw(5) << left << towelSold << " =" << endl;
    cout << "= Number of Action Figures sold:  " << setw(5) << left << actionFigureSold << " =" << endl;
    cout << "=========================================" << endl;

    cout << "Enter any key to Exit: ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y')
        cout << "Exiting process.....";

}

// Function to display all staff
void displayAllStaff(const unordered_map<string, string>& staffCredentials) {

    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");

    for (int i = 0; i < 15; i++)
        cout << "-";
    cout << " All Staff ";
    for (int i = 0; i < 15; i++)
        cout << "-";
    cout << endl;

    cout << "\nUsername\tPassword\n";
    cout << "------------------------\n";

    for (const auto& entry : staffCredentials) {
        cout << entry.first << "\t\t" << entry.second << endl;
    }

    cout << "\nEnter any key to Exit: ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y')
        cout << "Exiting process.....";
}

//staff 
void modifyCustomerPassword(unordered_map<string, string>& users) {
    char choice;
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");

    string username, newPassword;

    for (int i = 0; i < 15; i++)
        cout << "-";
    cout << " Modify Customer Password ";
    for (int i = 0; i < 15; i++)
        cout << "-";
    cout << endl;

    do {
        cout << "\nEnter the current username to modify: ";
        cin >> username;

        // Check if the old username exists in the credentials map
        auto it = users.find(username);
        if (it != users.end()) {
            cout << "Enter the new password: ";
            cin >> newPassword;

            // Modify the password for the customer account
            it->second = newPassword;  // Update the password for the existing username

            cout << "Password modified successfully." << endl;
        }
        else {
            cout << "Username not found. Modification failed." << endl;
        }

        cout << "\nDo you want to continue this process (Y-Yes, N-No): ";
        cin >> choice;
        for (int i = 0; i < 10; i++)
            cout << "-";
    } while (choice == 'y' || choice == 'Y');

    cout << "\nloading.....";
}

void staffWage(unordered_map<string, string>& staffCredentials) {
    char choice;
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");
    const int basicWage = 40;
    string username, workingHourStr;
    char carWashed;
    int workingWage, wage, bonus;

    for (int i = 0; i < 15; i++)
        cout << "-";
    cout << " Staff Wage ";
    for (int i = 0; i < 15; i++)
        cout << "-";
    cout << endl;

    do {
        cout << "\nEnter the current staff: ";
        cin >> username;

        // Check if the old username exists in the credentials map
        auto it = staffCredentials.find(username);
        if (it != staffCredentials.end()) {
            cout << "Every staff basic wage is RM40" << endl;
            cout << "Enter your working hours (1 Hour will be rewarded with RM15 ): ";
            cin >> workingHourStr;

            // Convert working hours from string to integer
            int workingHour = stoi(workingHourStr);

            cout << "Did you wash more than 10 cars ? (y/n) (for more than 10 cars will be rewarded extra RM30) : ";
            cin >> carWashed;
            if (carWashed == 'y' || carWashed == 'Y')
                bonus = 30;
            else
                bonus = 0;

            workingWage = workingHour * 15;
            wage = bonus + basicWage + workingWage;

            cout << "Basic wage : RM " << basicWage << endl;
            cout << "Bonus : RM " << bonus << endl;
            cout << "Working wage : RM " << workingWage << endl;
            cout << "Your overall wage is: RM " << wage << endl;
        }
        else {
            cout << "Username not found. Enter again." << endl;
        }

        cout << "\nDo you want to continue this process (Y-Yes, N-No): ";
        cin >> choice;
        for (int i = 0; i < 10; i++)
            cout << "-";
    } while (choice == 'y' || choice == 'Y');

    cout << "\nloading.....";
}

struct CarDetails {
    string carType;
    string model;
    string color;
    string plateNumber;
};
vector<CarDetails> allCars;

// Function to generate a random alphanumeric plate number
string generateRandomPlateNumber() {
    const string alphanumeric = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int plateLength = 4;

    string plateNumber;
    for (int i = 0; i < plateLength; ++i) {
        int randomIndex = rand() % alphanumeric.size();
        plateNumber += alphanumeric[randomIndex];
    }

    return plateNumber;
}

void displayAllCars(unordered_map<string, string>& staffCredentials) {
    cout << "\n=======================================" << endl;
    cout << "= Car Type     | Model         |   Color | Plate Number" << endl;
    cout << "=======================================" << endl;
    for (const auto& car : allCars) {
        cout << left << setw(15) << car.carType << setw(20) << car.model << setw(15) << car.color << setw(15) << car.plateNumber << endl;
    }
    cout << "=======================================" << endl;
}

void toLowercase(string& str) {
    for (char& c : str) {
        c = tolower(c);
    }
}

void carDetail(unordered_map<string, string>& staffCredentials) {
    char choice = 'y';
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");

    while (choice == 'y' || choice == 'Y') {
        CarDetails car;

        cout << "Please enter your car type (suv, sedan, hatchback, mpv): ";
        cin >> car.carType;

        if (car.carType == "suv" || car.carType == "SUV") {
            car.model = "HONDA HRV";
        }
        else if (car.carType == "sedan" || car.carType == "SEDAN") {
            car.model = "BMW";
        }
        else if (car.carType == "hatchback" || car.carType == "HATCHBACK") {
            car.model = "MYVI";
        }
        else if (car.carType == "MPV" || car.carType == "mpv") {
            car.model = "avanza";
        }
        else {
            cout << "Invalid car type entered. Please try again." << endl;
            continue;  // Restart the loop if an invalid car type is entered
        }

        // Randomly select a color and generate a plate number
        const char* colors[] = { "Red", "Green", "Blue", "Yellow", "Purple" };
        int numColors = sizeof(colors) / sizeof(colors[0]);
        int randomIndex = rand() % numColors;
        car.color = colors[randomIndex];
        car.plateNumber = generateRandomPlateNumber();

        // Store car details
        allCars.push_back(car);

        // Print formatted car details
        displayAllCars(staffCredentials);

        cout << "Do you want to enter another car (y/n)? ";
        cin >> choice;
    }

    cout << "\nLoading.....";
}

void editCarDetail(unordered_map<string, string>& staffCredentials) {
    char choice = 'y';
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");

    do {
        string carTypeToEdit;
        CarDetails car;

        cout << "--------------- Edit Car Detail ---------------" << endl;
        cout << "\nEnter the car type you want to edit: ";
        cin >> carTypeToEdit;

        // Convert the entered car type to lowercase
        toLowercase(carTypeToEdit);

        // Find the car in the vector
        for (auto& car : allCars) {
            if (car.carType == carTypeToEdit) {
                cout << "Enter the new plate number: ";
                cin >> car.plateNumber;

                cout << "Enter the new color: ";
                cin >> car.color;

                cout << "Car details updated successfully!" << endl;
                break;  // No need to continue searching after updating
            }
        }

        // Display all cars after editing
        displayAllCars(staffCredentials);

        cout << "Do you want to continue this process (Y-Yes, N-No): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "\nLoading.....";
}

int main() {
    system("color 0C");
    PlaySound(TEXT("Hampter.wav"), NULL, SND_ASYNC | SND_LOOP);
    unordered_map<string, string> users = { {"user1", "password1"}, {"user2", "password2"}, {"syahmi1", "afif1"} };
    unordered_map<string, string> staffCredentials = { {"staff1", "staff1pwd"} };
    unordered_map<string, string> adminCredentials = { {"admin1", "admin1pwd"} };
    int option;
    char itemOption;
    int quantity;
    int adminOption;
    int staffOption;
    do {
        displayMenu();
        cin >> option;

        switch (option) {
        case 1:
            if (customerLogin(users)) {
                int carOption = handleCustomerChoice(users);
                int washOption = handleCarWashChoice(carOption);
                //selection to determine wash option
                if (carOption != 1 && carOption != 2 && carOption != 3 && carOption != 4) {
                    invalidCarChoice();
                }
                else if (washOption != 1 && washOption != 2 && washOption != 3) {
                    invalidCarChoice();
                }

                else {
                    double carWashPrice = handleCarWashPrice(washOption, carOption); // Store car wash price
                    double price = 0.0; // Initialize merchandise price
                    handleCarMerchandise(price, itemOption, quantity, tShirtSold, mugSold, towelSold, actionFigureSold); // Update merchandise price
                    // ... (retrieve itemOption and quantity)

                    DetDiscountCode(carWashPrice, price, discountCode); // Apply discount to both prices

                    generateReceipt(carWashPrice, itemOption, quantity, price); // Pass prices to receipt
                    paymentMethod();

                    char continueChoice;
                    cout << "Do you want to continue this process (Y-Yes, N-No): ";
                    cin >> continueChoice;
                    if (continueChoice == 'y' || continueChoice == 'Y')
                    {
                    }
                    else if (continueChoice != 'y' && continueChoice != 'Y')
                    {
                        return 0;
                    }
                }
                
            }
            else {
            }
            break;
        case 2:
            if (staffLogin(staffCredentials)) {
                do {
                    staffOption = handleStaffChoice(staffCredentials);
                    switch (staffOption) {
                    case 1:
                        modifyCustomerPassword(users);
                        break;
                    case 2:
                        staffWage(staffCredentials);
                        break;
                    case 3:
                        carDetail(staffCredentials);
                        break;
                    case 4:
                        displayAllCars(staffCredentials);
                        editCarDetail(staffCredentials);
                        break;
                    case 5:
                        cout << "Exiting program...";
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                    }
                } while (staffOption != 5);
            }
            break;
        case 3:
            if (adminLogin(adminCredentials)) {
                // Perform admin actions
                do {
                    adminOption = handleAdminOption(adminCredentials);
                    switch (adminOption) {
                    case 1:
                        createStaffAccount(staffCredentials);
                        break;
                    case 2:
                        deleteStaffAccount(staffCredentials);
                        break;
                    case 3:
                        modifyStaffAccount(staffCredentials);
                        break;
                    case 4:
                        changeDiscountCode(discountCode);
                        break;
                    case 5:
                        displaySalesSummary(carWashCustomers, tShirtSold, mugSold, towelSold, actionFigureSold);
                        break;
                    case 6:
                        displayAllStaff(staffCredentials);
                        break;
                    case 7:
                        cout << "Exiting program.\n";
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                    }
                } while (adminOption != 7);
            }
            break;
        case 4:
            cout << "\nExiting the program....";
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
            return 0;
        }
    } while (option != 4);

    return 0;
}
