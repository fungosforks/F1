#include "CGlobalVars.h"

#include "SDK.h"

bool streql ( const char *a, const char *b )
{
	register const char	*s1 = a;
	register const char	*s2 = b;

	if ( s1 == NULL || s2 == NULL )
		return true;

	while ( *s1 == *s2++ )
		if ( *s1++ == '\0' )
			return true;

	return false;
}

CNetworkedVar::CNetworkedVar ( )
{
	pNetvarLog = fopen ( "netvar.log", "w" );
}
CNetworkedVar::~CNetworkedVar ( )
{
	fclose ( pNetvarLog );
}
FILE *CNetworkedVar::getFilePtr ( )
{
	return pNetvarLog;
}
void CNetworkedVar::dump ( )
{
	DumpOffset ( pNetvarLog );
}

void CPlayerVars::findOffset ( )
{

	// CTFPlayer
	this->m_iHealth = gNetvars.get_offset ( "DT_BasePlayer", "m_iHealth" );
	this->m_lifeState = gNetvars.get_offset ( "DT_BasePlayer", "m_lifeState" );
	this->m_iTeamNum = gNetvars.get_offset ( "DT_BaseEntity", "m_iTeamNum" );
	this->m_iPlayerClass = gNetvars.get_offset ( "DT_TFPlayer", "m_playerClass", "m_iClass" ); //m_iClass
	this->m_fFlags = gNetvars.get_offset ( "DT_BasePlayer", "m_fFlags" );
	this->m_Shared = gNetvars.get_offset ( "DT_TFPlayer", "m_Shared" );
	this->m_bGlowEnabled = gNetvars.get_offset ( "DT_TFPlayer", "m_bGlowEnabled" );
	this->m_hActiveWeapon = gNetvars.get_offset ( "DT_BaseCombatCharacter", "m_hActiveWeapon" );
	this->m_bReadyToBackstab = gNetvars.get_offset ( "DT_BaseAttributableItem", "m_AttributeManager", "m_Item", "m_ReadyToBackstab" );
	/* m_Shared subclass */
	this->m_nPlayerCond = gNetvars.get_offset ( "DT_TFPlayerShared", "m_nPlayerCond" );

	// DT_BaseCombatCharacter
	//this->m_iMaxHealth = 0xF38;

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
//===================================================================================
void DumpOffset ( char* file )
{
	FILE *fp;
	fp = fopen ( file, "a+" );

	DumpOffset ( fp );

	fclose ( fp );
}

void DumpOffset ( FILE *fp )
{
	ClientClass *pClass = gInts.Client->GetAllClasses ( );

	for ( ; pClass; pClass = pClass->m_pNext )
	{
		RecvTable *pTable = pClass->m_pRecvTable;

		fprintf ( fp, "> %s [%i]\n", pClass->m_pNetworkName, pTable->GetNumProps ( ) );

		for ( int i = 0; i < pTable->GetNumProps ( ); i++ )
		{
			RecvProp *pProp = pTable->GetProp ( i );

			if ( !pProp ) continue;
			fprintf ( fp, "-> %s [0x%.4X]\n", pProp->GetName ( ), pProp->GetOffset ( ) );

			if ( pProp->GetDataTable ( ) )
			{
				DumpTable ( pProp->GetDataTable ( ), fp );
			}
		}
	}
}
//===================================================================================
void DumpTable ( RecvTable *pTable, FILE* fp )
{
	fprintf ( fp, "--> %s | [%i]\n", pTable->GetName ( ), pTable->GetNumProps ( ) );

	for ( int i = 0; i < pTable->GetNumProps ( ); i++ )
	{
		RecvProp *pProp = pTable->GetProp ( i );

		if ( !pProp ) continue;
		fprintf ( fp, "---> %s [0x%.4X\n", pProp->GetName ( ), pProp->GetOffset ( ) );
		if ( pProp->GetDataTable ( ) )
			DumpTable ( pProp->GetDataTable ( ), fp );
	}
	fprintf ( fp, "> %s | [%i]\n", pTable->GetName ( ), pTable->GetNumProps ( ) );
}
//===================================================================================

// Currently it was 2 level deep, it was enough.
int getOffset ( char *szClassName, char *szVariable )
{
	ClientClass *pClass = gInts.Client->GetAllClasses ( );

	for ( ; pClass; pClass = pClass->m_pNext )
	{
		RecvTable *pTable = pClass->m_pRecvTable;

		if ( pTable->GetNumProps ( ) <= 1 ) continue;

		for ( int i = 0; i < pTable->GetNumProps ( ); i++ )
		{
			RecvProp *pProp = pTable->GetProp ( i );

			if ( !pProp ) continue;

			if ( streql ( pTable->GetName ( ), szClassName ) && streql ( pProp->GetName ( ), szVariable ) )
			{
				//fprintf(gNetworkedVar.getFilePtr(), "Found Offset --> [%s --> 0x%.4X [%s]", pProp->GetName(), pProp->GetOffset(), pTable->GetName());
				return pProp->GetOffset ( );
			}
			if ( pProp->GetDataTable ( ) )
			{
				RecvTable *pTable = pProp->GetDataTable ( );
				for ( int i = 0; i < pTable->GetNumProps ( ); i++ )
				{
					RecvProp *pProp = pTable->GetProp ( i );

					if ( !pProp ) continue;

					if ( streql ( pTable->GetName ( ), szClassName ) && streql ( pProp->GetName ( ), szVariable ) )
					{
						//fprintf(gNetworkedVar.getFilePtr(),"Found Offset --> [%s --> 0x%.4X] [%s]", pProp->GetName(), pProp->GetOffset(), pTable->GetName());
						return pProp->GetOffset ( );
					}
				}
			}
		}
	}
	return 0;
}
//============================================================================================

COffsets gOffsets;
CPlayerVars gPlayerVars;
CNetworkedVar gNetworkedVar;
CVars gVars;

