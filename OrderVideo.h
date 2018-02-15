// #include ""
#ifndef ORDERVIDEO_H_INCLUDED
#define ORDERVIDEO_H_INCLUDED
#include <deque>
#include <opencv2/core/core.hpp>
#include <iostream>


// this class get a matrix containing the set of similarities between each set of two images, and give the ordering to use
class OrderVideo
{
	public:
		OrderVideo(const cv::Mat &distanceMatrices);
		OrderVideo(const std::string &filename);
		void naiveReordering();
		void getOrderedVideo(const std::vector<cv::Mat> &disordoredVideos, std::vector<cv::Mat> &orderedVideos);
	private:
		cv::Mat m_distanceMatrices;
		int m_numberOfVideos;
		std::vector<int> m_path;

};

#endif