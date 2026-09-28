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
    cout << "8.  Resizing Images\n";
    cout << "9.  Merge Images\n";
    cout << "10. Detect Image Edges\n";
    cout << "11. Crop Images\n";
    cout << "12. Blur Images\n";
    cout << "13.Sunlight / Brightness Correction (Wano Sunlight)\n";
    cout << "14. TV Screen Effect (Den Den Mushi TV)\n";
    cout << "15. Purple Night Effect\n"; //Purple Effect
    cout << "16. Infrared Photography\n";
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
int GetColorChoice(const string& message = "Choose Color Number: ") {
    cout << message;
    int ColorChoice;
    cin >> ColorChoice;

    if (ColorChoice < 1 || ColorChoice > colors.size()) { 
        cout << "Invalid Color\n";
        return -1;
    }
    return ColorChoice;
}
void AddFrame(Image& image){ // filter No.4 Marwan
    cout << "Available Frame styles:\n";
    cout << "1. Simple Frame\n";
    cout << "2. Fancy Frame\n";
    cout << "Choose Frame Style: ";
    int option;
    cin >> option;

    if (option < 1 || option > 2) { //to limit the options
        cout << "Invalid Frame Style\n";
        return;
    }

    cout << "Enter frame thickness: ";
    int thickness;
    cin >> thickness;

    int MaxThickness= min(image.height, image.width)/2;  //Validate the thickness to not exceed the half of photo 
    if (thickness <= 0 || thickness > MaxThickness)
    {
        cout << "Invalid Thickness\n";
        return;
    }

    DisplayColorMenu();                     //displaying the 5 colors to choose      
    int Color1Choice = GetColorChoice();    //get the value from from getcolorvalue 
    if (Color1Choice == -1) {               //for wrong choice
        return;
    }
    vector<int> Color1Value = colors[Color1Choice]; //colors[1] = white and this is the values come from map

    if (option == 1){
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                if (i < thickness ||i >= image.width - thickness ||j < thickness ||j >= image.height - thickness){
                    for (int k = 0; k < 3; ++k) {image(i, j, k) = Color1Value[k];}
                }
            }
        }
        return;
    }

    int SecondColorChoice = GetColorChoice("Choose The Second Color Number: ");
    if (SecondColorChoice == -1) {
        return;
    }
    vector<int> Color2Value = colors[SecondColorChoice];

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int layer = min(min(i, image.width - 1 - i),min(j, image.height - 1 - j));  //check the layer from the edge from all directions
            if (layer < thickness) {            //if the layer in frame zone will be colored
                if (layer % 2 == 0){            //if layer even =color 1 else color 2 
                    for (int k = 0; k < 3; ++k) {
                        image(i, j, k) = Color1Value[k];
                    }
                } 
                else{
                    for (int k = 0; k < 3; ++k) {
                        image(i, j, k) = Color2Value[k];
                    }
                }
            }
        }
    }
}
void ReSize(Image& image){
    cout<<"Choose your Resize Method Number: \n";
    cout<<"1.Dimensions \n";
    cout<<"2.Ratio \n";
    int Option ;
    cin>> Option;
    if(Option < 1 ||Option > 2){
        cout<<"Invalid Resize Method \n";
        return;
    }
        int NewWidth ,NewHight;
    if(Option == 1){
        cout<<"Please Enter a New Width and Hight \n";
        cin>>NewWidth >>NewHight;
    }else{
    double Ratio;
    cout<<"Enter a Ratio to Resize\n";
    cin>>Ratio;
    if(Ratio <=0){
        cout<<"Invalid Ratio \n";
        return;
    }
    NewWidth =image.width * Ratio ;
    NewHight =image.height * Ratio;}
    if(NewWidth <= 0 || NewHight <=0){
        cout<<"Invalid Dimensions \n";
        return;
    }
    Image NewImage (NewWidth ,NewHight);
        for(int i = 0; i < NewImage.width; ++i){
            for(int j = 0; j<NewImage.height; ++j){
                int old_X = i* image.width / NewImage.width;
                int old_Y = j * image.height / NewImage.height;
                for(int k=0; k<3;++k){
                    NewImage(i,j,k)=image(old_X,old_Y,k);
                }
            }
        }
        image = NewImage;
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
    case 8: //Resizing Image
            ReSize(CurrentImage);
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
            // Sunlight / Brightness Correction (Wano Sunlight)
        break;
    case 14:
            // TV Screen Effect (Den Den Mushi TV)
        break;
    case 15:
            // Purple Night Effect (Purple Luffy)
        break;
    case 16:
            //Infrared Photography
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