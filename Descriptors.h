#ifndef DESCRIPTOR_H_INCLUDED
#define DESCRIPTOR_H_INCLUDED
// using namespace std;
#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/nonfree/features2d.hpp> 
// #include "opencv2/features2d/features2d.hpp"
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

// opencv2/xfeatures2d/nonfree.hpp
// #include "nonfree.hpp"

//This class is in charge of computing the descriptors of a list of Images by one of the algorithms (maybe with the SIFT algorithm at first attempt), and also in charge of filtering the keypoints

class Descriptors 
{

public:
	Descriptors(const std::vector<cv::Mat> &disorderedImages);

	void showKeypointsOnImage(int indexImage);
	size_t getSize();// int size;
	const void getDescriptors(std::vector<cv::Mat> &descriptors);
// Descriptor(const cv::Mat &image);
// Descriptor(Descriptor const &autreDescripteur);
// ~Descriptor();
// void setImage(const cv::Mat &image);
// void computeDescriptor();
// cv::Mat* getDescriptor() const;
// std::vector<cv::KeyPoint>* getKeypoints() const;

// cv::Mat process(const cv::Mat &image);
private:

// target color
	// std::vector<cv::Mat> m_disorderedImages;
 // cv::Mat m_image; // vectors of descriptors

	//list of the input images
	std::vector<cv::Mat> m_disorderedImages;
	//and its size
	size_t m_size;
	//with respect to the opencv library, m_keypoints[i] refers to the keypoints of the image i and keypoints[i][j] refer to the keypoint number j of the  image i
	std::vector<std::vector<cv::KeyPoint> > m_keypoints;
	// m_descriptors[i] refer to the descriptors associated with m_keypoints[i] and the row j of m_descriptors[i] is the descriptor associated with keypoints[i][j] 
	std::vector<cv::Mat> m_descriptors;

};
#endif 
