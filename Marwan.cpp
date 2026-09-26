#include <iostream>
#include "Image_Class.h"
using namespace std ;

string LoadImage(string Message){
    cout<< Message<<endl;
    string ImageFileName = "";
    cin>>ws;                           //3lshan el white space 
    getline(cin,ImageFileName);
    Image Img(ImageFileName);

    return ImageFileName;
}
int main(){
    cout<<LoadImage("Please enter");
    return 0;
}