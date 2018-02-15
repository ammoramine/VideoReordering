#include "Matcher.h"

Matcher::Matcher( Descriptors &descriptors)
{
	descriptors.getDescriptors(m_descriptors);
	// m_descriptor = new Descriptors (descriptor);
	computeDistanceMatrices();
}
// Matcher::~Matcher()
// {
// 	delete m_descriptor;
// }

double Matcher::computeDistanceDescriptor(const cv::Mat &Descriptori,const cv::Mat &Descriptorj)
{
	cv::FlannBasedMatcher aMatcher=cv::FlannBasedMatcher();
	std::vector<cv::DMatch> matches;
	aMatcher.match(Descriptori,Descriptorj, matches);
	double distanceImage=0;
	for (int i=0;i<matches.size();i++)
	{
		distanceImage+=matches[i].distance;
	}
	return distanceImage;
	// add a file storage method to put the matches between two images but in a loop maybe
}

void Matcher::computeDistanceMatrices()
//method to generate the matrix of similarity measures between all the matrices
// in a first attempt, use a full matrix
// we will fill only the upper part without the diagonal
{
	std::cout<<"computing the matrices of distances"<<std::endl;
	size_t numberOfImages=m_descriptors.size();
	// int size=n*(n-1)/2;
	m_distanceMatrices=cv::Mat(numberOfImages,numberOfImages,CV_32FC1,std::numeric_limits<double>::infinity());
	// cv::Ptr<float> m_distanceMatricesi;
	for (int i=0;i<numberOfImages;i++)
	{
		// cv::Ptr<cv::Mat_<CV_32FC1>> m_distanceMatricesi=m_distanceMatrices.ptr<float>(i);
		cv::Mat Descriptori=m_descriptors[i];
		for (int j=0;j<i;j++)
		{	
			std::cout<<"compute distance between images"<<i<<" and "<<j<<std::endl;
			m_distanceMatrices.at<float>(i,j)=computeDistanceDescriptor(Descriptori,m_descriptors[j]);
		}
	}
	// delete m_distanceMatricesi;
	for (int i=0;i<numberOfImages;i++)
	{
		for (int j=i+1;j<numberOfImages;j++)
		{
			m_distanceMatrices.at<float>(i,j)=m_distanceMatrices.at<float>(j,i);
		}
	}
	//store the matrix to avoid the recomputation
	cv::FileStorage myFileStorage("tempDistanceMatrix.txt", cv::FileStorage::WRITE);
	myFileStorage << "distanceMatrix" << m_distanceMatrices;
	// myFileStorage.open( "tempDistanceMatrix", );
}
// double Matcher::
// Matcher::computeMatches()
// {
// 	std::vector<cv::DMatch> matches;
// 	for (int i=0;i<m_descriptor->size();i++)
// 	{
// 		for (int j=0;j<i;j++)
// 		{

// 		}	
// 	}
// }
// Matcher::