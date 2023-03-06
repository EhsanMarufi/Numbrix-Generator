#include "GridNodeEdge.h"

using namespace NumbrixGenerator;

extern EdgeLabel NumbrixGenerator::getOppositeSideLabel( const EdgeLabel& lbl )
{
	EdgeLabel out = UNDEFINED;
	#define CASE(dir, opp) case dir: out = opp; break; case opp: out = dir; break
	switch ( lbl )
	{
		CASE( LEFT_EDGE, RIGHT_EDGE );
		CASE( UP_EDGE, DOWN_EDGE );
	}
	#undef CASE
	return out;
}