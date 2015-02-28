#include "ESP.h"

void CEsp::DrawPlayerESP ( CPlayer &player, CPlayer &localPlayer )
{
	player_info_t pInfo;

	if ( player == localPlayer )
		return;

	if ( player.isEntityNull ( ) )
		return;

	try
	{

		bool isDormant = player.getEnt ( )->IsDormant ( );
		bool isPlayer = player.getEnt ( )->IsPlayer ( );
		bool getPlayerInfo = gInts.Engine->GetPlayerInfo ( player.index ( ), &pInfo );
		bool playerState = player.GetLifeState ( ) == LIFE_ALIVE;

		gBaseAPI.ColorLogToConsole ( FOREGROUND_INTENSITY | FOREGROUND_BLUE, "Player: %i has life state: %i", player.index ( ), player.GetLifeState ( ) );


		// is it a player??
		if ( isPlayer && getPlayerInfo && !isDormant && playerState )
		{
			Vector vScreen, vWorldPos;

			int team = player.GetTeam ( );

			DWORD dwGetTeamColor = gDrawManager.dwGetTeamColor ( team );
			GetWorldSpaceCenter ( player.getEnt ( ), vWorldPos );

			if ( gDrawManager.WorldToScreen ( vWorldPos, vScreen ) == false )
				return;

			// draw radar first so no esp stuff messes with it
			gRadar.DrawRadarPoint ( player.getEnt ( )->GetAbsOrigin ( ), localPlayer.getEnt ( )->GetAbsOrigin ( ), localPlayer.getEnt ( )->GetAbsAngles ( ), player.getEnt ( ), dwGetTeamColor );

			float Distance = flGetDistance ( player.getEnt ( )->GetAbsOrigin ( ), localPlayer.getEnt ( )->GetAbsOrigin ( ) );
			int iRadius = 360 / Distance;

			int health = player.GetHealth ( );

			// basic 2d square around player
			gDrawManager.DrawPlayerBox ( player.getEnt ( ), dwGetTeamColor );

			// draw name & class under it
			gDrawManager.DrawString ( vScreen.x, vScreen.y, dwGetTeamColor, "%s | %s", pInfo.name, player.GetClass ( ) );
			vScreen.y += gDrawManager.GetESPHeight ( );

			// draw health
			gDrawManager.DrawString ( vScreen.x, vScreen.y, dwGetTeamColor, "%i", health );
			vScreen.y += gDrawManager.GetESPHeight ( );

			// draw distance
			gDrawManager.DrawString ( vScreen.x, vScreen.y, dwGetTeamColor, "%3f", Distance );
			vScreen += gDrawManager.GetESPHeight ( );
		}
	}
	catch ( ... )
	{
		gBaseAPI.ColorLogToConsole ( FOREGROUND_INTENSITY | FOREGROUND_RED, "Error drawing on entity: %i", player.index ( ) );
		return;
	}
}

CEsp gEsp;