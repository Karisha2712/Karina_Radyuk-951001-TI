#include <iostream>
#include <string>

using namespace std;

const int n = 26;

string generateKey(string key, string encrypted){
    string result = key;
    if (result.length() < encrypted.length()){
        int i = result.length() - 1;
        int j = 0;
        while (i < encrypted.length()){
            result = result + encrypted[j];
            i++;
            j++;
        }
    }
    return result;
}

string generateAlphabet(char start){
    string result;
    if (start == 'a') {
        for (int i = 0; i < n; i++){
            result += start;
            start++;
        }
        return result;
    }
}

int getLetterNum(string& alphabet, char letter){
    return alphabet.find(letter);
}

string shiftAlphabet(string& alphabet, int num){
    string result;
    result = alphabet;
    for (int i = 0; i < num; i++){
        char first = result[0];
        result.erase(0, 1);
        result += first;
    }
    return result;
}

string encrypt(string key, string encrypted){
    string result;
    key = generateKey(key, encrypted);
    string alphebet = generateAlphabet('a');
    int len = encrypted.length();
    for (int i = 0; i < len; i++){
        int shiftNum = getLetterNum(alphebet, key[i]);
        int letterNum = getLetterNum(alphebet, encrypted[i]);
        string shiftedAlphebet = shiftAlphabet(alphebet, shiftNum);
        char symbol = shiftedAlphebet[letterNum];
        result = result + symbol;
    }
    return result;
}

string decrypt(string key, string decrypted){
    string result;
    string alphebet = generateAlphabet('a');
    int len = decrypted.length();
    for (int i = 0; i < len; i++){
        int shiftNum = getLetterNum(alphebet, key[i]);
        string shiftedAlphebet = shiftAlphabet(alphebet, shiftNum);
        int letterNum = getLetterNum(shiftedAlphebet, decrypted[i]);
        char symbol = alphebet[letterNum];
        result += symbol;
        if (key.length() < decrypted.length()){
            key += symbol;
        }
    }
    return result;
}

string DeleteSpace(string& str){
    string result;
    for(auto i : str){
        if (i != ' '){
            result += i;
        }
    }
    return result;
}

int main() {
    string encrypted;
    string key;
    cout << "Enter text" << endl;
    getline(cin, encrypted);
    encrypted = DeleteSpace(encrypted);
    cout << "Enter key" << endl;
    cin >> key;
    string alphabet = generateAlphabet('a');
    string str = encrypt(key, encrypted);
    cout << "Encrypted: " << str << endl;
    cout << "Decrypted: " << decrypt(key, str) << endl;
    return 0;
}
