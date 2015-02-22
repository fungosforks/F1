#include "Glow.h"

#include "Players.h"
#include "SDK.h"

//void CGlow::EnableGlowOnEntity ( int index )
//{
//	bool isGlowEnabled = gPlayers[ index ].GlowEnabled ( );
//
//	if ( !isGlowEnabled )
//	{
//		gInts.GlowManager.SetRenderFlags ( index, true, true );
//	}
//
//}
//
//void CGlow::DisableGlowOnEntity ( int index )
//{
//	bool isGlowEnabled = gPlayers[ index ].GlowEnabled ( );
//
//	if ( isGlowEnabled )
//	{
//		gInts.GlowManager.SetRenderFlags ( index, false, false );
//	}
//}

CGlow gGlow;