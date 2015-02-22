#include "SDK.h"
#include "Client.h"
#include "Panels.h"
#include "CGlobalVars.h"


CInterfaces gInts;

CreateInterface_t EngineFactory = NULL;
CreateInterface_t ClientFactory = NULL;
CreateInterface_t VGUIFactory = NULL;
CreateInterface_t VGUI2Factory = NULL;
CreateInterface_t CVarFactory = NULL;

DWORD WINAPI dwMainThread( LPVOID lpArguments )
{
	if (gInts.Client == NULL) //Prevent repeat callings.
	{
		//Gottammove those factorys up.
		//Grab the factorys from their resptive module's EAT.
		ClientFactory = ( CreateInterfaceFn ) GetProcAddress( gBaseAPI.GetModuleHandleSafe( "client.dll" ), "CreateInterface" );
		gInts.Client = ( IBaseClientDLL* )ClientFactory( "VClient017", NULL);
		XASSERT(gInts.Client);
		gInts.EntList = ( IClientEntityList* ) ClientFactory( "VClientEntityList003", NULL );
		EngineFactory = ( CreateInterfaceFn ) GetProcAddress( gBaseAPI.GetModuleHandleSafe( "engine.dll" ), "CreateInterface" );
		gInts.Engine = ( IVEngineClient* ) EngineFactory( "VEngineClient013", NULL );
		VGUIFactory = ( CreateInterfaceFn ) GetProcAddress( gBaseAPI.GetModuleHandleSafe( "vguimatsurface.dll" ), "CreateInterface" );
		gInts.Surface = ( ISurface* ) VGUIFactory( "VGUI_Surface030", NULL );
		VGUI2Factory = ( CreateInterfaceFn ) GetProcAddress( gBaseAPI.GetModuleHandleSafe( "vgui2.dll" ), "CreateInterface" );
		CVarFactory = (CreateInterfaceFn)GetProcAddress(gBaseAPI.GetModuleHandleSafe("vstdlib.dll"), "CreateInterface");
		gInts.Cvar = (ICvar*)CVarFactory("VEngineCvar004", NULL);
		XASSERT(gInts.Cvar);

		//Setup the CHLClient hooks.
		if( gInts.Client )
		{
			VMTBaseManager* clientHook = new VMTBaseManager(); //Setup our VMTBaseManager for Client.
			clientHook->Init(gInts.Client); //Tell it that we're creating a new hook.
			clientHook->HookMethod(&Hooked_CreateMove, gOffsets.iCreateMoveOffset); //Hook CreateMove and store the address of the original in OriginalCreateMove.
			clientHook->HookMethod(&Hooked_WriteUserCmdDeltaToBuffer, gOffsets.iWriteUserCmdToBufferOffset); //This is required so it doesn't CRC the CUserCmd.  We're not going to call the original, because we're reconstructing the function.
			DWORD dwInputPointer = (gBaseAPI.dwFindPattern((DWORD)clientHook->GetMethod<DWORD>(gOffsets.iCreateMoveOffset), ((DWORD)clientHook->GetMethod<DWORD>(gOffsets.iCreateMoveOffset)) + 0x100, "8B 0D")) + (0x2); //Find the pointer to CInput in CHLClient::CreateMove.
			XASSERT(dwInputPointer);
			gInts.Input = **(CInput***)dwInputPointer;
			clientHook->Rehook(); //We just created a prototype for the VMTHooking class. Now that we declared the functions we want to hook, we tell the manager class to now hook the functions we want.
		}

		//Setup the Panel hook so we can draw.
		if( !gInts.Panels )
		{
			gInts.Panels = ( IPanel* ) VGUI2Factory( "VGUI_Panel009", NULL );
			XASSERT( gInts.Panels );

			if( gInts.Panels )
			{
				VMTBaseManager* panelHook = new VMTBaseManager(); //Setup our VMTBaseManager for Panels.
				panelHook->Init(gInts.Panels);
				panelHook->HookMethod(&Hooked_PaintTraverse, gOffsets.iPaintTraverseOffset);
				panelHook->Rehook();
			}
		}
	}
	return 0; //The thread has been completed, and we do not need to call anything once we're done. The call to Hooked_PaintTraverse is now our main thread.
}

int WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	//If you manually map, make sure you setup this function properly.
	if(dwReason == DLL_PROCESS_ATTACH)
	{
		CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)dwMainThread, NULL, 0, NULL ); //CreateThread > _BeginThread. (For what we're doing, of course.)
	}
	return true;
}