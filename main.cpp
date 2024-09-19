// Program Name : MatrixVerticalAdd
// Date : 2024 - 9 - 16
// Author : Yash Baruah
// Module Purpose : Checks if a matrix has vertical symmetry

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const unsigned MAX_MATRIX_SIZE = 20;
const unsigned WIDTH_DISPLAY = 12;

// Function prototypes
bool    readMatrixFromFile(int[][MAX_MATRIX_SIZE], unsigned&, unsigned&, ifstream&);
void         displayMatrix(int[][MAX_MATRIX_SIZE], unsigned, unsigned);
void displayCalcMatrixSums(int[][MAX_MATRIX_SIZE], unsigned, unsigned, int[MAX_MATRIX_SIZE]);
void   symmetryCheckMatrix(int[], unsigned);
void        sortMatrixRows(int[][MAX_MATRIX_SIZE], unsigned, unsigned);
void         sortRow(int[], unsigned);

int main() {
    unsigned height, width;
    int      matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], colSums[MAX_MATRIX_SIZE];
    string   INPUT_FILE_NAME = "matrixes.txt";
    ifstream inputFileStreamObj(INPUT_FILE_NAME);

    if (inputFileStreamObj.fail()) {
        cout << "File " << INPUT_FILE_NAME << " could not be opened !" << endl;
        cout << endl << "Press the enter key once or twice to leave..." << endl; cin.ignore(); cin.get();
        exit(EXIT_FAILURE);
    }

    do {
        if (readMatrixFromFile(matrix, height, width, inputFileStreamObj))
            break;

        cout << "Input:" << endl;
        displayMatrix(matrix, height, width);
        displayCalcMatrixSums(matrix, height, width, colSums);
        symmetryCheckMatrix(colSums, width);
        sortMatrixRows(matrix, height, width);
        cout << "Sorted:" << endl;
        displayMatrix(matrix, height, width);

        cout << endl << "Press the enter key once or twice to continue..." << endl; cin.ignore(); cin.get();

    } while (true);

    cout << "Program Done" << endl;

    exit(EXIT_SUCCESS);
}

bool readMatrixFromFile(int matrix[][MAX_MATRIX_SIZE], unsigned& height, unsigned& width, ifstream& inputFileStreamObj) {
    // Read the dimensions of the matrix
    if (!(inputFileStreamObj >> height >> width)) {
        // Return true to indicate end of file or read error
        return true;
    }

    // Read the matrix data
    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j < width; ++j) {
            inputFileStreamObj >> matrix[i][j];
            // No error checking required as per assignment instructions
        }
    }
    return false; // Indicate that the matrix was read successfully
}

void displayMatrix(int matrix[][MAX_MATRIX_SIZE], unsigned height, unsigned width)
{
    for (unsigned i = 0; i < height; ++i)
    {
        for (unsigned j = 0; j < width; ++j)
        {
            cout << setw(WIDTH_DISPLAY) << matrix[i][j];
        }
        cout << endl;
    }
}

void displayCalcMatrixSums(int matrix[][MAX_MATRIX_SIZE], unsigned height, unsigned width, int colSums[MAX_MATRIX_SIZE])
{
    // Initialize colSums to zero
    for (unsigned j = 0; j < width; ++j)
    {
        colSums[j] = 0;
    }
    // Calculate the sums
    for (unsigned i = 0; i < height; ++i)
    {
        for (unsigned j = 0; j < width; ++j)
        {
            colSums[j] += matrix[i][j];
        }
    }
    // Display the sums
    cout << "Sums :" << endl;
    for (unsigned j = 0; j < width; ++j)
    {
        cout << setw(WIDTH_DISPLAY) << colSums[j];
    }
    cout << endl;
}

void symmetryCheckMatrix(int colSums[], unsigned width)
{
    bool isSymmetric = true;
    for (unsigned j = 0; j < width / 2; ++j)
    {
        if (colSums[j] != colSums[width - 1 - j])
        {
            isSymmetric = false;
            break;
        }
    }
    cout << "Vertical additive symmetry : " << (isSymmetric ? "Yes" : "No") << endl;
}

void sortMatrixRows(int matrix[][MAX_MATRIX_SIZE], unsigned height, unsigned width)
{
    for (unsigned i = 0; i < height; ++i)
    {
        sortRow(matrix[i], width);
    }
}

void sortRow(int row[], unsigned width)
{
    // Simple selection sort
    for (unsigned j = 0; j < width - 1; ++j)
    {
        unsigned minIndex = j;
        for (unsigned k = j + 1; k < width; ++k)
        {
            if (row[k] < row[minIndex])
            {
                minIndex = k;
            }
        }
        if (minIndex != j)
        {
            // Swap elements
            int temp = row[j];
            row[j] = row[minIndex];
            row[minIndex] = temp;
        }
    }
}
