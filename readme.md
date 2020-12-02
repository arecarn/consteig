## What Is This
Consteig is a constexpr template library which uses both constexpr functions and
template meta-programming to calculate the eigenvalues of a square matrix at
compile time. That is, the eigenvalues can be saved as `static constexpr` values
and no processor execution time is spent calculating them at run-time.  Constmat
is also provided alongside Consteig which allows for compile time static matrix
manipulation. That means users can create matrices and perform a collection of
[operations]() on them.

## Why Does This Exist
Originally this library was developed to support a generic digital filter
library targeted at embedded systems in which the digital filter coefficients
could be calculated at compile time. In order to find the filter coefficients
it’s required to solve a multi order polynomial. Implementing a root finder
natively is tedious and error prone. Finding the roots of a polynomial can be
reframed as an eigenvalue problem which makes life easier. The matlab and octave
root finding functions actually operate in this way. As such development began
on a compile time eigenvalue finder.

## How To Use Consteig
Consteig is a templated library and as such a user does not need to compile
anything separately. Simply `#include “Consteig.hpp”` into your project. The
cmake files here are only to facilitate testing and development.

Here are some examples to help get started:
* [Declaring a matrix]()
* [Matrix Arithmetic]()
* [Finding eigenvalues]()

## How Is This Different
There are powerful open source C++ eigenvalues solvers already in existence
which are more robust, better optimized, and better tested. The caveat is that
they cannot currently calculate Eigenvalues at compile time. There’s been talk
of [adding constexpr functionality to
Eigen](https://gitlab.com/libeigen/eigen/-/issues/820) but as of yet that hasn’t
happened.

Another key component to most eigenvalues solvers is the reliance on the
standard library. This is for good reason as the standard library, in particular
the STL containers, are powerful and solve many commonly faced problems.
Unfortunately in some systems, particularly for embedded systems the standard
library isn’t available.

This solves those two problems in a limited capacity.

## When To Use Consteig
* Eigenvalues need to be known at compile time
* Eigenvalues need to be known and the standard library is unavailable
* You need to manipulate static matrices at compile time

## When Not To Use Consteig
* Eigen Values do not need to be known at compile time
* Eigen Values can be solved at runtime and the compiler can leverage standard
  library functionality
* Matrices do not need to be manipulated at compile time

## What Can Improve
* Declaring matrices can be initializer bracket hell. Refer to [this example]()
  for help.
* The algorithms implemented here do not necessarily take advantage of a
  collection of optimization techniques for solving matrices nor has there been
  a concerted effort to optimize the implementations themselves. As such, for
  extremely large matrices compilation may be slow. Compilation has been tested
  on [these]() machines for matrices up to size NxN.
* Currently the matrix [decompositions]() require square matrices.
* No complex number support is natively supported. That said, matrices can be
  declared as any type and any operation can be performed on a matrix of any
  type. Matrix decomposition however only operate on matrices of floating point
  types.

## Notes On Performance
* Float vs. double

## TODO
* Remove dependency on gcem and any std library implementations
* Compile with `-wall`

## References
