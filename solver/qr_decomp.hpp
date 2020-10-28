#ifndef QR_DECOMP_HPP
#define QR_DECOMP_HPP

#include "stddef.h"
#include "matrix.hpp"

template<typename T, size_t S>
struct QrMatrix
{
    Matrix<T,S,S> _q;
    Matrix<T,S,S> _r;
};

template<typename T, size_t R, size_t C>
constexpr QrMatrix<T, R> qrDecomp( const Matrix<T,R,C> mat )
{
    //TODO(tthompkins): Remove this necessity
    static_assert( R==C, "QR decomposition must be a square matrix");

    QrMatrix<T,R> result{};

    Matrix<T,1,R> a[R] {};
    Matrix<T,1,R> e[R] {};

    // Solve q by gram-schmidt process
    // (https://www.math.ucla.edu/~yanovsky/Teaching/Math151B/handouts/GramSchmidt.pdf)

    // a[0] = u[0]
    a[0] = mat.row(0);
    e[0] = (1/normE(a[0])) * a[0];

    for(size_t i {1}; i<R; i++)
    {
        a[i] = mat.row(i);
        Matrix<T,1,R> u {a[i]};

        for(size_t j {1}; j<=i; j++)
            u = u - ((dot(a[i],e[j-1]))*e[j-1]);

        e[i] = (1/normE(u)) * u;
    }

    // Create Q Matrix
    for(size_t i {0}; i<R; i++)
        result._q.setCol(transpose(e[i]),i);

    // Create R Matrix
    for(size_t i {0}; i<R; i++)
        for(size_t j {i}; j<R; j++)
            result._r(i,j) = dot(a[j],e[i]);

    return result;
}

#endif
