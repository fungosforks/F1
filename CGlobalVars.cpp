#include "CGlobalVars.h"

#include "SDK.h"

void CPlayerVars::findOffset ( )
{
	try
	{
		// CTFPlayer
		this->m_iHealth = gNetvars.get_offset ( "DT_BasePlayer", "m_iHealth" );
		this->m_lifeState = gNetvars.get_offset ( "DT_BasePlayer", "m_lifeState" );
		this->m_iTeamNum = gNetvars.get_offset ( "DT_BaseEntity", "m_iTeamNum" );
		this->m_iPlayerClass = gNetvars.get_offset ( "DT_TFPlayer", "m_PlayerClass", "m_iClass" );
		this->m_fFlags = gNetvars.get_offset ( "DT_BasePlayer", "m_fFlags" );
		this->m_Shared = gNetvars.get_offset ( "DT_TFPlayer", "m_Shared" );
		//this->m_bGlowEnabled = gNetvars.get_offset ( "DT_TFPlayer", "m_bGlowEnabled" );
		this->m_hActiveWeapon = gNetvars.get_offset ( "DT_BaseCombatCharacter", "m_hActiveWeapon" );
		//this->m_bReadyToBackstab = gNetvars.get_offset ( "DT_EconEntity", "m_AttributeManager", "m_Item", "m_bReadyToBackstab" );
		/* m_Shared subclass */
		//this->m_nPlayerCond = gNetvars.get_offset ( "DT_TFPlayerShared", "m_nPlayerCond" );

		// CBaseObject
		this->m_bHasSapper = gNetvars.get_offset ( "DT_BaseObject", "m_bHasSapper" );
		this->m_iHealth_object = gNetvars.get_offset ( "DT_BaseObject", "m_iHealth" );
		this->m_iUpgradeLevel = gNetvars.get_offset ( "DT_BaseObject", "m_iUpgradeLevel" );
		this->m_iUpgradeMetal = gNetvars.get_offset ( "DT_BaseObject", "m_iUpgradeMetal" );
		this->m_bBuilding = gNetvars.get_offset ( "DT_BaseObject", "m_bBuilding" );
		this->m_flPercentageConstructed = gNetvars.get_offset ( "DT_BaseObject", "m_flPercentageConstructed" );

		// CObjectSentrygun
		this->m_iAmmoShells = gNetvars.get_offset ( "DT_ObjectSentrygun", "m_iAmmoShells" );
		this->m_iState = gNetvars.get_offset ( "DT_ObjectSentrygun", "m_iState" ); // Actually this offset was universal
		this->m_bPlayerControlled = gNetvars.get_offset ( "DT_ObjectSentrygun", "m_bPlayerControlled" );
		this->m_iAmmoRockets = gNetvars.get_offset ( "DT_ObjectSentrygun", "m_iAmmoRockets" );

		// CObjectDispenser
		this->m_iAmmoMetal = gNetvars.get_offset ( "DT_ObjectDispenser", "m_iAmmoMetal" );
	}
	catch ( ... )
	{
		gBaseAPI.ColorLogToConsole ( FOREGROUND_INTENSITY | FOREGROUND_RED, "FAILED NETVAR GRAB! PLEASE RESTART!" );
	}
}
//===================================================================================



COffsets gOffsets;
CPlayerVars gPlayerVars;
CVars gVars;

