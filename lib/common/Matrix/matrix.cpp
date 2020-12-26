#include "matrix.hpp"
#include <vector>
#include <cassert>
#include <iostream>


Matrix::Matrix(int r, int c) {
    assert(0 < r && r < 3 && 0 < c && c < 3);
    this->rows = r;
    this->columns = c;
}

void Matrix::fill(std::vector<float> data) {
    assert(data.size() == rows * columns);
    this->matrixData = data;
}

float Matrix::at(int r, int c) const {
    return matrixData.at((r * rows) + c);
}

Matrix Matrix::inverse() {
    Matrix r(rows, columns);
    std::vector<float> data = std::vector<float>();
    for (int i = 0; i < matrixData.size(); i++) {
        data.push_back(1 / matrixData.at(i));
    }
    r.fill(data);
    return r;
}

Matrix Matrix::transpose() {
    if (rows == 2 && columns == 2) {
        Matrix r = Matrix(2, 2);
        std::vector<float> data {
            at(0, 0),
            at(1, 0),
            at(0, 1),
            at(1, 1)
        };
        r.fill(data);
        return r;
    }
    if (rows == 1 && columns == 2) {
        Matrix r = Matrix(2, 1);
        std::vector<float> data {
            at(0, 0),
            at(0, 1)
        };
        r.fill(data);
        return r;
    }

    Matrix r = Matrix(2,2);
    return r;
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

Matrix Matrix::operator - (const Matrix& matrix2) const {
    assert(this->rows == matrix2.rows);
    assert(this->columns == matrix2.columns);

    Matrix r = Matrix(this->rows, this->columns);
    std::vector<float> data = std::vector<float>();

    for (int i = 0; i < this->matrixData.size(); i++) {
        data.push_back(this->matrixData.at(i) - matrix2.matrixData.at(i));
    }

    r.fill(data);

    return r;
}

Matrix Matrix::operator * (const Matrix& matrix2) const {
    assert(this->columns == matrix2.rows);

    Matrix r = Matrix(this->rows, matrix2.columns);
    if (r.rows == 2 && r.columns == 1 && matrix2.rows != 1) {
        std::vector<float> data {
            at(0, 0) * matrix2.at(0, 0) + at(0, 1) * matrix2.at(0, 1),
            at(1, 0) * matrix2.at(0, 0) + at(1, 1) * matrix2.at(0, 1) 
        };
        r.fill(data);
    } else if(r.rows == 2 && r.columns == 1) {
        std::vector<float> data {
            at(0, 0) * matrix2.at(0, 0),
            at(0, 1) * matrix2.at(0, 0)
        };
        r.fill(data);
    } else if (r.rows == 2 && r.columns == 2 && this->columns != 1) {
        std::vector<float> data {
            at(0, 0) * matrix2.at(0, 0) + at(0, 1) * matrix2.at(1,0),
            at(0, 0) * matrix2.at(0, 1) + at(0, 1) * matrix2.at(1,1),
            at(1, 0) * matrix2.at(0, 0) + at(1, 1) * matrix2.at(1,0),
            at(1, 0) * matrix2.at(0, 1) + at(1, 1) * matrix2.at(1,1)
        };
        r.fill(data);
    } else if (r.rows == 2 && r.columns == 2) {
        std::vector<float> data {
            at(0, 0) * matrix2.at(0, 0),
            at(0, 0) * matrix2.at(0, 1),
            at(0, 1) * matrix2.at(0, 0),
            at(0, 1) * matrix2.at(0, 1)
        };
        r.fill(data);
    } else if (r.rows == 1 && this->columns==2 && r.columns == 1) {
        std::vector<float> data {
            at(0,0) * matrix2.at(0,0) + at(0, 1) * matrix2.at(0, 1)
        };
        r.fill(data);
    } else if (r.rows == 1 && r.columns == 1) {
        std::vector<float> data {
            at(0,0) * matrix2.at(0,0)
        };
        r.fill(data);
    } else if (r.rows == 1 && r.columns == 2 && this->columns != 1) {
        std::vector<float> data {
            at(0,0) * matrix2.at(0, 0) + at(0, 1) * matrix2.at(0, 1),
            at(0,0) * matrix2.at(1, 0) + at(0, 1) * matrix2.at(1, 1),
        };
        r.fill(data);
    } else {
        assert(7 == 0);
    }

    return r;
}

Matrix Matrix::operator * (const float scaler) const {
    Matrix r = Matrix(this->rows, this->columns);
    std::vector<float> data = std::vector<float>();

    for (int i = 0; i < this->matrixData.size(); i++) {
        data.push_back(scaler * this->matrixData.at(i));
    }

    r.fill(data);
    return r;
}
