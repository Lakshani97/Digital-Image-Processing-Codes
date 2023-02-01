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

	Mat medianImg = image.clone();
	int k = atoi(argv[2]);
	int adj = k / 2;

//---------------------------------------MEDIAN FILTERING------------------------------------

	int index;
  int middle;
	int size = k * k;
	int* arr = new int[size];

	for (int i = adj; i < image.rows - adj; i++) {
		for (int j = adj; j < image.cols - adj; j++) {
			index = 0;
			for (int g = i - adj; g <= i + adj; g++) {
				for (int h = j - adj; h <= j + adj; h++) {
					arr[index] = (int)image.at<uchar>(g, h);
					index++;
			}
			}

			insertionSort(arr, size);
			middle = size / 2;
			medianImg.at<uchar>(i, j) = (uchar)arr[middle];
		}
	}




	namedWindow("Image");
	imshow("Image", image);
	namedWindow("Median Filter");
	imshow("Median Filter", medianImg);
	waitKey(0);

	return 0;
}

			
