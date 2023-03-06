#include "grid.h"
#include "safe.h"

#include <stack>
#include <vector>

using namespace NumbrixGenerator;

CGrid::CGrid( const UINT& uiRowsCount, const UINT& uiColumnsCount )
	: m_uiRowsCount( uiRowsCount ), m_uiColumnsCount( uiColumnsCount )
{
	m_arrNodes = 0;
	m_arrNodes = new (CGridNode*[ m_uiRowsCount * m_uiColumnsCount ]);

	// creating the nodes and temporarily label them for debugging purposes.
	UINT uiLabel = 1;
	for ( UINT uiRow = 1; uiRow <= m_uiRowsCount; uiRow++ )
	{
		for ( UINT uiColumn = 1; uiColumn <= m_uiColumnsCount; uiColumn++ )
		{
			CGridNode*& pCurrentNode	= getNode( uiRow, uiColumn );
			pCurrentNode = new CGridNode();

			pCurrentNode->setLabel( uiLabel++ );
		}
	}

	// connecting edges..
	// o--o--o--o     As you can see in this 3x4 grid, the most of the connecting job
	// |  |  |        could've been done through a simple nested loop, but the right and
	// o--o--o--o     down borders (last column and last row) doesn't have appropriate
	// |  |  |        connections, their connection job is done through two other loops
	// o  o  o  o     that follows..
	//
	for ( UINT uiRow = 1; uiRow < m_uiRowsCount; uiRow++ )
		for ( UINT uiColumn = 1; uiColumn < m_uiColumnsCount; uiColumn++ )
		{
			CGridNode*& pCurrentNode	= getNode( uiRow, uiColumn );
			CGridNode*& pRightNode		= getNode( uiRow, uiColumn + 1 );
			CGridNode*& pDownNode		= getNode( uiRow + 1, uiColumn );
			
			pCurrentNode->getEdge( RIGHT_EDGE )->connect( pRightNode->getEdge( LEFT_EDGE ) );
			pCurrentNode->getEdge( DOWN_EDGE )->connect ( pDownNode->getEdge ( UP_EDGE ) );
		}

	// right column's connection job
	for ( UINT uiRow = 1; uiRow < m_uiRowsCount; uiRow++ )
	{
		CGridNode* pCurrentNode	= getNode( uiRow, m_uiColumnsCount );
		CGridNode* pDownNode	= getNode( uiRow + 1, m_uiColumnsCount );

		pCurrentNode->getEdge( DOWN_EDGE )->connect ( pDownNode->getEdge ( UP_EDGE ) );
	}

	// bottom row's connection job
	for ( UINT uiColumn = 1; uiColumn < m_uiColumnsCount; uiColumn++ )
	{
		CGridNode* pCurrentNode	= getNode( m_uiRowsCount, uiColumn );
		CGridNode* pRightNode	= getNode( m_uiRowsCount, uiColumn + 1 );

		pCurrentNode->getEdge( RIGHT_EDGE )->connect( pRightNode->getEdge( LEFT_EDGE ) );
	}
}


bool CGrid::isConnected()
{
	class CNodeMetState
	{
	public:
		CNodeMetState( const UINT& uiRowsCount, const UINT& uiColumnsCount )
			: m_cuiRowsCount( uiRowsCount ), m_cuiColumnsCount( uiColumnsCount )
		{
			// create a grid of bool for every node, that when the program traverses over them
			// they become true.
			const UINT uiNodesCount = m_cuiRowsCount * m_cuiColumnsCount;
			m_arrNodesMet = new bool[ uiNodesCount ];

			// Initializing the array members to 'false', (No nodes has been traversed yet!)
			for ( UINT i = 0; i < uiNodesCount; i++ )
				m_arrNodesMet[i] = false;
		}

		~CNodeMetState()
		{
			SAFE_DELETE_ARRAY( m_arrNodesMet );
		}


		inline bool& getState( const UINT& uiRow, const UINT& uiColumn )
		{
			return m_arrNodesMet[ (uiRow -1 ) * m_cuiColumnsCount + ( uiColumn -1 ) ];
		}

		inline bool& getState( const UINT& cuiNodeLabel )
		{
			const UINT cuiColumn = cuiNodeLabel % m_cuiColumnsCount;
			const UINT cuiRow = ( cuiNodeLabel - cuiColumn ) / m_cuiColumnsCount + 1;
			return getState( cuiRow, cuiColumn );
		}

		inline UINT getMetNodesCount() const
		{
			UINT uiCount = 0;

			const UINT cuiNodesCount = m_cuiRowsCount * m_cuiColumnsCount;
			for ( UINT i = 0; i < cuiNodesCount; i++ )
				if ( m_arrNodesMet[i] )
					uiCount++;

			return uiCount;
		}

	private:
		const UINT m_cuiRowsCount, m_cuiColumnsCount;
		bool* m_arrNodesMet;

	} nodeMetState( m_uiRowsCount, m_uiColumnsCount );


	// create a stack of evey node's label and node's pointer to traverse the graph
	struct CTraverseData
	{
		typedef std::stack<EdgeLabel> EdgeLabelStack;

		CTraverseData( const std::vector<CGridNodeEdge*>& lstEdges, CGridNode*& pNode )
		{
			EdgeLabelStack labelsStack;
			const size_t& cuiEdgesCount = lstEdges.size();

			for ( UINT i = 0; i < cuiEdgesCount; i++ )
				labelsStack.push( lstEdges[i]->getLabel() );

			edgeLabelStack = labelsStack;
			pCurrentNode = pNode;
		}


		CGridNode* pCurrentNode;
		EdgeLabelStack edgeLabelStack;
	};


	typedef std::stack<CTraverseData> traverseStack;
	traverseStack mainStack;

	// let's start with the stack of first node:
	CGridNode*& pCurrentNode = getNode( 1, 1 );
	mainStack.push( CTraverseData( pCurrentNode->getAvailableEdges(), pCurrentNode ) );
	nodeMetState.getState( pCurrentNode->getLabel() ) = true;


	// let's do the traverse..
	while ( mainStack.size() )
	{
		// get the top edge label to travel in that direction
		CTraverseData& topObject = mainStack.top();
		CTraverseData tempCopy = topObject;

		if ( topObject.edgeLabelStack.empty() )
		{
			mainStack.pop();
			continue;
		}

		const EdgeLabel& travelDirection = topObject.edgeLabelStack.top();
		CGridNode*& pCurrentNode = topObject.pCurrentNode;

		CGridNode* pNextNode = pCurrentNode->getEdge( UINT(travelDirection) )->getOtherNode();
		
		// the edge has done its work, for progress to another node, this one ( the top one ) should be removed!
		topObject.edgeLabelStack.pop();
		tempCopy = topObject;

		// if the next node is already traversed, then ignore it and move forwards.
		if ( nodeMetState.getState( pNextNode->getLabel() ) )
			continue;




		// create a stack of edge labels
		mainStack.push( CTraverseData( pNextNode->getAvailableEdges(), pNextNode ) );
		nodeMetState.getState( pNextNode->getLabel() ) = true;
	}


	// The moment of truth! (if all the nodes are 'ON', then the graph is connected!)
	UINT uiNodesCount = nodeMetState.getMetNodesCount();
	return  uiNodesCount == ( m_uiRowsCount * m_uiColumnsCount );
}


CGrid::~CGrid()
{
	for ( UINT uiRow = 1; uiRow < m_uiRowsCount; uiRow++ )
		for ( UINT uiColumn = 1; uiColumn < m_uiColumnsCount; uiColumn++ )
		{
			CGridNode* pNode = getNode( uiRow, uiColumn );
			SAFE_DELETE( pNode );
		}

	SAFE_DELETE_ARRAY( m_arrNodes );
}