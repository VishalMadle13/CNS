#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to remove spaces and make the input uppercase
string preprocessText(string text) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            result += toupper(c);
        }
    }
    return result;
}

// Function to generate the Playfair matrix from the key
vector<vector<char>> generatePlayfairMatrix(string key) {
    vector<vector<char>> matrix(5, vector<char>(5, ' '));
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Note: No 'J' in the Playfair matrix
    
    // Fill the matrix with the key
    int keyIndex = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyIndex < key.length()) {
                char currentChar = toupper(key[keyIndex]);
                // Check if the character is already in the matrix or is 'J'
                if (matrix[i][j] == ' ' && currentChar != 'J') {
                    matrix[i][j] = currentChar;
                } else {
                    keyIndex++;
                    j--;
                }
                keyIndex++;
            } else {
                // Fill the remaining matrix cells with the alphabet
                for (char c : alphabet) {
                    bool found = false;
                    // Check if the character is already in the matrix
                    for (int x = 0; x < 5; x++) {
                        for (int y = 0; y < 5; y++) {
                            if (matrix[x][y] == c || c == 'J') {
                                found = true;
                                break;
                            }
                        }
                        if (found) {
                            break;
                        }
                    }
                    if (!found) {
                        matrix[i][j] = c;
                        break;
                    }
                }
            }
        }
    }
    
    return matrix;
}

// Function to find the coordinates of a character in the Playfair matrix
pair<int, int> findCoordinates(vector<vector<char>>& matrix, char c) {
    pair<int, int> coordinates;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                coordinates.first = i;
                coordinates.second = j;
                return coordinates;
            }
        }
    }
    return coordinates; // Character not found in the matrix
}

// Function to encrypt a digraph (two-character block)
string encryptDigraph(vector<vector<char>>& matrix, char a, char b) {
    pair<int, int> coordA = findCoordinates(matrix, a);
    pair<int, int> coordB = findCoordinates(matrix, b);
    
    if (coordA.first == coordB.first) { // Same row
        return string(1, matrix[coordA.first][(coordA.second + 1) % 5]) +
               string(1, matrix[coordB.first][(coordB.second + 1) % 5]);
    } else if (coordA.second == coordB.second) { // Same column
        return string(1, matrix[(coordA.first + 1) % 5][coordA.second]) +
               string(1, matrix[(coordB.first + 1) % 5][coordB.second]);
    } else { // Forming a rectangle
        return string(1, matrix[coordA.first][coordB.second]) +
               string(1, matrix[coordB.first][coordA.second]);
    }
}

// Function to perform Playfair encryption
string playfairEncrypt(string plaintext, string key) {
    string processedText = preprocessText(plaintext);
    vector<vector<char>> matrix = generatePlayfairMatrix(key);
    for(auto x : matrix){
        for(auto c : x)cout<<c<<" ";
        cout<<endl;
    }
    string ciphertext = "";
    
    for (int i = 0; i < processedText.length(); i += 2) {
        if (i + 1 < processedText.length()) {
            ciphertext += encryptDigraph(matrix, processedText[i], processedText[i + 1]);
        } else {
            // If there's an odd number of characters, pad the last one with 'X'
            ciphertext += encryptDigraph(matrix, processedText[i], 'X');
        }
    }
    
    return ciphertext;
}

int main() {
    string key, plaintext;
    
    cout << "Enter the key (no spaces and only uppercase letters): ";
    cin >> key;
    
    cout << "Enter the plaintext: ";
    cin.ignore(); // Ignore newline from previous input
    getline(cin, plaintext);
    
    string ciphertext = playfairEncrypt(plaintext, key);
    
    cout << "Cipher Text: " << ciphertext << endl;
    
    return 0;
}
