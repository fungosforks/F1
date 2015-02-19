#pragma once

#include "SDK.h"

#include "Players.h"
#include "CDrawManager.h"
#include <cmath>

#define FastSqrt(x)	::sqrtf(x)

class CEsp
{

	float flGetDistance(Vector vOrigin, Vector vLocalOrigin)
	{
		Vector vDelta = vOrigin - vLocalOrigin;

		float m_fDistance = FastSqrt(vDelta.Length());

		if (m_fDistance < 1.0f)
			return 1.0f;

		return m_fDistance;
	}

	void GetWorldSpaceCenter(CBaseEntity *pBaseEnt, Vector& vWorldSpaceCenter)
	{
		if (pBaseEnt)
		{
			Vector vMin, vMax;
			pBaseEnt->GetRenderBounds(vMin, vMax);
			vWorldSpaceCenter = pBaseEnt->GetAbsOrigin();
			vWorldSpaceCenter.z += (vMin.z + vMax.z) / 2.0f;
		}
	}

public:

	void DrawPlayerESP(int iIndex);

};

extern CEsp gEsp;
