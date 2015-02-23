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

enum TFClassType
{
	TFClass_Unknown = 0,
	TFClass_Scout,
	TFClass_Sniper,
	TFClass_Soldier,
	TFClass_DemoMan,
	TFClass_Medic,
	TFClass_Heavy,
	TFClass_Pyro,
	TFClass_Spy,
	TFClass_Engineer
};


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
#include "Netvar.h"
//===================================================================================

enum TF2_ClassID_e
{
	CTFWearableDemoShield = 253,
	CTFBaseRocket = 166,
	CTFWeaponBaseMelee = 244,
	CTFWeaponBaseGun = 243,
	CTFWeaponBaseGrenadeProj = 242,
	CTFWeaponBase = 241,
	CTFWearableRobotArm = 255,
	CTFRobotArm = 221,
	CTFWrench = 256,
	CTFSyringeGun = 238,
	CTFKatana = 191,
	CTFSword = 237,
	CSniperDot = 100,
	CTFSniperRifleDecap = 233,
	CTFSniperRifle = 232,
	CTFSMG = 231,
	CTFShovel = 230,
	CTFPEPBrawlerBlaster = 200,
	CTFSodaPopper = 234,
	CTFShotgun_Revenge = 228,
	CTFScatterGun = 224,
	CTFShotgun_Pyro = 227,
	CTFShotgun_HWG = 226,
	CTFShotgun_Soldier = 229,
	CTFShotgun = 225,
	CTFCrossbow = 177,
	CTFRocketLauncher_DirectHit = 223,
	CTFRocketLauncher = 222,
	CTFRevolver = 220,
	CTFDRGPomson = 178,
	CTFRaygun = 219,
	CTFPistol_ScoutSecondary = 205,
	CTFPistol_ScoutPrimary = 204,
	CTFPistol_Scout = 203,
	CTFPistol = 202,
	CTFPipebombLauncher = 201,
	CTFWeaponPDA_Spy = 250,
	CTFWeaponPDA_Engineer_Destroy = 249,
	CTFWeaponPDA_Engineer_Build = 248,
	CTFWeaponPDA = 247,
	CTFParticleCannon = 199,
	CTFMinigun = 197,
	CWeaponMedigun = 264,
	CTFMechanicalArm = 196,
	CTFLunchBox_Drink = 195,
	CTFLunchBox = 194,
	CLaserDot = 68,
	CTFLaserPointer = 193,
	CTFKnife = 192,
	CTFProjectile_Cleaver = 209,
	CTFProjectile_JarMilk = 214,
	CTFProjectile_Jar = 213,
	CTFCleaver = 174,
	CTFJarMilk = 190,
	CTFJar = 189,
	CTFWeaponInvis = 246,
	CTFGrenadeLauncher = 186,
	CTFGrenadePipebombProjectile = 187,
	CTFFlareGun_Revenge = 184,
	CTFFlareGun = 183,
	CTFFlameRocket = 181,
	CTFFlameThrower = 182,
	CTFFists = 180,
	CTFFireAxe = 179,
	CTFCompoundBow = 176,
	CTFClub = 175,
	CTFBuffItem = 173,
	CTFStickBomb = 235,
	CTFBottle = 172,
	CTFBonesaw = 171,
	CTFBall_Ornament = 164,
	CTFStunBall = 236,
	CTFBat_Giftwrap = 169,
	CTFBat_Wood = 170,
	CTFBat_Fish = 168,
	CTFBat = 167,
	CTFWeaponSapper = 251,
	CTFWeaponBuilder = 245,
	CTFProjectile_Rocket = 215,
	CTFProjectile_Flare = 211,
	CTFProjectile_EnergyBall = 210,
	CTFProjectile_HealingBolt = 212,
	CTFProjectile_Arrow = 208,
	CTeleportVortex = 142,
	CHeadlessHatman = 64,
	CEyeballBoss = 44,
	CTFViewModel = 240,
	CTFPumpkinBomb = 217,
	CTFBaseProjectile = 165,
	CBaseObjectUpgrade = 11,
	CTFItem = 188,
	CBonusRoundLogic = 20,
	CTFGameRulesProxy = 185,
	CTETFParticleEffect = 161,
	CTETFExplosion = 160,
	CTETFBlood = 159,
	CCaptureFlagReturnIcon = 24,
	CCaptureFlag = 23,
	CTFTeam = 239,
	CTFPlayerResource = 207,
	CTFPlayer = 206,
	CTFRagdoll = 218,
	CTEPlayerAnimEvent = 147,
	CTFObjectiveResource = 198,
	CTEFireBullets = 134,
	CTFBuffBanner = 0,
	CTFAmmoPack = 163,
	CObjectTeleporter = 76,
	CObjectSentrygun = 75,
	CTFProjectile_SentryRocket = 216,
	CObjectSapper = 74,
	CObjectCartDispenser = 72,
	CObjectDispenser = 73,
	CMonsterResource = 71,
	CFuncRespawnRoomVisualizer = 58,
	CFuncRespawnRoom = 57,
	CCaptureZone = 25,
	CBaseObject = 10,
	CTestTraceline = 158,
	CTEWorldDecal = 162,
	CTESpriteSpray = 156,
	CTESprite = 155,
	CTESparks = 154,
	CTESmoke = 153,
	CTEShowLine = 151,
	CTEProjectedDecal = 149,
	CTEPlayerDecal = 148,
	CTEPhysicsProp = 146,
	CTEParticleSystem = 145,
	CTEMuzzleFlash = 144,
	CTELargeFunnel = 141,
	CTEKillPlayerAttachments = 140,
	CTEImpact = 139,
	CTEGlowSprite = 138,
	CTEShatterSurface = 150,
	CTEFootprintDecal = 136,
	CTEFizz = 135,
	CTEExplosion = 133,
	CTEEnergySplash = 132,
	CTEEffectDispatch = 131,
	CTEDynamicLight = 130,
	CTEDecal = 128,
	CTEClientProjectile = 127,
	CTEBubbleTrail = 126,
	CTEBubbles = 125,
	CTEBSPDecal = 124,
	CTEBreakModel = 123,
	CTEBloodStream = 122,
	CTEBloodSprite = 121,
	CTEBeamSpline = 120,
	CTEBeamRingPoint = 119,
	CTEBeamRing = 118,
	CTEBeamPoints = 117,
	CTEBeamLaser = 116,
	CTEBeamFollow = 115,
	CTEBeamEnts = 114,
	CTEBeamEntPoint = 113,
	CTEBaseBeam = 112,
	CTEArmorRicochet = 111,
	CTEMetalSparks = 143,
	CSteamJet = 105,
	CSmokeStack = 99,
	DustTrail = 266,
	CFireTrail = 46,
	SporeTrail = 273,
	SporeExplosion = 272,
	RocketTrail = 270,
	SmokeTrail = 271,
	CPropVehicleDriveable = 91,
	ParticleSmokeGrenade = 269,
	CParticleFire = 77,
	MovieExplosion = 267,
	CTEGaussExplosion = 137,
	CEnvQuadraticBeam = 39,
	CEmbers = 32,
	CEnvWind = 43,
	CPrecipitation = 90,
	CBaseTempEntity = 16,
	NextBotCombatCharacter = 268,
	CWeaponIFMSteadyCam = 263,
	CWeaponIFMBaseCamera = 262,
	CWeaponIFMBase = 261,
	CTFWearable = 252,
	CTFWearableItem = 254,
	CEconWearable = 31,
	CBaseAttributableItem = 3,
	CEconEntity = 30,
	CHandleTest = 63,
	CTeamplayRoundBasedRulesProxy = 108,
	CTeamRoundTimer = 109,
	CSpriteTrail = 104,
	CSpriteOriented = 103,
	CSprite = 102,
	CRagdollPropAttached = 94,
	CRagdollProp = 93,
	CPoseController = 89,
	CInfoLadderDismount = 65,
	CFuncLadder = 53,
	CEnvDetailController = 36,
	CWorld = 265,
	CWaterLODControl = 260,
	CWaterBullet = 259,
	CVoteController = 258,
	CVGuiScreen = 257,
	CPropJeep = 0,
	CPropVehicleChoreoGeneric = 0,
	CTest_ProxyToggle_Networkable = 157,
	CTesla = 152,
	CTeamTrainWatcher = 110,
	CBaseTeamObjectiveResource = 15,
	CTeam = 107,
	CSun = 106,
	CParticlePerformanceMonitor = 78,
	CSpotlightEnd = 101,
	CSlideshowDisplay = 98,
	CShadowControl = 97,
	CRopeKeyframe = 95,
	CRagdollManager = 92,
	CPhysicsPropMultiplayer = 83,
	CPhysBoxMultiplayer = 81,
	CBasePropDoor = 14,
	CDynamicProp = 29,
	CPointCommentaryNode = 88,
	CPointCamera = 87,
	CPlayerResource = 86,
	CPlasma = 85,
	CPhysMagnet = 84,
	CPhysicsProp = 82,
	CPhysBox = 80,
	CParticleSystem = 79,
	CMaterialModifyControl = 70,
	CLightGlow = 69,
	CInfoOverlayAccessor = 67,
	CFuncTrackTrain = 61,
	CFuncSmokeVolume = 60,
	CFuncRotating = 59,
	CFuncReflectiveGlass = 56,
	CFuncOccluder = 55,
	CFuncMonitor = 54,
	CFunc_LOD = 50,
	CTEDust = 129,
	CFunc_Dust = 49,
	CFuncConveyor = 52,
	CBreakableSurface = 22,
	CFuncAreaPortalWindow = 51,
	CFish = 47,
	CEntityFlame = 34,
	CFireSmoke = 45,
	CEnvTonemapController = 42,
	CEnvScreenEffect = 40,
	CEnvScreenOverlay = 41,
	CEnvProjectedTexture = 38,
	CEnvParticleScript = 37,
	CEntityParticleTrail = 35,
	CEntityDissolve = 33,
	CDynamicLight = 28,
	CColorCorrectionVolume = 27,
	CColorCorrection = 26,
	CBreakableProp = 21,
	CInfoLightingRelative = 66,
	CAI_BaseNPC = 0,
	CBeam = 18,
	CBaseParticleEntity = 12,
	CBaseGrenade = 9,
};

#endif