#include "BranchAndBound.h"

std::string BranchAndBound::m_filePath="path_history.txt";
int BranchAndBound::m_number=0;

BranchAndBound::BranchAndBound(const cv::Mat &matrixOfDistances,std::vector<int> &list)
{
	PartialPath currentPath=PartialPath(std::vector<int>(1,0),matrixOfDistances);
	currentPath.initPathWithNoOrdering();
	// currentPath.initPathByNaiveReordering();
	CompletePath goldenPath=PartialPath(currentPath);
	int excludedNode;currentPath.remove(excludedNode);
	BranchAndBound(matrixOfDistances,currentPath,goldenPath,excludedNode);
	// goldenPath.getList(list);
	// goldenPath.printPath();
}
BranchAndBound::BranchAndBound(const cv::Mat &matrixOfDistances,const PartialPath &currentPath,CompletePath &goldenPath,int excludedNode)
{
	// printNodeInformationsOnFile(currentPath);
	// m_currentPath=PartialPath(currentPath);
	// PartialPath::PartialPathCopy(currentPath,m_currentPath);
	PartialPath m_currentPath=PartialPath(currentPath);
	if (m_currentPath.getSizePath()==0)
	{
		return;
	}
	std::vector<int> remainingList;
	m_currentPath.remainingList(remainingList);

	// remove the excluded Node
	for (int i=0;i<remainingList.size();i++)
	{
		if (remainingList[i]==excludedNode)
		{
			remainingList.erase(remainingList.begin()+i);
			break;
		}
	}

	for (int k=0;k<remainingList.size();k++)
	{
		// PartialPath::PartialPathCopy(m_currentPath,currentPathPlusNodeRemainingListk);
		// PartialPath currentPathPlusNodeRemainingListk=PartialPath(m_currentPath);
		// currentPathPlusNodeRemainingListk.add(remainingList[k]);
		m_currentPath.add(remainingList[k]);
		// std::cout<<m_currentPath.getSizePath()<<std::endl;
		// m_currentPath.printPath();
		double value=m_currentPath.krushkallBound();
		if (value<goldenPath.getTheCost())
		{
			// m_currentPath.printPath();
			BranchAndBound(matrixOfDistances,m_currentPath,goldenPath,-1);
		}
		int anElement;m_currentPath.remove(anElement); // get Back to the initial form before the next iteration of the loop
	}
	int AnOtherExcludedNode;m_currentPath.remove(AnOtherExcludedNode);
	BranchAndBound(matrixOfDistances,m_currentPath,goldenPath,AnOtherExcludedNode);
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