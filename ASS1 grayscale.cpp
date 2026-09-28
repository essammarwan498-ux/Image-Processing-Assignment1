#include<iostream>
#include"Image_Class.h"
#include <string>
using namespace std;

Image grayscale(){
    Image myImg;
    cout<<"enter image name with extension"<<endl;
    cout<<"allowed extensions are : .jpg , .bmp , , .png , .tga"<<endl;
    string imageName;
    cin>>imageName;
    myImg.loadNewImage(imageName);

    for (int j = 0; j < myImg.height; j++)
    {
        for (int i = 0; i < myImg.width; i++)
        {
          
            unsigned char red   = myImg(i, j, 0);
            unsigned char green = myImg(i, j, 1);
            unsigned char blue  = myImg(i, j, 2);
            int avg=(red+green+blue)/3;
            myImg(i, j, 0) = myImg(i, j, 1) = myImg(i, j, 2) = avg;
        
        }
    }
    cout << "enter output image name with extension to save: " << endl;
    string outputName;
    cin >> outputName;
    myImg.saveImage(outputName);
    
    return myImg;
}
int main(){
    grayscale();
    return 0;
}
