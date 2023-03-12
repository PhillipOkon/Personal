//Ascii art converter
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

string density = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\" ^ `\'. "; //Ascii Variant for replacing text 

// Driver code
int main(int argc, char** argv)
{
    Mat image = imread(/*Example image here*/); //Reads in image

    // Error Handling
    if (image.empty()) {
        cout << "Image File " << "Not Found" << endl;
        return -1;
    }

    //Rescales Images and Blurs it making pixels easier to replace

    auto width = image.rows;
    auto height = image.cols;
    auto w = image.rows / 20;
    auto h = image.cols / 20;
    
    Scalar color = (0, 0, 0);

    resize(image, image, Size(20, 20), width, height, INTER_LANCZOS4);
    namedWindow("ASCII Image", WINDOW_FREERATIO);

    // Greyscales the images and puts text over each pixel
    for (int j = 0; j < image.cols; j++) {
        for (int i = 0; i < image.rows; i++) {
            auto b = image.at<Vec3b>(i, j)[0];
            auto g = image.at<Vec3b>(i, j)[1];
            auto r = image.at<Vec3b>(i, j)[2];
            auto grey = (0.21 * r) + (0.72 * g) + (0.07 * b);
            
            int len = density.length();
            auto charIndex = round((len -1)* grey /255);
            char c = density.at(charIndex);
            string text(1, c);
            
            putText(image, text, Point(i, j), FONT_HERSHEY_SIMPLEX, 1 , color, 1);
        }
    }
    
    //Shows the image
    imshow("ASCII Image", image);

    waitKey (0);
    return 0;
}