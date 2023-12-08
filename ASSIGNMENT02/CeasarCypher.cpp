#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string CaesarCipherDecryption(string ciphertext, int key)
{
    string plaintext = "";
    for (int i = 0; i < ciphertext.length(); i++)
    {
        plaintext += char(int(ciphertext[i] - key - 65 + 26) % 26 + 65);
    }
    return plaintext;
}

int main()
{
    int Choice, key;
    string input_text;

    cout << "-----Caesar Cipher Decryption-----\n";
    cout << "Enter Choice:\n1) Console\n2) File\n";
    cin >> Choice;

    cout << "Enter key: ";
    cin >> key;

    switch (Choice)
    {
    case 1:
        cout << "Enter cipher text: ";
        cin >> input_text;
        break;
    case 2:
        {
            ifstream inputFile("input.txt");
            if (!inputFile)
            {
                cerr << "Error opening input file." << endl;
                return 1;
            }

            getline(inputFile, input_text);
            inputFile.close();
        }
        break;
    default:
        cerr << "Invalid choice." << endl;
        return 1;
    }

    string plaintext = CaesarCipherDecryption(input_text, key);

    // Print the decrypted text to the console
    cout << "Decrypted Text: " << plaintext << endl;

    // Open the "output.txt" file for writing decrypted text
    ofstream outputFile("output.txt");
    if (!outputFile)
    {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    // Write the decrypted text to the output file
    outputFile << "Decrypted Text: " << plaintext << endl;

    // Close the output file
    outputFile.close();

    return 0;
}
