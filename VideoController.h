#ifndef VIDEOCONTROLLER_H_INCLUDED
#define VIDEOCONTROLLER_H_INCLUDED
// #include "siftMatcher.h"
// #include <deque>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

// the class read the video,produces a vector of images m_disorderedImages,from the video input, 
//and write a video by reading a vector of the images m_orderedImages

class VideoController
{

	public:
		VideoController(const std::string &filenameInput,const std::string &filenameOutput);
		void writeVideo();
		~VideoController();
		void getDisorderedImages(std::vector<cv::Mat> &disordered_images);
		void setOrderedImages(const std::vector<cv::Mat> &ordered_images);
// 		void writeVideo(const std::vector<cv::Mat> &orderedImages);
// // couldn't make a method to write a video for some problem of codec, so created a method that shows the ordered image
// 		// void setOutput();
// 		static std::vector<cv::Mat> castDequeToVector(const std::deque<cv::Mat> theDeque );


	private:
		std::string m_filenameInput;
		std::string m_filenameOutput;
		std::vector<cv::Mat> m_disorderedImages;
		std::vector<cv::Mat> m_orderedImages;
		cv::VideoCapture m_capture;// we need it as an attribute in order to write the video with ordered images with the same properties of the input video with disordered images
		// cv::VideoWriter m_writer;
		// int m_codec;

		// std::deque<int> m_indexOrderedImages; //ordered index images that we wish to construct
		// std::deque<int> m_distances;//equivalent distances of the m_indexOrderedImages

};
#endif




