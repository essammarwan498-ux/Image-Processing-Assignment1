#include <iostream>
#include "Image_Class.h"
#include <vector>
#include <map>
#include <algorithm> // For std::swap
#include <string>

using namespace std;

Image LoadImage(string Message) {
    cout << Message << endl;
    string ImageFileName = "";
    cin >> ws;                           // 3lshan el white space 
    getline(cin, ImageFileName);
    Image Img(ImageFileName);

    return Img;
}

void DisplayMenu() {
    cout << "\n========================================\n";
    cout << "      IMAGE PROCESSING PROGRAM MENU     \n";
    cout << "========================================\n";
    cout << "1.  Grayscale Conversion\n";
    cout << "2.  Black and White\n";
    cout << "3.  Invert Image\n";
    cout << "4.  Adding Frame to the Picture \n";
    cout << "5.  Flip Image\n";
    cout << "6.  Rotate Image\n";
    cout << "7.  Darken and Lighten Image\n";
    cout << "8.  Crop Images\n";
    cout << "9.  Merge Images\n";
    cout << "10. Detect Image Edges\n";
    cout << "11. Resizing Images\n";
    cout << "12. Blur Images\n";
    cout << "13. Natural Sun Light\n";
    cout << "14. Oil Painting Effect\n";
    cout << "15. Old TV Effect\n";
    cout << "16. Purple Effect\n";
    cout << "----------------------------------------\n";
    cout << "17. Load a New Image\n";
    cout << "18. Save the Current Image\n";
    cout << "19. Exit Program\n";
    cout << "========================================\n";
    cout << "Please enter your choice (1-19): ";
}

map<int, vector<int>> colors = {
    {1, {255, 255, 255}}, // white
    {2, {0, 0, 0}},       // black
    {3, {0, 0, 255}},     // blue
    {4, {0, 255, 0}},     // green
    {5, {255, 0, 0}}      // red
};

void DisplayColorMenu() {
    cout << "1. White\n";
    cout << "2. Black\n";
    cout << "3. Blue\n";
    cout << "4. Green\n";
    cout << "5. Red\n";
}

// --- Filter 1 Peter (GRAYSCALE CONVERSION) ---
void FilterGrayScale(Image& pic) {
    for (int j = 0; j < pic.height; j++) {
        for (int i = 0; i < pic.width; i++) {
            unsigned char red   = pic(i, j, 0);
            unsigned char green = pic(i, j, 1);
            unsigned char blue  = pic(i, j, 2);
            
            int avg = (red + green + blue) / 3;
            pic(i, j, 0) = pic(i, j, 1) = pic(i, j, 2) = avg;
        }
    }
}

// --- Filter 3 Marina(INVERT IMAGE) ---
void InvertImage(Image& pic) {
    for (int i = 0; i < pic.width; i++) {
        for (int j = 0; j < pic.height; j++) {
            for (int c = 0; c < pic.channels; c++) {
                pic(i, j, c) = 255 - pic(i, j, c);
            }
        }
    }
}

// --- Filter 5 (FLIP IMAGE) ---
void FlipImage(Image& pic) {
    cout << "Choose Flip Direction:\n1. Horizontal\n2. Vertical\nEnter choice (1 or 2): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        // Horizontal Flip
        for (int y = 0; y < pic.height; y++) {
            for (int x = 0; x < pic.width / 2; x++) {
                for (int c = 0; c < 3; c++) {
                    swap(pic(x, y, c), pic(pic.width - 1 - x, y, c));
                }
            }
        }
    } else if (choice == 2) {
        // Vertical Flip
        for (int y = 0; y < pic.height / 2; y++) {
            for (int x = 0; x < pic.width; x++) {
                for (int c = 0; c < 3; c++) {
                    swap(pic(x, y, c), pic(x, pic.height - 1 - y, c));
                }
            }
        }
    } else {
        cout << "Invalid choice!\n";
    }
}

// --- Filter 7 Marina(LIGHTEN & DARKEN IMAGE)___
void LightenImage(Image& pic, float percentage) {
    float rate = percentage / 100.0;
    for (int i = 0; i < pic.width; i++) {
        for (int j = 0; j < pic.height; j++) {
            for (int c = 0; c < pic.channels; c++) {
                unsigned char oldcol = pic.getPixel(i, j, c);
                int newcol = oldcol + (255 - oldcol) * rate;
                if (newcol > 255) {
                    newcol = 255;
                }
                pic.setPixel(i, j, c, newcol);
            }
        }
    }
}

void DarkenImage(Image& pic, float percentage) {
    float rate = 1.0 - (percentage / 100.0);
    for (int i = 0; i < pic.width; i++) {
        for (int j = 0; j < pic.height; j++) {
            for (int c = 0; c < pic.channels; c++) {
                unsigned char oldcol = pic.getPixel(i, j, c);
                int newcol = oldcol * rate;
                if (newcol < 0) {
                    newcol = 0;
                }
                pic.setPixel(i, j, c, newcol);
            }
        }
    }
}

void ProcessChoice(int Choice, Image& CurrentImage, bool& IsRunning) {
    switch (Choice) {
    case 1:
        FilterGrayScale(CurrentImage);
        cout << "Grayscale Filter Applied Successfully\n";
        break;

    case 2:
        // filterBlackAndWhite(CurrentImage);
        break;

    case 3:
        InvertImage(CurrentImage);
        cout << "Image Inverted Successfully\n";
        break;

    case 4:
        // AddFrame(CurrentImage);
        break;

    case 5:
        FlipImage(CurrentImage);
        cout << "Image Flipped Successfully\n";
        break;

    case 6:
        // Rotate Image
        break;

    case 7:
    {
        int choice;
        float percentage;
        cout << "\n== Choose Darken / Lighten Image ==\n";
        cout << "1. Lighten Image\n";
        cout << "2. Darken Image\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;
        cout << "Enter percentage: ";
        cin >> percentage;

        switch (choice) {
        case 1:
            LightenImage(CurrentImage, percentage);
            cout << "Image Lightened Successfully\n";
            break;
        case 2:
            DarkenImage(CurrentImage, percentage);
            cout << "Image Darkened Successfully\n";
            break;
        default:
            cout << "Invalid choice for Darken/Lighten!\n";
            break;
        }
        break;
    }

    case 8:
        // Crop Images
        break;

    case 9:
        // Merge Images
        break;

    case 10:
        // Detect Edges
        break;

    case 11:
        // Resizing Images
        break;

    case 12:
        // Blur Images
        break;

    case 13:
        // Natural Sun Light
        break;

    case 14:
        // Oil Painting
        break;

    case 15:
        // Old TV Effect
        break;

    case 16:
        // Purple Effect
        break;

    case 17: // load a new image 
        CurrentImage = LoadImage("Enter the new image name with extension:");
        break;

    case 18: // save current Image 
    {
        cout << "Enter a Name to Store a New Image: \n";
        cout << "And Specify Extention: (.jpg, .bmp, .png, .tga) \n";
        string NewImageName;
        cin >> ws;
        getline(cin, NewImageName);
        CurrentImage.saveImage(NewImageName);
        cout << "Image Saved Successfully\n";
        break;
    }

    case 19: // exit
        IsRunning = false;
        break;

    default:
        cout << "Invalid choice! Please select a number from 1 to 19.\n";
        break;
    }
}

int main() {
    bool IsRunning = true;
    int Choice;

    Image CurrentImage = LoadImage("Please Enter your Image Name\n");

    while (IsRunning) {
        DisplayMenu();
        cin >> Choice;
        ProcessChoice(Choice, CurrentImage, IsRunning);
    }

    return 0;
}