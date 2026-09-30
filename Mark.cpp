#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;

// filter 2 Mark emad
void blackAndWhite(Image& image) {
    for (int _y = 0; _y < image.height; _y++) {
        for (int _x = 0; _x < image.width; _x++) {
            int gray = 0;
            for (int k = 0; k < 3; k++) gray += image(_x, _y, k);
            gray /= 3;
            unsigned char v = gray > 127 ? 255 : 0;
            for (int k = 0; k < 3; k++) image(_x, _y, k) = v;
        }
    }
}

// filter 6 Mark emad
Image rotate90(Image& image) {
    Image out(image.height, image.width, 3);
    for (int _y = 0; _y < image.height; _y++)
        for (int _x = 0; _x < image.width; _x++)
            for (int k = 0; k < 3; k++)
                out(image.height - 1 - _y, _x, k) = image(_x, _y, k);
    return out;
}

Image rotate180(Image& image) {
    Image out(image.width, image.height, 3);
    for (int _y = 0; _y < image.height; _y++)
        for (int _x = 0; _x < image.width; _x++)
            for (int k = 0; k < 3; k++)
                out(image.width - 1 - _x, image.height - 1 - _y, k) = image(_x, _y, k);
    return out;
}

Image rotate270(Image& image) {
    Image out(image.height, image.width, 3);
    for (int _y = 0; _y < image.height; _y++)
        for (int _x = 0; _x < image.width; _x++)
            for (int k = 0; k < 3; k++)
                out(_y, image.width - 1 - _x, k) = image(_x, _y, k);
    return out;
}

void runMenu(Image& image) {
    int choice;
    do {
        cout << "\n1. Black & White\n2. Rotate 90\n3. Rotate 180\n4. Rotate 270\n5. Save\n6. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) blackAndWhite(image);
        else if (choice == 2) image = rotate90(image);
        else if (choice == 3) image = rotate180(image);
        else if (choice == 4) image = rotate270(image);
        else if (choice == 5) {
            string outname;
            cout << "Output name: ";
            cin >> outname;
            image.saveImage(outname);
        }
    } while (choice != 6);
}

int main() {
    string filename;
    cout << "Enter image name: ";
    cin >> filename;
    Image image;
    if (!image.loadImage(filename)) {
        cout << "Error loading image!\n";
        return 1;
    }
    runMenu(image);
    return 0;
}