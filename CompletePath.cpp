#include "CompletePath.h"

CompletePath::CompletePath(const PartialPath & partialPath) :PartialPath(partialPath)
{
	// m_list=partialPath.m_list;
	// m_matrixDistances=partialPath.m_matrixDistances;
	// m_n=partialPath.m_n;
	// m_cost=partialPath.m_cost;
	// this->add()
	int lackingElement=searchForLackingElement();// we look for the last element to add to have the complete tour
	add(lackingElement);//we added  the last element
	m_cost+=m_matrixDistances.at<float>(m_list[m_list.size()-1],m_list[0]);//then we add the cost of the edge thtat links to the first element
}

void CompletePath::CompletePathCopy(const CompletePath & completePath1, CompletePath & completePath2)
{
	completePath2.m_list=completePath1.m_list;
	completePath2.m_matrixDistances=completePath1.m_matrixDistances;
	completePath2.m_n=completePath1.m_n;
	completePath2.m_cost=completePath1.m_cost;
}
double CompletePath::getTheCost()
{
	return m_cost;
}

int CompletePath::searchForLackingElement()
{
	int lackingElement;
	if (m_list.size()!=m_n-1)
	{
		std::cout<<"the list should have m_n-1 element"<<std::endl;
		exit(-1);
	}
	else
	{
		std::vector<int> completeList=std::vector<int>(m_n,0);for (int i=0;i<m_n;i++) completeList[i]=i;
		for (int i=0;i<m_n;i++) 
		{
			int element=m_list[i];
			for (int j=0;j<completeList.size();j++)
			{
				if (element==completeList[j])
				{
					completeList.erase(completeList.begin()+j);
					break;
				}
			}
		}
		return completeList[0];
	}
}