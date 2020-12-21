#include <vector>

class Matrix {

    public:
        int rows;
        int columns;
        std::vector<float> matrixData;

        Matrix(int r, int c);
        void fill(std::vector<float> data);

        Matrix operator * (const Matrix& matrix2) const;
        Matrix operator + (const Matrix& matrix2) const;
        Matrix transpose ();
        Matrix inverse ();

};


/*

x - 2x1
P - 2x2
F - 2x2
B - 2x1
Q - 2x2
S - 1x1
S^-1 - 1x1
F^T - 2x2
y = 1x1
z = 1x1
H = 1 x 2
H^T = 2 x 1
P

*/
