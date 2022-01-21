// Copyright (C) 2022 Yomei Otani <yomei.otani@gmail.com>
// 
// This program is part of Protra.
//
// Protra is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
// 

#ifndef DF_STREAMWRITER_H_
#define DF_STREAMWRITER_H_

#include <stdio.h>
#include <string.h>
#include <string>
#include <stdexcept>
#include "zengoopen.h"


class StreamWriter {
public:
	StreamWriter() 
	{
		f = 0;
		fp = NULL;
	}
	virtual ~StreamWriter()
	{
		f = 1;
		Close();
	}
	StreamWriter(const char* nm)
	{
		f = 0;
		fp = NULL;
		filename = nm;
	}
	StreamWriter(std::string& nm)
	{
		f = 0;
		fp = NULL;
		filename = nm;
	}
	StreamWriter(const StreamWriter& o_)
	{
		StreamWriter& o = (StreamWriter&)o_;
		fp = NULL;
		filename = o.filename;
		f = o.f;

	}
	void Close()
	{
		f = 1;
		if (fp)fclose(fp);
		fp = NULL;
	}
	void WriteLine(std::string str) {
		if (f)return;
		if (fp == NULL) {
			fp = zengo_protra_open(filename.c_str(), "wt");
		}
		if (fp == NULL) {
			throw std::runtime_error("file cannot open.");
			return;
		}
		fprintf(fp,"%s\n",str.c_str());
	}
private:
	FILE* fp;
	std::string filename;
	int f;
};


#endif

