#ifndef PARTIALPATH_H_INCLUDED
#define PARTIALPATH_H_INCLUDED
#include <vector>
#include "kruskall.h"
#include "stdlib.h"
#include <opencv2/imgproc/imgproc.hpp>
// We use this class to represent a partial path of the "traveling salesman" problem

class PartialPath
{
	public:
		PartialPath(const std::vector<int> &list,const cv::Mat &matrixDistances);
		PartialPath(const PartialPath& partialPath);
		void add(int element);// add element to the list at the end of the list
		void remove(int &element); // remove element of the list at its end 
		void remainingList(std::vector<int> &m_remainingList);
		void listOfVerticesForGraphOfRemainingPath(std::vector<int> &verticesOfGraph);
		void remainingGraph(Graph &graph);// compute a graph that contains the remaining elements
		// void getGraph(Graph &graph);
		double krushkallBound(); //compute the bound associated to the partial path for the branch and bound algorithm using the krushkall algorithm for computing the minimum spanning tree
		double closedCost();
		int getSizePath();
		void initPathByNaiveReordering();
	private:
		int m_n; //length of the complete path equal to the height and width of m_matrixDistances
		// int m_closingVertex;
		cv::Mat m_matrixDistances;
		std::vector<int> m_list;
		// Graph m_graph;
		float m_cost;
};

#endif


// here, we should highlight an important detail for the modelisation of this class
// the matrixDistances could be of a size equal to the number of images on the videos, in this case : we have two cases
// if m_list.size() is strictly below m_matrixDistances.size()-1, (i.e the path is incomplete), the cost is equal to the sum of the concatenation of the vertexes of m_list(), otherwise we should add to this last term the value that links the end to the begining of the path (i.e informally m_matrixDistances.at<>(m_list(end),m_list(begin))

//the matrixDistances could be of a size  smaller than the number of images on the videos, it represents the situation for which, we have an initial formed path, and we want to extend it to sweep all the remaining vertices. In this case we should add the first vertex of the formed Path (m_closingVertex)in order to complete the computation of the cost

//we have (again) two cases:
// if m_list.size() is strictly below m_matrixDistances.size()-1 (i.e the path is incomplete), the cost is as in the previous case (i.e the cost is equal to the sum of the concatenation of the vertexes of m_list() ), otherwise we should add to the term the value that links the end of the list() to m_closingVertex (i.e informally m_matrixDistances.at<>(m_list(end),m_closingVertex )
