#include <cassert>
#include "Image.hpp"

// REQUIRES: img points to an Image
//           0 < width && 0 < height
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height, with
//           all pixels initialized to RGB values of 0.
void Image_init(Image* img, int width, int height) {
  assert(img != nullptr);
  assert(0 < width && 0 < height);
  
  img->height = height;
  img->width = width;
  Matrix_init(&img->blue_channel, width, height);
  Matrix_init(&img->red_channel, width, height);
  Matrix_init(&img->green_channel, width, height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img, is
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
void Image_init(Image* img, std::istream& is) {
  assert(img != nullptr);
  
  std::string format;
  int max_intensity;

  is >> format;
  assert(format == "P3");

  int width, height;
  is >> width >> height;

  is >> max_intensity;
  assert(max_intensity == 255);

  img->height = height;
  img->width = width;
  Matrix_init(&img->blue_channel, width, height);
  Matrix_init(&img->red_channel, width, height);
  Matrix_init(&img->green_channel, width, height);

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      Pixel p;
      is >> p.r >> p.g >> p.b;

      int *ptr_red = Matrix_at(&img->red_channel, i, j);
      *ptr_red = p.r;

      int *ptr_green = Matrix_at(&img->green_channel, i, j);
      *ptr_green = p.g;

      int *ptr_blue = Matrix_at(&img->blue_channel, i, j);
      *ptr_blue = p.b;
    }
  }

}

// REQUIRES: img points to a valid Image
// MODIFIES: os
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  assert(false); // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  assert(false); // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  assert(false); // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  assert(false); // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  assert(false); // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  assert(false); // TODO Replace with your implementation!
}
