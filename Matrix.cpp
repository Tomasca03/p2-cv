#include <cassert>
#include "Matrix.hpp"


// REQUIRES: mat points to a Matrix
//           0 < width && 0 < height
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height,
//           with all elements initialized to 0.
void Matrix_init(Matrix* mat, int width, int height) {
  assert(mat != nullptr);
  assert(width > 0);
  assert(height > 0);

  mat ->data.resize(height * width, 0);
  mat->height = height;
  mat->width = width;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {

  assert(mat != nullptr);
  assert(mat -> data.size() == Matrix_height(mat)*Matrix_width(mat));

  os << Matrix_width(mat) << " " << Matrix_height(mat) << "\n";
  
  for (int i = 0; i < Matrix_height(mat); i++)
  {
    for (int j = 0; j < Matrix_width(mat); j++)
    {
      os << *Matrix_at(mat, i, j) << " ";
    }
    os << "\n";
  }
  
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  assert(mat != nullptr);

  return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  assert(mat != nullptr);

  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  
  assert(mat != nullptr);
  assert(row >= 0 && row < Matrix_height(mat));
  assert(column >= 0 && column < Matrix_width(mat));

  int value = row * Matrix_width(mat) + column;
  return &mat->data[value];
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  assert(mat != nullptr);
  assert(row >= 0 && row < Matrix_height(mat));
  assert(column >= 0 && column < Matrix_width(mat));
  
  int value = row * Matrix_width(mat) + column;
  return &mat->data[value];
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  assert(mat != nullptr);

  for (int i = 0; i < Matrix_height(mat); i++)
  {
    for (int j = 0; j < Matrix_width(mat); j++)
    {
      *Matrix_at(mat, i, j) = value;
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  assert(mat != nullptr);

  for(int i = 0; i < mat->height; i++)
  {
    for(int j = 0; j < mat->width; j++)
    {
            
      if(i == 0 || i == mat->height - 1 || j == 0 || j == mat->width - 1)
      {
        *Matrix_at(mat, i, j) = value;
      }
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  assert(mat != nullptr);

  int max = *Matrix_at(mat, 0,0);

  for (int i = 0; i < Matrix_height(mat); i++)
  {
    for (int j = 0; j < Matrix_width(mat); j++)
    {
      if (*Matrix_at(mat, i, j) > max)
      {
        max = *Matrix_at(mat, i, j);
      }
    }
  }

  return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  assert(mat != nullptr);
  assert(row >= 0 && row < Matrix_height(mat));
  assert(column_start >= 0 && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  
  int min_value = *Matrix_at(mat, row, column_start);
  int min_column = column_start;
    
  for (int col = column_start + 1; col < column_end; col++) 
  {
    int current_value = *Matrix_at(mat, row, col);
    if (current_value < min_value) 
    {
        min_value = current_value;
        min_column = col;
    }
  }

  return min_column;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
  assert(mat != nullptr);
  assert(row >= 0 && row < Matrix_height(mat));
  assert(column_start >= 0 && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

 
  int min_value = *Matrix_at(mat, row, column_start);
    
  for (int col = column_start + 1; col < column_end; col++) 
  {
    int current_value = *Matrix_at(mat, row, col);
       
    if (current_value < min_value) 
    {
        min_value = current_value;
    }
  }

  
  return min_value;
}
