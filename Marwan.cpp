#include <iostream>
#include "Image_Class.h"
#include <vector>
#include <map>
using namespace std ;

Image LoadImage(string Message){
    cout<< Message<<endl;
    string ImageFileName = "";
    cin>>ws;                           //3lshan el white space 
    getline(cin,ImageFileName);
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
    {1, {255, 255, 255}}, //white
    {2, {0, 0, 0}},//black
    {3, {0, 0, 255}}, //blue
    {4, {0, 255, 0}},//green
    {5, {255, 0, 0}} // red
};
void DisplayColorMenu()
{
    cout << "1. White\n";
    cout << "2. Black\n";
    cout << "3. Blue\n";
    cout << "4. Green\n";
    cout << "5. Red\n";
}
void AddFrame(Image& image){ // filter No.4 Marwan
    cout << "Choose Frame style:\n";
    cout << "1. Simple Frame\n";
    cout << "2. Fancy Frame\n";
    int option;
    cin >> option;
    if (option == 1)
    {
        cout<<"Choose Your Color: \n";
        DisplayColorMenu();
        int ColorChoice;
        cout<<"Enter Your Color Number: ";
        cin>>ColorChoice;
        if (colors.find(ColorChoice) == colors.end()) //checking if the color no is in range
        {
        cout << "Invalid Color\n";
        return;
    }
        vector<int> ColorValue = colors[ColorChoice];

        int thickness;
        cout << "Enter your thickness: ";
        cin >> thickness;

        int MaxThickness= min(image.height, image.width)/2;
        if (thickness <= 0||thickness >= MaxThickness)
        {
            cout << "Invalid Thickness\n";
            return;
        }

        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                if (i < thickness ||i >= image.width - thickness ||j < thickness ||j >= image.height - thickness){
                    for (int k = 0; k < 3; ++k){image(i, j, k) = ColorValue[k];}}
            }
        }
    }
    else if (option == 2)
    {
        cout<<"Choose Your First Color: \n";
        DisplayColorMenu();
        int ColorChoice;
        cout<<"Enter Your Color Number: ";
        cin>>ColorChoice;
        if (colors.find(ColorChoice) == colors.end()) //checking if the color no is in range
        {
        cout << "Invalid Color\n";
        return;
    }
        vector<int> ColorValue = colors[ColorChoice];
        cout<<"Choose The Second Color: \n";
        DisplayColorMenu();
        int SecondColorChoice;
        cin>>SecondColorChoice;
        if(colors.find(SecondColorChoice)==colors.end()){
            cout<<"Invalid Color \n";
            return;}
        int thickness;
        cout << "Enter your thickness: ";
        cin >> thickness;
        int MaxThickness= min(image.height, image.width)/2;
        if (thickness <= 0||thickness >= MaxThickness){
            cout << "Invalid Thickness\n";
            return;}
        vector<int> ColorValue2 = colors[SecondColorChoice];
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                int layer = min(min(i, image.width - 1 - i),min(j, image.height - 1 - j));  
                if (layer < thickness)
                {
                    if (layer % 2 == 0){
                        for (int k = 0; k < 3; ++k){image(i, j, k) = ColorValue[k];}}
                    else{
                        for (int k = 0; k < 3; ++k){image(i, j, k) = ColorValue2[k];}}
                }
            }
        }
    }
    else{cout << "Invalid Frame Style\n";}
}
void ProcessChoice(int Choice , Image& CurrentImage , bool& IsRunning){
    switch (Choice)
    {
    case 1 :
       // FilterGrayScale(CurrentImage);
        break;
    case 2:
        //filterBlackAndWhite(currentImage);
        break;
    case 3:
            //filterInvert(currentImage);
        break;
    case 4:
         AddFrame(CurrentImage);
        break;
    case 5:
            // Flip Image
        break;
    case 6:
            // Rotate Image
        break;
    case 7:
            // Darken and Lighten
        break;
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
    case 17:  //load a new image 
        CurrentImage= LoadImage("Enter the new image name with extension:");
        break;
    case 18: //save current Image 
            {cout<<"Enter a Name to Store a New Image: \n";
            cout<<"And Specify Extention: (.jpg, .bmp, .png, .tga) \n";
            string NewImageName;
            cin>> ws;
            getline(cin,NewImageName);
            CurrentImage.saveImage(NewImageName);
        break;
        }
    case 19: //exit
            IsRunning = false ;
        break;
       
    default:
            cout << "Invalid choice! Please select a number from 1 to 19.\n";
        break;
    }
}
int main(){
    bool IsRunning = true;
    int Choice;
    Image CurrentImage = LoadImage("Please Enter your Image Name\n");
    while (IsRunning){
        DisplayMenu();
        cin>>Choice;
        ProcessChoice(Choice , CurrentImage , IsRunning);
    }
    return 0;
}