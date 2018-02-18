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
		// cv::Mat distanceMatrix;OrderVideo::readMatrix("tempDistanceMatrix.txt",distanceMatrix);

	// std::vector<int> goldenList;BranchAndBound(m_distanceMatrices,goldenList);

	// m_path=goldenList;
	naiveReordering();

	// for (int i=0;i<m_path.size();i++)
	// {
	// 	m_path[i]=goldenList[i];
	// 	// std::cout<<m_path[i]<<std::endl;
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

// void OrderVideo::orderImages_exhaustiveResearch_WithPriorComputedCost()
// {
// 	// std::vector<std::vector<double> > cost;
// 	// computeSiftBasedCostForAllImages_Optimised(cost);
// 	std::vector<int> indexDisorderedImagesRemaining=std::vector<int>(m_numberOfVideos,0);
// 	for (int i=0;i<indexDisorderedImagesRemaining->size();i++) indexDisorderedImagesRemaining[i]=i;
// 	m_path.clear
// 	// std::vector<int> indexOrderedImages;
// 	// m_path.clear();
// 	// int totalFrames=m_disorderedImages->size();
// 	// for (int i=0;i<m_disorderedImages->size();i++) indexDisorderedImagesRemaining.push_back(i);

// 	int currentIndex=0;// the currentIndex refers here to the element of rank (currentIndex+1) of the vector, we begin with the first image and look at the image that may be the closest
// 	while(indexOrderedImages.size()<totalFrames)
// 	{
// 		double distance=std::numeric_limits<double>::infinity();

// 		/// we add the currentIndex in the vector indexOrderedImages and we remove it from the vector indexDisorderedImagesRemaining
// 		indexOrderedImages.push_back(currentIndex);


// 		int indexOfCurrentIndex=0;
// 	    for (int i=0;i<indexDisorderedImagesRemaining.size();i++)
// 	    {
// 	       if(indexDisorderedImagesRemaining[i]==currentIndex)
// 	       {
// 	       	indexOfCurrentIndex=i;
// 	       }	
// 	    }
// 	    indexDisorderedImagesRemaining.erase(indexDisorderedImagesRemaining.begin()+indexOfCurrentIndex);

		
// 	int nextIndex=0; // the nextIndex that will take the value of currentIndex
// 	for (int j=0;j<indexDisorderedImagesRemaining.size();j++)
// 	{
// 		if (cost[currentIndex][indexDisorderedImagesRemaining[j]]<distance) // !!
// 		{
// 			distance=cost[currentIndex][indexDisorderedImagesRemaining[j]];
// 			nextIndex=indexDisorderedImagesRemaining[j];
// 		}
// 	}
// 	currentIndex=nextIndex;
// 	}

// 	if (indexOrderedImages.size()==totalFrames)
// 	{
// 		std::cout<<"allTheImages reordered"<<std::endl;
// 	}
// 	for (int i=0;i<indexOrderedImages.size();i++)
// 	{
// 		(*m_disorderedImages)[indexOrderedImages[i]].copyTo((*m_orderedImages)[i]);
// 	}
// 	for (int i=0;i<indexOrderedImages.size();i++)
// 	{
// 		std::cout<< indexOrderedImages[i]<<std::endl;
// 	}
// }
// }
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