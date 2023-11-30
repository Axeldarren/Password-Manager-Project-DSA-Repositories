#include "PasswordManager.h"
#include "Function.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>

void displayWelcomeMessage() {
    std::cout << R"(
  _____                                           _  
 |  __ \                                         | | 
 | |_) |_ _  ___  ___ __      __ ___   _ __  __| | 
 |  ___// _` |/ __|/ __|\ \ /\ / // _ \ | '__|/ _` | 
 | |   | (| |\_ \\__ \ \ V  V /| (_) || |  | (_| | 
 |_|    \__,_||___/|___/  \_/\_/  \___/ |_|   \__,_| 
  __  __                                             
 |  \/  |                                            
 | \  / |  __ _  _ __    __ _   __ _   ___  _ __     
 | |\/| | / ` || ' \  / _` | / _` | / _ \| '__|    
 | |  | || (_| || | | || (_| || (_| ||  __/| |       
 |_|  |_| \__,_||_| |_| \__,_| \__, | \___||_|       
                                __/ |                
                               |___/                 
)" << std::endl;
    std::cout << "Created by Axel, Abdi, Abi, Marlon, and Gerald" << std::endl;
}

void displayCompletionMessage() {
    std::cout << "Task completed successfully!" << std::endl;
    std::cout << "Press any key to continue...";
    _getch(); // Wait for a key press
    system("CLS"); // Clear the console screen
}

int main() {
    displayWelcomeMessage();
    PasswordManager passwordManager;
    std::cout << "Welcome to Password Manager!" << std::endl;
    std::cout << "Please register or log in to continue." << std::endl;

    int choice;
    do {
        std::cout << "1. Register\n2. Log In\n3. Exit\nEnter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string username, password;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                password = getPasswordMasked();
                passwordManager.registerUser(username, password);
                displayCompletionMessage();
                break;
            }
            case 2: {
                std::string username, password;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                password = getPasswordMasked();
                if (passwordManager.loginUser(username, password)) {
                    int option;
                    do {
                        std::cout << "\nPassword Manager Menu\n";
                        std::cout << "1. Add Password\n2. Get Password\n3. Remove Password\n";
                        std::cout << "4. Edit Password\n5. Display History\n6. Logout\nEnter option: ";
                        std::cin >> option;

                        switch (option) {
                            case 1: {
                                std::string website, usr, pwd;
                                bool save;
                                std::cout << "Enter website: ";
                                std::cin >> website;
                                std::cout << "Enter username: ";
                                std::cin >> usr;
                                std::cout << "Enter password: ";
                                pwd = getPasswordMasked();
                                std::cout << "Do you want to save this password? (1 for Yes, 0 for No): ";
                                std::cin >> save;
                                passwordManager.addPassword(website, usr, pwd, save);
                                displayCompletionMessage();
                                break;
                            }
                            case 2: {
                                std::string website;
                                std::cout << "Enter website: ";
                                std::cin >> website;
                                std::cout << "Password for " << website << ": " << passwordManager.getPassword(website) << std::endl;
                                displayCompletionMessage();
                                break;
                            }
                            case 3: {
                                std::string website;
                                std::cout << "Enter website: ";
                                std::cin >> website;
                                passwordManager.removePassword(website);
                                displayCompletionMessage();
                                break;
                            }
                            case 4: {
                                std::string website, newPassword;
                                std::cout << "Enter website: ";
                                std::cin >> website;
                                std::cout << "Enter new password: ";
                                newPassword = getPasswordMasked();
                                passwordManager.editPassword(website, newPassword);
                                displayCompletionMessage();
                                break;
                            }
                            case 5: {
                                passwordManager.displayHistory();
                                displayCompletionMessage();
                                break;
                            }
                            case 6: {
                                passwordManager.logoutUser();
                                displayCompletionMessage();
                                break;
                            }
                            default: {
                                std::cout << "Invalid choice. Please try again." << std::endl;
                                break;
                            }
                        }
                    } while (option != 6);
                }
                break;
            }
            case 3: {
                std::cout << "Exiting..." << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }
    } while (choice != 3);

    return 0;
}