// this algorithm is an attempt to reconstruct the video by using the similarity between the various images from "matrixOfDistances" and the branch and bound algorithm by using the krushkall bound 
#ifndef BRANCHANDBOUND_H_INCLUDED
#define BRANCHANDBOUND_H_INCLUDED
#include "kruskall.h"
#include "PartialPath.h"
#include "CompletePath.h"
#include <string>
class BranchAndBound
{
	public:
		BranchAndBound(const cv::Mat &matrixOfDistances,const PartialPath &currentPath,CompletePath &goldenPath,int excludedNode);
		BranchAndBound(const cv::Mat &matrixOfDistances,std::vector<int> &list);
		void initPath();
		void printNodeInformationsOnFile(const PartialPath &currentPath);
		// void initPath();
	private:
		// cv::Mat m_matrixOfDistances;
		// PartialPath* m_currentPathAdress=0;
		// std::vector<int> m_goldenPath;
		static std::string m_filePath;
		static int m_number;
		int m_firstNode;
};
#endif