#include "NumbrixGenerator.h"
#include "safe.h"

#include <stack>

using namespace NumbrixGenerator;
using namespace Numbrix;


CNumbrixGenerator::CNumbrixGenerator( const UINT& uiRowsCount, const UINT& uiColumnsCount )
	: m_NodeGrid( uiRowsCount, uiColumnsCount )
{
	generateRandomPath();
}


void CNumbrixGenerator::generateRandomPath()
{
	typedef std::vector<EdgeLabel> EdgeLabelList;

	class CGenerationInfo
	{
	public:
		CGenerationInfo( const CGridNode*& pNode, const EdgeLabel& selectedEdgeLabel, const EdgeLabelList& disabledEdges,
			const EdgeLabelList& forbiddenEdges )
		{
			m_pNode = const_cast<CGridNode*>( pNode );
			m_SelectedEdgeLabel = selectedEdgeLabel;
			m_lstDisabledEdges = disabledEdges;
			m_lstForbiddenEdges = forbiddenEdges;
		}

		inline const CGridNode *const& getNode() const { return m_pNode; }
		inline const EdgeLabel& getSelectedEdgeLabel() const { return m_SelectedEdgeLabel; }
		inline const EdgeLabelList& getDisabledEdgesList() const { return m_lstDisabledEdges; }
		inline const EdgeLabelList& getForbiddenEdgesList() const { return m_lstForbiddenEdges; }


	protected:
		EdgeLabel m_SelectedEdgeLabel;
		EdgeLabelList m_lstDisabledEdges;
		EdgeLabelList m_lstForbiddenEdges;
		CGridNode* m_pNode;
	}; // end of class 'CGenerationInfo'

	std::stack<CGenerationInfo> generationInfoStack;


	m_vecPath.clear();

	const UINT& uiRowsCount = m_NodeGrid.getRowsCount();
	const UINT& uiColumnsCount = m_NodeGrid.getColumnsCount();

	// specify a random start point
	m_vecPath.push_back( CCoordination( random(uiRowsCount), random(uiColumnsCount) ) );

	const CCoordination& firstNodeAddress = m_vecPath[0];

	CGridNode* pCurrentNode = m_NodeGrid.getNode( firstNodeAddress.getRow(), firstNodeAddress.getColumn() );


	const UINT cuiGridSize = uiRowsCount * uiColumnsCount;
	EdgeLabelList lstCurrenNodeForbiddenEdges;

	while ( m_vecPath.size() != cuiGridSize )
	{
		std::vector<CGridNodeEdge*> lstEdges = pCurrentNode->getAvailableEdges();


		// Remove the connecting edge label from the selection candidates.
		// The edge (actually the reminder segment: the opposite direction ) which led us here ( from previuos node ) shouldn't be considered again
		if ( generationInfoStack.size() )
		{
			const EdgeLabel connectingEdgeLabel = getOppositeSideLabel( generationInfoStack.top().getSelectedEdgeLabel() );
			const size_t& cuiEdgesListSize = lstEdges.size();
			for ( UINT i = 0; i < cuiEdgesListSize; i++ )
			{
				if ( lstEdges[i]->getLabel() == connectingEdgeLabel )
				{
					lstEdges.erase( lstEdges.begin() + i );
					break;
				}
			}
		}

		// Now ommit the forbidden edges from the list of candidates
		const EdgeLabelList& forbiddenEdgesLabel = lstCurrenNodeForbiddenEdges;
		const size_t& cuiForbiddenEdgesSize = forbiddenEdgesLabel.size();
		for ( UINT i = 0; i < cuiForbiddenEdgesSize; i++ )
		{
			const EdgeLabel& currentForbiddenEdge = forbiddenEdgesLabel[i];
			const size_t& cuiEdgesListSize = lstEdges.size();
			for ( UINT j = 0; j < cuiEdgesListSize; j++ )
			{
				if ( currentForbiddenEdge == lstEdges[j]->getLabel() )
				{
					lstEdges[j]->disable();
					lstEdges.erase( lstEdges.begin() + j );
					break; // no more than once can an edgeLabel occour!
				}
			}
		}


		// now check whether or not the 'lstEdges' is empty
		if ( !lstEdges.size() )
		{
			// reEnable the this iteration's forbidden edges
			const size_t& cuiForbiddenEdgesSize = forbiddenEdgesLabel.size();
			for ( UINT i = 0; i < cuiForbiddenEdgesSize; i++ )
				pCurrentNode->getEdge( (UINT)forbiddenEdgesLabel[i] )->enable();


			CGenerationInfo& topObject = generationInfoStack.top();

			CGridNode*& pTopObjectNode = const_cast<CGridNode*&>( topObject.getNode() );

			// reEnable the top object's disabled ones
			const EdgeLabelList& lstDisabledEdges = topObject.getDisabledEdgesList();
			const size_t& cuiDisabledEdgesCount = lstDisabledEdges.size();
			for ( UINT i = 0; i < cuiDisabledEdgesCount; i++ )
				pTopObjectNode->getEdge( lstDisabledEdges[i] )->enable();

			// reEnable the top object's forbidden edges
			const EdgeLabelList& lstForbiddenEdges = topObject.getForbiddenEdgesList();
			const size_t& cuiForbiddenEdgesCount = lstForbiddenEdges.size();
			for ( UINT i = 0; i < cuiForbiddenEdgesCount; i++ )
				pTopObjectNode->getEdge( lstForbiddenEdges[i] )->enable();

			// update the forbidden edges' list
			lstCurrenNodeForbiddenEdges.clear();
			lstCurrenNodeForbiddenEdges = lstForbiddenEdges;
			lstCurrenNodeForbiddenEdges.push_back( topObject.getSelectedEdgeLabel() );

			pCurrentNode = pTopObjectNode;
			generationInfoStack.pop();
			m_vecPath.pop_back();
			continue;
		}

		// select a random direction
		UINT uiRandomEdgeIndex = random( lstEdges.size() -1, 0 );
		CGridNodeEdge* pSelectedEdge = lstEdges[ uiRandomEdgeIndex ];
		const EdgeLabel& selectedEdgeLabel = pSelectedEdge->getLabel();

		// specify the Edges which are going to be disabled
		lstEdges.erase( lstEdges.begin() + uiRandomEdgeIndex );
		EdgeLabelList lstEdgesToBeDisabled;
		for ( UINT i = 0; i < lstEdges.size(); i++ )
		{
			lstEdgesToBeDisabled.push_back( lstEdges[i]->getLabel() );
			lstEdges[i]->disable();
		}


		// if this direction causes the graph to be unconnected, then return the selected edge back and select another one!
		if ( !m_NodeGrid.isConnected() )
		{
			lstCurrenNodeForbiddenEdges.push_back( selectedEdgeLabel );


			// reEnable the prviously disabled edges
			const EdgeLabelList& lstDisabledEdges = lstEdgesToBeDisabled;//pTopObject->getDisabledEdgesList();
			const size_t& uiDisabledEdgesCount = lstDisabledEdges.size();
			for ( UINT i = 0; i < uiDisabledEdgesCount; i++ )
				pCurrentNode->getEdge( (UINT)lstDisabledEdges[i] )->enable();

			const size_t& uiForbiddenEdgesCount = lstCurrenNodeForbiddenEdges.size();
			for ( UINT i = 0; i < uiForbiddenEdgesCount; i++ )
				pCurrentNode->getEdge( (UINT)lstCurrenNodeForbiddenEdges[i] )->enable();

			continue;
		}


		// push the information to the information stack
		generationInfoStack.push( CGenerationInfo( const_cast<const CGridNode*&>(pCurrentNode), selectedEdgeLabel, lstEdgesToBeDisabled, lstCurrenNodeForbiddenEdges ) );

		// this forbidden list is just for the current node, every other node should have its own forbidden list of edges
		lstCurrenNodeForbiddenEdges.clear();

		// update the current node
		pCurrentNode = pCurrentNode->getEdge( (UINT)selectedEdgeLabel )->getOtherNode();
		

		// update the vecPath
		CCoordination& lastCell = m_vecPath[ m_vecPath.size() -1 ];
		m_vecPath.push_back( CCoordination( lastCell.getRow() + (selectedEdgeLabel == UP_EDGE ? -1 : selectedEdgeLabel == DOWN_EDGE ? 1 : 0),
			lastCell.getColumn() + (selectedEdgeLabel == RIGHT_EDGE ? 1 : selectedEdgeLabel == LEFT_EDGE ? -1 : 0) ) );
	}
}
