#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include<string>
//using namespace cv;
//using namespace std;
int main( )
{
	std:: string filename;
	int thresh = 100;
	cv::namedWindow( "Display window", CV_WINDOW_AUTOSIZE );
	// cv::imshow( "Display window", image );
	std::string windowName = "BasketBall";

	cv::Mat src_hsv;
	cv::Mat dilateoutput;
	cv::Mat threshold;

	cv::Mat image = cv::imread("E:/workspace/OpenCv/OpenCVFindContours/src/redball6.png");
	cv::cvtColor( image, src_hsv,CV_BGR2HSV );

	//cv::blur( src_gray, src_gray, cv::Size(3,3) );
	//cv::Canny( src_gray, canny_output, thresh, thresh*2 );



	//cv::inRange(src_hsv, cv::Scalar(161, 155, 84), cv::Scalar(179, 255, 255), threshold);---black
	cv::Mat image_blurred_with_3x3_kernel;
	cv::inRange(src_hsv, cv::Scalar(0, 0, 200, 0), cv::Scalar(180, 255, 255, 0), threshold);//white
//	cv::inRange(src_hsv, cv::Scalar(161, 155, 84), cv::Scalar(179, 255, 255), threshold);//---black
	cv::GaussianBlur(threshold, image_blurred_with_3x3_kernel, cv::Size(5,5), 0);
	//cv::dilate(threshold, dilateoutput, cv::Mat(), cv::Point(-1, -1), 3, 1, 1);
	cv::imshow( "Mask window", image_blurred_with_3x3_kernel );
	/// Find contours
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::RNG rng(12345);
	//cv::Scalar color1 = cv::Scalar(0,255,0 );
	cv::findContours( image_blurred_with_3x3_kernel, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, cv::Point(0, 0) );
	for( size_t i = 0; i< contours.size(); i++ )
		{
			//cv::Scalar color = cv::Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
			cv::Scalar color = cv::Scalar(0,255,0 );
			cv::drawContours( dilateoutput, contours, (int)i, color, 2, cv::LINE_8, hierarchy, 0 );
		}

	//Drawing ellipse

	std::vector<cv::RotatedRect> minEllipse( contours.size() );
	for( size_t i = 0; i < contours.size(); i++ )
	{
		// minRect[i] = minAreaRect( contours[i] );
		if( contours[i].size() > 5 )
		{
			minEllipse[i] = fitEllipse( contours[i] );
		}
	}

	for( size_t i = 0; i< contours.size(); i++ )
	{
		cv::Scalar color = cv::Scalar( rng.uniform(0, 0), rng.uniform(0,255), rng.uniform(0,0) );
		// contour
	//	cv::drawContours( image, contours, (int)i, color );
		// ellipse
	//	if(int(minEllipse[i].center.y) > 580 && int(minEllipse[i].center.x) > 500 && int(minEllipse[i].center.x) < 700)
		if(int(minEllipse[i].center.y) > 580)
		{
			std::cout<<" X coordinate is----> "<<int(minEllipse[i].center.x)<<std::endl;
			std::cout<<" Y coordinate is----> "<<int(minEllipse[i].center.y)<<std::endl;
			cv::ellipse( image, minEllipse[i], color, 2 );
		}


	}
	/// Draw contours


	cv::imshow( "Result window", image );
	cv::waitKey(0);
	return 0;
}
