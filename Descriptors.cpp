#include "Descriptors.h"

Descriptors::Descriptors(const std::vector<cv::Mat> &disorderedImages)
{
	cv::Ptr<cv::xfeatures2d::SIFT> sift=cv::xfeatures2d::SIFT::create(2500);
	// sift>detectAndCompute();
	// m_disorderedImages=disorderedImages;
	m_size=m_disorderedImages.size();
	// std::vector<cv::Mat> masks(disorderedImages.size(),cv::Mat::ones(4,4,CV_32FC1));
	// std::vector<cv::Mat> masks(disorderedImages.size(),cv::noArray());

	m_keypoints.resize(disorderedImages.size());
	m_descriptors.resize(disorderedImages.size());

	for (int i=0;i<disorderedImages.size();i++)
	{
		std::cout<<"sift applied to image"<<i<<std::endl;
		sift->detectAndCompute(disorderedImages[i],cv::noArray(),m_keypoints[i],m_descriptors[i]);
	}
	// for (int i=0;i<disorderedImages.size();i++)
	// {
	// 	showKeypointsOnImage(i);
	// 	cv::waitKey(0);
	// }
	// sift->detectAndCompute(disorderedImages,cv::noArray(),m_keypoints,m_descriptors);
// 	virtual void detect(
// cv::InputArrayOfArrays images, // Images on which to detect
// vector<vector< cv::KeyPoint > >& keypoints, // keypoints for each image
// cv::InputArrayOfArrays masks = cv::noArray ()
// ) const;
}

void Descriptors::showKeypointsOnImage(int indexImage)
{
	cv::Mat imageWhereToDrawKeyPointsOfImagei;
	drawKeypoints(m_disorderedImages[indexImage],m_keypoints[indexImage],imageWhereToDrawKeyPointsOfImagei);
	cv::namedWindow( "Example3", cv::WINDOW_AUTOSIZE );
	cv::imshow( "Example3",imageWhereToDrawKeyPointsOfImagei);
}
const void Descriptors::getDescriptors(std::vector<cv::Mat> &descriptors)
{
	descriptors= m_descriptors;
	// descriptors.resize(descriptors.size());
	// for (int i=0;m_descriptors.size();i++) m_descriptors.push_back(descriptors[i]);//descriptors[i]=m_descriptors[i];
	// return m_descriptors;
}
const void Descriptors::getKeypoints(std::vector<std::vector<cv::KeyPoint> > &keypoints)
{
	keypoints= m_keypoints;
	// descriptors.resize(descriptors.size());
	// for (int i=0;m_descriptors.size();i++) m_descriptors.push_back(descriptors[i]);//descriptors[i]=m_descriptors[i];
	// return m_descriptors;
}
size_t Descriptors::getSize()
{
	return m_size;
}
// Descriptor::showImageWithKeyPoint(int indexImage i)
// {
	
// }