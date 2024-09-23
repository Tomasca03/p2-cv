#include <iostream>
#include <cstdlib>  
#include <cassert>  
#include <fstream>  

#include "Image.hpp"
#include "processing.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4 && argc != 5) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
             << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }

    const char* input_file = argv[1];
    const char* output_file = argv[2];
    int new_width = std::atoi(argv[3]);
    int new_height = (argc == 5) ? std::atoi(argv[4]) : 0;

    ifstream in(input_file);
    if (!in) {
        cout << "Error opening file: " << input_file << endl;
        return 1;
    }

    Image input_img;
    Image_init(&input_img, in);

    int original_width = Image_width(&input_img);
    int original_height = Image_height(&input_img);

    if (new_height == 0) {
        new_height = original_height;
    }

    if (new_width <= 0 || new_width > original_width || 
        new_height <= 0 || new_height > original_height) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
             << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }

    seam_carve(&input_img, new_width, new_height);
    
    ofstream out(output_file);
    if (!out) {
        cout << "Error opening file: " << output_file << endl;
        return 1;
    }

    Image_print(&input_img, out);

    return 1;
}
