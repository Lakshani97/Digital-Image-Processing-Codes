//Edge detection - Canny edge detection

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "math.h"
#define PI 3.14159265

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
	Mat image = imread(argv[1], IMREAD_GRAYSCALE);

	if (!image.data) {
		cout << "Could not find the image! " << endl;
		return -1;
	}

	Mat smooth = image.clone();

	int k[5][5] = { {2, 4, 5, 4, 2},
					{4, 9, 12, 9, 4},
					{5, 12, 15, 12, 5},
					{ 4, 9, 12, 9, 4 },
					{ 2, 4, 5, 4, 2 } };

	double val;
	for (int i = 2; i < image.rows - 2; i++) {
		for (int j = 2; j < image.cols - 2; j++) {
			val = 0.0;
			for (int m = -2; m <= 2; m++) {
				for (int n = -2; n <= 2; n++) {
					val = val + double(k[m + 2][n + 2] * image.at<uchar>(i + m, j + n)) / 159;
				}
			}
			smooth.at<uchar>(i, j) = cvRound(val);
		}
	}

	int G, gx, gy, orientation;
	Mat gradient = smooth.clone();
	int** arr = new int* [image.rows];
	for (int i = 0; i < image.rows; i++) {
		arr[i] = new int[image.cols];
	}

	for (int i = 1; i < image.rows - 1; i++) {
		for (int j = 1; j < image.cols - 1; j++) {

			/*gx = -1 * smooth.at<uchar>(i, j) + smooth.at<uchar>(i, j + 1) - smooth.at<uchar>(i + 1, j) + smooth.at<uchar>(i + 1, j + 1);
			gy = smooth.at<uchar>(i, j) + smooth.at<uchar>(i, j + 1) - smooth.at<uchar>(i + 1, j) - smooth.at<uchar>(i + 1, j + 1);*/

			gx = -1 * smooth.at<uchar>(i - 1, j - 1) - 2 * smooth.at<uchar>(i - 1, j) - 1 * smooth.at<uchar>(i - 1, j + 1) + 1 * smooth.at<uchar>(i + 1, j - 1) + 2 * smooth.at<uchar>(i + 1, j) + 1 * smooth.at<uchar>(i + 1, j + 1);
			gy = -1 * smooth.at<uchar>(i - 1, j - 1) - 2 * smooth.at<uchar>(i, j - 1) - 1 * smooth.at<uchar>(i + 1, j - 1) + 1 * smooth.at<uchar>(i - 1, j + 1) + 2 * smooth.at<uchar>(i, j + 1) + 1 * smooth.at<uchar>(i + 1, j + 1);

			G = sqrt(pow(gx, 2) + pow(gx, 2));
			gradient.at<uchar>(i, j) = (uchar)G;

			orientation = abs(atan2(gx, gy) * 180 / PI);
			//cout << orientation << ' ';
			arr[i][j] = orientation;
		}
		//cout << endl;
	}

	int a, b, px;
	Mat tnin_edges = Mat::zeros(Size(gradient.cols, gradient.rows), CV_8UC1);
	for (int i = 1; i < image.rows - 1; i++) {
		for (int j = 1; j < image.cols - 1; j++) {
			a = 255;
			b = 255;

			//if angele is 0 
			if ((arr[i][j] >= 0 && arr[i][j] < 22.5) || (arr[i][j] >= 157.5 && arr[i][j] <= 180)) {
				a = (int)gradient.at<uchar>(i, j + 1);
				b = (int)gradient.at<uchar>(i, j - 1);
			}

			// angle 45
			else if (arr[i][j] >= 22.5 && arr[i][j] < 67.5) {
				a = (int)gradient.at<uchar>(i + 1, j - 1);
				b = (int)gradient.at<uchar>(i - 1, j + 1);
			}

			//angle 90
			else if (arr[i][j] >= 67.5 && arr[i][j] < 112.5) {
				a = (int)gradient.at<uchar>(i + 1, j);
				b = (int)gradient.at<uchar>(i - 1, j);
			}

			//angle 135
			else if (arr[i][j] >= 112.5 && arr[i][j] < 157.5) {
				a = (int)gradient.at<uchar>(i - 1, j - 1);
				b = (int)gradient.at<uchar>(i + 1, j + 1);
			}
			px = (int)gradient.at<uchar>(i, j);
			if ((px >= a) && (px >= b))
				tnin_edges.at<uchar>(i, j) = gradient.at<uchar>(i, j);
			else
				tnin_edges.at<uchar>(i, j) = 0;
		}
	}

	Mat t1 = Mat::zeros(Size(gradient.cols, gradient.rows), CV_8UC1);
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			if (tnin_edges.at<uchar>(i, j) >= 20)
				t1.at<uchar>(i, j) = 255;

			else
				t1.at<uchar>(i, j) = 0;
		}
	}

	Mat t2 = Mat::zeros(Size(gradient.cols, gradient.rows), CV_8UC1);
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			if (tnin_edges.at<uchar>(i, j) >= 40)
				t2.at<uchar>(i, j) = 255;

			else
				t2.at<uchar>(i, j) = 0;
		}
	}


	Mat t1t2 = Mat::zeros(Size(gradient.cols, gradient.rows), CV_8UC1);
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			if (tnin_edges.at<uchar>(i, j) >= 40)
				t1t2.at<uchar>(i, j) = 255;

			else if ((tnin_edges.at<uchar>(i, j) < 40) && (tnin_edges.at<uchar>(i, j) >= 20))
				t1t2.at<uchar>(i, j) = 40;

			else
				t1t2.at<uchar>(i, j) = 0;
		}
	}


	//Linking the edges
	Mat output = Mat::zeros(Size(gradient.cols, gradient.rows), CV_8UC1);
	for (int i = 1; i < image.rows - 1; i++) {
		for (int j = 1; j < image.cols - 1; j++) {
			if ((int)t1t2.at<uchar>(i - 1, j - 1) == 255 || (int)t1t2.at<uchar>(i - 1, j) == 255 || (int)t1t2.at<uchar>(i - 1, j + 1) == 255
				|| (int)t1t2.at<uchar>(i, j - 1) == 255 || (int)t1t2.at<uchar>(i, j + 1) == 255 || (int)t1t2.at<uchar>(i + 1, j - 1) == 255
				|| (int)t1t2.at<uchar>(i + 1, j) == 255 || (int)t1t2.at<uchar>(i + 1, j + 1) == 255)

				output.at<uchar>(i, j) = 255;

			else
				output.at<uchar>(i, j) = 0;
		}
	}



	namedWindow("Image");
	imshow("Image", image);

	namedWindow("Smooth Image");
	imshow("Smooth Image", smooth);

	namedWindow("Gradient Magnitute");
	imshow("Gradient Magnitute", gradient);

	namedWindow("Non - Maxima Suppression");
	imshow("Non - Maxima Suppression", tnin_edges);

	namedWindow("Threshold 1");
	imshow("Threshold 1", t1);

	namedWindow("Threshold 2");
	imshow("Threshold 2", t2);

	namedWindow("Double Threshold");
	imshow("Double Threshold", t1t2);

	namedWindow("Output");
	imshow("Output", output);

	waitKey(0);
	return 0;
}

			
