#include <iostream>
#include <string>
using namespace std;


void printMatrix(int** matrix, int n){
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int** rotateKey(int n, int** matrix) {
    int** rotatedMatrix;
    rotatedMatrix = new int *[n];
    for (int i = 0; i < n; i++){
        rotatedMatrix[i] = new int [n];
    }
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            rotatedMatrix[i][j] = matrix[n - 1 - j][i];
            rotatedMatrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
            rotatedMatrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
            rotatedMatrix[j][n - 1 - i] = matrix[i][j];
        }
    }
   return rotatedMatrix;
}



int getTableSize(){
    int tableSize;
    cout << "Enter table size: " << endl;
    cin >> tableSize;
    while (tableSize % 2 != 0){
        cout << "The size of the table must be even. Enter again: " << endl;
        cin >> tableSize;
    }
    return tableSize;
}

int** generateNumerateMatrix(int n){
    int** matrix;
    matrix = new int *[n];
    for (int i = 0; i < n; i++){
        matrix[i] = new int [n];
    }
    int counter = 1;
    for (int i = 0; i < n / 2; i++) {
        for (int j = i; j < n - i - 1; j++) {
            matrix[i][j] = counter;
            matrix[n - 1 - j][i] = counter;
            matrix[n - 1 - i][n - 1 - j] = counter;
            matrix[j][n - 1 - i] = counter;
            counter++;
        }
    }
    return matrix;

}

bool generateMatrix(int tableSize, int **matrix){
    int holesNum = tableSize * tableSize / 4;
    for (int i = 0; i < tableSize; i++){
        for (int j = 0; j < tableSize; j++){
            matrix[i][j] = 0;
        }
    }
    int x;
    int y;
    for (int i = 0; i < holesNum; i++){
        cout << "Enter x and y" << endl;
        cin >> x;
        cin >> y;
        matrix[x][y] = 1;
    }
    cout << "Lattice is" << endl;
    printMatrix(matrix, tableSize);
    bool result = false;
    int counter = 1;
    int** numerateMatrix = generateNumerateMatrix(tableSize);
    while (counter <= tableSize){
        result = false;
        for(int i = 0; i < tableSize; i++){
            for (int j = 0; j < tableSize; j++){
                if ((numerateMatrix[i][j] == counter) && (matrix[i][j] == 1)){
                    result = true;
                }
            }
        }
        if (!result){
            return result;
        }
        counter++;
    }
    return result;
}


string encrypt(string encrypted, int n, int** keyMatrix){
    string result;
    string matrix[n][n];
    int counter = 0;
    while (counter < encrypted.length()){
        for(int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if ((keyMatrix[i][j] == 1) && (counter < encrypted.length())){
                    matrix[i][j] = encrypted[counter];
                    counter++;
                }
            }
        }
        keyMatrix = rotateKey(n, keyMatrix);
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
                result += matrix[i][j];
        }

    }
    return result;
}

string decrypt(string decrypted, int n, int** keyMatrix){
    string result;
    string matrix[n][n];
    int counter = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            if (counter < decrypted.length()){
                matrix[i][j] = decrypted[counter];
                counter++;
            }
            else{
                break;
            }
        }
    }
    counter = 0;
    while (counter < decrypted.length()){
        for(int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if ((keyMatrix[i][j] == 1) && (counter < decrypted.length())){
                   result += matrix[i][j];
                    counter++;
                }
            }
        }
        keyMatrix = rotateKey(n, keyMatrix);
    }
    return result;
}

string DeleteSpace(string str){
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
    cout << "Enter text" << endl;
    getline(cin, encrypted);
    encrypted = DeleteSpace(encrypted);
    int tableSize = getTableSize();
    if (tableSize * tableSize < encrypted.length()){
        cout << "Incorrect size";
    }
    else{
        int **matrix;
        matrix = new int *[tableSize];
        for (int i = 0; i < tableSize; i++){
            matrix[i] = new int [tableSize];
        }
        if (generateMatrix(tableSize, matrix)){
            string str = encrypt(encrypted, tableSize, matrix);
            cout << "Encrypted: " << str << endl;
            cout << "Decrypted: " << decrypt(str, tableSize, matrix);
        }
        else{
            cout << "Incorrect coordinates";
        }
        return 0;
    }
}
