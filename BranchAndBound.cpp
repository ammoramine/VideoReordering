#include "BranchAndBound.h"

std::string BranchAndBound::m_filePath="path_history.txt";
// std::string BranchAndBound::m_currentNodeOfTree;
int BranchAndBound::m_number=0;

BranchAndBound::BranchAndBound(const cv::Mat &matrixOfDistances,std::vector<int> &list)
{
	PartialPath currentPath=PartialPath(std::vector<int>(1,0),matrixOfDistances);
	// currentPath.initPathWithNoOrdering();
	currentPath.initPathByNaiveReordering();
	CompletePath goldenPath=PartialPath(currentPath);
	int excludedNode;currentPath.remove(excludedNode);
	bool onlyDeeperNodes=false;// we begin by a completePath at the beginning
	BranchAndBound(matrixOfDistances,currentPath,goldenPath,excludedNode,onlyDeeperNodes);
	goldenPath.getList(list);
	goldenPath.printPath();
}
BranchAndBound::BranchAndBound(const cv::Mat &matrixOfDistances, PartialPath &m_currentPath,CompletePath &goldenPath,int excludedNode,bool onlyDeeperNodes)
// For recursivity's purpose and a good use of memory, we will integrate two modes,
// in the first mode: onlyDeeperNodes=false
// we explore all the  nodes that are below the final node of current Path, aside the excludedNode, and then we remove the last node of m_currentPath  (that we name lastNode) to  apply again the Branch and bound algorithm on the reduced m_currentPath aside the node lastNode, and by using the last update of goldenPath
//in the second Mode, we don't apply again the BranchAnd bound algorithm again, i.e that we explore only the nodes that could complete m_currentPath
{
	if (onlyDeeperNodes==false)
	{
		std::cout<<"\n current level of tree exploration : "<<m_currentPath.getSizePath()<<std::endl;
	}
	if (m_currentPath.getSizePath()==0)
	{
		return;
	}
	// printNodeInformationsOnFile(currentPath);
	// m_currentPath=PartialPath(currentPath);
	// PartialPath::PartialPathCopy(currentPath,m_currentPath);
	// PartialPath m_currentPath=PartialPath(currentPath);
	

	// we have two cases: the current Path is of size m_n-1, in this case we just compute the complete cost and compare it with the cost of the last best path, ->
	if  (m_currentPath.isTourWellDefined())//mm_currentPath.getSizePath()==m_currentPath.m_n-1)
	{
		CompletePath theCompleteAssociatedPath=CompletePath(m_currentPath);
		if (theCompleteAssociatedPath.getTheCost()<goldenPath.getTheCost())
		{
			CompletePath::CompletePathCopy(theCompleteAssociatedPath,goldenPath);
		}
	}
	
	else
		//-> otherwise we test the krushkall bound for all the node aside the excludedNode then if the test is valid we explore the node by applying the branch and bound algorithm
	{
	std::vector<int> searchList;
	searchListConstruct(m_currentPath, searchList, excludedNode); 

	for (int k=0;k<searchList.size();k++)
	{
		// PartialPath::PartialPathCopy(m_currentPath,currentPathPlusNodesearchListk);
		// PartialPath currentPathPlusNodesearchListk=PartialPath(m_currentPath);
		// currentPathPlusNodesearchListk.add(searchList[k]);
		m_currentPath.add(searchList[k]);
		// std::cout<<m_currentPath.getSizePath()<<std::endl;
		// m_currentPath.printPath();
		double value=m_currentPath.krushkallBound();
		if (value<goldenPath.getTheCost())
		{
			// m_currentPath.printPath();
			BranchAndBound(matrixOfDistances,m_currentPath,goldenPath,-1,true);
		}
		int anElement;m_currentPath.remove(anElement); // get Back to the initial form before the next iteration of the loop
	}
	}

	
	if (onlyDeeperNodes==false)
	{
		int AnOtherExcludedNode;m_currentPath.remove(AnOtherExcludedNode);
		// once we explored all the node and updated the goldenpath (the name given for the current best path), we go up on the tree of if possible,
	
		BranchAndBound(matrixOfDistances,m_currentPath,goldenPath,AnOtherExcludedNode,false);
		m_currentPath.add(AnOtherExcludedNode);// this step is very important Because we want to conceive the BranchAndBound Algorithm in order to don't change its value
	}
	return;
}

// void BranchAndBound::initPath(const cv::Mat &matrixOfDistances,const PartialPath &currentPath,PartialPath &goldenPath,int excludedNode)
// {
// 	// if (goldenPath.getSizePath()==0)
// 	// {
// 		m_currentPath.initPathByNaiveReordering();
// 		PartialPath::PartialPathCopy(m_currentPath,goldenPath);
// 		int AnExcludedNode;m_currentPath.remove(AnExcludedNode);
// 		BranchAndBound(matrixOfDistances,m_currentPath,goldenPath,AnExcludedNode);
// 		// return;
// 	// }

// }


void BranchAndBound::searchListConstruct(const PartialPath &m_currentPath, std::vector<int> &searchList,int excludedNode)
// construct the list of node to explore after the last node of the current Path, aside the excluded node
{
	m_currentPath.remainingList(searchList);

	// remove the excluded Node
	for (int i=0;i<searchList.size();i++)
	{
		if (searchList[i]==excludedNode)
		{
			searchList.erase(searchList.begin()+i);
			break;
		}
	}

}







void BranchAndBound::printNodeInformationsOnFile(const PartialPath &currentPath)
{
	// cv::FileStorage myFileStorage(m_filePath, cv::FileStorage::WRITE);
	std::vector<int> ListOfNode;currentPath.getList(ListOfNode);
	std::cout<<"\n"<<"Branch and bound called for the "<< std::to_string(m_number)<<"time"<<std::endl;
	for (int i=0;i<ListOfNode.size();i++)
	{
		std::cout<<" "<<ListOfNode[i];
	}
	// std::cout<<"\n"<<std::endl;
	m_number+=1;
	// myFileStorage.release();
}