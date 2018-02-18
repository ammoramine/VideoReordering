#include "VideoController.h"
#include "Descriptors.h"
#include "Matcher.h"
#include "OrderVideo.h"
#include "kruskall.h"
#include "partialPath.h"
#include "BranchAndBound.h"


int main (int argc, char* argv[])
{
	// bool testBranchAndBound=true;
	bool testBranchAndBound=false;
	if(testBranchAndBound)
	{

	// cv::Mat distanceMatrix;OrderVideo::readMatrix("tempDistanceMatrix.txt",distanceMatrix);
	// std::vector<int> goldenList;BranchAndBound(distanceMatrix,goldenList);

	// int initList[] = {0,1,2,7,10,3};
	// std::vector<int> aList(initList,initList+sizeof(initList)/sizeof(int));
	// PartialPath currentPath=PartialPath(aList,distanceMatrix);
	// std::cout<<currentPath.krushkallBound()<<std::endl;



	cv::Mat distanceMatrix=cv::Mat(5,5,CV_32FC1);
	distanceMatrix.at<float>(0,1)=3;
	distanceMatrix.at<float>(0,2)=2;
	distanceMatrix.at<float>(0,3)=5;
	distanceMatrix.at<float>(0,4)=3;
	distanceMatrix.at<float>(1,2)=3;
	distanceMatrix.at<float>(1,3)=2;
	distanceMatrix.at<float>(1,4)=6;
	distanceMatrix.at<float>(2,3)=3;
	distanceMatrix.at<float>(2,4)=3;
	distanceMatrix.at<float>(3,4)=4;
	for (int i=0;i<5;i++) distanceMatrix.at<float>(i,i)=std::numeric_limits<float>::infinity();
	
	for (int i=0;i<5;i++)
	{
		cv::Mat distanceMatrixiRow=distanceMatrix.row(i);
		cv::Mat distanceMatrixiCol=distanceMatrix.col(i);
		for (int j=0;j<i;j++)
		{
			distanceMatrixiRow.at<float>(j)=distanceMatrixiCol.at<float>(j);
		}
	}
	std::vector<int> goldenList;BranchAndBound(distanceMatrix,goldenList);


	// 	int n=5;
	// cv::Mat distanceMatrix=cv::Mat(n,n,CV_32FC1,cv::Scalar(0));
	// cv::randu(distanceMatrix,1,10);
	// for (int i=0;i<n;i++) distanceMatrix.at<float>(i,i)=std::numeric_limits<float>::infinity();
	// for (int i=0;i<n;i++)
	// {
	// 	cv::Mat distanceMatrixiRow=distanceMatrix.row(i);
	// 	cv::Mat distanceMatrixiCol=distanceMatrix.col(i);
	// 	for (int j=0;j<i;j++)
	// 	{
	// 		distanceMatrixiRow.at<float>(j)=distanceMatrixiCol.at<float>(j);
	// 	}
	// }
	// cv::FileStorage myFileStorage("RandomdistanceMatrix.txt", cv::FileStorage::WRITE);
	// myFileStorage<<"matrix" << distanceMatrix;
	// distanceMatrix
	// std::vector<int> goldenList;BranchAndBound(distanceMatrix,goldenList);
	// std::cout<<"elements of the list"<<std::endl;
	// for (int i=0;i<goldenList.size();i++)
	// {
	// 	std::cout<<goldenList[i]<<std::endl;
	// }
	// std::cout<<"the cost is : "<<m_cost<<std::endl;
	// cv::Size sizeMatrice=distanceMatrix.size();
	// std::vector<int> list=std::vector<int>(sizeMatrice.height-1);

	// for (int i=0;i<list.size();i++) list[i]=i;	
	
	// PartialPath partialPath=PartialPath(list,distanceMatrix);
	// PartialPath anotherPartialPath=PartialPath(partialPath);
	// std::cout<<partialPath.closedCost()<<std::endl;
	// int element;
	// partialPath.remove(element);
	// // std::cout<<partialPath.closedCost()<<std::endl;
	// partialPath.remove(element);
	// partialPath.remove(element);
	// partialPath.add(element);
	// std::vector<int> remainingList;
	// partialPath.remainingList(remainingList);

	// partialPath.initPathByNaiveReordering();
	// std::cout<<partialPath.closedCost()<<std::endl;
	// std::vector<int> aList;partialPath.getList(aList);
	// std::vector<int> vertivesOfGraph;
	// partialPath.listOfVerticesForGraphOfRemainingPath(vertivesOfGraph);
	// int a=partialPath.getSizePath();
	// Graph graph;partialPath.remainingGraph(graph);
	// std::cout<<KruskalMST(&graph)<<std::endl;

	return 0;
	}
	// bool dirtyTest=true;
	bool dirtyTest=false;
	if (!dirtyTest)
	{
	// if (true)
	// {
	VideoController videoController=VideoController("corrupted_video.mp4","corrupted_video_ordered.mp4");
	std::vector<cv::Mat> disorderedImages;
	videoController.getDisorderedImages(disorderedImages);


	//the if statements are artifices used due to memory issues on my computer
	if (true)
	{
	Descriptors descriptors=Descriptors(disorderedImages);
	Matcher matcher=Matcher(descriptors);
	}
	// matcher.~Matcher();
	// descriptors.~Descriptors();

	if (true)
	{
	std::vector<cv::Mat> orderedImages;
	OrderVideo orderVideo=OrderVideo("tempDistanceMatrix.txt");
	orderVideo.getOrderedVideo(disorderedImages,orderedImages);
	videoController.setOrderedImages(orderedImages);
	videoController.writeVideo();
	}
	}
	else
	{

		// for (int i=0;i<-1;i++)
	// {
	// 	std::cout<<"test : "<<i<<std::endl;
	// }
	// return 0;

	    /* Let us create following weighted graph

         10

     0--------1

     | \      |

    6|   \5   |15

     |      \ |

     2--------3-----4

     4           1 */

    int V = 5; // Number of vertices in graph

    int E = 10; // Number of edges in graph

    std::vector<int> vertexes=std::vector<int>(V,0);for (int i=0;i<V;i++) vertexes[i]=i;
    Graph graph = createGraph(vertexes, E);

 

    // add edge 0-1

    graph.edge[0].src = 0;
    graph.edge[0].dest = 1;
    graph.edge[0].weight = 3;

    // add edge 0-2

    graph.edge[1].src = 0;
    graph.edge[1].dest = 2;
    graph.edge[1].weight = 2;

 

    // add edge 0-3

    graph.edge[2].src = 0;
    graph.edge[2].dest = 3;
    graph.edge[2].weight = 5;

    // add edge 0-4

    graph.edge[3].src = 0;
    graph.edge[3].dest = 4;
    graph.edge[3].weight = 3; 

    // add edge 1-2

    graph.edge[4].src = 1;
    graph.edge[4].dest = 2;
    graph.edge[4].weight =3;

     // add edge 1-3

    graph.edge[5].src = 1;
    graph.edge[5].dest = 3;
    graph.edge[5].weight =2;

      // add edge 1-4

    graph.edge[6].src = 1;
    graph.edge[6].dest = 4;
    graph.edge[6].weight =6;

      // add edge 2-3

    graph.edge[7].src = 2;
    graph.edge[7].dest = 3;
    graph.edge[7].weight =3;

      // add edge 2-4

    graph.edge[8].src = 2;
    graph.edge[8].dest = 4;
    graph.edge[8].weight =3;

      // add edge 3-4

    graph.edge[9].src = 3;
    graph.edge[9].dest = 4;
    graph.edge[9].weight =4;

    double cost=KruskalMST(graph);
    std::cout<<"the cost is : "<< cost<<std::endl;
}

	// std::vector<int> path;
	// orderVideo.naiveReordering();
	
	// double a=1;
	// VideoController videoController=VideoController("corrupted_video.mp4","corrupted_video_ordered.mp4");
	// std::vector<cv::Mat> disorderedImages;
	// videoController.getDisorderedImages(disorderedImages);



	
	// videoController.writeVideo();
	// std::vector<cv::Mat> disorderedImages=videoController.getDisorderedImages();
	// VideoProcessor videoProcessor=VideoProcessor(*disorderedImages);
	// videoProcessor.orderImages_exhaustiveResearch_WithPriorComputedCost();
	// std::deque<cv::Mat> orderedImages=videoProcessor.getOrderedImages();
	// videoController.writeVideo(std::vector<cv::Mat>(orderedImages.begin(),orderedImages.end()));
	//read options
	// std::string filename="corrupted_video_copie.avi";
	// cv::VideoCapture cap(filename);
	// std::vector<cv::Mat> disorderedImages;
	// ideoProcessor(const std::vector<cv::Mat> &disorderedImages)
// 	cv::VideoCapture cap;
// cap.open( string(argv[1]) );
// cv::Mat frame;
// for(;;) {
// cap >> frame;
// if( frame.empty() ) break; // Ran out of film
// cv::imshow( "Example3", frame );
// if( cv::waitKey(33) >= 0 ) break;
// }
	return 0;
}
