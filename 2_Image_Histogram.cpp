#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
	
	Mat image = imread(argv[1]); //load image

	if (!image.data) {
		cout << "Couldn't find the image!" << endl;
		return -1;
	}

	//----------------------convert color image to gray---------------------
	Mat gray(image.rows, image.cols, CV_8UC1, Scalar(0));
	cvtColor(image, gray, COLOR_BGR2GRAY);

	//----------------Declare an array to allocate memory for all the intensity values----------------
	int histogram[256];

	//-----------------Initialize "0" to all array element---------------
	for (int i = 0; i < 256; i++) {
		histogram[i] = 0;
	}
	
	// ---------------------count one by one pixels of gray image---------------------------
	for (int y = 0; y < image.rows; y++) { // this for loop for row - height
		for (int x = 0; x < image.cols; x++) { // this for loop for colum - width 
			int pix_in = (int)gray.at<uchar>(y, x);  //get the each pixel (read pixels) - number of pixel
			int cnt = histogram[(int)gray.at<uchar>(y, x)]; // currently how many number of pixels for each intensity value
			histogram[(int)gray.at<uchar>(y, x)] = cnt + 1; // that value increment by 1 and assign to relevant intensity of the histogram array
		}
	} 

	//-----------------------Print number of pixel for each intensity-------------------
	for (int i = 0; i < 256; i++)
		cout << i << ": " << histogram[i] << endl;

	//-------------------create window to draw histogram--------------------------
	int histogram_height = 400;
	int histogram_width = 512;
	Mat histogramImage(histogram_height, histogram_width, CV_8UC1, Scalar(255,255,255));

	//-----------------find the maximum no: of pixel from histogram array------------------------
	int max = histogram[0]; //initialize the max as first histogram value
	for (int i = 1; i < 256; i++) {
		if (max < histogram[i])
			max = histogram[i];
	}

	// --------------------Normalize the histogram array values between 0 and histogram window height--------------------
	for (int i = 0; i < 256; i++) { // read the 1 by 1 0-255 pixel values
		histogram[i] = ((double)histogram[i] / max) * histogram_height;
		cout << histogram[i] << endl; 
	}

	// -----------------------Draw the lines in histogram window----------------------
	int bin_w = cvRound((double)histogram_width / 256); // width of the line

	for (int i = 0; i < 256; i++) {
		line(histogramImage, Point(bin_w * (i), histogram_height), Point(bin_w * (i), histogram_height - histogram[i]), Scalar(0, 0, 0), 1, 8, 0);
	}

	namedWindow("Image"); //image window
	imshow("Image", image); //show image in window

	namedWindow("Gray");
	imshow("Gray", gray);

	namedWindow("Histogram");
	imshow("Histogram", histogramImage);

	waitKey(0);
	return 0;
}

