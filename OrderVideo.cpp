#include "OrderVideo.h"


OrderVideo::OrderVideo(const cv::Mat &distanceMatrices)
{
	// for (int i=0;i<distanceMatrices.size();i++)
	// {
	// 	m_distanceMatrices[i]=distanceMatrices[i];
	// }
	m_distanceMatrices=distanceMatrices;
	cv::Size sizeMatrice=distanceMatrices.size();
	m_numberOfVideos=sizeMatrice.height;
}
OrderVideo::OrderVideo(const std::string &filename)
{
	cv::FileStorage myFileStorage(filename, cv::FileStorage::READ);
	myFileStorage["distanceMatrix"] >> m_distanceMatrices;
	// std::cout<<m_distanceMatrices.at<float>(0,1)<<std::endl;
	// m_distanceMatrices=distanceMatrices;
	cv::Size sizeMatrice=m_distanceMatrices.size();
	m_numberOfVideos=sizeMatrice.height;

	std::cout<<"ordering the video"<<std::endl;
	naiveReordering();
	// for (int i=0;i<m_path.size();i++)
	// {
	// 	std::cout<<m_path[i]<<std::endl;
	// }
}

void OrderVideo::readMatrix(const std::string &filename,cv::Mat &distanceMatrices)
{
	cv::FileStorage myFileStorage(filename, cv::FileStorage::READ);
	myFileStorage["distanceMatrix"] >> distanceMatrices;
}
void OrderVideo::naiveReordering()
// reorder the index of the frames bo a naive reordering
{
	std::vector<int> listOfRemainingIndexes=std::vector<int>(m_numberOfVideos,0);
	for (int i=0;i<listOfRemainingIndexes.size();i++) listOfRemainingIndexes[i]=i;

	listOfRemainingIndexes.erase(listOfRemainingIndexes.begin());
	m_path.push_back(0);//
	
	// std::vector<int> m_path=std::vector<int>(1,0);
	int i=0;//
	int iNext;
	int iNextIndex;
	// listOfRemainingIndexes
	while(listOfRemainingIndexes.size()>1)
	{
		// const float* distanceMatricesi=m_distanceMatrices.ptr<float>(i);
		// int minDistancei=distanceMatricesi[i];
		float minDistancei=m_distanceMatrices.at<float>(i,i);
		for (int j=0;j<listOfRemainingIndexes.size();j++)
		{
			// float newDistance=distanceMatricesi[listOfRemainingIndexes[j]];
			float newDistance=m_distanceMatrices.at<float>(i,listOfRemainingIndexes[j]);
			if(newDistance<minDistancei)
			{
				iNext=listOfRemainingIndexes[j];
				iNextIndex=j;
				minDistancei=newDistance;
			}
		}
		listOfRemainingIndexes.erase(listOfRemainingIndexes.begin()+iNextIndex);
		m_path.push_back(iNext);
		i=iNext;
	}
}
void OrderVideo::getOrderedVideo(const std::vector<cv::Mat> &disordoredImages, std::vector<cv::Mat> &orderedImages)
// order the Images using the calculated m_path !  we should have disordoredImages.size()=m_path.size !!
{
	// if (m_path.size()!= disordoredImages.size())
	// {

	// }
	// CV_Assert(m_path.size()!= disordoredImages.size());
	// orderedImages.resize(disordoredImages.size());
	// orderedImages=disordoredImages;
	for (int i=0;i<disordoredImages.size();i++)
	{
		orderedImages.push_back(disordoredImages[m_path[i]].clone());
	}
}