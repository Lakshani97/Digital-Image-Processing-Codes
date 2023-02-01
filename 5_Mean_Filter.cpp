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

	Mat meanImg = image.clone();
	int k = atoi(argv[2]);
	int adj = k / 2;

//-----------------------------MEAN FILTERING----------------------------

	int sum;
	double avg;

	for (int i = adj; i < image.rows - adj; i++) {
		for (int j = adj; j < image.cols - adj; j++) {
			sum = 0;
			for (int g = i - adj; g <= i + adj; g++) {
				for (int h = j - adj; h <= j + adj; h++) {
					sum = sum + (int)image.at<uchar>(g, h);
				}
			}
			avg = sum / (k * k);
			meanImg.at<uchar>(i, j) = (uchar)avg;
		}
	}

	namedWindow("Image");
	imshow("Image", image);
	namedWindow("Mean Filter");
	imshow("Mean Filter", meanImg);
	waitKey(0);

	return 0;
}

			
