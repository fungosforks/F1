#pragma once

class Vector;
class QAngle;
class C_BaseEntity;

#include <Windows.h>

class CRadar
{

	float m_flx;
	float m_fly;
	float m_flw;

public:
	FORCEINLINE CRadar ( )
	{
		m_flx = 101;
		m_fly = 101;
		m_flw = 100;
	}
	void DrawRadarBack ( void );
	void DrawRadarPoint ( Vector vOriginX, Vector vOriginY, QAngle qAngle, C_BaseEntity *pBaseEntity, DWORD dwTeamColor );
};
extern CRadar gRadar;