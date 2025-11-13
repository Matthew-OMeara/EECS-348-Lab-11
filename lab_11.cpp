#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <iomanip>

using namespace std;

class Matrix
{
    private:
        int size;
        int* matrix;
    public:
        Matrix(int matrixSize = 0, list<int> entries = list<int>());
        Matrix(const Matrix& other);
        void printMatrix();
        Matrix operator+(Matrix const& obj);
        Matrix operator*(Matrix const& obj);
        void diagonalSum();
        void swapRows(Matrix obj, int row1 = 0, int row2 = 1);
        void swapCols(Matrix obj, int col1 = 0, int col2 = 1);
        void changeElement(Matrix obj, int row = 0, int col = 0, int value = 100);
};

Matrix::Matrix(int matrixSize, list<int> entries) {
    size = matrixSize;
    matrix = new int [size * size];
    list<int>::iterator it = entries.begin();
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            matrix[(i * size) + j] = *it;
            advance(it, 1);
        }
    }
}

Matrix::Matrix(const Matrix& other) {
    size = other.size;
    if (size > 0) {
        matrix = new int [size * size];
        copy(other.matrix, other.matrix + (size * size), matrix);
    }
}

void Matrix::printMatrix() {
    int maxWidth = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int currentWidth = to_string(matrix[(i*size) + j]).length();
            if (currentWidth > maxWidth) {
                maxWidth = currentWidth;
            }
        }
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << setw(maxWidth + 2) << matrix[(i*size) + j];
        }
        cout << endl;
    }
    cout << endl;
}

list<list<int> > readData(string filename, int& size) {
    ifstream inputFile(filename);

    inputFile >> size;

    int recentNum;
    list<list<int> > entries;
    list<int> entry;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
           if(inputFile >> recentNum) {
                entry.push_back(recentNum);
            }
        }
    }
    entries.push_back(entry);
    entry.clear();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
           if(inputFile >> recentNum) {
                entry.push_back(recentNum);
            }
        }
    }
    entries.push_back(entry);
    inputFile.close();

    return entries;
}

Matrix Matrix::operator+(Matrix const& obj) {
    Matrix matrixC;
    matrixC.size = size;
    matrixC.matrix = new int [size * size];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrixC.matrix[(i*size) + j] = matrix[(i*size) + j] + obj.matrix[(i*size) + j];
        }
    }
    return matrixC;
}

Matrix Matrix::operator*(Matrix const& obj) {
    Matrix matrixC;
    matrixC.size = size;
    matrixC.matrix = new int [size * size];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrixC.matrix[(i * size) + j] = 0;
            for (int k = 0; k < size; ++k) {
                matrixC.matrix[(i * size) + j] += matrix[(i*size) + k] * obj.matrix[(k*size) + j];
            }
        }
    }
    return matrixC;
}

void Matrix::diagonalSum() {
    int mainDiagonal = 0;
    for (int i = 0; i < size; ++i) {
        mainDiagonal += matrix[(i * size) + i];
    }
    int secDiagonal = 0;
    for (int i = size - 1; i > -1; --i) {
        secDiagonal += matrix[((3-i) * size) + i];
    }
    cout << "Main Diagonal: " << mainDiagonal << endl;
    cout << "Secondary Diagonal: " << secDiagonal << endl;
    cout << endl;
}

void Matrix::swapRows(Matrix obj, int row1, int row2) {
    int tempEntry = 0;
    if (-1 < row1 && row1 < obj.size && -1 < row2 && row2 < obj.size) {
        for (int i = 0; i < obj.size; ++i) {
            tempEntry = obj.matrix[(row1 * obj.size) + i];
            obj.matrix[(row1 * obj.size) + i] = obj.matrix[(row2 * obj.size) + i];
            obj.matrix[(row2 * obj.size) + i] = tempEntry;
        }
        obj.printMatrix();
    } else {
        cout << "Invalid rows entered, make sure you are entering the row indices\n" << endl;
    }
}

void Matrix::swapCols(Matrix obj, int col1, int col2) {
    int tempEntry = 0;
    if (-1 < col1 && col1 < obj.size && -1 < col2 && col2 < obj.size) {
        for (int i = 0; i < obj.size; ++i) {
            tempEntry = obj.matrix[(i * obj.size) + col1];
            obj.matrix[(i * obj.size) + col1] = obj.matrix[(i * obj.size) + col2];
            obj.matrix[(i * obj.size) + col2] = tempEntry;
        }
        obj.printMatrix();
    } else {
        cout << "Invalid columns entered, make sure you are entering the column indices\n" << endl;
    }
}

void Matrix::changeElement(Matrix obj, int row, int col, int value) {
    if (-1 < row && row < obj.size && -1 < col && col < obj.size) {
        obj.matrix[(row*size) + col] = value;
        obj.printMatrix();
    } else {
        cout << "Invalid indice entered, make sure you are entering the indeces starting at zero\n" << endl;
    }
}

int main() {
    int size;
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;
    cout << endl;

    list<list<int> > entries = readData(filename, size);
    list<list<int> >::iterator it = entries.begin();
    Matrix matrixA = Matrix(size, *it);
    advance(it, 1);
    Matrix matrixB = Matrix(size, *it);
    cout << "Matrix A:\n" << endl;
    matrixA.printMatrix();
    cout << "Matrix B:\n" << endl;
    matrixB.printMatrix();

    cout << "Matrix C = A + B:\n" << endl;
    Matrix matrixC = matrixA + matrixB;
    matrixC.printMatrix();

    cout << "Matrix D = A * B:\n" << endl;
    Matrix matrixD = matrixA * matrixB;
    matrixD.printMatrix();

    cout << "Sum of diagonal elements in A:\n" << endl;
    matrixA.diagonalSum();

    cout << "Swap matrix rows in A:" << endl;
    int row1 = 0;
    int row2 = 1;
    cout << "Enter the first row index: ";
    cin >> row1;
    cout << "Enter the second row index: ";
    cin >> row2;
    cout << endl;
    matrixA.swapRows(matrixA, row1, row2);

    cout << "Swap matrix columns in A:" << endl;
    int col1 = 0;
    int col2 = 1;
    cout << "Enter the first column index: ";
    cin >> col1;
    cout << "Enter the second column index: ";
    cin >> col2;
    cout << endl;
    matrixA.swapCols(matrixA, col1, col2);

    cout << "Change entry in A:" << endl;
    int row = 0;
    int col = 0;
    int value = 100;
    cout << "Enter the row index: ";
    cin >> row;
    cout << "Enter the column index: ";
    cin >> col;
    cout << "Enter the new value: ";
    cin >> value;
    cout << endl;
    matrixA.changeElement(matrixA, row, col, value);
    
    cout << "Show that A was not changed from previous changes:\n" << endl;
    matrixA.printMatrix();
}
