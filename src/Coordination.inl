#pragma once
#ifndef COORDINATION_INL
#define COORDINATION_INL

typedef unsigned int UINT;

namespace Numbrix
{

	class CCoordination
	{
	public:
		CCoordination( const UINT& uiRow = 0, const UINT& uiColumn = 0 )
		{
			setRow( uiRow );
			setColumn( uiColumn );
		}

		CCoordination( const CCoordination& copy )
		{
			setRow ( copy.getRow() );
			setColumn( copy.getColumn() );
		}

		~CCoordination() {}

		// inline operators
		inline bool operator== ( const CCoordination& right ) const
		{
			return m_uiRow == right.getRow() && m_uiColumn == right.getColumn();
		}
		inline bool operator!= ( const CCoordination& right ) const
		{
			return !( (*this) == right );
		}


		// utility methodes
		static inline UINT calculateTaxiCabDistance( const CCoordination& from, const CCoordination& to )
		{
			const UINT& cuiFromRow = from.getRow();
			const UINT& cuiFromColumn = from.getColumn();
			const UINT& cuiToRow = to.getRow();
			const UINT& cuiToColumn = to.getRow();
			#define Distance( a, b )( (a) > (b) ? (a) -(b) : (b) -(a) )
			UINT uiHorDistance = Distance( cuiFromRow, cuiToRow );
			UINT uiVerDistance = Distance( cuiFromColumn, cuiToColumn );
			#undef Distance
			return uiHorDistance + uiVerDistance;
		}

		// Inline getters and setters
		inline void setRow( const UINT& uiRow ) { m_uiRow = uiRow; }
		inline void setColumn( const UINT& uiColumn ) { m_uiColumn = uiColumn; }
		inline const UINT& getRow() const { return m_uiRow; }
		inline const UINT& getColumn() const { return m_uiColumn; }

	protected:
		UINT m_uiRow;
		UINT m_uiColumn;
	}; // end of class 'CCoordination'

}// end of namespace 'Numbrix'

#endif // COORDINATION_INL