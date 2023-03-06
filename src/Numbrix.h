#pragma once
#ifndef NUMBRIX_H
#define NUMBRIX_H


namespace Numbrix
{
	class CNumbrix
	{
	public:
		CNumbrix( const UINT& uiRowsCount = 6, const UINT& uiColumnsCount = 6 );

	protected:
		UINT m_uiRowsCount, m_uiColumnsCount;
	};

} // end of namespace 'CNumbrix'

#endif // NUMBRIX_H