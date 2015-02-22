#ifndef _SDK_H_
#define _SDK_H_
//===================================================================================
#define CLIENT_DLL
//===================================================================================
#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#pragma warning( disable : 4541 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4183 )
//===================================================================================
#include <windows.h>
#include <tlhelp32.h>
#include <winsock.h>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string.h>

#define SECURITY_WIN32
#define WIN32_LEAN_AND_MEAN
#pragma optimize("gsy",on)

#define VERSION_SAFE_STEAM_API_INTERFACES
#define GLOWS_ENABLE

#include <Security.h>
#include <shlwapi.h>
#include "public\cdll_int.h"
#include "public\iprediction.h"
#include "public\client\imessagechars.h"
#include "public\client\iclientmode.h"
#include "public\client\cliententitylist.h"
#include "public\client\cdll_client_int.h"
#include "public\client\cbase.h"
#include "public\client\sdk\c_sdk_player.h"
#include "public\client\c_baseanimating.h"
#include "public\client\ivieweffects.h"
#include "public\client\c_basecombatweapon.h"
#include "public\client\c_baseplayer.h"
#include "public\icliententitylist.h"
#include "public\engine/ivmodelrender.h"
#include "public\iefx.h"
#include "public\icvar.h"
#include "public\ivrenderview.h"
#include "public\engine/ivdebugoverlay.h"
#include "public\materialsystem/imaterialsystemstub.h"
#include "public\engine\ivmodelinfo.h"
#include "public\ienginevgui.h"
#include "public\networkstringtabledefs.h"
#include "public\ispatialpartition.h"
#include "public\engine\ishadowmgr.h"
#include "public\engine\IStaticPropMgr.h"
#include "public\engine\IEngineSound.h"
#include "public\vstdlib/random.h"
#include "public\VGuiMatSurface/IMatSystemSurface.h"
#include "public\vgui\Cursor.h"
#include "public\vgui\Dar.h"
#include "public\vgui\IBorder.h"
#include "public\vgui\IClientPanel.h"
#include "public\vgui\IPanel.h"
#include "public\vgui_controls/controls.h"
#include "public\vgui\ISurface.h"
#include "public\vgui_controls\Panel.h"
#include "public\engine\IEngineTrace.h"
#include "public\IGameUIFuncs.h"
#include "public\igameevents.h"
#include "public\client\input.h"
#include "public\shared\usermessages.h"
#include "public\vgui\IInputInternal.h"
#include "public\vgui_controls\Frame.h"
#include "public\vgui_controls\CheckButton.h"
#include "public\vgui_controls\ComboBox.h"
#include "public\vgui_controls\Button.h"
#include "public\vgui_controls\Controls.h"
#include "public\vgui_controls\DialogManager.h"
#include "public\vgui_controls\RadioButton.h"
#include "public\vgui_controls\Menu.h"
#include "public\client/game_controls/commandmenu.h"
#include "public\tier1\convar.h"
#include "public\shared\basecombatweapon_shared.h"
#include "public\shared\takedamageinfo.h"
#include "public\vphysics_interface.h"
#include "public\shake.h"
#include "public\dlight.h"
#include "public\iefx.h" 
#include "public\igameevents.h"
#include "public\materialsystem\IMaterialVar.h"
#include "public\vgui\ILocalize.h"
#include "public\engine\ivdebugoverlay.h"
#include "public\igameresources.h"
#include "public\inetchannelinfo.h"
#include "public\inputsystem\iinputsystem.h"
#include "public\iachievementmgr.h"
#include "public\shared\achievementmgr.h"
#include "public\steam\steam_api.h"
#include "public\IGameUIFuncs.h"
//===================================================================================
#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)	// Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
//===================================================================================
#define	HIDEHUD_WEAPONSELECTION		( 1<<0 )	// Hide ammo count & weapon selection
#define	HIDEHUD_FLASHLIGHT			( 1<<1 )	// Hide flashlight energy indication
#define	HIDEHUD_ALL					( 1<<2 )	// Hide the whole HUD
#define HIDEHUD_HEALTH				( 1<<3 )	// Hide health & armor / suit battery
#define HIDEHUD_PLAYERDEAD			( 1<<4 )	// Hide when local player's dead
#define HIDEHUD_NEEDSUIT			( 1<<5 )	// Hide when the local player doesn't have the HEV suit
#define HIDEHUD_MISCSTATUS			( 1<<6 )	// Hide miscellaneous status elements (trains, pickup history, death notices, etc)
#define HIDEHUD_CHAT				( 1<<7 )	// Hide all communication elements (saytext, voice icon, etc)
#define	HIDEHUD_CROSSHAIR			( 1<<8 )	// Hide crosshairs
#define	HIDEHUD_VEHICLE_CROSSHAIR	( 1<<9 )	// Hide vehicle crosshair
#define HIDEHUD_INVEHICLE			( 1<<10 )
#define HIDEHUD_SCOPE				( 1<<11 )
//===================================================================================
#pragma comment ( lib, "public/ImportLibrarys/tier0.lib" )
#pragma comment ( lib, "public/ImportLibrarys/tier1.lib" )
#pragma comment ( lib, "public/ImportLibrarys/tier2.lib" )
#pragma comment ( lib, "public/ImportLibrarys/tier3.lib" )
#pragma comment ( lib, "public/ImportLibrarys/mathlib.lib" )
#pragma comment ( lib, "public/ImportLibrarys/vstdlib.lib" )
#pragma comment ( lib, "public/ImportLibrarys/raytrace.lib" )
#pragma comment ( lib, "public/ImportLibrarys/vgui_controls.lib" )

using namespace std;

#define XASSERT( x ) if( !x ) MessageBoxW( 0, L#x, 0, 0 );
#define MakePtr( Type, dwBase, dwOffset ) ( ( Type )( DWORD( dwBase ) + (DWORD)( dwOffset ) ) )
//===================================================================================

// push this include up to stop the macros interfering with it
#include "VMTHooks.h"

#define VMTManager toolkit::VMTManager
#define VMTBaseManager toolkit::VMTBaseManager

typedef void* ( __cdecl* CreateInterface_t )( const char*, int* );
typedef void* ( *CreateInterfaceFn )( const char *pName, int *pReturnCode );

#define me gInts.Engine->GetLocalPlayer()

class CInterfaces
{
public:
	CInput* Input;
	IClientEntityList* EntList;
	IVEngineClient* Engine;
	IPanel* Panels;
	ISurface* Surface;
	IBaseClientDLL* Client;
	ICvar* Cvar;
	IEngineTrace *EngineTrace;
	CGlowObjectManager GlowManager; // wtf am i doing?? nb. dont do this.
};
extern CInterfaces gInts;

#include "CBaseAPI.h"
#include "CGlobalVars.h"
#include "Glow.h"
//===================================================================================
#endif