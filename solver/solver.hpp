#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "stddef.h"
#include "matrix.hpp"
#include "qr_decomp.hpp"

template<typename T, size_t S>
struct UtMatrix
{
    Matrix<T,S,S> _u;
    Matrix<T,S,S> _t;
};

template<typename T, size_t R, size_t C>
constexpr Matrix<T,R,R> house(Matrix<T,R,C> a)
{
    static_assert( R==C, "Householder expects a square matrix");

    T alphaSum {0};
    for(size_t i {1}; i<R; i++)
        alphaSum += (a(i,0)*a(i,0));

    T alpha { static_cast<T>(-1)
        * gcem::sgn(a(1,0))
        * gcem::sqrt(alphaSum) };

    T r { gcem::sqrt(
            static_cast<T>(0.5)
            * ((alpha*alpha) - (a(1,0)*alpha)) ) };

    T oneOverTwoR {1/(static_cast<T>(2)*r)};

    Matrix<T,R,1> v {static_cast<T>(0)};
    v(1,0) = (a(1,0) - alpha) * oneOverTwoR;
    for(size_t i {2}; i<R; i++)
        v(i,0) = a(i,0) * oneOverTwoR;

    Matrix<T,R,R> p { eye<T,R>() -
        (static_cast<T>(2) * v * transpose(v)) };

    return p;
}

template<typename T>
constexpr Matrix<T,2,2> house(Matrix<T,2,2> a)
{
    return a;
}

template<typename T, size_t R, size_t C>
constexpr Matrix<T,R,R> hess(Matrix<T,R,C> a)
{
    static_assert( R==C, "Hessenberg reduction expects a square matrix");

    constexpr size_t end {R-1};

    //{
    //    size_t sizeNew {R-i};
    //    Matrix<T, R-i, R-i> aNew { a.template sub<i,end,i,end>() };
    //    Matrix<T,R,R> p { house(aNew) };
    //}

    //Matrix<T, R-1, R-1> aNew { a.template sub<1,end,1,end>() };

    Matrix<T,R-1,1> a1 {a.template col<1,R-1>(0)};
    //Matrix<T, R-1, R-1> q { house(a.template sub<1,1,end,end>()) };
    Matrix<T, R, R> qHouse { house(a) };
    Matrix<T, R-1, R-1> q { a.template sub<1,1,end,end>() };

    a.template setCol<1,R-1>(q*a1, 0);

    Matrix<T,1,R-1> aRow {a.template row<1,R-1>(0)};
    a.template setRow<1,R-1>(aRow*q, 0);

    Matrix<T,R-1,R-1> subA {a.template sub<1,1,R-1,R-1>()};
    //a.template setSub<1,1,R-1,R-1>(q*subA*transpose(q));
    a.template setSub<1,1,R-1,R-1>(q*subA*q);

    //H = hess(a.template sub<1,1,R-1,R-1>());
    subA = a.template sub<1,1,R-1,R-1>();
    hess(subA);

    //hess(aNew);

    return a;
}

template<typename T>
constexpr Matrix<T,2,2> hess(Matrix<T,2,2> a)
{
    return a;
}

template<typename T>
constexpr T wilkinsonShift(const T a, const T b, const T c)
{
    T delta {(a-c)/2};

    if( delta == static_cast<T>(0) )
        delta = static_cast<T>(1);

    return c - (gcem::sgn(delta)*gcem::pow(b,2)/
        (gcem::abs(delta) + gcem::sqrt(gcem::pow(delta,2)+gcem::pow(delta,2))));
}

// http://pi.math.cornell.edu/~web6140/TopTenAlgorithms/QRalgorithm.html
template<typename T, size_t R, size_t C>
constexpr UtMatrix<T, R> eigensolver( const Matrix<T,R,C> x )
{
    //TODO(mthompkins): Remove this necessity
    static_assert( R==C, "Eigenvalue Solver expects a square matrix");

    Matrix<T,R,R> identity {diagional<T,R>(static_cast<T>(1U))};

    Matrix<T,R,R> test {hess<T,R,R>(x)};

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

