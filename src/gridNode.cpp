#include "gridNode.h"
#include "safe.h"
#include <vector>

using namespace NumbrixGenerator;

CGridNode::CGridNode()
	: m_uiTempLabel( 0 )
{
	m_arrEdges[0] = new CGridNodeEdge( this, LEFT_EDGE );
	m_arrEdges[1] = new CGridNodeEdge( this, UP_EDGE );
	m_arrEdges[2] = new CGridNodeEdge( this, RIGHT_EDGE );
	m_arrEdges[3] = new CGridNodeEdge( this, DOWN_EDGE );
}

CGridNode::~CGridNode()
{
	for( int i = 0; i < 4; i++ )
		SAFE_DELETE( m_arrEdges[i] );
}


UINT CGridNode::getAvailableEgdesCount() const
{
	UINT uiCount = 0;
	for( UINT uiIndex = 0; uiIndex < 4; uiIndex++ )
	{
		if ( m_arrEdges[uiIndex]->isEnabled() )
			uiCount++;
	}

	return uiCount;
}


CGridNodeEdge* CGridNode::getAvailableEdge( const UINT& uiIndex )
{
	std::vector<CGridNodeEdge*> arrAvailableEdges;
	for ( UINT i = 0; i < 4; i++ )
		if (  m_arrEdges[i]->isEnabled() )
			arrAvailableEdges.push_back( m_arrEdges[i] );

	if ( uiIndex > arrAvailableEdges.size() )
		return 0;
	else
		return arrAvailableEdges[uiIndex];
}


std::vector<CGridNodeEdge*> CGridNode::getAvailableEdges()
{
	std::vector<CGridNodeEdge*> lstAllAvailableEdges;
	for ( UINT i = 0; i < 4; i++ )
		if (  m_arrEdges[i]->isEnabled() )
			lstAllAvailableEdges.push_back( m_arrEdges[i] );
	return lstAllAvailableEdges;
}