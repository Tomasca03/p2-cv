#include <iostream>
#include <cstdlib>  // For std::atoi
#include <cassert>  // For assert
#include <fstream>  // For file I/O

#include "Image.hpp"
#include "processing.hpp"

int main(int argc, char *argv[]) {
    // Check for correct number of arguments (4 or 5)
    if (argc != 4 && argc != 5) {
        std::cerr << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
                  << "WIDTH and HEIGHT must be less than or equal to original" << std::endl;
        return 1;
    }

    // Read command-line arguments
    const char* input_file = argv[1];
    const char* output_file = argv[2];
    int new_width = std::atoi(argv[3]);
    int new_height = (argc == 5) ? std::atoi(argv[4]) : 0;

    // Open input file
    std::ifstream in(input_file);
    if (!in) {
        std::cerr << "Error opening file: " << input_file << std::endl;
        return 1;
    }

    // Initialize the input image from the input file
    Image input_img;
    Image_init(&input_img, in);

    // Get original width and height of the image
    int original_width = Image_width(&input_img);
    int original_height = Image_height(&input_img);

    // If no height is specified, keep the original height
    if (new_height == 0) {
        new_height = original_height;
    }

    // Check if new width and height are valid
    if (new_width <= 0 || new_width > original_width || 
        new_height <= 0 || new_height > original_height) {
        std::cerr << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
                  << "WIDTH and HEIGHT must be less than or equal to original" << std::endl;
        return 1;
    }

    seam_carve(&input_img, new_width, new_height);
    

    // Open output file
    std::ofstream out(output_file);
    if (!out) {
        std::cerr << "Error opening file: " << output_file << std::endl;
        return 1;
    }

    // Write the resized image to the output file
    Image_print(&input_img, out);

    return 0;
}
