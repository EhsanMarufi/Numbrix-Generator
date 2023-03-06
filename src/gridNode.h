// Grid nodes are the building blocks of the Connection grid.

#pragma once
#ifndef GRIDNODE_H
#define GRIDNODE_H

#include "GridNodeEdge.h"
#include "typedefs.h"
#include <vector>

namespace NumbrixGenerator
{

	class CGridNode
	{
	public:
		CGridNode();
		~CGridNode();

		inline CGridNodeEdge* getEdge( const UINT& uiIndex ) { return m_arrEdges[ uiIndex ]; }
		UINT getAvailableEgdesCount() const;
		CGridNodeEdge* getAvailableEdge( const UINT& uiIndex );
		std::vector<CGridNodeEdge*> getAvailableEdges();

		// temp
		inline const UINT& getLabel() const { return m_uiTempLabel; }
		inline void setLabel( const UINT& uiLabel ) { m_uiTempLabel = uiLabel; }

	protected:
		CGridNodeEdge* m_arrEdges[4];
		UINT m_uiTempLabel;
	}; // end of class 'CGridNode'
} // end of namespace 'NumbrixGenerator'

#endif // GRIDNODE_H