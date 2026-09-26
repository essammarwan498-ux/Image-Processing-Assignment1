#include <iostream>
#include "Image_Class.h"
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

/*
    filters from 1---->16 Must be here 
    Peter 1,5,9,13
    mark  2,6,10,14
    marina3,7,11,15
    maro  4,8,12,16
*/
enum enBorderColor {White,Black,Blue,Green,Red,Unknown};
void AddFrame(Image& image) // filter No.4 Marwan
{
    cout << "Choose Frame style:\n";
    cout << "1. Simple Frame\n";
    cout << "2. Fancy Frame\n";
    int option;
    cin >> option;

    if (option == 1)
    {
    string color;

    cout << "Choose Your Color (White, Black, Blue, Green, Red): \n";
    cin >> ws;           //to clean the buffer for getline 
    getline(cin, color);

    for (char& c : color) // to allow any typo Red ReD rED reD etc
    {
        c = tolower(c);
    }
    enBorderColor selectedColor = Unknown; //for Switch case 
    if (color == "white")
        selectedColor = White;
    else if (color == "black")
        selectedColor = Black;
    else if (color == "blue")
        selectedColor = Blue;
    else if (color == "green")
        selectedColor = Green;
    else if (color == "red")
        selectedColor = Red;
    int thickness;
    cout << "Enter your thickness: ";
    cin >> thickness;
    int r = 0, g = 0, b = 0;
    switch (selectedColor)
    {
    case White:
        r = 255, g = 255, b = 255;
        break;
    case Black:
        r = 0, g = 0, b = 0;
        break;
    case Blue:
        r = 0, g = 0, b = 255;
        break;
    case Green:
        r = 0, g = 255, b = 0;
        break;
    case Red:
        r = 255, g = 0, b = 0;
        break;
    default:
        cout << "Invalid Color\n";
        return;
    }

    int colorValue[3] = {r, g, b};  

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            if (i < thickness ||                //left
                i >= image.width - thickness || //right
                j < thickness ||                //top
                j >= image.height - thickness)  //bottom
            {
                for (int k = 0; k < 3; ++k)
                {
                    image(i, j, k) = colorValue[k];
                }
            }
        }
    }
}
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
            {cout<<"Enter a Name to Store a New Image: ";
            cout<<"And Specify Extention .jpg .bmp .png .tga";
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