#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>



using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----

TEST(test_image_init) {
    Image img;
    Image_init(&img, 3, 2);

    ostringstream s;
    Image_print(&img, s);

    
    ostringstream correct;
    correct << "P3\n3 2\n255\n";
    correct << "0 0 0 0 0 0 0 0 0 \n";
    correct << "0 0 0 0 0 0 0 0 0 \n";

    ASSERT_EQUAL(s.str(), correct.str());
    
    
}

TEST(test_image_init_stream) {
    
    Image img;
    Image_init(&img, 2, 2);
    string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
    istringstream ss_input(input);
    Image_init(&img, ss_input);
    
    string output_correct = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
    
    ostringstream ss_output;
    Image_print(&img, ss_output);
    string actual = ss_output.str();
    cout << actual << "\n";
    ASSERT_EQUAL(actual, output_correct);
    
}

TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  ostringstream s;
  Image_print(&img, s);


  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

TEST(test_image_width_and_height) {
    Image img;
    Image_init(&img, 5, 2);
    
    ASSERT_EQUAL(Image_width(&img), 5);
    ASSERT_EQUAL(Image_height(&img), 2);
    
    Image_init(&img, 1, 1);
    ASSERT_EQUAL(Image_width(&img), 1);
    ASSERT_EQUAL(Image_height(&img), 1);
}

TEST(test_image_get_pixel) {
    Image img;
    Image_init(&img, 3, 3);
    
    Pixel red = {255, 0, 0};
    Pixel green = {0, 255, 0};
    Pixel blue = {255, 255, 255};
    
    // Set specific pixels
    Image_set_pixel(&img, 0, 0, red);
    Image_set_pixel(&img, 1, 1, green);
    Image_set_pixel(&img, 2, 2, blue);
    
    Pixel a = Image_get_pixel(&img, 0, 0);
    Pixel b = Image_get_pixel(&img, 1, 1);
    Pixel c = Image_get_pixel(&img, 2, 2);
    
   
    ASSERT_EQUAL(a.r, 255);
    ASSERT_EQUAL(a.g, 0);
    ASSERT_EQUAL(a.b, 0);
    
    ASSERT_EQUAL(b.r, 0);
    ASSERT_EQUAL(b.g, 255);
    ASSERT_EQUAL(b.b, 0);
    
    ASSERT_EQUAL(c.r, 255);
    ASSERT_EQUAL(c.g, 255);
    ASSERT_EQUAL(c.b, 255);
    
}

TEST(test_image_set_pixel) {
    Image img;
    Image_init(&img, 1, 1);
    
    Pixel color1 = {0, 0, 255};
    
    

    Image_set_pixel(&img, 0, 0, color1);
    
    Pixel P1 = Image_get_pixel(&img, 0, 0);
    
    ASSERT_TRUE(Pixel_equal(P1, color1));
    
    
    Image_init(&img, 3, 2);
    Pixel color2 = {255, 0, 255};
    
    Image_set_pixel(&img, 1, 2, color2);
    
    Pixel P2 = Image_get_pixel(&img, 1, 2);
    
    
    ASSERT_TRUE(Pixel_equal(P2, color2));
}

TEST(test_image_fill) {
    
    Image img;
    Image_init(&img, 1, 1);
    
    Pixel color1 = {255, 255, 255};
    
    Image_fill(&img, color1);
    
    Image expected;
    Image_init(&expected, 1, 1);
    
    Image_fill(&expected, color1);
    
    ASSERT_TRUE(Image_equal(&img, &expected));
    
    Image_init(&img, 6, 3);
    Image_init(&expected, 6, 3);
    
    Pixel color2 = {0, 0, 0};
    
    Image_fill(&img, color2);
    Image_fill(&expected, color2);
   
    ASSERT_TRUE(Image_equal(&img, &expected));
    
    
    
    
}
// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

TEST_MAIN() // Do NOT put a semicolon here
