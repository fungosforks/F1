#include "SDK.h"
#include "Client.h"
#include "CGlobalVars.h"

bool __fastcall Hooked_WriteUserCmdDeltaToBuffer( PVOID pClient, int edx, DWORD* buf, int from, int to, bool isnewcommand ) 
{
	try
	{
		typedef void ( __cdecl *WriteUserCmdFn )( DWORD*, CUserCmd *, CUserCmd* );
		static WriteUserCmdFn CallWriteUserCmd = (WriteUserCmdFn)gOffsets.dwWriteUserCmd;

		CUserCmd nullcmd, *pFrom, *pTo;

		if ( from == -1 )
		{
			pFrom = &nullcmd;
		}
		else
		{
			pFrom = gInts.Input->GetUserCmd( from );

			if ( !pFrom )
				pFrom = &nullcmd;
		}

		pTo = gInts.Input->GetUserCmd(to);

		if ( !pTo )
			pTo = &nullcmd;

		CallWriteUserCmd( buf, pTo, pFrom );

		if ( *(bool*)((DWORD)buf+0x10) ) //IsOverflowed
			return false;

		return true;
	}
	catch(...)
	{
		gBaseAPI.LogToFile("Failed Hooked_WriteUserCmdDeltaToBuffer");
		return false;
	}
}
//============================================================================================
void __fastcall Hooked_CreateMove(PVOID pClient, int edx, int sequence_number, float input_sample_frametime, bool active)
{
	try
	{
		CBaseEntity *pLocalBaseEntity = gInts.EntList->GetClientEntity ( me )->GetBaseEntity ( ); //Grab the local player's entity pointer.

		if ( pLocalBaseEntity == NULL) //This should never happen, but never say never. 0xC0000005 is no laughing matter.
			return;

		VMTManager& hook = VMTManager::GetHook(pClient); //Get a pointer to the instance of your VMTManager with the function GetHook.
		hook.GetMethod<void(__thiscall*)(PVOID, int, float, bool)>(gOffsets.iCreateMoveOffset)(pClient, sequence_number, input_sample_frametime, active); //Call the original.

		CUserCmd *pCommand = gInts.Input->GetUserCmd(sequence_number); //Grab the CUserCmd from CInput::GetUserCmd.

		//Do your client hook stuff here. This function is called once per tick. For time-critical functions, run your code in PaintTraverse. For move specific functions, run them here.

		if ( pLocalBaseEntity == NULL )
			return;

		EHANDLE hActiveWeapon = ( EHANDLE )*( MakePtr ( int *, pLocalBaseEntity, gPlayerVars.m_hActiveWeapon ) );
		CBaseCombatWeapon *pBaseWeapon = dynamic_cast< CBaseCombatWeapon * >( gInts.EntList->GetClientEntityFromHandle ( hActiveWeapon ) );

		if ( pBaseWeapon == NULL )
			return;

		bool readyToBackstab = *MakePtr ( bool *, pLocalBaseEntity, gPlayerVars.m_bReadyToBackstab );

		if ( readyToBackstab )
		{
			if ( strcmpi ( "Knife", pBaseWeapon->GetName ( ) ) )
			{
				pCommand->buttons |= IN_ATTACK;
			}
		}

		if ( pCommand->buttons & IN_JUMP )
		{
			int iFlags = pLocalBaseEntity->GetFlags ( );

			if ( !( iFlags & FL_ONGROUND ) )
				pCommand->buttons &= ~IN_JUMP;
		}
	}
	catch(...)
	{
		gBaseAPI.LogToFile("Failed Hooked_CreateMove");
	}
}
//============================================================================================