#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

Mat drawHistogram(int* histogram) {

	//create window to draw histogram
	int histogram_height = 400;
	int histogram_width = 512;
	Mat histogramImage(histogram_height, histogram_width, CV_8UC1, Scalar(255, 255, 255));

	//find the maximum no: of pixel from histogram array
	int max = histogram[0]; //initialize the max as first histogram value
	for (int i = 1; i < 256; i++) {
		if (max < histogram[i])
			max = histogram[i];
	}

	// Normalize the histogram array values between 0 and histogram window height
	for (int i = 0; i < 256; i++) { // read the 1 by 1 0-255 pixel values
		histogram[i] = ((double)histogram[i] / max) * histogram_height;
		//cout << histogram[i] << endl;
	}

	// Draw the lines in histogram window
	int bin_w = cvRound((double)histogram_width / 256); // width of the line

	for (int i = 0; i < 256; i++) {
		line(histogramImage, Point(bin_w * (i), histogram_height), Point(bin_w * (i), histogram_height - histogram[i]), Scalar(0, 0, 0), 1, 8, 0);
	}

	return histogramImage;
}

int main(int argc, char* argv[]) {
	//load image
	Mat image = imread(argv[1]);

	//Mat image = imread(argv[1], IMREAD_GRAYSCALE); //Directly load the gray image

	if (!image.data) {
		cout << "Couldn't find the image!" << endl;
		return -1;
	}

	//convert color image to gray
	Mat gray(image.rows, image.cols, CV_8UC1, Scalar(0));
	cvtColor(image, gray, COLOR_BGR2GRAY);

	//Declare an array to allocate memory for all the intensity values
	int histogram[256];
	double prob[256]; // initialize probability array
	double cumProb[256]; // initialize cumalative probability array
	int sCumProb[256]; // initialize scale cumalative probability array
	int equalizedHist[256]; // define array for equalized histogram value

	//Initialize "0" to all array element
	for (int i = 0; i < 256; i++) {
		histogram[i] = 0;
		prob[i] = 0.0;
		cumProb[i] = 0.0;
		sCumProb[i] = 0;
		equalizedHist[i] = 0;
	}

	// count one by one pixels of gray image for each intensity value
	for (int y = 0; y < gray.rows; y++) { // this for loop for row - height
		for (int x = 0; x < gray.cols; x++) { // this for loop for colum - width 
			//int pix_in = (int)gray.at<uchar>(y, x);  //get the each pixel (read pixels) - number of pixel
			//int cnt = histogram[(int)gray.at<uchar>(y, x)]; // currently how many number of pixels for each intensity value
			//histogram[(int)gray.at<uchar>(y, x)] = cnt + 1; // that value increment by 1 and assign to relevant intensity of the histogram array
			histogram[(int)gray.at<uchar>(y, x)]++;
		}
	}

	/*for (int i = 0; i < 256; i++)
		cout << i << ": " << histogram[i] << endl;*/

	//calculate total number of pixel
	int N = gray.rows * gray.cols;
	printf("Total Number of pixels: %d\n", N);

	//Calculate the probability of each intensity
	for (int i = 0; i < 256; i++) {
		prob[i] = (double)histogram[i] / N;
	}

	//Generate cumalative probability
	cumProb[0] = prob[0];
	for (int i = 1; i < 256; i++) {
		cumProb[i] = cumProb[i - 1] + prob[i];
	}

	/*for (int i = 0; i < 256; i++)
		cout << i << ": " << cumProb[i] << endl;*/

	//Scale cumalative probability
	for (int i = 0; i < 256; i++) {
		sCumProb[i] = round(cumProb[i] * 255); //round the result (this is intensity value)
	}

	/*for (int i = 0; i < 256; i++)
		cout << i << ": " << sCumProb[i] << endl;*/

	//Generate the equalized image
	Mat output = gray.clone();
	int z = 0;
	for (int y = 0; y < gray.rows; y++) {
		for (int x = 0; x < gray.cols; x++) {
			z = sCumProb[(int)gray.at<uchar>(y, x)]; // find the pixel value of gray image (this is also intensity value)
			output.at<uchar>(y, x) = (uchar)z;
		}
	}

	//draw the histogram for original image
	Mat histogramImage = drawHistogram(histogram);

	//count no: of pixel for each intensity value in equalized image
	for (int y = 0; y < output.rows; y++) { 
		for (int x = 0; x < output.cols; x++) {  
			/*int pix_in = (int)output.at<uchar>(y, x);  
			int cnt = equalizedHist[(int)output.at<uchar>(y, x)]; 
			equalizedHist[(int)output.at<uchar>(y, x)] = cnt + 1;*/
			equalizedHist[(int)output.at<uchar>(y, x)]++;
		}
	}

	for (int i = 0; i < 256; i++)
		cout << i << ": " << equalizedHist[i] << endl;

	//draw the histogram for histogram equalized image
	Mat equalizedHistImage = drawHistogram(equalizedHist);


	/*namedWindow("Image"); //image window
	imshow("Image", image); //show image in window */

	namedWindow("Gray");
	imshow("Gray", gray);

	namedWindow("Output"); 
	imshow("Output", output);

	namedWindow("Histogram");
	imshow("Histogram", histogramImage);

	namedWindow("Equalized Histogram");
	imshow("Equalized Histogram", equalizedHistImage);

	waitKey(0);
	return 0;
}

			
