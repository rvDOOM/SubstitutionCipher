#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

class SubstitutionCipher {
private:
    unordered_map<char, double> cipherTextFreq;     //hash map holding cipher text
    unordered_map<char, char> plainText;            //hash map holding plain text conversion
    string cipherText;                              //string that holds contents of file
    string fileName;                                //holds name of file to be read
    double cipherTextCount;                         //Keeps track of character count(not including whitespace);
    const char letterFreqAnalysis[26] = {'e', 't', 'a', 'n', 'o', 'i', 'h', 's', 'r', 'c', 'd', 'l', 'm', 'g', 'p', 'u',
                                         'f', 'y', 'w', 'b', 'v', 'z', 'k', 'j', 'x', 'q'};

public:
    SubstitutionCipher(string fName);

    void getFileInput();                    //Populates cipherText with file contents

    void setCipherTextFreq(char k);         //Calculates the frequency of a character

    void setPlainText();                    //This works. Uses array to get plaintext

    void displayCipherTextFreq();

    void displayPlainText();              //Works with getMaxFreq()

    void displayCipherText();

    void displayCipherPlainTextKey();       //Displays cipher to plain text conversion

    void driver();

};

//Constructor
SubstitutionCipher::SubstitutionCipher(string fileName) {
    cipherTextCount = 0;
    this->fileName = fileName;
}

void SubstitutionCipher::getFileInput() {
    cipherTextCount = 0;
    ifstream inFile;
    inFile.open(fileName, ios::in);

    //Iterate through file and get contents string by string
    while (!inFile.eof()) {
        getline(inFile, cipherText);
        /* Iterate through string
         * If char is not in cipher text hashmap, create key && element = 1, count++
         * else increment element in key by 1, count++
         */
        for (int i = 0; cipherText[i]; i++) {
            if (cipherTextFreq.find(cipherText[i]) == cipherTextFreq.end()) {
                cipherTextFreq.insert(make_pair(cipherText[i], 1));
                cipherTextCount++;
            } else {
                cipherTextFreq[cipherText[i]]++;
                cipherTextCount++;
            }
        }
    }
    //Remove all ' ' values from hash map and count
    auto result = cipherTextFreq.find(' ');
    cipherTextCount -= result->second;
    cipherTextFreq.erase(' ');

    //iterate through hash map and calculate letter analysis frequency
    for (auto &calc: cipherTextFreq) {
        setCipherTextFreq(calc.first);
    }
}

//Calculates the frequency of each character in the hash table
void SubstitutionCipher::setCipherTextFreq(char k) {
    auto index = cipherTextFreq.find(k);
    index->second /= cipherTextCount;
}

void SubstitutionCipher::displayCipherTextFreq() {
    for (auto &display: cipherTextFreq)
        cout << display.first << ' ' << display.second << '\n';
    cout << "Cipher Text Count: " << cipherTextCount;
}


void SubstitutionCipher::setPlainText() {
    char key;
    double max;
    int i = 0;

    /* inserts letter frequncy array into plain text hash map
     * stops when j exceeds number of keys in cipher text hash map
     */
    for (int j = 0; j < cipherTextFreq.size(); j++)
        plainText.insert(make_pair(letterFreqAnalysis[j], NULL));

    //Get key with highest frequency in cipher text hash map
    //set max = 0 when previous max has been found
    for (auto plainTextTraverse: plainText) {
        max = 0.0;

        for (auto cipherTextTraverse: cipherTextFreq) {
            if (cipherTextTraverse.second > max) {
                max = cipherTextTraverse.second;
                key = cipherTextTraverse.first;
            }
        }

        /* Add key of highest frequency in cipher text as element to plain text
         * plain text key is determined by order of hard coded letterFrequncyAnalysis[]
         * erase highest frequncy key from cipher text hash map, i++
         */
        auto find = plainText.find(letterFreqAnalysis[i]);
        find->second = key;
        cipherTextFreq.erase(key);
        i++;
    }
    getFileInput();             //repopulate cipherTextFrequency hash map
}

void SubstitutionCipher::displayCipherPlainTextKey() {
    cout << "Cipher Text ------> Frequency -------> Plain Text" << endl;
    char key;
    for (auto traverse: plainText) {
        key = traverse.second;
        auto find = cipherTextFreq.find(key);
        if (traverse.first == 'e')
            cout << "\t" << traverse.second << "\t\t\t\t" << find->second << "\t\t\t\t\t" << traverse.first << endl;
        else
            cout << "\t" << traverse.second << "\t\t\t\t" << find->second << "\t\t\t\t" << traverse.first << endl;
    }
    cout << endl;
}

void SubstitutionCipher::displayCipherText() {
    ifstream inFile;
    string display;
    char key;


    cout << "Cipher Text:" << endl;

    inFile.open(fileName, ios::in);
    while (!inFile.eof()) {
        getline(inFile, display);
        cout << display << endl;
    }
}


void SubstitutionCipher::displayPlainText() {

    ifstream inFile;
    string decrypt;
    char key;

    cout << "Plain Text:" << endl;

    inFile.open(fileName, ios::in);
    while (!inFile.eof()) {
        getline(inFile, decrypt);
        for (int i = 0; i < decrypt.size(); i++) {
            if (decrypt[i] == ' ')
                cout << ' ';
            else {
                for (auto plainTraverse: plainText) {
                    if (plainTraverse.second == decrypt[i]) {
                        cout << plainTraverse.first;
                    }
                }
            }
        }
        cout << endl;
    }
}

void SubstitutionCipher::driver() {
    getFileInput();
    displayCipherText();
    setPlainText();
    displayCipherPlainTextKey();
    displayPlainText();
}


int main() {

    SubstitutionCipher sub("cipher.txt");
    sub.driver();

    return 0;
}
