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


//v1.1 copyright Comine.com 20240728U1532
#include "MStdLib.h"
#include "MWinProcessList.h"
#include "MLicenseGPL.h"
#include "MCommandArg.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MProcList";	// Used in Help
static const char *GApplicationVersion="1.1";	// Used in Help

////////////////////////////////////////////////////
static void GDisplayHelp(void);

////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);

	if(args.CheckRemoveHelp()==true)
		{
		GDisplayHelp();
		return 0;
		}

	if(args.CheckRemoveArg("-gpl")==true)
		{
		MLicenseGPL license(true);
		license.Print();
		return 0;
		}

	bool flaglongpath=false;
	if(args.CheckRemoveArg("-l")==true) { flaglongpath=true; }

	bool flagsessionid=false;
	if(args.CheckRemoveArg("-s")==true) { flagsessionid=true; }
	
	bool flagusersid=false;
	if(args.CheckRemoveArg("-u")==true) { flagusersid=true; }

	MWinProcessList proclist;
	if(proclist.Create()==false)
		{
		MStdPrintf("**Unable to init system\n");
		return 1;
		}

	proclist.Print(flagusersid,flaglongpath,flagsessionid);

	return 0;
	}


////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(	"\n"
				"   usage:  %s [-?|-gpl] [-u] [-l] [-s] \n"
				"           v%s copyright Comine.com\n"
				"           -gpl Displays the GPL license\n"
				"\n"
				"           Display all running process Identifiers\n"
				"\n"
				"   flags:\n"
				"              -u   : Show User SID\n"
				"              -l   : Show path to process\n"
				"              -s   : Show Session ID\n"
				"\n"
				,GApplicationName,GApplicationVersion);
	}


