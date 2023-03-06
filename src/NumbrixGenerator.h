// In the name of God
// Numbrix v1.0
// Ehsan Marufi Azar, 2013

#pragma once
#ifndef NUMBRIXGENERATOR_H
#define NUMBRIXGENERATOR_H

#include <vector>
#include <stdlib.h>

#include "Coordination.inl"
#include "grid.h"
#include "gridNode.h"


namespace NumbrixGenerator
{
	class CNumbrixGenerator
	{
	public:
		CNumbrixGenerator( const UINT& uiRowsCount = 6, const UINT& uiColumnsCount = 6 );
		~CNumbrixGenerator() {}

		// For debugging purposes
		inline const CGrid& getNodeGrid() const { return m_NodeGrid; }
		inline const std::vector<Numbrix::CCoordination>& getPath() const { return m_vecPath; }

		// inline getters and setters
		inline const UINT& getRowsCount() const { return m_NodeGrid.getRowsCount(); }
		inline const UINT& getColumnsCount() const { return m_NodeGrid.getColumnsCount(); }

	protected:
		void generateRandomPath();
		std::vector<Numbrix::CCoordination> m_vecPath;
		CGrid m_NodeGrid;

		inline UINT random( const UINT& uiMax, const UINT& uiMin = 1 )	{ return rand() % (uiMax - uiMin +1) + uiMin; }
	}; // end of class 'CNumbrixGenerator'
} // end of namespace 'Numbrix'

#endif // NUMBRIXGENERATOR_H