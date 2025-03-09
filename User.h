#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <conio.h> // for getch()

using namespace std;

class User {
public:
    void loginInput(string& username, string& password) {
        cout << "-----------------------\n";
        cout << "       Login Page      \n";
        cout << "-----------------------\n";
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";

        char ch;
        do {
            ch = getch();
            if (isdigit(ch) || isalpha(ch) || ispunct(ch)) {
                password += ch;
                cout << "*";
            }
        } while (isdigit(ch) || isalpha(ch) || ispunct(ch));
    }

    bool loginProcess(const string& storedUsername, const string& storedPassword, string username, string password)
    {
        return (username == storedUsername && password == storedPassword);
    }

    void loginOutput(bool success) 
    {
        cout << endl;
        if (success) 
        {
            cout << "-----------------------\n";
            cout << "    Login successful!  \n";
            cout << "-----------------------\n\n";
        } 
        else 
        {
            cout << "-----------------------\n";
            cout << " Invalid username or password! \n";
            cout << "-----------------------\n\n";
            Sleep(1500);
            system("cls");
        }
    }
};

#endif
