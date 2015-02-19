#include "ESP.h"

void CEsp::DrawPlayerESP(int iIndex)
{
	player_info_t pInfo;
	//================================================================
	CPlayer __pLocalBaseEntity = gPlayers[me];

	CBaseEntity* pLocalBaseEntity = __pLocalBaseEntity(); // no crash here, gets loal ent, always avalible

	if (iIndex == pLocalBaseEntity->index)
		return;
	//================================================================
	CPlayer __pBaseEntity = gPlayers[iIndex];

	CBaseEntity* pBaseEntity = __pBaseEntity(); // crash here??

	if (pBaseEntity == NULL)
		return;
	//================================================================

	bool isDormant = pBaseEntity->IsDormant();
	bool isAlive = __pBaseEntity.GetLifeState() == LIFE_ALIVE;

	if (isAlive && !isDormant && gInts.Engine->GetPlayerInfo(iIndex, &pInfo))
	{
		Vector vScreen, vWorldPos;

		int team = __pBaseEntity.GetTeam();

		DWORD dwGetTeamColor = gDrawManager.dwGetTeamColor(team);
		GetWorldSpaceCenter(pBaseEntity, vWorldPos);

		if (gDrawManager.WorldToScreen(vWorldPos, vScreen) == false)
			return;

		float Distance = flGetDistance(pBaseEntity->GetAbsOrigin(), pLocalBaseEntity->GetAbsOrigin());
		int iRadius = 300.0 / Distance;

		int health = __pBaseEntity.GetHealth();
		//int maxHealth = __pBaseEntity.GetMaxHealth();

		// basic 2d square around player
		gDrawManager.DrawPlayerBox(pBaseEntity, dwGetTeamColor);

		// draw name & class under it
		gDrawManager.DrawString(vScreen.x, vScreen.y, dwGetTeamColor, "%s | %s", pInfo.name, __pBaseEntity.GetClass());
		vScreen.y += gDrawManager.GetESPHeight();

		// draw health
		gDrawManager.DrawString(vScreen.x, vScreen.y, dwGetTeamColor, "%i", health);
		vScreen.y += gDrawManager.GetESPHeight();

		// draw distance
		gDrawManager.DrawString(vScreen.x, vScreen.y, dwGetTeamColor, "%f", Distance);
		vScreen += gDrawManager.GetESPHeight();
	}
}

CEsp gEsp;