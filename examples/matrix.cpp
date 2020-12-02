#include "example_helper.hpp"

int main()
{
    static constexpr int x {3};

    // Create a 3x3 matrix
    static constexpr constmat::Matrix<int, x, x> mat1
    {{{{5, -4, 2}, {-1, 2 , 3}, {-2, 1, 0}}}};

    // Create a matrix which is the transpose
    static constexpr constmat::Matrix<int, x, x> mat2 {transpose(mat1)};

    // Multiply the two
    static constexpr constmat::Matrix<int, x, x> mat3 {mat1*mat2};

    // Multiply by a scalar
    static constexpr constmat::Matrix<int, x, x> mat4 {-3*mat2};
    //TODO(mthompkins): Investigate this
    //static constexpr constmat::Matrix<float, x, x> mat4 {3.4*static_cast<constmat::Matrix<float, x, x>>(mat2)};

    printMat("Mat1", mat1);
    printMat("Mat2", mat2);
    printMat("Mat3", mat3);
    printMat("Mat4", mat4);
}
