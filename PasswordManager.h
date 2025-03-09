#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_PASSWORDS = 100;

template <typename T>
class PasswordManager {
private:
    struct PasswordEntry {
        T website;
        T username;
        T password;
    };

    PasswordEntry entry[MAX_PASSWORDS];
    int numPasswords;

public:
    PasswordManager() {
        numPasswords = 0;
    }

    void viewPasswords() {
        if (numPasswords == 0) {
            cout << "No passwords available." << endl;
            return;
        }
        cout << "Passwords:" << endl;
        for (int i = 0; i < numPasswords; ++i) {
            cout << i + 1 << ". Website: " << entry[i].website << ", Username: " << entry[i].username << ", Password: " << entry[i].password << endl;
        }
    }

    void addPassword(string &website, string &username, string &password) {
        if (numPasswords < MAX_PASSWORDS) {
            entry[numPasswords].website = website;
            entry[numPasswords].username = username;
            entry[numPasswords].password = password;
            numPasswords++;
            cout << "Password added successfully." << endl;
        } else {
            cout << "Password manager is full. No more room for passwords." << endl;
        }
    }

    void deletePassword(int index) {
        if (numPasswords == 0) {
            cout << "No passwords available to delete." << endl;
            return;
        }

        if (index < 1 || index > numPasswords) {
            cout << "Invalid index." << endl;
            return;
        }

        for (int i = index - 1; i < numPasswords - 1; ++i) {
            entry[i] = entry[i + 1];
        }
        numPasswords--;
        cout << "Password deleted successfully." << endl;
    }

    void savePasswordsToFile(const string &filename) {
        ofstream outfile(filename);
        if (outfile.is_open()) {
            for (int i = 0; i < numPasswords; ++i) {
                outfile << entry[i].website << "," << entry[i].username << "," << entry[i].password << endl;
            }
            cout << "Passwords saved to file successfully." << endl;
        } else {
            cout << "Unable to open file for saving passwords." << endl;
        }
    }

    void loadPasswordsFromFile(const string& filename) {
        ifstream infile(filename);
        if (infile.is_open()) {
            string website, username, password;
            while (getline(infile, website, ',') && getline(infile, username, ',') && getline(infile, password)) {
                if (numPasswords < MAX_PASSWORDS) {
                    entry[numPasswords].website = website;
                    entry[numPasswords].username = username;
                    entry[numPasswords].password = password;
                    numPasswords++;
                } else {
                    cout << "Maximum limit reached. Some passwords could not be loaded." << endl;
                    break;
                }
            }
            cout << "Passwords loaded from file successfully." << endl;
        } else {
            cout << "File not found. Starting with empty passwords." << endl;
        }
    }

    void showMenu() {
        int passwordChoice;
        do {
            cout << "-------------------------\n";
            cout << "\nPassword Manager Menu:\n";
            cout << "-------------------------\n\n";
            cout << "1. View Passwords\n";
            cout << "2. Add Password\n";
            cout << "3. Delete Password\n";
            cout << "4. Exit Password Manager\n";
            cout << "Enter your choice: ";
            cin >> passwordChoice;

            if (cin.fail()) {
                cout << "Invalid choice. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            system("cls");
            switch (passwordChoice) {
                case 1:
                    viewPasswords();
                    break;
                case 2: {
                    string website, username, password;
                    cout << "Enter website: ";
                    cin.ignore();
                    getline(cin, website);
                    cout << "Enter username: ";
                    getline(cin, username);
                    cout << "Enter password: ";
                    getline(cin, password);
                    addPassword(website, username, password);
                    break;
                }
                case 3: {
                    int index;
                    cout << "Enter the index of the password to delete: ";
                    cin >> index;
                    deletePassword(index);
                    break;
                }
                case 4:
                    cout << "-------------------------\n";
                    cout << "Exiting Password Manager.\n";
                    cout << "-------------------------\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        } while (passwordChoice != 4);
        savePasswordsToFile("passwords.txt");
    }
};

#endif