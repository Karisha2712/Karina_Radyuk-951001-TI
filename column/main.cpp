#include <iostream>
#include "algorithm"

using namespace std;


void makeKey(string key, int* arr3, int n) {
    int arr[n];
    int arr2[n];
    for (int i = 0; i < n; i++) {
        arr[i] = int(key[i]);
    }
    cout << endl;
    sort(arr + 0, arr + n);
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != arr[i + 1]){
            for (int j = 0; j < n; j++) {
                if (arr[i] == int(key[j])) {
                    arr2[j] = counter;
                    counter++;
                }
            }
        }
    }
    for (int i = 0; i < n; i++){
        arr3[arr2[i]] = i;
    }
}


string encrypt(string encrypted, string key) {
    string result;
    int m = key.length();
    int arr[m];
    makeKey(key, arr, m);
    int len = encrypted.length();
    int n = 0;
    if (len % m == 0) {
        n = len / m;
    } else {
        n = len / m + 1;
    }
    int counter = 0;
    string matrix[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (counter < len) {
                matrix[i][j] = encrypted[counter];
                counter++;
            } else {
                break;
            }
        }
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            result += matrix[j][arr[i]];
        }
    }
    return result;
}


string decrypt(string decrypted, string key){
    string result;
    int m = key.size();
    int arr[m];
    makeKey(key, arr, m);
    int len = decrypted.size();
    int n = 0;
    if (len % m == 0) {
        n = len / m;
    } else {
        n = len / m + 1;
    }
    int rest = len % m;
    string matrix[n][m];
    int counter = 0;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n - 1; j++){
            matrix[j][arr[i]] = decrypted[counter];
            counter++;
        }
        if (arr[i] < rest){
            matrix[n - 1][arr[i]] = decrypted[counter];
            counter++;
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            result += matrix[i][j];
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
    string str;
    string key;
    cout << "Enter text" << endl;
    getline(cin, str);
    str = DeleteSpace(str);
    cout << "Enter key" << endl;
    cin >> key;
    str = encrypt(str, key);
    cout << "Encrypted: " << str << endl;
    str = decrypt(str, key);
    cout << "Decrypted: " << str << endl;
    return 0;
}
