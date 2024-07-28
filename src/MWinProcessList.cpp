/*
Copyright (C) 2011-2024, Comine.com ( profdevi@ymail.com )
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
- The the names of the contributors of this project may not be used to 
  endorse or promote products derived from this software without specific 
  prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
`AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/


//v1.2 copyright Comine.com 20240728U1529
#include <Windows.h>
#include <WtsApi32.h>
#include <sddl.h>
#include "MStdLib.h"
#include "TVector.h"
#include "MString.h"
#include "MWinProcessList.h"


//******************************************************
//**  Module elements
//******************************************************
#pragma comment(lib,"Wtsapi32.lib")
#pragma comment(lib,"Advapi32.lib")

//******************************************************
//**  MWinProcessList class
//******************************************************
void MWinProcessList::ClearObject(void)
	{
	mpInfo=0;
	}


////////////////////////////////////////////////
MWinProcessList::MWinProcessList(bool create)
	{
	ClearObject();
	if(create==true && Create()==false)
		{
		return;
		}
	}


////////////////////////////////////////////////
MWinProcessList::~MWinProcessList(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MWinProcessList::Create(void)
	{
	Destroy();

	if(WTSEnumerateProcesses(WTS_CURRENT_SERVER_HANDLE,0,1,&mpInfo,(DWORD *)&mProcCount)==FALSE)
		{
		Destroy();
		return false;
		}

	return true;
	}


////////////////////////////////////////////////
bool MWinProcessList::Destroy(void)
	{
	if(mpInfo!=0)
		{
		WTSFreeMemory(mpInfo);
		mpInfo=0;
		}

	ClearObject();
	return true;
	}


/////////////////////////////////////////////////
int MWinProcessList::GetCount(void) const
	{
	return (int)mProcCount;
	}


////////////////////////////////////////////////
int MWinProcessList::GetProcessID(int index) const
	{
	MStdAssert(index>=0 && index<mProcCount);
	return (int) mpInfo[index].ProcessId;
	}


//////////////////////////////////////////////////
int MWinProcessList::GetSessionID(int index) const
	{
	MStdAssert(index>=0 && index<mProcCount);
	return (int) mpInfo[index].SessionId;
	}


////////////////////////////////////////////////
const PSID MWinProcessList::GetUserSID(int index) const
	{
	MStdAssert(index>=0 && index<mProcCount);
	return mpInfo[index].pUserSid;
	}


/////////////////////////////////////////////////
bool MWinProcessList::GetUserSIDString(int index,MString &usersid)
	{
	MStdAssert(index>=0 && index<mProcCount);

	PSID pusersid=mpInfo[index].pUserSid;
	if(pusersid==0) {  return false; }

	LPWSTR strsid=0;
	if(ConvertSidToStringSidW(mpInfo[index].pUserSid,&strsid)==FALSE)
		{
		return false;
		}

	if(usersid.Create(strsid)==false)
		{
		LocalFree(strsid);
		strsid=0;
		return false;
		}

	LocalFree(strsid);
	strsid=0;
	return true;
	}


/////////////////////////////////////////////////
bool MWinProcessList::GetProcessName(int index,MString &procname) const
	{
	MStdAssert(index>=0 && index<mProcCount);
	if(procname.Create(mpInfo[index].pProcessName)==false)
		{
		return false;
		}

	return true;
	}


//////////////////////////////////////////////////////////////
bool MWinProcessList::GetFullPath(int index,MString &fullpathname)
	{
	MStdAssert(index>=0 && index<mProcCount);
	const DWORD procid=mpInfo[index].ProcessId;
	HANDLE hprocess=OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION,FALSE,procid);
	if(hprocess==INVALID_HANDLE_VALUE)
		{
		return false;
		}

	TVector<char> buffer(MStdPathMaxSize);
	DWORD exepathlen=buffer.GetCount();
	if(QueryFullProcessImageNameA(hprocess,0,buffer.Get(),&exepathlen)==FALSE)
		{
		CloseHandle(hprocess);
		return false;
		}

	CloseHandle(hprocess);
	if(fullpathname.Create(buffer.Get())==false)
		{
		return false;
		}

	return true;	
	}


//////////////////////////////////////////////////////////
int MWinProcessList::FindProcessIndex(const char *processname)
	{
	for(int i=0;i<mProcCount;++i)
		{
		MString name;
		if(GetProcessName(i,name)==false)
			{
			continue;
			}

		if(MStdStrICmp(name.Get(),processname)!=0) { continue; }
		return i;
		}

	return -1;
	}


/////////////////////////////////////////////////////////
bool MWinProcessList::Print(bool printsid,bool printfullpath,bool printsessionid)
	{
	for(int i=0;i<mProcCount;++i)
		{
		MString procname;
		MString usersid;
		MString fullpath;
		if(GetProcessName(i,procname)==false ) { continue; }
		if(GetUserSIDString(i,usersid)==false) { usersid.Create(""); }
		if(GetFullPath(i,fullpath)==false) { fullpath.Create("");  }
	
		MStdPrintf("%5d ",GetProcessID(i));
		
		if(printsessionid==true) { MStdPrintf("SessID=%d  ",GetSessionID(i) );  }

		if(printfullpath==true)
			{  MStdPrintf("%s  ",fullpath.Get());  }
		else
			{  MStdPrintf("%s  ",procname.Get() );  }


		if(printsid==true) { MStdPrintf("SID=%s  ",usersid.Get());  }

		MStdPrintf("\n");
		}


	return true;
	}


