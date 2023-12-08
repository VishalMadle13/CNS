#include <iostream>
#include <fstream>
#include <string>
using namespace std;
string CaesarCipherEncryption(string text, int key)
{
    string ciphertext = "";
    for (int i = 0; i < text.length(); i++)
    {
        ciphertext += char(int(text[i] + key - 65) % 26 + 65);
    }
    return ciphertext;
}
int main()
{
    int Choice, key;
    string plain_text;
    cout << "-----Caesar Cipher Encryption-----\n";
    cout << "Enter Choice:\n1) Console\n2) File\n";
    cin >> Choice;
    cout << "Enter key: ";
    cin >> key;
    switch (Choice)
    {
    case 1:
        cout << "Enter plain text: ";
        cin >> plain_text;
        break;
    case 2:
        {
            ifstream inputFile("input.txt");
            if (!inputFile)
            {
                cerr << "Error opening input file." << endl;
                return 1;
            }

            getline(inputFile, plain_text);
            inputFile.close();
        }
        break;
    default:
        cerr << "Invalid choice." << endl;
        return 1;
    }
    string ciphertext = CaesarCipherEncryption(plain_text, key);
    // Open the "output.txt" file for writing
    ofstream outputFile("output.txt");
    if (!outputFile)
    {
        cerr << "Error opening output file." << endl;
        return 1;
    }
    // Write the cipher text to the output file
    outputFile << "Cipher Text: " << ciphertext << endl;
    // Close the output file
    outputFile.close(); 
    cout << "Cipher Text: " << ciphertext << endl; 
    return 0;
}
