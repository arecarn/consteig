#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "stddef.h"
#include "qr_decomp.hpp"

template<typename T, size_t S>
struct UtMatrix
{
    Matrix<T,S,S> _u;
    Matrix<T,S,S> _t;
};

template<typename T>
constexpr T sign(const T delta)
{
    T rtn {static_cast<T>(0)};

    if( delta > static_cast<T>(0) )
        rtn = 1;
    else if( delta < static_cast<T>(0) )
        rtn = -1;
    else
        rtn = 0;

    return rtn;
}

template<typename T, size_t R, size_t C>
constexpr T hess (Matrix<T,R,C> a)
{
    static_assert( R==C, "Hessenberg reduction expects a square matrix");

    Matrix<T,R,R> H {a};
    if(R>2)
    {
        auto a1 {a.col<2,R-1>(1)};
        Matrix<T,R-1,C> e1 {static_cast<T>(0)};
        e1(0,0) = static_cast<T>(1);

        auto v {a1 + sign(a1(0,0))*normE(a1)*e1};
        v = v * (1/normE(v));

        Matrix<T,R,R> identity {diagional<T,R-1>(static_cast<T>(1))};
        auto q {identity - static_cast<T>(2)*(v*transpose(v))};
    }

    return H;
}

template<typename T>
constexpr T wilkinsonShift(const T a, const T b, const T c)
{
    T delta {(a-c)/2};

    if( delta == static_cast<T>(0) )
        delta = static_cast<T>(1);

    return c - (sign(delta)*gcem::pow(b,2)/
        (gcem::abs(delta) + gcem::sqrt(gcem::pow(delta,2)+gcem::pow(delta,2))));
}

// http://pi.math.cornell.edu/~web6140/TopTenAlgorithms/QRalgorithm.html
template<typename T, size_t R, size_t C>
constexpr UtMatrix<T, R> eigensolver( const Matrix<T,R,C> x )
{
    //TODO(mthompkins): Remove this necessity
    static_assert( R==C, "Eigenvalue Solver expects a square matrix");

    Matrix<T,R,R> identity {diagional<T,R>(static_cast<T>(1U))};

    Matrix<T,R,R> a {x};
    Matrix<T,R,R> u[2] = {0};
    u[0] = {identity};

    //TODO(mthompkins): Instead of running for a fixed time, continuously check
    //for an upper triangular matrix
    for( size_t i {1}; i<200; i++ )
    {
        QrMatrix<T, R> aq {qrDecomp(a)};
        a = aq._r*aq._q;
        u[1] = u[0]*aq._q;
        u[0] = u[1];
    }

    return { a, u[0] };

}

template<typename T, size_t R, size_t C>
constexpr Matrix<T, R, 1> eigenvalues( const Matrix<T,R,C> x )
{
    UtMatrix<T,R> ut {eigensolver(x)};

    Matrix<T,R,1> result {};

    for( size_t i {0}; i<R; i++ )
        result(i,0) = ut._u(i,i);

    return result;
}

#endif

