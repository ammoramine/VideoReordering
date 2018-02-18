#include "Matcher.h"

Matcher::Matcher( Descriptors &descriptors)
{
	descriptors.getDescriptors(m_descriptors);
	descriptors.getKeypoints(m_keypoints);
	// m_descriptor = new Descriptors (descriptor);
	computeDistanceMatrices();
}
// Matcher::~Matcher()
// {
// 	delete m_descriptor;
// }


		// std::vector<cv::Mat> m_descriptors; //a pointer to the descriptors of every frame of the video

		// std::vector<std::vector<cv::KeyPoint> > m_keypoints;
bool Matcher::wayToSortMatches(const cv::DMatch &matche1,const cv::DMatch &matche2) { return matche1.distance< matche2.distance; }
double Matcher::computeDistanceDescriptor(const cv::Mat &Descriptori,const cv::Mat &Descriptorj,const std::vector<cv::KeyPoint> &keypointsi,const std::vector<cv::KeyPoint>& keypointsj)
{
	// cv::FlannBasedMatcher aMatcher=cv::FlannBasedMatcher();
	std::vector<cv::DMatch> matches;
		cv::BFMatcher aMatcher(cv::NORM_L2);
	aMatcher.match(Descriptori,Descriptorj, matches);// Descriptori corresponds to the queryImage and Descriptorj to the trainImage
	double distanceImage=0;
	int numberOfTakenMatches=std::min<int>(matches.size(),60);
	sort(matches.begin(),matches.end(),wayToSortMatches);
	// std::nth_element(matches.begin(),matches.begin()+numberOfTakenMatches,matches.end());
	for (int k=0;k<numberOfTakenMatches;k++)
	{
		cv::DMatch matchesk=matches[k];
		float distanceDescriptor=matchesk.distance;

		int queryIdx=matchesk.queryIdx;
		int trainIdx=matchesk.trainIdx;
		cv::Point2f pti=keypointsi[queryIdx].pt;
		cv::Point2f ptj=keypointsj[trainIdx].pt;
		cv::Point2f keypointDiff=pti-ptj;
		float distanceKeypoint=sqrt(keypointDiff.x*keypointDiff.x+keypointDiff.y*keypointDiff.y);

		distanceImage+=distanceKeypoint*distanceDescriptor;
		// distanceImage+=distanceDescriptor;
	}
	distanceImage/=numberOfTakenMatches;
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
		std::vector<cv::KeyPoint> keypointsi=m_keypoints[i];
				// std::vector<cv::Mat> m_descriptors; //a pointer to the descriptors of every frame of the video

		// std::vector<std::vector<cv::KeyPoint> > m_keypoints;
		for (int j=0;j<i;j++)
		{	
			cv::Mat Descriptorj=m_descriptors[j];
			std::vector<cv::KeyPoint> keypointsj=m_keypoints[j];
			std::cout<<"compute distance between images"<<i<<" and "<<j<<std::endl;
			m_distanceMatrices.at<float>(i,j)=computeDistanceDescriptor(Descriptori,Descriptorj,keypointsi,keypointsj);
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