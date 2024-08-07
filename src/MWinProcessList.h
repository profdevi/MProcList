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
#ifndef MWinProcessList_h
#define MWinProcessList_h

/////////////////////////////////////////////////
#include <Windows.h>
#include <WtsApi32.h>
#include "MStdLib.h"
#include "MString.h"


//******************************************************
//**  MWinProcessList class
//******************************************************
class MWinProcessList
	{
	////////////////////////////////////////////////
	WTS_PROCESS_INFO *mpInfo;
	int mProcCount;
	
	
	
	////////////////////////////////////////////////
	void ClearObject(void);

	////////////////////////////////////////////////
	public:
	MWinProcessList(bool create=false);
	~MWinProcessList(void);
	bool Create(void);
	bool Destroy(void);
	int GetCount(void) const;										// Get Count of processes
	int GetProcessID(int index) const ;
	int GetSessionID(int index) const;
	const PSID GetUserSID(int index) const;
	bool GetUserSIDString(int index,MString &usersid);				// Get SID as a string
	bool GetProcessName(int index,MString &procname) const;
	bool GetFullPath(int index,MString &fullpathname);				// Get Full Path to executable
	int FindProcessIndex(const char *processname);					// =pid of process with name,=-1(on failure)
	bool Print(bool printsid=false,bool printfullpath=false,bool printsessionid=false);
	};

#endif // MWinProcessList_h

