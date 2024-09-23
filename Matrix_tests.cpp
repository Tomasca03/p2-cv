#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
    
    Matrix mat2;
      Matrix_init(&mat2, 3, 1);
      Matrix_fill(&mat2, 123);

      for (int j = 0; j < 3; ++j) {
          ASSERT_EQUAL(*Matrix_at(&mat2, 0, j), 123);
      }
    
    Matrix mat3;
    Matrix_init(&mat3, 1, 1);
    Matrix_fill(&mat3, -1000);
    
    ASSERT_EQUAL(*Matrix_at(&mat3, 0, 0), -1000);
    
    Matrix mat4;
    
    Matrix_init(&mat4, 1, 6);
    Matrix_fill(&mat4, 11);
    
    for(int i = 0; i < 6; i++){
        ASSERT_EQUAL(*Matrix_at(&mat4, i, 0), 11);
    }
    
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.
TEST(test_matrix_init) {
    
    Matrix mat;
    
    
    Matrix_init(&mat, 2, 3);
    ASSERT_EQUAL(Matrix_width(&mat), 2);
    ASSERT_EQUAL(Matrix_height(&mat), 3);
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 2; j++){
            ASSERT_EQUAL(*Matrix_at(&mat, i, j), 0);
        }
    }
    
    Matrix mat2;
    
    Matrix_init(&mat2, 1, 1);
    ASSERT_EQUAL(Matrix_width(&mat2), 1);
    ASSERT_EQUAL(Matrix_height(&mat2), 1);
    ASSERT_EQUAL(*Matrix_at(&mat2, 0, 0), 0);
    
}
TEST(test_matrix_print) {
  Matrix mat;

const int value = 42;
  Matrix_init(&mat, 1, 1);

  *Matrix_at(&mat, 0, 0) = value;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
    
   
    Matrix mat2;
    Matrix_init(&mat2, 3, 4);
    Matrix_fill(&mat2, 5);
    ostringstream expected2;
    
    expected2 << "3 4\n"
             << "5 5 5 \n"
             << "5 5 5 \n"
             << "5 5 5 \n"
             << "5 5 5 \n";
    
    
    ostringstream actual2;
    Matrix_print(&mat2, actual2);
    ASSERT_EQUAL(expected2.str(), actual2.str());
}

TEST(test_matrix_at) {
    
        Matrix mat;
        Matrix_init(&mat, 3, 3);

        *Matrix_at(&mat, 0, 0) = 7;
        ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 7);
    
    *Matrix_at(&mat, 1, 1) = -200;
    ASSERT_EQUAL(*Matrix_at(&mat, 1, 1), -200);

        *Matrix_at(&mat, 2, 2) = 18;
        ASSERT_EQUAL(*Matrix_at(&mat, 2, 2), 18);

}

TEST(test_const_matrix_at) {
   
        Matrix mat;
        Matrix_init(&mat, 6, 6);

        *Matrix_at(&mat, 2, 3) = -813;

        const Matrix* con_mat = &mat;
        ASSERT_EQUAL(*Matrix_at(con_mat, 2, 3), -813);
        ASSERT_EQUAL(*Matrix_at(con_mat, 1, 1), 0);


}

TEST(test_matrix_fill_border) {
    
    Matrix mat;
    Matrix_init(&mat, 3, 5);
    Matrix_fill_border(&mat, -333);
    
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 3; j++){
            if(i == 0 || i == 4 || j == 0 || j == 2){
                ASSERT_EQUAL(*Matrix_at(&mat, i, j), -333);
            }
            else {
                ASSERT_EQUAL(*Matrix_at(&mat, i, j), 0);
            }
        }
    }
    
    Matrix mat2;
      Matrix_init(&mat2, 1, 3);
      Matrix_fill_border(&mat2, 123);

      for (int i = 0; i < 3; ++i) {
          ASSERT_EQUAL(*Matrix_at(&mat2, i, 0), 123);
      }
    
    Matrix mat3;
    Matrix_init(&mat3, 1, 1);
    Matrix_fill_border(&mat3, -1000);
    
    ASSERT_EQUAL(*Matrix_at(&mat3, 0, 0), -1000);
    
    Matrix mat4;
    
    Matrix_init(&mat4, 6, 1);
    Matrix_fill_border(&mat4, 11);
    
    for(int i = 0; i < 6; i++){
        ASSERT_EQUAL(*Matrix_at(&mat4, 0, i), 11);
    }
    
}

TEST(test_matrix_max) {
    Matrix mat;
    Matrix_init(&mat, 8, 10);
    
    Matrix_fill(&mat, 180);
    
    ASSERT_EQUAL(Matrix_max(&mat), 180);
    
    *Matrix_at(&mat, 5, 3) = 9877;
    
    ASSERT_EQUAL(Matrix_max(&mat), 9877);
    
    *Matrix_at(&mat, 5, 3) = 18732;
    
    ASSERT_EQUAL(Matrix_max(&mat), 18732);
    
    Matrix mat2;
    Matrix_init(&mat2, 1, 1);
    
    ASSERT_EQUAL(Matrix_max(&mat2), 0);
    
    *Matrix_at(&mat2, 0, 0) = 1;
    ASSERT_EQUAL(Matrix_max(&mat2), 1);
    
}

TEST(test_matrix_column_of_min_value_in_row) {
  
        Matrix mat;
        Matrix_init(&mat, 7, 7);

        *Matrix_at(&mat, 1, 0) = 4;
        *Matrix_at(&mat, 1, 1) = 3;
        *Matrix_at(&mat, 1, 2) = 99;
        *Matrix_at(&mat, 1, 3) = 18;
    
       
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 1, 0, 4), 1);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 1, 0, 7), 4);
    *Matrix_at(&mat, 1, 4) = -33;
    *Matrix_at(&mat, 1, 5) = -33;
    *Matrix_at(&mat, 1, 6) = -21;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 1, 0, 7), 4);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 1, 6, 7), 6);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 1, 1, 2), 1);
    
    Matrix_fill(&mat, 800);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 2, 0, 7), 0);
    *Matrix_at(&mat, 2, 3) = -8000;
    *Matrix_at(&mat, 2, 4) = -8001;
    *Matrix_at(&mat, 2, 5) = -8002;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 2, 3, 6), 5);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 2, 3, 5), 4);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 2, 3, 4), 3);
    
    Matrix mat2;
    Matrix_init(&mat2, 1, 1);
    *Matrix_at(&mat2, 0, 0) = 1;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat2, 0, 0, 1), 0);
}

TEST(test_min_value_in_row) {
    
    Matrix mat;
    Matrix_init(&mat, 7, 7);

    *Matrix_at(&mat, 1, 0) = 4;
    *Matrix_at(&mat, 1, 1) = 7;
    *Matrix_at(&mat, 1, 2) = 99;
    *Matrix_at(&mat, 1, 3) = 3;
    
    ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 7), 0);
    ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 4), 3);
    ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 3), 4);
    ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 2, 3), 99);
    
    *Matrix_at(&mat, 1, 6) = -777;
    ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 7), -777);
    ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 6), 0);
    
    
}
TEST_MAIN() // Do NOT put a semicolon here
