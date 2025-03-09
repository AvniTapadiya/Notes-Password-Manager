#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h> // for Sleep()

using namespace std;

class Authenticator {
public:
    void createAccount() {
        ofstream file("user.txt");
        if (file.is_open()) {
            string username, password;
            cout << "-----------------------\n";
            cout << "     Create Account    \n";
            cout << "-----------------------\n";
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            file << username << " " << password;
            cout << "\nUser registered successfully!\n\n";
            Sleep(1000);
            system("cls");
        } 
        else 
        {
            cerr << "Error: Unable to open file for writing!\n";
        }
    }
};

#endif
