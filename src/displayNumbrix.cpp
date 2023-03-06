#include "debugging.h"
#include <iostream>

using namespace std;
using namespace NumbrixGenerator;

extern void Numbrix::displayNumbrix( const CNumbrixGenerator& numbrix )
{
	CGrid& nodeGrid = const_cast<CGrid&>( numbrix.getNodeGrid() );

	const UINT& uiRowsCount = numbrix.getRowsCount();
	const UINT& uiColumnsCount = numbrix.getColumnsCount();

	const Numbrix::CCoordination& firstNodeAddress = numbrix.getPath()[0],
		lastNodeAddress = numbrix.getPath()[ numbrix.getPath().size() -1 ];

	const char* horEdge = "--", *horSpace = "  ";
	const char verEdge = '|', node = 'o', space = ' ', startNode = 'S', endNode = 'E';


	for ( UINT uiRow = 1; uiRow <= uiRowsCount; uiRow++ )
	{

		for ( UINT uiColumn = 1; uiColumn <= uiColumnsCount; uiColumn++ )
		{
			Numbrix::CCoordination currCoord( uiRow, uiColumn );
			cout << ( currCoord == firstNodeAddress ? startNode :  currCoord == lastNodeAddress ? endNode : node );
			CGridNode*& pCurrentNode = nodeGrid.getNode( uiRow, uiColumn );
			cout << ( pCurrentNode->getEdge( RIGHT_EDGE )->isEnabled() ? horEdge : horSpace );
		}
		cout << endl;


		for ( UINT uiColumn = 1; uiColumn <= uiColumnsCount; uiColumn++ )
		{
			CGridNode*& pCurrentNode = nodeGrid.getNode( uiRow, uiColumn );
			cout << ( pCurrentNode->getEdge( DOWN_EDGE )->isEnabled() ? verEdge : space ) << horSpace;
		}
		cout << endl;
	}
}