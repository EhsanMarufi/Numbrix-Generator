// evry node has four edges, this is the edge class

#pragma once
#ifndef GRIDNODEEDGE_H
#define GRIDNODEEDGE_H

namespace NumbrixGenerator
{
	typedef enum _EdgeLabel { LEFT_EDGE, UP_EDGE, RIGHT_EDGE, DOWN_EDGE, UNDEFINED } EdgeLabel;

	extern EdgeLabel getOppositeSideLabel( const EdgeLabel& lbl );

	class CGridNode; // Forward declaration
	class CGridNodeEdge
	{
	public:
		CGridNodeEdge( CGridNode *pOwnerNode, const EdgeLabel& label )
			: m_pOwnerNode( pOwnerNode ), m_pConnectedEdge( 0 ), m_bEnabled( false ), m_EdgeLabel( label )
		{}

		inline CGridNode* getOwnerNode() const { return m_pOwnerNode; }
		inline CGridNode* getOtherNode() const
		{
			return m_bEnabled && m_pConnectedEdge ? m_pConnectedEdge->getOwnerNode() : 0;
		}

		inline void connect( CGridNodeEdge* pOtherEdge, const bool& bFirstConnection = true )
		{
			enable();
			m_pConnectedEdge = pOtherEdge;

			if ( bFirstConnection )
			{
				m_pConnectedEdge->connect( this, false );
			}
		}

		inline void enable( const bool& bFirstTime = true )
		{
			m_bEnabled = true;
			if ( bFirstTime && m_pConnectedEdge )
			{
				m_pConnectedEdge->enable( false );
			}
		}

		inline void disable( const bool& bFirstTime = true )
		{
			m_bEnabled = false;
			if ( bFirstTime && m_pConnectedEdge )
			{
				m_pConnectedEdge->disable( false );
			}
		}

		inline const bool& isEnabled() const { return m_bEnabled; }
		inline const EdgeLabel& getLabel() const { return m_EdgeLabel; }

	protected:
		CGridNode* m_pOwnerNode;
		CGridNodeEdge* m_pConnectedEdge;
		bool m_bEnabled;
		EdgeLabel m_EdgeLabel;
	}; // end of class 'CGridNodeEdge'
} // end of namespace 'NumbirxGenerator'

#endif // GRIDNODEEDGE_H