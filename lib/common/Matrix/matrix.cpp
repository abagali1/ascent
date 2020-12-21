#include "matrix.hpp"
#include <vector>
#include <cassert>

Matrix::Matrix(int r, int c) {
    assert(0 < r && r < 3 && 0 < c && c < 3);
    this->rows = r;
    this->columns = c;
}

void Matrix::fill(std::vector<float> data) {
    assert(data.size() == rows * columns);
    this->matrixData = data;
}

Matrix Matrix::operator + (const Matrix& matrix2) const {
    assert(this->rows == matrix2.rows);
    assert(this->columns == matrix2.columns);

    Matrix r = Matrix(this->rows, this->columns);
    std::vector<float> data = std::vector<float>();

    for (int i = 0; i < this->matrixData.size(); i++) {
        data.push_back(this->matrixData.at(i) + matrix2.matrixData.at(i));
    }

    r.fill(data);

    return r;
}
