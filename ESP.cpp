#include "ESP.h"

void CEsp::DrawPlayerESP ( CPlayer &player, CPlayer &localPlayer )
{

	gBaseAPI.LogToConsole ( "Trying ESP on Entity:%i", player.handle().GetEntryIndex ( ) );

	player_info_t pInfo;

	if ( player == localPlayer )
		return;

	try
	{
		// is it a player??
		if ( player.GetLifeState ( ) == LIFE_ALIVE && !player.getEnt ( )->IsDormant ( ) && gInts.Engine->GetPlayerInfo ( player.handle ( ).GetEntryIndex ( ), &pInfo ) && player.getEnt ( )->IsPlayer ( ) )
		{
			Vector vScreen, vWorldPos;

			int team = player.GetTeam ( );

			DWORD dwGetTeamColor = gDrawManager.dwGetTeamColor ( team );
			GetWorldSpaceCenter ( player.getEnt ( ), vWorldPos );

			if ( gDrawManager.WorldToScreen ( vWorldPos, vScreen ) == false )
				return;

			float Distance = flGetDistance ( player.getEnt ( )->GetAbsOrigin ( ), localPlayer.getEnt ( )->GetAbsOrigin ( ) );
			int iRadius = 300.0 / Distance;

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
			gDrawManager.DrawString ( vScreen.x, vScreen.y, dwGetTeamColor, "%f", Distance );
			vScreen += gDrawManager.GetESPHeight ( );
		}
	}
	catch ( ... )
	{
		gBaseAPI.LogToConsole ( "ERROR IS DRAWPLAYERESP!!" );
		return;
	}
}

CEsp gEsp;