#pragma once

#include "SDK.h"


// me first
class CPlayerHelper
{

public:
	const char* szGetTF2Class ( int iClass );
	const unsigned int getWeaponID ( CBaseCombatWeapon *pBaseWeapon );
};


extern CPlayerHelper gPlayerHelper;


// genius player mechanism
// instead of storing pointers, they store the index that the pointer relates to
class CPlayer
{
	int m_index;

public:

	inline void init ( int index )
	{
		m_index = index;
	}

	inline const int index ( ) const
	{
		return m_index;
	}

	inline BYTE GetLifeState ( ) const
	{
		return *MakePtr ( byte *, getEnt ( ), gPlayerVars.m_iState );
	}

	inline int GetHealth ( ) const
	{
		return *MakePtr ( int *, getEnt ( ), gPlayerVars.m_iHealth );
	}

	inline int GetTeam ( ) const
	{
		return *MakePtr ( int *, getEnt ( ), gPlayerVars.m_iTeamNum );
	}

	inline int GetMaxHealth ( ) const
	{
		return *MakePtr ( int *, getEnt ( ), gPlayerVars.m_iMaxHealth );
	}
	inline byte GetFlags ( ) const
	{
		return *MakePtr ( byte *, getEnt ( ), gPlayerVars.m_fFlags );
	}
	inline const char *GetClass ( ) const
	{
		return gPlayerHelper.szGetTF2Class ( *MakePtr ( int *, getEnt ( ), gPlayerVars.m_iClass ) );
	}
	inline bool GlowEnabled ( ) const
	{
		return *MakePtr ( bool *, getEnt ( ), gPlayerVars.m_bGlowEnabled );
	}

	inline CBaseEntity *getEnt ( ) const
	{
		return gInts.EntList->GetClientEntity ( m_index )->GetBaseEntity ( );
	}

	inline IClientEntity *getClientEntity ( ) const
	{
		return gInts.EntList->GetClientEntity ( m_index );
	}

	bool operator== ( const CPlayer &b )
	{
		const CPlayer a = *this;

		if ( a.index ( ) == b.index ( ) )
		{
			return true;
		}

		return false;
	}

	bool operator!= ( const CPlayer &b )
	{
		return !(*this == b);
	}

	inline bool isEntityNull ( )
	{
		return gInts.EntList->GetClientEntity ( m_index ) == NULL;
	}
};

class CPlayerList
{
	CPlayer *pPlayers;

public:

	inline CPlayerList ( )
	{
		pPlayers = new CPlayer[ 65 ];

		for ( unsigned int i = 0; i <= 64; i++ )
		{
			pPlayers[ i ].init ( i );
		}
			
	}

	inline ~CPlayerList ( )
	{
		delete[ ] pPlayers;
	}

	inline CPlayer& operator [] ( unsigned int i ) const
	{
		if ( i == me )
			return pPlayers[ gInts.Engine->GetLocalPlayer ( ) ];

		else if ( i > 64 || i <= 0 )
			return pPlayers[ 0 ];

		return pPlayers[ i ];
	}
};


extern CPlayerList gPlayers;