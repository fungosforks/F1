#include "Players.h"

const unsigned int CPlayerHelper::getWeaponID ( CBaseCombatWeapon *pBaseWeapon )
{
	return pBaseWeapon->GetClientClass ( )->m_ClassID;
}

const char* CPlayerHelper::szGetTF2Class ( int iClass )
{
	switch ( iClass )
	{
	case TFClass_Scout: return "Scout";
	case TFClass_Soldier: return "Soldier";
	case TFClass_Pyro: return  "Pyro";
	case TFClass_DemoMan: return "Demoman";
	case TFClass_Heavy: return "Heavy";
	case TFClass_Engineer: return "Engineer";
	case TFClass_Medic: return "Medic";
	case TFClass_Sniper: return "Sniper";
	case TFClass_Spy: return "Spy";
	}
	return "unknown";
}


CPlayerList gPlayers;
CPlayerHelper gPlayerHelper;