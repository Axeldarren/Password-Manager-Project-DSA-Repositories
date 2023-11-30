// Function.h
#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>
#include <conio.h>

std::string PasswordManager::caesarCipherEncrypt(const std::string& input, int shift) {
    std::string encryptedText = "";
    for (char c : input) {
        if (isalpha(c)) {
            char shifted = islower(c) ? 'a' + (c - 'a' + shift) % 26 : 'A' + (c - 'A' + shift) % 26;
            encryptedText += shifted;
        } else {
            encryptedText += c;
        }
    }
    return encryptedText;
}

PasswordManager::PasswordManager() : historyHead(nullptr) {}

PasswordManager::~PasswordManager() {
    HistoryNode* current = historyHead;
    while (current != nullptr) {
        HistoryNode* temp = current;
        current = current->next;
        delete temp;
    }
}

void PasswordManager::registerUser(const std::string& username, const std::string& password) {
    users[username] = { username, password };
    std::cout << "User registered successfully!" << std::endl;
}

bool PasswordManager::loginUser(const std::string& username, const std::string& password) {
    if (users.count(username) > 0 && users[username].password == password) {
        currentUser = username;
        std::cout << "Logged in successfully!" << std::endl;
        return true;
    }
    std::cout << "Invalid username or password. Please try again." << std::endl;
    return false;
}

void PasswordManager::addPassword(const std::string& website, const std::string& username, const std::string& password, bool savePassword) {
    if (currentUser.empty()) {
        std::cout << "Please log in first." << std::endl;
        return;
    }

    if (savePassword) {
        passwords[website] = caesarCipherEncrypt(password, 3); // Encrypt password before storing
        addToHistory(website, username, password);
        std::cout << "Password saved for " << website << std::endl;
    } else {
        std::cout << "Password not saved for " << website << std::endl;
    }

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string PasswordManager::getPassword(const std::string& website) {
    if (passwords.count(website) > 0) {
        return caesarCipherEncrypt(passwords[website], -3); // Decrypt password before returning
    }
    return "";
}

void PasswordManager::removePassword(const std::string& website) {
    if (passwords.erase(website) > 0) {
        std::cout << "Password for " << website << " deleted successfully!" << std::endl;
        deleteFromHistory(website); // Remove from history when deleting a password
    } else {
        std::cout << "Password for " << website << " not found." << std::endl;
    }

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void PasswordManager::addToHistory(const std::string& website, const std::string& username, const std::string& password) {
    HistoryNode* newNode = new HistoryNode(website, username, password);
    newNode->next = historyHead;
    historyHead = newNode;
}

void PasswordManager::deleteFromHistory(const std::string& website) {
    HistoryNode* current = historyHead;
    HistoryNode* prev = nullptr;

    while (current != nullptr && current->website != website) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "Website not found in history." << std::endl;
        return;
    }

    if (prev == nullptr) {
        historyHead = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
}

void PasswordManager::displayHistory() {
    HistoryNode* current = historyHead;
    std::cout << "History:" << std::endl;
    while (current != nullptr) {
        std::cout << "Website: " << current->website << ", Username: " << current->username << ", Password: " << current->password << std::endl;
        current = current->next;
    }
}

void PasswordManager::logoutUser() {
    currentUser = "";
    std::cout << "Logged out successfully." << std::endl;
}

void PasswordManager::editPassword(const std::string& website, const std::string& newPassword) {
    if (passwords.count(website) > 0) {
        std::string oldPassword = passwords[website]; // Save the old password

        // Update password in the history if it exists
        HistoryNode* current = historyHead;
        while (current != nullptr) {
            if (current->website == website && current->password == oldPassword) {
                current->password = newPassword;
                break;
            }
            current = current->next;
        }

        passwords[website] = caesarCipherEncrypt(newPassword, 3); // Encrypt and update password

        std::cout << "Password for " << website << " updated successfully!" << std::endl;
    } else {
        std::cout << "Website not found. Cannot edit password." << std::endl;
    }

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string getPasswordMasked() {
    const char BACKSPACE = 8;
    const char ENTER = 13;
    std::string password;
    char ch = _getch();

    while (ch != ENTER) {
        if (ch == BACKSPACE) {
            if (password.length() > 0) {
                std::cout << "\b \b";
                password.pop_back();
            }
        } else {
            std::cout << '*';
            password += ch;
        }
        ch = _getch();
    }
    std::cout << std::endl;
    return password;
}

#endif // FUNCTION_H