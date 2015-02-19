#pragma once

#include <Windows.h>
#include "getvfunc.h"
// Seperate header for all things related to cvars
// SDK.h == far to messy

#define MakePtr( Type, dwBase, dwOffset ) ( ( Type )( DWORD( dwBase ) + (DWORD)( dwOffset ) ) )

// __declspec(novtable) creates classes with no vtable!!
#define abstract_class class __declspec(novtable)

class ConVar;
class IConVar;
class ConVarRef;
class ConCommand;
class ICvar;


// copied from SDK
abstract_class IConVar
{
public:
	// Value set
	virtual void SetValue(const char *pValue) = 0;
	virtual void SetValue(float flValue) = 0;
	virtual void SetValue(int nValue) = 0;

	// Return name of command
	virtual const char *GetName(void) const = 0;

	// Accessors.. not as efficient as using GetState()/GetInfo()
	// if you call these methods multiple times on the same IConVar
	virtual bool IsFlagSet(int nFlag) const = 0;
};

// unknown class
// unable to find ANY vtable for it
// appears to be a base class for all other con related things
// according to sdk not abstract_class like the iconvar
class ConCommandBase
{

public:




};

class ConVar : public IConVar
{
	friend class ConVarRef;

	// all these values are stored in offsets 

	// parent
	ConVar	*m_pParent;

	// static
	const char	*m_pszDefaultValue;

	// Value
	// Dynamically allocated
	char	*m_pszString;
	int		m_StringLength;

	// Values
	float	*m_fValue = MakePtr(float *, this, 0x2C);
	int		*m_nValue = MakePtr(int *, this, 0x30);

	// Min/Max values
	bool	*m_bHasMin;
	float	*m_fMinVal;
	bool	*m_bHasMax;
	float	*m_fMaxVal;


public:
	const char *GetName()
	{
		typedef const char *(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 4)(this);
	}
	void SetValue(const char *pValue)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const char *);
		return getvfunc<OriginalFn>(this, 10)(this, pValue);
	}
	void SetValue(float flValue)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, float);
		return getvfunc<OriginalFn>(this, 11)(this, flValue);
	}
	void SetValue(int iValue)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int);
		return getvfunc<OriginalFn>(this, 12)(this, iValue);
	}
	bool IsRegistered()
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 6)(this);
	}
	bool IsFlagSet(int iFlag)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, int);
		return getvfunc<OriginalFn>(this, 2)(this, iFlag);
	}
	bool IsCommand()
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return getvfunc<OriginalFn>(this, 1)(this);
	}
	void AddFlags(int iFlags)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int);
		getvfunc<OriginalFn>(this, 2)(this, iFlags);
	}
};

// non-virtual class
// helper wraper for ConVar class
class ConVarRef
{
public:
	ConVarRef(const char *pName)
	{
		Init(pName, false);
	}
	ConVarRef(const char *pName, bool bIgnoreMissing)
	{
		Init(pName, bIgnoreMissing);
	}
	ConVarRef(IConVar *pConVar) // setup from existing IConVar pointer
	{
		m_pConVar = pConVar; 
	}

	void Init(const char *pName, bool bIgnoreMissing)
	{
		// call findVar or something similar
	}
	bool IsValid() const
	{

	}
	bool IsFlagSet(int nFlags) const // check if flag is set
	{
		return (m_pConVar->IsFlagSet(nFlags) != 0);
	}
	IConVar *GetLinkedConVar() // return IConVar
	{
		return m_pConVar;
	}

	// Get/Set value
	float GetFloat(void) const // get as float
	{
		return *m_pConVarState->m_fValue;
	}
	int GetInt(void) const // get as int
	{
		return *m_pConVarState->m_nValue;
	}
	bool GetBool() const { return !!GetInt(); } // get as bool ( calls get as int internally )

	const char *GetString(void) const // get as char * - string
	{
		return m_pConVarState->m_pszString;
	}

	void SetValue(const char *pValue); // set as string
	void SetValue(float flValue); // set as float
	void SetValue(int nValue); // set as int
	void SetValue(bool bValue); // set as bool (maybe calls set as int internally?)

	const char *GetName() const // get name of convar
	{
		return m_pConVar->GetName();
	}

	const char *GetDefault() const // get default value of convar
	{
		return m_pConVarState->m_pszDefaultValue;
	}

private:
	// High-speed method to read convar data
	IConVar *m_pConVar;
	ConVar *m_pConVarState;
};

class ConCommand
{
public:

};

class ICvar
{
public:
	void ConsolePrintf(const char *pszMessage, ...)
	{
		//gBaseAPI.LogToConsole("ConsolePrintf: %s", pszMessage);

		typedef void(__stdcall* OriginalFn)(const char*, ...);
		getvfunc<OriginalFn>(this, 24)(pszMessage);
	}

	ConVar *FindVar(const char *var_name)
	{
		typedef ConVar *(__thiscall* OriginalFn)(PVOID, const char*);
		return getvfunc<OriginalFn>(this, 12)(this, var_name);
	}
};