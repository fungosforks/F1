#pragma once

#include "SDK.h"


// genius player mechanism
// instead of storing pointers, they store the index that the pointer relates to
class CPlayer
{
	//int m_index;

	CBaseHandle m_handleToEnt;

public:

	inline void init ( int index )
	{
		m_handleToEnt = CBaseHandle ( index );
	}

	inline const CBaseHandle handle ( ) const
	{
		return m_handleToEnt;
	}

	inline BYTE GetLifeState ( )
	{
		return *MakePtr ( byte *, getEnt ( ), gPlayerVars.m_iState );
	}

	inline int GetHealth ( )
	{
		return *MakePtr ( int *, getEnt ( ), gPlayerVars.m_iHealth );
	}

	inline int GetTeam ( )
	{
		return *MakePtr ( int *, getEnt ( ), gPlayerVars.m_iTeamNum );
	}

	inline int GetMaxHealth ( ) // NULLL
	{
		return *MakePtr ( int *, getEnt ( ), gPlayerVars.m_iMaxHealth );
	}
	inline byte GetFlags ( )
	{
		return *MakePtr ( byte *, getEnt ( ), gPlayerVars.m_fFlags );
	}
	inline int GetClass ( )
	{
		return *MakePtr ( int *, getEnt ( ), gPlayerVars.m_iClass );
	}
	inline bool GlowEnabled ( )
	{
		return *MakePtr ( bool *, getEnt ( ), gPlayerVars.m_bGlowEnabled );
	}

	inline CBaseEntity *getEnt ( ) const
	{
		return gInts.EntList->GetClientEntityFromHandle ( m_handleToEnt )->GetBaseEntity ( );
	}

	inline IClientEntity *getClientEntity ( ) const
	{
		return gInts.EntList->GetClientEntityFromHandle ( m_handleToEnt );
	}

	inline bool operator== ( const CPlayer &b )
	{
		const CPlayer a = *this;

		if ( a.handle ( ) == b.handle ( ) )
		{
			return true;
		}

		return false;
	}

	inline void enableGlow ( )
	{
		gGlow.EnableGlowOnEntity ( getEnt ( )->index );
	}

	inline void disableGlow ( )
	{
		gGlow.DisableGlowOnEntity ( getEnt ( )->index );
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
			gInts.GlowManager.SetEntity ( i, pPlayers[ i ].getEnt ( ) );
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