#include <iostream>
#include <fstream> // for file handling
#include <string> // for string handling
#include <limits> // for cin.ignore()
#include <windows.h> // for Sleep()

#include "Authenticator.h"
#include "User.h"
#include "NotesManager.h"
#include "PasswordManager.h"

using namespace std;

int main() 
{
    const string notesFilename = "notes.txt";
    const string passwordsFilename = "passwords.txt";

    Authenticator authenticator;
    User user;

    NotesManager<string> notesManager;
    PasswordManager<string> passwordManager;

    bool success = false;

    do 
    {
        ifstream file("user.txt");

        if (!file || file.peek() == ifstream::traits_type::eof()) 
        {
            cout << "------------------------------\n";
            cout << "    Welcome to the MANAGER \n";
            cout << "------------------------------\n\n";
            cout << "No user registered. Let's create an account.\n";
            authenticator.createAccount();
        } 
        else 
        {
            cout << "-------------------------\n";
            cout << "    Welcome to MANAGER    \n";
            cout << "-------------------------\n\n";
            cout << "User found. Please log in.\n";
            string storedUsername, storedPassword;
            file >> storedUsername >> storedPassword;
            file.close();

            string username, password;
            user.loginInput(username, password);
            success = user.loginProcess(storedUsername, storedPassword, username, password);
            user.loginOutput(success);
        }
    } while (!success);
    Sleep(1500);
    system("cls");

    notesManager.loadNotesFromFile(notesFilename);
    passwordManager.loadPasswordsFromFile(passwordsFilename);

    int mainMenuChoice;
    do {
        cout << "-------------------------\n";
        cout << "Main Menu:\n";
        cout << "-------------------------\n\n";
        cout << "1. Enter Notes Manager\n";
        cout << "2. Enter Password Manager\n";
        cout << "3. Exit Program\n";
        cout << "Enter your choice: ";
        cin >> mainMenuChoice;

        if (cin.fail())
        {
            cout << "Invalid choice. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Sleep(1500);
            system("cls");
            continue;
        }

        switch (mainMenuChoice) {
            case 1:
                notesManager.showMenu();
                break;
            case 2:
                passwordManager.showMenu();
                break;
            case 3:
                system("cls");
                cout << "-------------------------\n";
                cout << "Exiting the program.\n";
                cout << "-------------------------\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (mainMenuChoice != 3);
    return 0;
}
