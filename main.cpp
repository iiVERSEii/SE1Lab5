#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using Matrix = std::vector<std::vector<long long>>;

bool loadMatrices(const std::string& filename, Matrix& matrixA, Matrix& matrixB) {
    std::ifstream input(filename);
    if (!input) {
        std::cerr << "Error: could not open input file '" << filename << "'.\n";
        return false;
    }

    long long sizeValue;
    if (!(input >> sizeValue) || sizeValue <= 0) {
        std::cerr << "Error: the first value in the file must be a positive matrix size.\n";
        return false;
    }

    const auto size = static_cast<std::size_t>(sizeValue);
    matrixA.assign(size, std::vector<long long>(size));
    matrixB.assign(size, std::vector<long long>(size));

    for (auto& row : matrixA) {
        for (long long& value : row) {
            if (!(input >> value)) {
                std::cerr << "Error: the file does not contain two complete "
                          << size << " x " << size << " matrices.\n";
                return false;
            }
        }
    }
    for (auto& row : matrixB) {
        for (long long& value : row) {
            if (!(input >> value)) {
                std::cerr << "Error: the file does not contain two complete "
                          << size << " x " << size << " matrices.\n";
                return false;
            }
        }
    }

    return true;
}

void printMatrix(const Matrix& matrix) {
    std::size_t width = 4;
    for (const auto& row : matrix) {
        for (long long value : row) {
            const std::size_t valueWidth = std::to_string(value).size();
            if (valueWidth > width) {
                width = valueWidth;
            }
        }
    }

    for (const auto& row : matrix) {
        for (long long value : row) {
            std::cout << std::setw(static_cast<int>(width)) << value;
        }
        std::cout << '\n';
    }
}

Matrix addMatrices(const Matrix& matrixA, const Matrix& matrixB) {
    const std::size_t size = matrixA.size();
    Matrix result(size, std::vector<long long>(size));
    for (std::size_t row = 0; row < size; ++row) {
        for (std::size_t column = 0; column < size; ++column) {
            result[row][column] = matrixA[row][column] + matrixB[row][column];
        }
    }
    return result;
}

Matrix multiplyMatrices(const Matrix& matrixA, const Matrix& matrixB) {
    const std::size_t size = matrixA.size();
    Matrix result(size, std::vector<long long>(size, 0));
    for (std::size_t row = 0; row < size; ++row) {
        for (std::size_t column = 0; column < size; ++column) {
            for (std::size_t inner = 0; inner < size; ++inner) {
                result[row][column] += matrixA[row][inner] * matrixB[inner][column];
            }
        }
    }
    return result;
}

void displayDiagonalSums(const Matrix& matrix) {
    long long mainDiagonalSum = 0;
    long long secondaryDiagonalSum = 0;
    const std::size_t size = matrix.size();

    for (std::size_t index = 0; index < size; ++index) {
        mainDiagonalSum += matrix[index][index];
        secondaryDiagonalSum += matrix[index][size - 1 - index];
    }

    std::cout << "Main diagonal sum: " << mainDiagonalSum << '\n';
    std::cout << "Secondary diagonal sum: " << secondaryDiagonalSum << '\n';
}

bool swapRows(Matrix& matrix, std::size_t firstRow, std::size_t secondRow) {
    if (firstRow >= matrix.size() || secondRow >= matrix.size()) {
        return false;
    }
    for (std::size_t column = 0; column < matrix[firstRow].size(); ++column) {
        const long long temporary = matrix[firstRow][column];
        matrix[firstRow][column] = matrix[secondRow][column];
        matrix[secondRow][column] = temporary;
    }
    return true;
}

bool swapColumns(Matrix& matrix, std::size_t firstColumn, std::size_t secondColumn) {
    if (matrix.empty() || firstColumn >= matrix.front().size() ||
        secondColumn >= matrix.front().size()) {
        return false;
    }
    for (auto& row : matrix) {
        const long long temporary = row[firstColumn];
        row[firstColumn] = row[secondColumn];
        row[secondColumn] = temporary;
    }
    return true;
}

bool updateElement(Matrix& matrix, std::size_t row, std::size_t column,
                   long long newValue) {
    if (row >= matrix.size() || matrix.empty() || column >= matrix.front().size()) {
        return false;
    }
    matrix[row][column] = newValue;
    return true;
}

int main(int argc, char* argv[]) {
    std::string filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        std::cout << "Enter input filename: ";
        std::getline(std::cin, filename);
    }

    Matrix matrixA;
    Matrix matrixB;
    if (!loadMatrices(filename, matrixA, matrixB)) {
        return 1;
    }

    std::cout << "\nMatrix A:\n";
    printMatrix(matrixA);
    std::cout << "\nMatrix B:\n";
    printMatrix(matrixB);

    std::cout << "\nA + B:\n";
    printMatrix(addMatrices(matrixA, matrixB));

    std::cout << "\nA * B:\n";
    printMatrix(multiplyMatrices(matrixA, matrixB));

    std::cout << "\nDiagonal sums for Matrix A:\n";
    displayDiagonalSums(matrixA);

    Matrix rowSwapped = matrixA;
    std::cout << "\nProblem 5 - Rows 0 and 2 swapped:\n";
    if (!swapRows(rowSwapped, 0, 2)) {
        std::cout << "Row indices 0 and 2 are out of bounds; matrix unchanged.\n";
    }
    printMatrix(rowSwapped);

    Matrix columnSwapped = matrixA;
    std::cout << "\nProblem 6 - Columns 0 and 2 swapped:\n";
    if (!swapColumns(columnSwapped, 0, 2)) {
        std::cout << "Column indices 0 and 2 are out of bounds; matrix unchanged.\n";
    }
    printMatrix(columnSwapped);

    Matrix updated = matrixA;
    std::cout << "\nProblem 7 - Updated matrix:\n";
    if (!updateElement(updated, 1, 2, 99)) {
        std::cout << "Element index (1, 2) is out of bounds; matrix unchanged.\n";
    }
    printMatrix(updated);

    return 0;
}