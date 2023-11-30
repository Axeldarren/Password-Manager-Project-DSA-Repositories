// PasswordManager.h
#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <iostream>
#include <string>
#include <unordered_map>

class PasswordManager {
private:
    struct HistoryNode {
        std::string website;
        std::string username;
        std::string password;
        HistoryNode* next;

        HistoryNode(const std::string& site, const std::string& usr, const std::string& pwd)
            : website(site), username(usr), password(pwd), next(nullptr) {}
    };

    struct User {
        std::string username;
        std::string password;
    };

    HistoryNode* historyHead;
    std::unordered_map<std::string, std::string> passwords;
    std::unordered_map<std::string, User> users;
    std::string currentUser;

    std::string caesarCipherEncrypt(const std::string& input, int shift);
    void addToHistory(const std::string& website, const std::string& username, const std::string& password);

public:
    PasswordManager();
    ~PasswordManager();

    void registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password);
    void addPassword(const std::string& website, const std::string& username, const std::string& password, bool savePassword);
    std::string getPassword(const std::string& website);
    void removePassword(const std::string& website);
    void deleteFromHistory(const std::string& website);
    void displayHistory();
    void logoutUser();
    void editPassword(const std::string& website, const std::string& newPassword);
};

#endif // PASSWORD_MANAGER_H