#include "BranchAndBound.h"


// void initPath()
// {

// 	m_currentPath=std::vector<int>()
// }

// BranchAndBound::BranchAndBound(const cv::Mat &matrixOfDistances)
// {
// 	PartialPath currentPath=PartialPath(std::vector(1,0),matrixOfDistances);
// 	// PartialPath goldenPath=
// 	BranchAndBound(matrixOfDistances)
// }
BranchAndBound::BranchAndBound(const cv::Mat &matrixOfDistances,const PartialPath &currentPath,PartialPath &goldenPath,int excludedNode)
{
	// m_currentPath=PartialPath(currentPath);
	// PartialPath::PartialPathCopy(currentPath,m_currentPath);
	PartialPath m_currentPath=PartialPath(currentPath);
	if (m_currentPath.getSizePath()==0)
	{
		return;
	}
	if (goldenPath.getSizePath()==0)
	{
		m_currentPath.initPathByNaiveReordering();
		PartialPath::PartialPathCopy(m_currentPath,goldenPath);
		int AnExcludedNode;m_currentPath.remove(AnExcludedNode);
		BranchAndBound(matrixOfDistances,m_currentPath,goldenPath,AnExcludedNode);
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
		PartialPath currentPathPlusNodeRemainingListk=PartialPath(m_currentPath);
		currentPathPlusNodeRemainingListk.add(remainingList[k]);
		double value=currentPathPlusNodeRemainingListk.krushkallBound();
		if (value<goldenPath.closedCost())
		{
			BranchAndBound(matrixOfDistances,currentPathPlusNodeRemainingListk,goldenPath,excludedNode);
		} 
	}
	int AnOtherExcludedNode;m_currentPath.remove(AnOtherExcludedNode);
	BranchAndBound(matrixOfDistances,m_currentPath,goldenPath,excludedNode);
}