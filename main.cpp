/*
========================Part 1=========================================
1)Marwan Essam Abdulrahman El-Sayed: 20251383 || Filters 4,8
2)Peter Gawdat Habib:                20250128 || Filters 1,5
3)Mark Emad Raouf:                   20250515 || Filters 2,6
4)Marina Girgis Salama:              20250518 || Filters 3,7
Section : S23
=======================================================================
*/
#include <iostream>
#include "Image_Class.h"
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
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
	cout << " IMAGE PROCESSING PROGRAM MENU \n"; 
	cout << "========================================\n"; 
	cout << "1. Grayscale Conversion\n"; 
	cout << "2. Black and White\n"; 
	cout << "3. Invert Image\n"; 
	cout << "4. Adding Frame to the Picture \n"; 
	cout << "5. Flip Image\n"; 
	cout << "6. Rotate Image\n"; 
	cout << "7. Darken and Lighten Image\n"; 
	cout << "8. Resizing Image\n";
	cout << "9. Merge Images\n"; 
	cout << "10. Detect Image Edges\n"; 
	cout << "11. Crop Images\n"; 
	cout << "12. Blur Images\n"; 
	cout << "13. Sunlight / Brightness Correction \n"; 
	cout << "14. TV Screen Effect \n"; 
	cout << "15. Purple Night Effect \n"; 
	cout << "16. Infrared Photography\n"; 
	cout << "17. Skewing / Distortion\n";
	cout << "18. Oil Painting Effect\n"; 
	cout << "----------------------------------------\n"; 
	cout << "19. Load a New Image\n"; 
	cout << "20. Save the Current Image\n"; 
	cout << "21. Exit Program\n"; 
	cout << "========================================\n"; 
	cout << "Please enter your choice (1-21): "; 
}
// --- Filter 1 Peter (GRAYSCALE CONVERSION) ---
void FilterGrayScale(Image& image) {
    for (int j = 0; j < image.height; j++) {
        for (int i = 0; i < image.width; i++) {
            unsigned char red   = image(i, j, 0);
            unsigned char green = image(i, j, 1);
            unsigned char blue  = image(i, j, 2);
            
            int avg = (red + green + blue) / 3;
            image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = avg;
        }
    }
}
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
// --- Filter 3 Marina(INVERT IMAGE) ---
void InvertImage(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int c = 0; c < image.channels; c++) {
                image(i, j, c) = 255 - image(i, j, c);
            }
        }
    }
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

    if (ColorChoice < 1 || ColorChoice > 5) { 
        cout << "Invalid Color\n";
        return -1;
    }
    return ColorChoice;
}
void AddFrame(Image& image){ // filter No.4 Marwan Essam
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
// --- Filter 5 Peter (FLIP IMAGE) ---
void FlipImage(Image& image) {
    cout << "Choose Flip Direction:\n1. Horizontal\n2. Vertical\nEnter choice (1 or 2): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        // Horizontal Flip
        for (int y = 0; y < image.height; y++) {
            for (int x = 0; x < image.width / 2; x++) {
                for (int c = 0; c < 3; c++) {
                    swap(image(x, y, c), image(image.width - 1 - x, y, c));
                }
            }
        }
    } else if (choice == 2) {
        // Vertical Flip
        for (int y = 0; y < image.height / 2; y++) {
            for (int x = 0; x < image.width; x++) {
                for (int c = 0; c < 3; c++) {
                    swap(image(x, y, c), image(x, image.height - 1 - y, c));
                }
            }
        }
    } else {
        cout << "Invalid choice!\n";
    }
}
void RotateImage(Image& image)
{
    cout << "Choose Rotation Angle:\n";
    cout << "1. Rotate 90 Degrees\n";
    cout << "2. Rotate 180 Degrees\n";
    cout << "3. Rotate 270 Degrees\n";

    int choice;
    cin >> choice;

    if (choice < 1 || choice > 3)
    {
        cout << "Invalid Rotation Choice\n";
        return;
    }

    if (choice == 1)
    {
        Image temp(image.height, image.width);

        for (int y = 0; y < image.height; y++)
        {
            for (int x = 0; x < image.width; x++)
            {
                for (int k = 0; k < 3; k++)
                {
                    temp(image.height - 1 - y, x, k) = image(x, y, k);
                }
            }
        }

        image = temp;
    }

    else if (choice == 2)
    {
        Image temp(image.width, image.height);

        for (int y = 0; y < image.height; y++)
        {
            for (int x = 0; x < image.width; x++)
            {
                for (int k = 0; k < 3; k++)
                {
                    temp(image.width - 1 - x, image.height - 1 - y, k)
                        = image(x, y, k);
                }
            }
        }

        image = temp;
    }

    else if (choice == 3)
    {
        Image temp(image.height, image.width);

        for (int y = 0; y < image.height; y++)
        {
            for (int x = 0; x < image.width; x++)
            {
                for (int k = 0; k < 3; k++)
                {
                    temp(y, image.width - 1 - x, k) = image(x, y, k);
                }
            }
        }

        image = temp;
    }
}

// --- Filter 7 Marina(LIGHTEN & DARKEN IMAGE)___
void LightenImage(Image& image, float percentage) {
    float rate = percentage / 100.0;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int c = 0; c < image.channels; c++) {
                unsigned char oldcol = image.getPixel(i, j, c);
                int newcol = oldcol + (255 - oldcol) * rate;
                if (newcol > 255) {
                    newcol = 255;
                }
                image.setPixel(i, j, c, newcol);
            }
        }
    }
}

void DarkenImage(Image& image, float percentage) {
    float rate = 1.0 - (percentage / 100.0);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int c = 0; c < image.channels; c++) {
                unsigned char oldcol = image.getPixel(i, j, c);
                int newcol = oldcol * rate;
                if (newcol < 0) {
                    newcol = 0;
                }
                image.setPixel(i, j, c, newcol);
            }
        }
    }
}
// Filter NO.8 Marwan Essam
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
//---------filter 11 Marina(CROP IMAGE)---------
void CropImage(Image& image) {
    int x, y, W, H;

    cout << "Enter starting x(column from left): ";
    cin >> x;
    cout << "Enter starting y(row from top): ";
    cin >> y;
    cout << "Enter crop Width(W): ";
    cin >> W;
    cout << "Enter crop Height (H): ";
    cin >> H;

    if (x < 0 || y < 0 ||  W <= 0 || H <= 0) {
        cout << "Invalid value" << endl;
        return;
    }

    if ((x + W) > image.width || (y + H) > image.height) {
        cout << "Invalid crop size because it is outside the image" << endl;
        return;
    }

    Image cropped(W, H);

    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            for (int c = 0; c < image.channels; c++) {
                cropped(i, j, c) = image(x + i, y + j, c);
            }
        }
    }

    image = cropped;
    cout << "Image cropped successfully!" << endl;
}
/*------------------------- Filter NO.12 MARO --------------------------*/
void BlurImage(Image& image){
    Image NewImage(image.width , image.height);
    int radius;
    cout<<"Enter Your Blur Level (1,2,3,4,5)\n";
    cin>> radius;
    if(radius<1 || radius >5){
        cout<< "Invalid Level\n";
        return;
    }
    for(int i = 0 ; i < image.width ; ++i){
        for (int j = 0; j< image.height; ++j){
            for(int c =0 ; c<3; ++c){
                int sum=0, count=0;
                for(int k= i-radius; k <= i+radius; ++k){
                    for(int v =j - radius; v <= j+radius; ++v){
                        if (k >= 0 && k < image.width && v >= 0 && v < image.height) {
                            sum += image(k,v,c);
                            count++;
                        }
                    }
                }
        NewImage(i, j, c) = sum / count;
            }
        }
    }
    image = NewImage;   
}
//---------filter 15 Marina(PURPLE NIGHT EFFECT)----------
void PurpleNightEffect(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {  
            int red = image(i, j, 0);
            int green = image(i, j, 1);
            int blue = image(i, j, 2);

            int newRed = (int)(red * 1.1 + 15);
            int newGreen = (int)(green * 0.6);
            int newBlue= (int)(blue * 1.2 + 20);

            if (newRed > 255)
            {
                newRed = 255;
            }
            if (newGreen > 255)
            {
                newGreen = 255;
            }
            if (newBlue > 255)
            {
                newBlue = 255;
            }

            image(i, j, 0) = newRed;
            image(i, j, 1) = newGreen;
            image(i, j, 2) = newBlue;
        }
    }
    cout << "Purple Night Effect done Successfully!\n";
}
/*------------------filter No.16 MARO-------------*/
void InfraredImage(Image& image){
    for(int i=0;i<image.width;++i){
        for(int j=0;j<image.height;++j){
            image(i,j,0)= 255;
            image(i,j,1) = 255 - image(i,j,1);
            image(i, j,2) = 255 - image(i, j, 2);
        }
    }
}
/*Filter No. 17 MARO */
void Skewness(Image& image){
    float angle;
    cout<<"Enter Your Skewness Angle: ";
    cin>>angle;
    float rad = angle * M_PI /180.0;
    int maxShift = image.width * tan(rad);
    Image NewImage(image.width, image.height + maxShift);
    for (int i = 0; i < NewImage.width; ++i) {
        for (int j = 0; j < NewImage.height; ++j) {
            for (int c = 0; c < 3; ++c) {
                NewImage(i, j, c) = 255;
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        int shift = i * tan(rad);
        for (int j = 0; j < image.height; ++j) {
            for (int c = 0; c < 3; ++c) {
                NewImage(i, j + shift, c) = image(i, j, c);
            }
        }
    }
    image = NewImage;
}
void oilPainting(Image& image){
    int radius;
    int IntensityLevel;
    cout<<"Please Enter Brush Size: ";
    cin>>radius;
    if(radius<=0){
        cout<< "Invalid Brush Size\n";
        return;
    }
    cout<<"Please Enter Intensity Level: ";
    cin>>IntensityLevel;
    if(IntensityLevel <=0){
        cout<<"Invalid Intensity Level\n";
        return;
    }
    Image NewImage(image.width,image.height);
    for(int i = 0 ; i<image.width; ++i){
        for(int j =0 ; j<image.height; ++j){
            int IntensityCount [IntensityLevel]={0};
            int sumR[IntensityLevel] = {0};
            int sumG[IntensityLevel] = {0};
            int sumB[IntensityLevel] = {0};
            for (int k = i - radius; k <= i + radius; ++k) {
                for (int v = j - radius; v <= j + radius; ++v) {
                    if (k >= 0 && k < image.width && v >= 0 && v < image.height) {
                        int r = image(k, v, 0);
                        int g = image(k, v, 1);
                        int b = image(k, v, 2);

                        int curIntensity = ((r + g + b) / 3.0) * IntensityLevel / 255.0;
                        if (curIntensity >= IntensityLevel) curIntensity = IntensityLevel - 1;

                        IntensityCount[curIntensity]++;
                        sumR[curIntensity] += r;
                        sumG[curIntensity] += g;
                        sumB[curIntensity] += b;
                    }
                }
            }
            int maxCount = 0;
            int maxIndex = 0;
            for (int level = 0; level < IntensityLevel; ++level) {
                if (IntensityCount[level] > maxCount) {
                    maxCount = IntensityCount[level];
                    maxIndex = level;
                }
            }
            NewImage(i, j, 0) = sumR[maxIndex] / maxCount;
            NewImage(i, j, 1) = sumG[maxIndex] / maxCount;
            NewImage(i, j, 2) = sumB[maxIndex] / maxCount;
        }
    }
    image = NewImage;
}
void ProcessChoice(int Choice , Image& CurrentImage , bool& IsRunning){
    switch (Choice)
    {
    case 1 :
        FilterGrayScale(CurrentImage);
        cout << "Grayscale Filter Applied Successfully\n";
        break;
    case 2:
        blackAndWhite(CurrentImage);
        break;
    case 3:
        InvertImage(CurrentImage);
        cout << "Image Inverted Successfully\n";
        break;
    case 4:
         AddFrame(CurrentImage);
        break;
    case 5:
        FlipImage(CurrentImage);
        cout << "Image Flipped Successfully\n";
        break;
    case 6:
        RotateImage(CurrentImage);
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
        if (choice != 1 && choice != 2) {
            cout << "Invalid choice for Darken/Lighten!\n";
        break;
        }
        cout << "Enter percentage: ";
        cin >> percentage;
        if(percentage <= 0 || percentage >100){
            cout<< "Invalid Percentage: \n";
            break;
        }

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
            ReSize(CurrentImage);
            cout<<"Image Resized Successfully\n";
        break;
	case 11:
        CropImage(CurrentImage);
        break;
    case 12:
            BlurImage(CurrentImage);
            cout<<"Filter Applied Successfully\n";
        break;
	case 15:
        PurpleNightEffect(CurrentImage);
        break;
    case 16:
            InfraredImage(CurrentImage);
            cout<<"Filter Applied Successfully\n";
        break;
    case 17:
            Skewness(CurrentImage);
            cout<<"Filter Applied Successfully\n";
        break;
    case 18:
            oilPainting(CurrentImage);
            cout<<"Filter Applied Successfully\n";
        break;
    case 19:  //load a new image 
        CurrentImage= LoadImage("Enter the new image name with extension:");
        break;
    case 20: //save current Image 
            {cout<<"Enter a Name to Store a New Image: \n";
            cout<<"And Specify Extention: (.jpg, .bmp, .png, .tga) \n";
            string NewImageName;
            cin>> ws;
            getline(cin,NewImageName);
            CurrentImage.saveImage(NewImageName);
        break;
        }
    case 21: //exit
            IsRunning = false ;
        break;
       
    default:
            cout << "Invalid choice! Please select a number from 1 to 21.\n";
        break;
    }
}
int main() {
    bool IsRunning = true;
    int Choice;
    Image CurrentImage = LoadImage("Please Enter your Image Name: ");
    while (IsRunning) {
        DisplayMenu();
        cin >> Choice;
        ProcessChoice(Choice, CurrentImage, IsRunning);
    }
    return 0;
}
