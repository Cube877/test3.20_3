// test3.20_3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include "stdlib.h"

using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("E:\\Picture\\IMG_1989.jpg");
	Mat grayMat;
	Mat srcMat_b;
	Mat dst;
	Mat labels;
	Mat stats;
	Mat centroids;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	cvtColor(srcMat, grayMat, COLOR_BGR2GRAY);
	threshold(grayMat, srcMat_b, 100, 255, THRESH_OTSU);
	int height = srcMat_b.rows; 
	int width = srcMat_b.cols;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			srcMat_b.at<uchar>(j, i) = 255 - srcMat_b.at<uchar>(j, i);
		} 
	}
	erode(srcMat_b, dst, kernel);
	erode(dst, dst, kernel);
	erode(dst, dst, kernel);
	erode(dst, dst, kernel);
	dilate(dst, dst, kernel);
	dilate(dst, dst, kernel);
	dilate(dst, dst, kernel);
	dilate(dst, dst, kernel);
	Mat result = dst.clone();
	int t = connectedComponentsWithStats(dst, labels, stats, centroids);
	int count = t - 1;
	for (int i = 1; i < t; i++)
	{
		Rect bndbox;
		bndbox.x = stats.at<int>(i, 0);
		bndbox.y = stats.at<int>(i, 1);
		bndbox.width = stats.at<int>(i, 2);
		bndbox.height = stats.at<int>(i, 3);
		rectangle(result, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}
	imshow("srcMat", srcMat);
	imshow("dst", dst);
	imshow("result", result);
	cout << "硬币焊点数量：" << count << endl;
	waitKey();
	return 0;
}