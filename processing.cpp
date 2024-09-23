#include <cassert>
#include <vector>
#include "processing.hpp"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  
  Matrix_init(energy, Image_width(img), Image_height(img));

  Pixel n, s, w, e;

  for (int i = 1; i < Matrix_height(energy) - 1; i++)
  {
    for (int j = 1; j < Matrix_width(energy) - 1; j++)
    {
      n = Image_get_pixel(img, i - 1, j);
      s = Image_get_pixel(img, i + 1, j);
      w = Image_get_pixel(img, i, j - 1);
      e = Image_get_pixel(img, i, j + 1);
      int vertical = squared_difference(n, s);
      int horizontal = squared_difference(w, e);
      *Matrix_at(energy, i, j) =  vertical + horizontal;
    }
  }

  Matrix_fill_border(energy, Matrix_max(energy));
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  assert(energy != nullptr && cost != nullptr);

  Matrix_init(cost, Matrix_width(energy), Matrix_height(energy));

  for (int i = 0; i < Matrix_width(cost); i++)
  {
    *Matrix_at(cost, 0, i) = *Matrix_at(energy, 0, i);
  }

  for (int i = 1; i < Matrix_height(cost); i++)
  {
    for (int j = 0; j < Matrix_width(cost); j++)
    {
      if (j == 0)
      {
        *Matrix_at(cost, i, j) = *Matrix_at(energy, i, j) + Matrix_min_value_in_row(cost, i - 1, j, j + 2);
      }
      else if (j == Matrix_width(cost) - 1)
      {
        *Matrix_at(cost, i, j) = *Matrix_at(energy, i, j) + Matrix_min_value_in_row(cost, i - 1, j -1, j + 1);
      }
      else
      {
        *Matrix_at(cost, i, j) = *Matrix_at(energy, i, j) + Matrix_min_value_in_row(cost, i - 1, j -1, j + 2);
      }
    }
  }
}


// REQUIRES: cost points to a valid Matrix
// EFFECTS:  Returns the vertical seam with the minimal cost according to the given
//           cost matrix, represented as a vector filled with the column numbers for
//           each pixel along the seam, starting with the lowest numbered row (top
//           of image) and progressing to the highest (bottom of image). The length
//           of the returned vector is equal to Matrix_height(cost).
//           While determining the seam, if any pixels tie for lowest cost, the
//           leftmost one (i.e. with the lowest column number) is used.
//           See the project spec for details on computing the minimal seam.
vector<int> find_minimal_vertical_seam(const Matrix* cost) {
  assert(cost != nullptr);
  int height = Matrix_height(cost);
  int width = Matrix_width(cost);
  vector<int> seam(height, 0);
  vector<int> dir = {-1, 0, 1};
  seam[height - 1] = Matrix_column_of_min_value_in_row(cost, height - 1, 0, width);
    
    
  for(int i = height - 2; i >= 0; i--) {
      int prv = seam[i + 1];
        
      int st = (prv - 1 < 0) ? 0 : prv - 1;
      int en = (prv + 2 >= width) ? width : prv + 2;
        
      seam[i] = Matrix_column_of_min_value_in_row(cost, i, st, en);   
  }
  return seam;
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam.size() == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Declare a new variable to hold the smaller Image, and
//           then do an assignment at the end to copy it back into the
//           original image.
void remove_vertical_seam(Image *img, const vector<int> &seam) {
  assert(img != nullptr && Image_width(img) >= 2);
  assert(seam.size() == Image_height(img));
  for (int x : seam)
  {
    assert(0 <= x && x < Image_width(img));
  }

  Image aux_img;
  Image_init(&aux_img, Image_width(img) - 1, Image_height(img));

  for (int i = 0; i < Image_height(img); i++)
  {
    for (int j = 0; j < Image_width(img); j++)
    {
      Pixel p;
      p = Image_get_pixel(img, i, j);
      
      if (j < seam[i])
      {
        Image_set_pixel(&aux_img, i, j, p);
      }
      else if (j > seam[i])
      {
        Image_set_pixel(&aux_img, i, j - 1, p);
      }
    }
  }

  /*
  How to resize

  First thought:
  Image_init(img, Image_width(&aux_img), Image_height(&aux_img));

  Second Thought:
  No other thought
  
  */
   
  Image_init(img, Image_width(&aux_img), Image_height(&aux_img));

  for (int i = 0; i < Image_height(&aux_img); i++)
  {
    for (int j = 0; j < Image_width(&aux_img); j++)
    {
      Pixel p;
      p = Image_get_pixel(&aux_img, i, j);

      Image_set_pixel(img, i, j, p);
    }
  }
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use a vector to hold the seam, and make sure that it has
//           the right size. You can use .data() on a vector to get
//           the underlying array.
void seam_carve_width(Image *img, int newWidth) {
  assert(img != nullptr);

  Matrix energy;
  Matrix cost;
  vector<int> seam;

  while (Image_width(img) != newWidth)
  {
    compute_energy_matrix(img, &energy);
    compute_vertical_cost_matrix(&energy, &cost);
    seam = find_minimal_vertical_seam(&cost);
    remove_vertical_seam(img, seam);
  }
  


}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  assert(img != nullptr);
  assert(0 < newHeight && newHeight <= Image_height(img));

  rotate_left(img);
  seam_carve_width(img, newHeight);
  rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  assert(img != nullptr);
  assert(0 < newWidth && newWidth <= Image_width(img));
  assert(0 < newHeight && newHeight <= Image_height(img));

  seam_carve_width(img, newWidth);
  seam_carve_height(img, newHeight);
}
