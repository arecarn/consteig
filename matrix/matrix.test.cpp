#include <gtest/gtest.h>
#include "matrix.hpp"

TEST(matrix, static)
{
    static constexpr int s {2};
    static constexpr Matrix<int, s, s> matrix {{{{0, 1}, {2, 3}}}};

    // Check that created objects are constexpr
    static_assert(matrix(0,0) == 0, "Not constexpr");
    static_assert(matrix(0,1) == 1, "Not constexpr");
    static_assert(matrix(1,0) == 2, "Not constexpr");
    static_assert(matrix(1,1) == 3, "Not constexpr");

    int m = 0;
    for( size_t i {0}; i<s; i++ )
    {
        for( size_t j {0}; j<s; j++ )
        {
            ASSERT_EQ(m, matrix(i,j));
            m++;
        }
    }
}

TEST(matrix, equality)
{
    static constexpr int s {2};
    static constexpr Matrix<int, s, s> mat1 {{{{0, 1}, {2, 3}}}};
    static constexpr Matrix<int, s, s> mat2 {{{{0, 1}, {2, 3}}}};
    static constexpr Matrix<int, s, s> mat3 {{{{3, 2}, {1, 0}}}};

    // Check that created objects are constexpr
    static_assert(mat1==mat2, "Not constexpr");
    static_assert(mat2!=mat3, "Not constexpr");

    ASSERT_TRUE(mat1==mat2);
    ASSERT_FALSE(mat2==mat3);

    ASSERT_TRUE(mat1!=mat3);
    ASSERT_FALSE(mat1!=mat2);
}

TEST(matrix, static_constexpr_addition)
{
    static constexpr int s {2};
    static constexpr Matrix<int, s, s> mat1 {{{{3, 4}, {5, 6}}}};
    static constexpr Matrix<int, s, s> mat2 {{{{1, 3}, {2, 5}}}};

    static constexpr Matrix<int, s, s> answer {{{{4, 7}, {7, 11}}}};

    static constexpr Matrix<int, s, s> test {mat1 + mat2};

    // Check that created objects are constexpr
    static_assert(answer==test, "Not constexpr");

    ASSERT_TRUE(answer==test);
}

TEST(matrix, regular_addition)
{
    static constexpr int r {3};
    static constexpr int c {2};

    Matrix<int, r, c> mat1 = {{{{3, 4}, {5, 6}, {3, 9}}}};
    Matrix<int, r, c> mat2 = {{{{1, 3}, {2, 5}, {1, 10}}}};

    static constexpr Matrix<int, r, c> addAnswer
    {{{{4, 7}, {7, 11}, {4, 19}}}};
    static constexpr Matrix<int, r, c> subAnswer
    {{{{2, 1}, {3, 1}, {2, -1}}}};

    Matrix<int, r, c> add {mat1 + mat2};
    Matrix<int, r, c> sub {mat1 - mat2};

    ASSERT_TRUE(add==addAnswer);
    ASSERT_TRUE(sub==subAnswer);
}

TEST(matrix, static_constexpr_scalar)
{
    static constexpr int r {3};
    static constexpr int c {2};

    static constexpr int scalar {2};
    static constexpr Matrix<int, r, c> mat {{{{3, 4}, {5, 6}, {3, 9}}}};

    static constexpr Matrix<int, r, c> answer
    {{{{6, 8}, {10, 12}, {6, 18}}}};

    static constexpr Matrix<int, r, c> mult { scalar*mat };

    // Check that created objects are constexpr
    static_assert(mult==answer, "Not constexpr");

    ASSERT_TRUE(mult==answer);
}

TEST(matrix, static_constexpr_multiplication)
{
    static constexpr int r {3};
    static constexpr int c {2};

    static constexpr Matrix<int, r, c> mat1 {{{{3, 4}, {5, 6}, {3, 9}}}};
    static constexpr Matrix<int, c, r> mat2 {{{{1, -3, 7}, {2, 5, 9}}}};
    static constexpr Matrix<int, c, c> mat3 {{{{0, 1}, {2, 3}}}};

    static constexpr Matrix<int, r, r> answer1
    {{{{11, 11, 57}, {17, 15, 89}, {21, 36, 102}}}};
    static constexpr Matrix<int, c, c> answer2
    {{{{9, 49}, {58, 119}}}};
    static constexpr Matrix<int, c, c> answer3
    {{{{2, 3}, {6, 11}}}};

    static constexpr Matrix<int, r, r> mult1 { mat1*mat2 };
    static constexpr Matrix<int, c, c> mult2 { mat2*mat1 };
    static constexpr Matrix<int, c, c> mult3 { mat3*mat3 };

    // Check that created objects are constexpr
    static_assert(mult1==answer1, "Not constexpr");
    static_assert(mult2==answer2, "Not constexpr");
    static_assert(mult3==answer3, "Not constexpr");

    ASSERT_TRUE(mult1==answer1);
    ASSERT_TRUE(mult2==answer2);
    ASSERT_TRUE(mult3==answer3);
}

TEST(matrix, static_constexpr_trans)
{
    static constexpr int r {3};
    static constexpr int c {2};

    static constexpr Matrix<int, r, c> mat1 {{{{3, 4}, {5, 6}, {3, 9}}}};
    static constexpr Matrix<int, r, r> mat2 {{{{3, 4, 8}, {5, 6, 7}, {3, 9, 8}}}};

    static constexpr Matrix<int, c, r> answer1 {{{{3, 5, 3}, {4, 6, 9}}}};
    static constexpr Matrix<int, r, r> answer2 {{{{3, 5, 3}, {4, 6, 9}, {8, 7, 8}}}};

    static constexpr Matrix<int, c, r> mat1Transpose {transpose(mat1)};
    static constexpr Matrix<int, r, r> mat2Transpose {transpose(mat2)};

    // Check that created objects are constexpr
    static_assert(mat1Transpose==answer1, "Not constexpr");
    static_assert(mat2Transpose==answer2, "Not constexpr");

    ASSERT_TRUE(mat1Transpose==answer1);
    ASSERT_TRUE(mat2Transpose==answer2);
}

TEST(matrix, static_constexpr_dot)
{
    static constexpr int n {4};

    static constexpr Matrix<int, 1, n> mat1 {{{{3, 4, 4, 8}}}};
    static constexpr Matrix<int, 1, n> mat2 {{{{3, 5, 3, 9}}}};
    static constexpr Matrix<int, n, 1> mat3 {{{{3}, {5}, {3}, {9}}}};

    //static constexpr Matrix<int, n, 1> mat3 {transpose(mat1)};
    //static constexpr Matrix<int, 1, n> mat4 {transpose(mat2)};


    static constexpr int dotProduct1 {dot(mat1,mat2)};
    static constexpr int dotProduct2 {dot(transpose(mat3),mat1)};
    static constexpr int answer {113};

    // Check that created objects are constexpr
    static_assert(dotProduct1==answer, "Not constexpr");
    static_assert(dotProduct2==answer, "Not constexpr");

    ASSERT_TRUE(dotProduct1==answer);
    ASSERT_TRUE(dotProduct2==answer);
}

TEST(matrix, static_constexpr_diag)
{
    static constexpr int x {3};

    static constexpr Matrix<float, x, x> answer
    {{{{1.0F, 0, 0}, {0, 1.0F, 0}, {0, 0, 1.0F}}}};

    static constexpr auto mat {diagional<float,x>(1.0F)};

    // Check that created objects are constexpr
    static_assert(mat==answer, "Not constexpr");

    ASSERT_TRUE(mat==answer);
}

TEST(matrix, static_constexpr_norm_euclidean)
{
    static constexpr int x {3};
    static constexpr int r {2};

    static constexpr Matrix<float, x, x> mat1
    {{{{5.0F, -4.0F, 2.0F}, {-1.0F, 2.0F , 3.0F}, {-2.0F, 1.0F, 0.0F}}}};

    static constexpr Matrix<float, r, r> mat2
    {{{{1.0F, -7.0F}, {-2.0F, 3.0F}}}};

    static constexpr float n1 {normE(mat1)};
    static constexpr float n2 {normE(mat2)};

    static constexpr float answer1 = 8.0F;
    static constexpr float answer2 = 7.9373F;

    // ASSER_FLOAT_EQ will fail in this case, as answer2 above was rounded
    ASSERT_NEAR(n1, answer1, 0.0001F);
    ASSERT_NEAR(n2, answer2, 0.0001F);
}

TEST(matrix, static_constexpr_row)
{
    static constexpr int x {3};

    static constexpr Matrix<float, x, x> mat
    {{{{5.0F, -4.0F, 2.0F}, {-1.0F, 2.0F , 3.0F}, {-2.0F, 1.0F, 0.0F}}}};

    static constexpr Matrix<float, 1, x> rowExtract {mat.row(0)};

    static constexpr Matrix<float, 1, x> answer
    {{{{5.0F, -4.0F, 2.0F}}}};

    // Check that created objects are constexpr
    static_assert(rowExtract==answer, "Not constexpr");

    ASSERT_TRUE(rowExtract==answer);
}

TEST(matrix, static_constexpr_col)
{
    static constexpr int x {3};

    static constexpr Matrix<float, x, x> mat
    {{{{5.0F, -4.0F, 2.0F}, {-1.0F, 2.0F , 3.0F}, {-2.0F, 1.0F, 0.0F}}}};

    static constexpr Matrix<float, x, 1> colExtract {mat.col(0)};

    static constexpr Matrix<float, x, 1> answer
    {{{{5.0F}, {-1.0F}, {-2.0F}}}};

    // Check that created objects are constexpr
    static_assert(colExtract==answer, "Not constexpr");

    ASSERT_TRUE(colExtract==answer);
}
