#include <iostream>
#include <string>

using namespace std;

int main()
{
    string key, text;
    string const all_letters = "abcdefghijklmnopqrstuvwxyz";
    cout << "Enter the encryption key: ";
    cin >> key;
    // Checking if the key is appropriate

    string::size_type pituus = 0;
    pituus = key.length();
    if (pituus != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }
    
    string::size_type checked;
    string letters_known;
    char checking;
    int ok_chars = 0;

    for (long unsigned int i = 0; i < key.length(); ++i){
        checking = key.at(i);
        checked = all_letters.find(checking);
        if (checked != string::npos){
            checked = letters_known.find(checking);
            if(checked == string::npos){
                letters_known += checking;
                ok_chars += 1;
            }
        }
        else{
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
            }
    }
    // cout << ok_chars << endl;
    if (ok_chars != 26){
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return EXIT_FAILURE;
    }

    // Askin for text to encrypt and checking if it's appropriate
    cout << "Enter the text to be encrypted: ";
    cin >> text;
    for (long unsigned int i = 0; i < text.length(); ++i){
        checking = text.at(i);
        checked = all_letters.find(checking);
        if (checked == string::npos){
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
    }

    // Encrypting the text

    string encrypted_message;
    char old_char, new_char;
    int char_pos;
    for (long unsigned int i = 0; i < text.length(); ++i){
        old_char = text.at(i);
        char_pos = all_letters.find(old_char);
        new_char = key.at(char_pos);
        encrypted_message += new_char;
    }

    cout << "Encrypted text: " << encrypted_message << endl;
}
