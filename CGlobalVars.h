#pragma once

#include <stdio.h>
#include <Windows.h>

void DUMP ( );

class CPlayerVars
{
public:

	void findOffset ( );

	int m_lifeState;
	int m_iHealth;
	int m_iMaxHealth;
	int m_iHealth_object; // This one is for objects, not for living entities
	int m_iPlayerClass;
	int m_iClass;
	int m_iTeamNum;
	int m_bHasSapper;
	int m_iUpgradeLevel;
	int m_iUpgradeMetal;
	int m_Shared;
	int m_nPlayerCond;
	float m_flPercentageConstructed;
	int m_bBuilding;
	int m_iAmmoShells;
	int m_iState;
	int m_bPlayerControlled;
	int m_iAmmoRockets;
	int m_iAmmoMetal;
	int m_fFlags;
	bool m_bGlowEnabled;
	int m_hActiveWeapon;
	int m_bReadyToBackstab;
};

class COffsets
{
public:
	DWORD dwWriteUserCmd;
	int iCreateMoveOffset;
	int iWriteUserCmdToBufferOffset;
	int iPaintTraverseOffset;

	COffsets ( )
	{
		iCreateMoveOffset = 21;
		iWriteUserCmdToBufferOffset = 23;
		iPaintTraverseOffset = 41;
	}
};

class CVars
{
public:
	bool f1Cheats;
	bool f1Esp;
	bool f1BHop;
};

extern CPlayerVars gPlayerVars;
extern COffsets gOffsets;
extern CVars gVars;