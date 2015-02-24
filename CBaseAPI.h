#pragma once

#include <Windows.h>

//Original CBaseAPI class by P47TR!CK

class CBaseAPI
{

	HANDLE hDebugConsole;
	DWORD dwMessage;

public:
	DWORD dwFindPattern ( DWORD dwAddress, DWORD dwLength, const char* szPattern );
	HMODULE GetModuleHandleSafe ( const char* pszModuleName );
	void LogToFile ( const char * pszMessage, ... );
	DWORD GetClientSignature ( char* chPattern );
	DWORD GetEngineSignature ( char* chPattern );
	void ErrorBox ( char* error );
	void BuildDebugConsole ( void );
	void LogToConsole ( const char * pszMessage, ... );
	void ColorLogToConsole ( const WORD color, const char * pszMessage, ... );
};

extern CBaseAPI gBaseAPI;