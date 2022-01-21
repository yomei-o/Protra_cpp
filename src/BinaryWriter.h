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

#ifndef DF_BINARYWRITER_H_
#define DF_BINARYWRITER_H_

#include <stdio.h>
#include <string.h>
#include <string>

#include "zengoopen.h"

class BinaryWriter {
public:
	BinaryWriter()
	{
		fp = NULL;
	}
	virtual ~BinaryWriter()
	{
		Close();
	}
	BinaryWriter(const char* nm)
	{
		fp = NULL;
		filename = nm;
	}
	BinaryWriter(std::string& nm)
	{
		fp = NULL;
		filename = nm;
	}
	void Close()
	{
		if (fp)fclose(fp);
		fp = NULL;
	}
	int isOpen()
	{
		if (fp)return 1;
		fp = zengo_protra_open(filename.c_str(), "wb");
		if (fp)return 1;
		return 0;
	}
	int WriteInt32(int v) {
		unsigned char buf[4];
		int sz;
		if(isOpen()==0)return -1;
		
		buf[0] = v;
		v >>= 8;
		buf[1] = v;
		v >>= 8;
		buf[2] = v;
		v >>= 8;
		buf[3] = v;
		sz=fwrite(buf, 1, 4, fp);
		return sz;
	}
	int WriteDouble(double v_) {
		unsigned char buf[8];
		int sz;
		long long v;
		v = *((long long*)&v_);
		if (isOpen() == 0)return -1;

		buf[0] = v;
		v >>= 8;
		buf[1] = v;
		v >>= 8;
		buf[2] = v;
		v >>= 8;
		buf[3] = v;
		v >>= 8;
		buf[4] = v;
		v >>= 8;
		buf[5] = v;
		v >>= 8;
		buf[6] = v;
		v >>= 8;
		buf[7] = v;
		sz = fwrite(buf, 1, 8, fp);
		return sz;
	}
private:
	FILE* fp;
	std::string filename;
};


#endif

