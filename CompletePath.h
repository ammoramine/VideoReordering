#ifndef COMPLETEPATH_H_INCLUDED
#define COMPLETEPATH_H_INCLUDED

#include "PartialPath.h"

class CompletePath : public PartialPath
{
	public:
		CompletePath(const PartialPath & partialPath);
		static void CompletePathCopy(const CompletePath & completePath1, CompletePath & completePath2);
		int searchForLackingElement();
		double getTheCost();
		void CompareAndCopy(const PartialPath &partialPath);
		// Compare(PartialPath &partialPath);
};
#endif 