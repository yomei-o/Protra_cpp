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

#ifndef DF_STREAMREADER_H_
#define DF_STREAMREADER_H_

#include <stdio.h>
#include <string.h>
#include <string>
#include <stdexcept>
#include "zengoopen.h"


class StreamReader {
public:
	StreamReader() 
	{
		f = 0;
		fp = NULL;
		pos = 0;
	}
	virtual ~StreamReader()
	{
		f = 1;
		Close();
	}
	StreamReader(const char* nm)
	{
		f = 0;
		fp = NULL;
		pos = 0;
		filename = nm;
	}
	StreamReader(std::string& nm)
	{
		f = 0;
		fp = NULL;
		pos = 0;
		filename = nm;
	}
	StreamReader(const StreamReader& o_)
	{
		StreamReader& o = (StreamReader&)o_;

		o.Copy();
		fp = NULL;
		filename = o.filename;
		pos = o.pos;
		f = o.f;

	}
	StreamReader& operator=(const StreamReader& o_) {
		StreamReader& o = (StreamReader&)o_;
		if (fp)fclose(fp);

		o.Copy();
		fp = NULL;
		filename = o.filename;
		pos = o.pos;
		f = o.f;
		return *this;
	}
	void Close()
	{
		f = 1;
		if (fp)fclose(fp);
		fp = NULL;
	}
	void Copy()
	{
		if (fp) {
			pos = ftell(fp);
			fclose(fp);
		}
		fp = NULL;
	}
	std::string ReadLine() {
		std::string ret;
		char buf[1024];
		char* p;
		if (f)return ret;
		if (fp == NULL) {
			//fp = fopen(filename.c_str(), "rb");
			fp = zengo_protra_open(filename.c_str(), "rb");
			if(fp)fseek(fp, pos, SEEK_SET);
		}
		if (fp == NULL) {
			throw std::runtime_error("file cannot open.");
			return ret;
		}
		while (1) {
			memset(buf, 0, sizeof(buf));
			p=fgets(buf,sizeof(buf) - 1, fp);
			if (p == NULL) {
				return ret;
			}
			p = strchr(buf, '\r');
			if (p)*p = 0;
			p = strchr(buf, '\n');
			if (p)*p = 0;
			if (buf[0] == 0) {
				ret = " ";
				break;
			}
			ret = buf;
			break;
		}
		return ret;
	}
private:
	FILE* fp;
	std::string filename;
	int pos;
	int f;
};


#endif

