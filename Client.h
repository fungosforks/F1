#pragma once

#include "SDK.h"

#include "Players.h"

bool __fastcall Hooked_WriteUserCmdDeltaToBuffer ( PVOID pClient, int edx, DWORD* buf, int from, int to, bool isnewcommand );
void __fastcall Hooked_CreateMove ( PVOID pClient, int edx, int sequence_number, float input_sample_frametime, bool active );
void GetClassIDs ( );