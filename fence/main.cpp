#include <iostream>
#include <string>
using namespace std;

string encrypt(int rows, string encrypted){
    int period = 2 * (rows - 1);
    int n = encrypted.length();
    string matrix[rows][n];
    for (int i = 0; i < n; i++){
        int rest = i % period;
        int row = rows - 1 - abs(rows - 1 - rest);
        matrix[row][i] = encrypted[i];
    }
    string result;
    for (int j = 0; j < rows; j++){
        for (int i = 0; i < n; i++){
            if (!matrix[j][i].empty()){
                result += matrix[j][i];
            }
        }
    }

    return result;
}

string decrypt(int rows, string decrypted) {
    string result;
    int period = 2 * (rows - 1);
    int n = decrypted.length();
    string matrix[rows][n];
    for (int i = 0; i < n; i++) {
        int rest = i % period;
        int row = rows - 1 - abs(rows - 1 - rest);
        matrix[row][i] = '*';
    }
    int counter = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == "*") {
                matrix[i][j] = decrypted[counter];
                counter++;
            }
        }
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < rows; i++) {
            if (!matrix[i][j].empty()) {
                result += matrix[i][j];
            }
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
    int rows;
    string str;
    cout << "Enter text" << endl;
    getline(cin, str);
    str = DeleteSpace(str);
    cout << "Enter key" << endl;
    cin >> rows;
    str = encrypt(rows, str);
    cout << "Encrypted text: "<< str << endl;
    str = decrypt(rows, str);
    cout << "Decrypted text: " << str << endl;
    return 0;
}
