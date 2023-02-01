//Mat Structure
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

	int h = image.rows; //image height
	int w = image.cols; // image width
	int ws = image.step; // image width step
	int ch = image.channels(); // no: of channels

	printf("Height: % d\n", h);
	printf("Width: % d\n", w);
	printf("Width step: % d\n", ws);
	printf("No: of Channels: % d\n", ch);

	//change 100*100 pixel area to black or white
	/*for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			image.at<Vec3b>(i, j)[0] = 0;
			image.at<Vec3b>(i, j)[1] = 0;
			image.at<Vec3b>(i, j)[2] = 0;
		}
	}*/

	//access the pixels in 3 channel color image
	cout<<(image.at<Vec3b>(0, 0))<<endl;

	//also can access pixels channels seperatly
	int b = image.at<Vec3b>(0, 0)[0];
	int g = image.at<Vec3b>(0, 0)[1];
	int r = image.at<Vec3b>(0, 0)[2];

	printf("Blue: %d\n", b);
	printf("Green: %d\n", g);
	printf("Red: %d\n", r);

	//access the pixel in 1 channel image
	//cout<<(image.at<uchar>(0, 0))<<endl;

	//convert to Grayscale image (grayscale mean one channel image)
	Mat image2;
	image2.create(h, w, CV_8UC1);

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			image2.at<uchar>(i, j) = 0.1140 * image.at<Vec3b>(i, j)[0] + 0.5870 * image.at<Vec3b>(i, j)[1] + 0.2489 * image.at<Vec3b>(i, j)[2];
		}
	}
	
	namedWindow("Image"); //image window
	imshow("Image", image); //show image in window

	namedWindow("Gray");
	imshow("Gray", image2);

	waitKey(0);
	return 0;
}

