#pragma once

#include "SDK.h"

#include "CGlobalVars.h"

class CPlayer
{
	int m_index;

	// private
	// use () to infer getEnt()
	inline CBaseEntity *getEnt()
	{
		return GetBaseEnt(m_index);
	}

public:
	
	inline void init(int index)
	{
		m_index = index;
	}

	inline int index()
	{
		return m_index;
	}

	inline BYTE GetLifeState()
	{
		return *MakePtr(byte *, getEnt(), gPlayerVars.m_iState);
	}

	inline int GetHealth()
	{
		return *MakePtr(int *, getEnt(), gPlayerVars.m_iHealth);
	}

	inline int GetTeam()
	{
		return *MakePtr(int *, getEnt(), gPlayerVars.m_iTeamNum);
	}

	inline int GetMaxHealth()
	{
		return *MakePtr(int *, getEnt(), gPlayerVars.m_iMaxHealth);
	}
	inline byte GetFlags()
	{
		return *MakePtr(byte *, getEnt(), gPlayerVars.m_fFlags);
	}
	inline int GetClass()
	{
		return *MakePtr(int *, getEnt(), gPlayerVars.m_iClass);
	}

	inline CBaseEntity *operator()()
	{
		return getEnt();
	}

};

class CPlayerList
{
	CPlayer *pPlayers;

public:

	inline CPlayerList()
	{
		pPlayers = new CPlayer[65];

		for (unsigned int i = 0; i <= 64; i++)
			pPlayers[i].init(i);
	}

	inline ~CPlayerList()
	{
		delete[] pPlayers;
	}

	inline CPlayer& operator [] (unsigned int i) const
	{
		if (i == me)
			return pPlayers[gInts.Engine->GetLocalPlayer()];

		else if (i > 64 || i <= 0)
			return pPlayers[0];

		return pPlayers[i];
	}

};

extern CPlayerList gPlayers;