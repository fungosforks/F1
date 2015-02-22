#pragma once

#include "SDK.h"


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
	inline int GetClass ( ) const
	{
		return *MakePtr ( int *, getEnt ( ), gPlayerVars.m_iClass );
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

	//inline void enableGlow ( )
	//{
	//	gGlow.EnableGlowOnEntity ( getEnt ( )->index );
	//}

	//inline void disableGlow ( )
	//{
	//	gGlow.DisableGlowOnEntity ( getEnt ( )->index );
	//}

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


class CPlayerHelper
{

public:
	const char* szGetTF2Class ( int iClass )
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
		return NULL;
	}
};

extern CPlayerHelper gPlayerHelper;
extern CPlayerList gPlayers;