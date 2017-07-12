/*    
    MProcList.exe : Display the current running processes
    Copyright (C) 2017  Comine.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


//v1.0 copyright Comine.com 20170712W1243
#include "MStdLib.h"
#include "MWinProcessList.h"
#include "MLicenseGPL.h"
#include "MCommandArg.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MProcList";	// Used in Help
static const char *GApplicationVersion="1.0";	// Used in Help

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
				"   usage:  %s [-?|-gpl] [-u] [-f] [-s] \n"
				"           v%s copyright Comine.com\n"
				"           -gpl Displays the GPL license\n"
				"\n"
				"           Display all running process Identifiers\n"
				"\n"
				"   flags:\n"
				"              -u   : Show User SID\n"
				"              -f   : Show full path to process\n"
				"              -s   : Show Session ID\n"
				"\n"
				,GApplicationName,GApplicationVersion);
	}


