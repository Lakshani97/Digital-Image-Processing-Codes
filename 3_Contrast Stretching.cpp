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

	//convert color image to gray
	Mat gray(image.rows, image.cols, CV_8UC1, Scalar(0));
	cvtColor(image, gray, COLOR_BGR2GRAY);

	//create new image for place the output image
	Mat ContrastImg = gray.clone(); //get the copy of the gray image

	//contrast streching
	//int out;
	//for (int i = 0; i < gray.rows; i++) {  // access to rows pixel
	//	for (int j = 0; j < gray.cols; j++) { // access to columns pixel
	//		int x = int(gray.at<uchar>(i, j));  //get the pixel values

	//		if (0 <= x && x <= 103) {
	//			out = int((5 / 103)* x);
	//		}
	//		else if (x > 103 && x <= 234) {
	//			out = int((245 / 131) * (x - 103) + 5);
	//		}
	//		else if (x > 234 && x <= 255) {
	//			out = int((5 / 21) * (x - 234) + 250);
	//		}

	//		// convert integer value to uchar and assign to output pixel
	//		ContrastImg.at<uchar>(i, j) = uchar(out);
	//	}
	//}


	// contrast streching, get a and b values as user input
	int a = atoi(argv[2]); // get command line value for a (3rd argument)
	int	b = atoi(argv[3]); // get command line value for b (4th argument)
	int out;
	for (int i = 0; i < gray.rows; i++) {  // access to rows pixel
		for (int j = 0; j < gray.cols; j++) { // access to columns pixel
			int x = int(gray.at<uchar>(i, j));  //get the pixel values

			if (0 <= x && x <= a) {
				out = int((5 / 103) * x);
			}
			else if (x > a && x <= b) {
				out = int((250 - 5) / (b - a) * (x - a) + 5);
			}
			else if (x > b && x <= 255) {
				out = int((255 - 250)/(255 - b) * (x - b) + 250);
			}

			// convert integer value to uchar and assign to output pixel
			ContrastImg.at<uchar>(i, j) = uchar(out);
		}
	}

	namedWindow("Image"); //image window
	imshow("Image", image); //show image in window

	namedWindow("Gray");
	imshow("Gray", gray);

	namedWindow("Contrast Image");
	imshow("Contrast Image", ContrastImg);

	waitKey(0);
	return 0;
}
