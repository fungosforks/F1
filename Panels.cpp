#include "SDK.h"
#include "Panels.h"
#include "CDrawManager.h"

#include "Players.h"
#include "ESP.h"
#include "CGlobalVars.h"

CScreenSize gScreenSize;

//===================================================================================
void __fastcall Hooked_PaintTraverse( PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce )
{

	try
	{
		VMTManager& hook = VMTManager::GetHook(pPanels); //Get a pointer to the instance of your VMTManager with the function GetHook.
		hook.GetMethod<void(__thiscall*)(PVOID, unsigned int, bool, bool)>(gOffsets.iPaintTraverseOffset)(pPanels, vguiPanel, forceRepaint, allowForce); //Call the original.

		static unsigned int vguiMatSystemTopPanel;

		if (vguiMatSystemTopPanel == NULL)
		{
			const char* szName = gInts.Panels->GetName(vguiPanel);
			if( szName[0] == 'M' && szName[3] == 'S' ) //Look for MatSystemTopPanel without using slow operations like strcmp or strstr.
			{
				vguiMatSystemTopPanel = vguiPanel;
				Intro();
			}
		}
		
		if ( vguiMatSystemTopPanel == vguiPanel ) //If we're on MatSystemTopPanel, call our drawing code.
		{
			if( gInts.Engine->IsDrawingLoadingImage() || !gInts.Engine->IsInGame( ) || !gInts.Engine->IsConnected() || gInts.Engine->Con_IsVisible( ) || ( ( GetAsyncKeyState(VK_F12) || gInts.Engine->IsTakingScreenshot( ) ) ) )
			{
				return; //We don't want to draw at the menu.
			}

			//Test ESP code.

			// loop every entity

			// crashes beyond this point
			for (int iIndex = 0; iIndex < gInts.EntList->GetHighestEntityIndex(); iIndex++)
			{
				gEsp.DrawPlayerESP(iIndex); // crash in this func
			}
		}
	}
	catch(...)
	{
		gBaseAPI.LogToFile("Failed PaintTraverse");
		gBaseAPI.ErrorBox("Failed PaintTraverse");
	}
}
//===================================================================================
void Intro( void )
{
	try
	{
		gDrawManager.Initialize(); //Initalize the drawing class.

		gOffsets.dwWriteUserCmd = gBaseAPI.GetClientSignature( "55 8B EC 8B 45 10 83 EC 08 8B 40 04" ); //Grab WriteUserCmd from client.dll.
		XASSERT(gOffsets.dwWriteUserCmd); //Make sure it's not 0.
		#ifdef DEBUG
		if (gOffsets.dwWriteUserCmd)
		{
			gBaseAPI.LogToFile( "dwWriteUserCmd client.dll+0x%.4X", gOffsets.dwWriteUserCmd - (DWORD)gBaseAPI.GetModuleHandleSafe("client.dll") );
		}
		#endif

		gBaseAPI.LogToFile("Injection Successful"); //If the module got here without crashing, it is good day.

		// create debug console
		gBaseAPI.BuildDebugConsole();

		ConVarRef cheats("sv_cheats");

		gBaseAPI.LogToConsole("sv_cheats convar @%X", cheats.GetLinkedConVar);

		//gBaseAPI.LogToConsole("Dumping netvar offsets!!");

		//// dump offsets to netvars.log
		//gNetworkedVar.dump();

		// populate offsets
		gPlayerVars.findOffset();

	}
	catch(...)
	{
		gBaseAPI.LogToFile("Failed Intro");
		gBaseAPI.ErrorBox("Failed Intro");
	}
}