#include "Radar.h"

#include "SDK.h"

#include "CDrawManager.h"


void  CRadar::DrawRadarPoint ( Vector vOriginX, Vector vOriginY, QAngle qAngle, C_BaseEntity *pBaseEntity, DWORD dwTeamColor )
{
	C_BaseEntity* pLocalEntity = dynamic_cast< C_BaseEntity* >( gInts.EntList->GetClientEntity ( gInts.Engine->GetLocalPlayer ( ) )->GetBaseEntity ( ) );

	if ( pLocalEntity == NULL )
		return;

	float flDeltaX = vOriginX.x - vOriginY.x;
	float flDeltaY = vOriginX.y - vOriginY.y;

	float flAngle = qAngle.y;

	float flYaw = ( flAngle )* ( M_PI / 180.0 );
	float flMainViewAngles_CosYaw = cos ( flYaw );
	float flMainViewAngles_SinYaw = sin ( flYaw );

	// rotate
	float x = flDeltaY * ( -flMainViewAngles_CosYaw ) + flDeltaX * flMainViewAngles_SinYaw;
	float y = flDeltaX * ( -flMainViewAngles_CosYaw ) - flDeltaY * flMainViewAngles_SinYaw;

	float flRange = 2000;

	if ( fabs ( x ) > flRange || fabs ( y ) > flRange )
	{
		// clipping
		if ( y > x )
		{
			if ( y > -x )
			{
				x = flRange * x / y;
				y = flRange;
			}
			else
			{
				y = -flRange * y / x;
				x = -flRange;
			}
		}
		else
		{
			if ( y > -x )
			{
				y = flRange * y / x;
				x = flRange;
			}
			else
			{
				x = -flRange * x / y;
				y = -flRange;
			}
		}
	}

	int	iScreenX = m_flx + int ( x / flRange * m_flw );
	int iScreenY = m_fly + int ( y / flRange * m_flw );

	gDrawManager.DrawRect ( iScreenX - 3, iScreenY - 3, 7, 7, 0x777777FF );
	gDrawManager.DrawRect ( iScreenX - 2, iScreenY - 2, 5, 5, dwTeamColor );

}
//===================================================================================
void CRadar::DrawRadarBack ( )
{
	int iCenterX = m_flx;
	int iCenterY = m_fly;
	int iSize = m_flw;

	gDrawManager.DrawRect ( iCenterX - iSize, iCenterY - iSize, 2 * iSize + 2, 2 * iSize + 2, COLORCODE ( 30, 30, 30, 128 ) );
	iSize -= 10;

	gDrawManager.DrawRect ( iCenterX, iCenterY - iSize, 1, 2 * iSize, COLORCODE ( 255, 120, 0, 255 ) );
	gDrawManager.DrawRect ( iCenterX - iSize, iCenterY, 2 * iSize, 1, COLORCODE ( 255, 120, 0, 255 ) );
}


CRadar gRadar;