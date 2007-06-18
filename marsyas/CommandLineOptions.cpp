/*
** Copyright (C) 1998-2005 George Tzanetakis <gtzan@cs.uvic.ca>
**  
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software 
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

/** 
\class CommandLineOptions
	\ingroup none
\brief CommandLineOptions

Class for handling command-line options 
*/

#include "CommandLineOptions.h"

using namespace std;
using namespace Marsyas;

CommandLineOptions::CommandLineOptions()
{
}

void 
CommandLineOptions::addBoolOption(string lname, string sname, bool value) 
{
	string dlname;
	dlname += "--";
	dlname += lname;

	string dsname;
	dsname += "-";
	dsname += sname;

	boolOptions_[dsname] = value;
	boolOptions_[dlname] = value;
	longNames_[dsname] = dlname;
}

void 
CommandLineOptions::addNaturalOption(string lname, string sname, mrs_natural value)
{
	string dlname;
	dlname += "--";
	dlname += lname;

	string dsname;
	dsname += "-";
	dsname += sname;

	naturalOptions_[dsname] = value;
	naturalOptions_[dlname] = value;
	longNames_[dsname] = dlname;
}

void 
CommandLineOptions::addRealOption(string lname,string sname,mrs_real value)
{
	string dlname;
	dlname += "--";
	dlname += lname;

	string dsname;
	dsname += "-";
	dsname += sname;

	realOptions_[dsname] = value;
	realOptions_[dlname] = value;
	longNames_[dsname] = dlname;
}

void 
CommandLineOptions::addStringOption(string lname,string sname,string value)
{
	string dlname;
	dlname += "--";
	dlname += lname;

	string dsname;
	dsname += "-";
	dsname += sname;

	stringOptions_[dsname] = value;
	stringOptions_[dlname] = value;
	longNames_[dsname] = dlname;
}

void 
CommandLineOptions::readOptions(int argc, const char **argv)
{
	for (int i=0; i < argc; i++)
	{
		arguments_.push_back(argv[i]);
	}

	string key;
	string argument;
	bool notFound = true;

	for (int i=1; i < argc; i++)
	{
		argument = arguments_[i];
		if (argument.substr(0,1) == "-")
		{
			notFound = true;

			nameIter_ = longNames_.find(arguments_[i]);
			if (nameIter_ != longNames_.end())
				key = nameIter_->second;
			else 
				key = arguments_[i];

			// look for option in boolOptions_ 
			biter_ = boolOptions_.find(key);
			if (biter_ != boolOptions_.end())
			{
				boolOptions_[key] = true;
				notFound = false;
			}

			niter_ = naturalOptions_.find(key);
			if (niter_ != naturalOptions_.end())
			{
				if (i < argc -1) 
					naturalOptions_[key] = atoi((arguments_[i+1]).c_str());
				i++;
				notFound = false;
			}

			riter_ = realOptions_.find(key);
			if (riter_ != realOptions_.end())
			{
				if (i < argc -1) 
					realOptions_[key] = (mrs_real)atof((arguments_[i+1]).c_str());
				i++;
				notFound = false;
			}

			siter_ = stringOptions_.find(key);
			if (siter_ != stringOptions_.end())
			{
				if (i < argc -1) 
					stringOptions_[key] = (arguments_[i+1]).c_str();
				i++;
				notFound = false;
			}

			if (notFound) 
				cout << "Option " << key << " was not found. It is ignored " << endl;
		}
		else
			remaining_.push_back(argument);
	}
}

bool 
CommandLineOptions::getBoolOption(string lname)
{
	return boolOptions_["--" + lname];
}

mrs_natural 
CommandLineOptions::getNaturalOption(string lname)
{
	return naturalOptions_["--" + lname];
}

mrs_real 
CommandLineOptions::getRealOption(string lname)
{
	return realOptions_["--" + lname];
}

string 
CommandLineOptions::getStringOption(string lname)
{
	return stringOptions_["--" + lname];
}

vector<string> 
CommandLineOptions::getRemaining()
{
	return remaining_;
}
