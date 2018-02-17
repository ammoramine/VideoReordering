#include "PartialPath.h"

PartialPath::PartialPath(const std::vector<int> &list,const cv::Mat &matrixDistance)// the m_list could also be of length 1
{
	m_matrixDistances=matrixDistance;
	cv::Size sizeMatrice=m_matrixDistances.size();
	m_n=sizeMatrice.height;
	if (m_list.size()<m_n)
	{
		m_list=list;
	}
	else
	{
		throw string("the path should be smaller smaller than the size of the matrix by 1");			
	}
	//compute the cost of the partial path
	m_cost=0;
	for (int i=0;i<m_list.size()-1;i++)
	{
		m_cost+=m_matrixDistances.at<float>(m_list[i],m_list[i+1]);
	}
	// m_cost+=m_matrixDistances.at<float>(m_list[m_list.size()-1],list[0]);
}

PartialPath::PartialPath(const PartialPath& partialPath)
{
	m_list=partialPath.m_list;
	m_matrixDistances=partialPath.m_matrixDistances;
	m_n=partialPath.m_n;
	m_cost=partialPath.m_cost;

}
PartialPath::PartialPath(const cv::Mat &matrixDistances)
{
	m_matrixDistances=matrixDistances;
	cv::Size sizeMatrice=m_matrixDistances.size();
	m_n=sizeMatrice.height;
	m_cost=std::numeric_limits<float>::infinity();
}
void PartialPath::PartialPathCopy(const PartialPath& partialPath,PartialPath& newPartialPath)
{
	newPartialPath.m_list=partialPath.m_list;
	newPartialPath.m_matrixDistances=partialPath.m_matrixDistances;
	newPartialPath.m_n=partialPath.m_n;
	newPartialPath.m_cost=partialPath.m_cost;

}

void PartialPath::add(int element)
{
	m_cost+=m_matrixDistances.at<float>(m_list[m_list.size()-1],element);
	m_list.push_back(element);
}
void PartialPath::remove(int &element)
{
	element=m_list[m_list.size()-1];
	if (m_list.size()>1)
	{
		m_cost-=m_matrixDistances.at<float>(m_list[m_list.size()-2],element);
	}
	m_list.pop_back();
}
void PartialPath::remainingList(std::vector<int> &remainingList)
{
	remainingList=std::vector<int>(m_n,0); 
	for (int i=0;i<m_n;i++) remainingList[i]=i;
	for (int j=0;j<m_list.size();j++)
	{
		int valueToErase=m_list[j];
		for (int i=0;i<remainingList.size();i++)
		{
			if(remainingList[i]==valueToErase)
			{
				remainingList.erase(remainingList.begin()+i);
				break;
			}
		}	
	}
}
void PartialPath::listOfVerticesForGraphOfRemainingPath(std::vector<int> &verticesOfGraph)
// firstly we construct the vertices of the remainingGrap, we distinguish two case:
	//if m_list contains more than one vertice in this we consider the list remainingList constructed from the above function, and we add the last and first vertice of the list m_list to constructthe graph.
	// in the other case we don't add any vertice of  m_list
{
	// std::vector<int> verticesOfGraph;
	remainingList(verticesOfGraph);
	if (m_list.size()>1)
	{
		verticesOfGraph.push_back(m_list[0]);
		verticesOfGraph.push_back(m_list[m_list.size()-1]);
	}

}
void PartialPath::remainingGraph(Graph &graph)
// for the construction of the graph, we number the index of the graph from 0 to the size of its vertices, and  we give for each edge (i,j) the cost m_matrixDistances(verticei,verticej)
{
	
	std::vector<int> verticesOfGraph;listOfVerticesForGraphOfRemainingPath(verticesOfGraph);
	int V=verticesOfGraph.size();
	// if (m_list.size() >1)
	// {
	// 	V = m_n-m_list.size()+2; // Number of vertices in graph of the remaining path, 2 comes from the two edgs of the partialPath that should be integrated to compute
	// }
	// else
	// {
	// 	V = m_n-1;
	// }
    int E = (V*V-V)/2; // we consifer a full graph 
    graph = createGraph(verticesOfGraph, E);

    // for (int k=0;k<graph.E;k++)
    // {
    int k=0;
    cv::Mat m_matrixDistancesVerticei;
    	for (int i=0;i<graph.V;i++)
    	{
    		int verticei=verticesOfGraph[i];
    		m_matrixDistancesVerticei=m_matrixDistances.row(verticei);
    		for (int j=0;j<i;j++)
    		{
    			int verticej=verticesOfGraph[j];
    			graph.edge[k].src = i;
    			graph.edge[k].dest = j;
    			graph.edge[k].weight = m_matrixDistancesVerticei.at<float>(verticej);
    			k++;
    		}
    	}

}

// void PartialPath::getGraph(Graph &graph)
// {
// 	graph=graph;
// }
double PartialPath::krushkallBound()
{
	Graph graph;remainingGraph(graph);
	double costGraph=KruskalMST(graph);
	if (m_list.size() > 1)
	{
		return costGraph+m_cost;
	}
	else if (m_list.size() ==1)
	{
		int el=m_list[0];
		cv::Mat m_matrixDistancesEl=m_matrixDistances.col(el);
		double min1=0;
		cv::minMaxIdx(m_matrixDistancesEl,&min1,NULL);
		// m_matrixDistancesEl
		return costGraph+2*min1;// normaly we should use the two smallest values not two times the smaller value
	}
}

double PartialPath::closedCost()
{
	// try
	// {
	if (m_list.size()==m_n-1)
	{
		double value=m_cost+m_matrixDistances.at<float>(m_list[m_list.size()-1],m_list[0]);
		return value;
	}
	else
	{
			std::cout<<"the path is not complete, we can't compute the closed cost"<<std::endl;
			exit(1);
		// throw std::invalid_argument( "the path is not complete, we can't compute the closed cost" );
	}
	// }
	// catch (std::invalid_argument& e)
	// {
	// 	// exit(1);
	// // 	// std::cout<<"the path is not complete, we can't compute the closed cost"<<std::endl;
	// }
}
int PartialPath::getSizePath()
{
	return m_list.size();
}

void PartialPath::initPathByNaiveReordering()
// reorder the index of the frames bo a naive reordering
{
	m_list.clear();

	std::vector<int> listOfRemainingIndexes=std::vector<int>(m_n,0);
	for (int i=0;i<listOfRemainingIndexes.size();i++) listOfRemainingIndexes[i]=i;
	listOfRemainingIndexes.erase(listOfRemainingIndexes.begin());
	
	m_list.push_back(0);//
	
	// std::vector<int> m_path=std::vector<int>(1,0);
	int i=0;//
	int iNext;
	int iNextIndex;
	// listOfRemainingIndexes
	while(listOfRemainingIndexes.size()>1)
	{
		// const float* distanceMatricesi=m_distanceMatrices.ptr<float>(i);
		// int m_matrixDistancesiMin=distanceMatricesi[i];
		float m_matrixDistancesiMin=m_matrixDistances.at<float>(i,i);
		for (int j=0;j<listOfRemainingIndexes.size();j++)
		{
			// float newDistance=distanceMatricesi[listOfRemainingIndexes[j]];
			float newDistance=m_matrixDistances.at<float>(i,listOfRemainingIndexes[j]);
			if(newDistance<m_matrixDistancesiMin)
			{
				iNext=listOfRemainingIndexes[j];
				iNextIndex=j;
				m_matrixDistancesiMin=newDistance;
			}
		}
		listOfRemainingIndexes.erase(listOfRemainingIndexes.begin()+iNextIndex);
		m_list.push_back(iNext);
		i=iNext;
	}
	m_cost=0;
	for (int i=0;i<m_list.size()-1;i++) m_cost+=m_matrixDistances.at<float>(m_list[i],m_list[i+1]);
	// m_cost+=m_matrixDistances.at<float>(m_list[m_list.size()-1],m_list[0]);
}
void PartialPath::getList(std::vector<int> &list)
{
	list=m_list;
}
// void PartialPath::test()
// {

// }