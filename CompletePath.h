#ifndef COMPLETEPATH_H_INCLUDED
#define COMPLETEPATH_H_INCLUDED

#include "PartialPath.h"

class CompletePath : public PartialPath
{
	public:
		CompletePath(const PartialPath & partialPath);
		int searchForLackingElement();
		double getTheCost();
};
#endif COMPLETEPATH_H_INCLUDED