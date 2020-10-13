//============================================================================
// Name        : OpenCVFindContours.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<vector>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/types.hpp>
#include<string>
int main(int argc, const char * argv[]) {
	cv::RNG rng(12345);
	std::string windowName = "BasketBall"; //Name of the window
	//cv::Mat image1 = cv::imread("E:/workspace/OpenCv/OpenCVFindContours/src/redBall1.png");
	cv::Mat image = cv::imread("E:/workspace/OpenCv/OpenCVFindContours/src/redball6.png");
	if (image.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		std::cin.get(); //wait for any key press
		return -1;
	}

	cv::Mat threshold;
	cv::Mat hsvimage;
	cv::Mat src;
	cv::Mat dilateoutput;
	//Prepare the image for findContours
	cv::cvtColor(image, hsvimage, CV_BGR2HSV);
	cv::inRange(hsvimage, cv::Scalar(161, 155, 84), cv::Scalar(179, 255, 255), threshold);
	//cv::imshow("InImage", threshold);

	cv::dilate(threshold, dilateoutput, cv::Mat(), cv::Point(-1, -1), 3, 1, 1);
	//cv::imshow("DilatedImage", dilateoutput);

	/****Finding contours start**********/

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours( dilateoutput, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE );


	//	 cv::Mat drawing = cv::Mat::zeros( dilateoutput.size(1,49), cv::CV_8UC3 );
	for( size_t i = 0; i< contours.size(); i++ )
	{
		//cv::Scalar color = cv::Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
		cv::Scalar color = cv::Scalar(0,255,0 );
		cv::drawContours( dilateoutput, contours, (int)i, color, 2, cv::LINE_8, hierarchy, 0 );
	}
	//cv::imshow("DilatedImage", dilateoutput);
	/**********Finding contour ends***************/

	 std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
	    std::vector<cv::Rect> boundRect( contours.size() );
	    std::vector<cv::Point2f>centers( contours.size() );
	    std::vector<float>radius( contours.size() );

	    cv::Scalar color = cv::Scalar( rng.uniform(0, 0), rng.uniform(0,255), rng.uniform(0,0) );
	    for( size_t i = 0; i < contours.size(); i++ )
	    {
	        approxPolyDP( contours[i], contours_poly[i], 3, true );
	        boundRect[i] = boundingRect( contours_poly[i] );
	        minEnclosingCircle( contours_poly[i], centers[i], radius[i] );

	        //std::cout<<"x coordinate of the centre-->"<<centers[i].x<<"   y coordinate is-->  "<<centers[i].y<<"   radius is-->  "<<(int)radius[i]<<std::endl;
	    	if((int)radius[i] > 12 && (int)radius[i] < 15 && centers[i].y < 580)
	    	{
	        cv::circle( image, centers[i], (int)radius[i], color, 2 );
	        std::cout<<"x coordinate of the centre-->"<<centers[i].x<<"   y coordinate is-->  "<<centers[i].y<<"   radius is-->  "<<(int)radius[i]<<std::endl;
	    	}
	    }

	    cv::imshow("FinalOutput", image);






	cv::waitKey(0);
	cv::destroyWindow(windowName); //destroy the created window





	return 0;
}
