#include "example_helper.hpp"
#include "../consteig.hpp"
#include "../tools/gtest/test_tools.hpp"

template<typename T, size_t R, size_t C>
static inline constexpr bool checkEigenValues(
        const constmat::Matrix<T,R,C> a,
        const constmat::Matrix<T,R,1> lambda )
{
    //det(A-lambda*I)
    bool equal {true};
    auto identity {constmat::eye<T,R>()};

    for(int i {0}; i<R; i++)
    {
        auto b1 {a - (lambda(i,0)*identity)};
        auto a1 {det( a - (lambda(i,0)*identity))};
        equal &= compareFloat( det( a - (lambda(i,0)*identity)), static_cast<T>(0), 0.001 );
    }

    return equal;
}

int main()
{
    static constexpr size_t s {4};

    /*static constexpr*/ constmat::Matrix<float,s,s> mat
    {{{
    {-0.44529, 4.9063, -0.87871, 6.3036},
    {-6.3941, 13.354, 1.6668, 11.945},
    {3.6842, -6.6617, -0.060021, -7.0043},
    {3.1209, -5.2052, -1.413, -2.8484},
    }}};

    /*static constexpr*/ constmat::Matrix<float,s,s> testEig {consteig::eig(mat)};
    /*static constexpr*/ constmat::Matrix<float,s,1> testEigVals {consteig::eigvals(mat)};

    printMat("testEig", testEig);

    printMat("testEigVals", testEigVals);

    bool checkEigen = checkEigenValues<float,s,s>(mat, testEigVals);

    std::cout << checkEigen << "\n";
}

// T = [ -4.4529e-01  4.9063e+00 -8.7871e-01  6.3036e+00; -6.3941e+00  1.3354e+01  1.6668e+00  1.1945e+01; 3.6842e+00 -6.6617e+00 -6.0021e-02 -7.0043e+00; 3.1209e+00 -5.2052e+00 -1.4130e+00 -2.8484e+00; ];
