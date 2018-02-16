#ifndef PARTIALPATH_H_INCLUDED
#define PARTIALPATH_H_INCLUDED
#include <vector>
#include "kruskall.h"
#include <opencv2/imgproc/imgproc.hpp>

class PartialPath
{
	public:
		PartialPath(const std::vector<int> &list,const cv::Mat &matrixDistances);
		void add(int element);// add element to the list at the end of the list
		void remove(int &element); // remove element of the list at its end 
		void remainingList(std::vector<int> &m_remainingList);
		void listOfVerticesForGraphOfRemainingPath(std::vector<int> &verticesOfGraph);
		void remainingGraph();// compute a graph that contains the remaining elements
		void getGraph(Graph &graph);
		double krushkallBound(); //compute the bound associated to the partial path for the branch and bound algorithm using the krushkall algorithm for computing the minimum spanning tree

	private:
		int m_n; //length of the complete path
		cv::Mat m_matrixDistances;
		std::vector<int> m_list;
		Graph m_graph;
		float m_cost;
};

#endif