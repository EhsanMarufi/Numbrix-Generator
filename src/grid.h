#pragma once
#ifndef GRID_H
#define GRID_H

#include "gridNode.h"

namespace NumbrixGenerator
{
	class CGrid
	{
	public:
		CGrid( const UINT& uiRowsCount = 6, const UINT& uiColumnsCount = 6 );
		~CGrid();


		inline CGridNode*& getNode( const UINT& uiRow, const UINT& uiColumn )
		{
			return m_arrNodes[ m_uiColumnsCount * ( uiRow -1 ) + ( uiColumn -1 ) ];
		}

		// Determines whether or not the current graph is connected.
		bool isConnected();

		// inline getters and setters
		inline const UINT& getRowsCount() const { return m_uiRowsCount; }
		inline const UINT& getColumnsCount() const { return m_uiColumnsCount; }

	protected:
		UINT m_uiRowsCount, m_uiColumnsCount;
		CGridNode** m_arrNodes;

	}; // end of class 'CGrid'
} // end of namespace 'NumbrixGenerator'

#endif // GRID_H