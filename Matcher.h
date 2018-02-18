#ifndef MATCHER_H_INCLUDED
#define MATCHER_H_INCLUDED
#include "Descriptors.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/nonfree/features2d.hpp> 
#include <opencv2/xfeatures2d.hpp>

#include "opencv2/features2d/features2d.hpp"

// This class take two images as inputs and compute the distance between the two images

class Matcher
{
	public:
		Matcher( Descriptors &descriptor);
		// ~Matcher();
		// double computeDistanceDescriptor(const cv::Mat &Descriptori,const cv::Mat &Descriptorj);
		static bool wayToSortMatches(const cv::DMatch &matche1,const cv::DMatch &matche2);
		double computeDistanceDescriptor(const cv::Mat &Descriptori,const cv::Mat &Descriptorj,const std::vector<cv::KeyPoint> &keypointsi,const std::vector<cv::KeyPoint>& keypointsj);
		void computeDistanceMatrices();

		// SiftMatcher(const cv::Mat &image1,const cv::Mat &image2);// this constructor compute the descriptors and the matchs
		// SiftMatcher(const cv::Mat &image1,const cv::Mat &image2,const Descriptor &feature1,const Descriptor &feature2);
		// ~SiftMatcher();
		// void computeDescriptor(); //function that compute the feature of image that comprise the descriptor (the keypoints and their corresponding descriptor vector)
		// void computeMatches();// function that computes the vector of matches
		// void computeDistance(); //fonction qui calcule la distance entre deux images
		// double getDistance(); //une fonction séparé pour retourner la distance car l'on aura besoin de relire la distance pus d'une fois
		// void reduceMatches();
		// void drawMatches() const;
		// void changeImage1(const cv::Mat &image1);
		// void changeImage2(const cv::Mat &image2);
		// static void testSiftMatcher(const std::vector<cv::Mat> &disorderedImages,int i1,int i2) ;
		// static double computeNormCvMat(const cv::Mat &image1,const cv::Mat &image2);
		// static double computeDistanceMatches(const std::vector<cv::DMatch> &matches);
	private:
		std::vector<cv::Mat> m_descriptors; //a pointer to the descriptors of every frame of the video
		std::vector<std::vector<cv::KeyPoint> > m_keypoints;

		cv::Mat m_distanceMatrices;
		// std::vector<cv::DMatch> descripto
		// cv::Mat m_image1;
		// cv::Mat m_image2;
		// double m_distance;
		// Descriptor *m_feature1;
		// Descriptor *m_feature2;
		// std::vector<cv::DMatch> *m_matches;

};

#endif