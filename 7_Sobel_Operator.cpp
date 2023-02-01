//Edge detection - Sobel operator

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {

	Mat image = imread(argv[1], IMREAD_GRAYSCALE);

	if (!image.data) {
		cout << "Could not find the image! " << endl;
		return -1;
	}

	Mat output = image.clone();

	int T = atoi(argv[2]);
	int gx, gy, G;


	//----------------------------Sobel operator----------------------------------------
	for (int i = 1; i < image.rows - 1; i++) {
		for (int j = 1; j < image.cols - 1; j++) {
			gx = -1 * image.at<uchar>(i - 1, j - 1) - 2 * image.at<uchar>(i - 1, j) - 1 * image.at<uchar>(i - 1, j + 1) + 1 * image.at<uchar>(i+1, j+1) + 2 * image.at<uchar>(i + 1, j) + 1 * image.at<uchar>(i + 1, j + 1);
			gy = -1 * image.at<uchar>(i - 1, j - 1) + 1 * image.at<uchar>(i-1, j + 1) - 2 * image.at<uchar>(i , j - 1) + 2 * image.at<uchar>(i, j+1) - 1 * image.at<uchar>(i+1, j - 1) + 1 * image.at<uchar>(i + 1, j + 1);

			G = abs(gx) + abs(gy);

			if (G > T)
				output.at<uchar>(i, j) = 255;
			else
				output.at<uchar>(i, j) = 0;
		}
	}

	namedWindow("Image");
	imshow("Image", image);
	namedWindow("Output Image");
	imshow("Output Image", output);
	waitKey(0);

	return 0;
}

