#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_NOTES = 100;

template <typename T>
class NotesManager {
private:
    T notes[MAX_NOTES];
    int numNotes;

public:
    NotesManager() {
        numNotes = 0;
    }

    void viewNotes() {
        if (numNotes == 0) {
            cout << "\"Oops! It seems the notes manager went on vacation...without leaving any notes behind!\"" << endl;
            return;
        }
        cout << "Notes:" << endl;
        for (int i = 0; i < numNotes; ++i) {
            cout << i + 1 << ". " << notes[i] << endl;
        }
    }

    void addNote(string &note) {
        if (numNotes < MAX_NOTES) {
            notes[numNotes++] = note;
            cout << "Note added successfully." << endl;
        } else {
            cout << "\"Sorry, the notes manager is full! No more room for your brilliant ideas.\"" << endl;
        }
    }

    void deleteNote(int index) {
        if (numNotes == 0) {
            cout << "No notes available to delete." << endl;
            return;
        }

        if (index < 1 || index > numNotes) {
            cout << "\"Whoops! Looks like you're trying to reach notes from a parallel universe\"\nInvalid index number..." << endl;
            return;
        }

        for (int i = index - 1; i < numNotes - 1; ++i) {
            notes[i] = notes[i + 1];
        }
        numNotes--;
    }

    void saveNotesToFile(const string& filename) {
        ofstream outfile(filename);
        if (outfile.is_open()) {
            for (int i = 0; i < numNotes; ++i) {
                outfile << notes[i] << endl;
            }
        } else {
            cout << "Unable to open file for saving notes." << endl;
        }
    }

    void loadNotesFromFile(const string& filename) {
        ifstream infile(filename);
        if (infile.is_open()) {
            string note;
            while (getline(infile, note)) {
                if (numNotes < MAX_NOTES) {
                    notes[numNotes++] = note;
                } else {
                    cout << "Maximum limit reached. Some notes could not be loaded." << endl;
                    break;
                }
            }
        } else {
            cout << "File not found. Starting with empty notes." << endl;
        }
    }

    void showMenu() {
        int notesChoice;
        string note;
        do {
            cout << "-------------------------\n";
            cout << "Notes Manager Menu:\n";
            cout << "-------------------------\n\n";
            cout << "1. View Note\n";
            cout << "2. Add Note\n";
            cout << "3. Delete Note\n";
            cout << "4. Exit Notes Manager\n";
            cout << "Enter your choice: ";
            cin >> notesChoice;

            if (cin.fail()) {
                cout << "Invalid choice. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore();

            system("cls");
            switch (notesChoice) {
                case 1:
                    viewNotes();
                    break;
                case 2:
                    cout << "Enter your note: ";
                    getline(cin, note);
                    addNote(note);
                    break;
                case 3:
                    int index;
                    cout << "\nEnter the index of the note to delete: ";
                    cin >> index;
                    deleteNote(index);
                    break;
                case 4:
                    cout << "Exiting Notes Manager." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (notesChoice != 4);
        saveNotesToFile("notes.txt");
    }
};

#endif
