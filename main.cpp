/*TODO
 * Refine the conversion from cipher text to plain text to decode the message in the text file
 * Maybe add a way to print out plain text onto a file?
 */


#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

class SubstitutionCipher {
private:
    unordered_map<char, double> cipherTextFreq;     //hash map holding cipher text
    unordered_map<char, char> plainText;            //hash map holding plain text conversion
    string cipherText;                              //string that holds contents of file
    string fileName;                                //holds name of file to be read
    double cipherTextCount;                         //Keeps track of character count(not including whitespace);
    const char letterFreqAnalysis[24] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f',
                                         'g', 'y', 'p', 'b', 'v', 'k', 'x', 'j'};

public:
    SubstitutionCipher(string fName);

    void getFileInput();                    //Populates cipherText with file contents

    void getCipherTextFreq(char k);         //Calculates the frequency of a character

    void setPlainText();                    //This works. Uses array to get plaintext

    void displayCipherTextFreq();

    void displayPlainText();              //Works with getMaxFreq()

    void displayCipherPlainTextKey();       //Displays cipher to plain text conversion



};


SubstitutionCipher::SubstitutionCipher(string fName) {
    cipherTextCount = 0;
    fileName = fName;

    for (char text: letterFreqAnalysis)
        plainText.insert(make_pair(text, NULL));
}

/*
* Insert data from file to string cipherText
* Use the cipherText string to insert values into hash table one by one
*       If(character doesn't appear in hash table) Make new entry && increment cipherTextCount
*       else increment character's("key") secondary entry in hash table && increment cipherTextCount
* Remove ' ' total from cipherTextCount to prevent spaces from being included in the frequency calculation
* Remove ' ' from hash table
* Iterate through hash table and call on getCipherTextFreq()
*/
void SubstitutionCipher::getFileInput() {
    ifstream inFile;
    inFile.open(fileName, ios::in);

    while (!inFile.eof()) {
        getline(inFile, cipherText);
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
    auto result = cipherTextFreq.find(' ');
    cipherTextCount -= result->second;
    cipherTextFreq.erase(' ');

    for (auto &calc: cipherTextFreq) {
        getCipherTextFreq(calc.first);
    }
}

//Calculates the frequency of each character in the hash table
void SubstitutionCipher::getCipherTextFreq(char k) {
    auto index = cipherTextFreq.find(k);
    index->second /= cipherTextCount;
}

void SubstitutionCipher::displayCipherTextFreq() {
    for (auto &display: cipherTextFreq)
        cout << display.first << ' ' << display.second << '\n';

    cout << "Cipher Text Count: " << cipherTextCount;


}

void SubstitutionCipher::displayPlainText() {

    for (auto &display: plainText)
        cout << display.first << ' ' << display.second << '\n';


}
/*
 * Determines the plain text of the file
 * Traverse through both the plainTextAnalysis array and cipherTextFreq map
 * max counter set(and reset) at 0 at the start of plainTextAnalysis traversal
 * get the max value from cipherTextFreq mapped values
 * grab max value and store in key variable
 * erase key entry from cipherTextFreq to avoid encountering entry in next loop
 * run getFileInput() outside of loops to get cipherTextFreq map back
 * display plain text
 */
void SubstitutionCipher::setPlainText(){
    char key;
    double max;
    int i = 0;

    for(auto plainTextTraverse : plainText){
        max = 0.0;
        for(auto cipherTextTraverse : cipherTextFreq){
            if(cipherTextTraverse.second > max){
                max = cipherTextTraverse.second;
                key = cipherTextTraverse.first;
            }
        }

        auto find = plainText.find(letterFreqAnalysis[i]);
        find->second = key;
        cipherTextFreq.erase(key);
        i++;
    }
};


void SubstitutionCipher::displayCipherPlainTextKey(){
    cout << "Cipher Text -----> Plain Text" << endl;
    for(auto traverse : plainText)
        cout << "\t" << traverse.second << "\t\t\t\t\t" << traverse.first << endl;
}


int main() {
    SubstitutionCipher sub("cipher.txt");
    sub.getFileInput();
    sub.displayCipherTextFreq();
    sub.setPlainText();
    cout << endl;
    sub.displayCipherPlainTextKey();


    return 0;
}
