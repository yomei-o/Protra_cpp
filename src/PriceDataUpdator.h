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

#ifndef DF_PRICEDATAUPDATOR_H_
#define DF_PRICEDATAUPDATOR_H_

#include <stdio.h>
#include <string>
#include <filesystem>

namespace Protra {
namespace Lib {
namespace Update {

enum {
	COMPTYPE_UNCOMP,
	COMPTYPE_LHA,
	COMPTYPE_ZIP,
};

class DownloadUtil {
public:
	std::string url;
	std::string file;
	std::string path;
	int type; // 0:uncompress 1:lha 2:zip 

	static int wget(std::string url, std::string file)
	{
		char buf[1024];
		int ret;
		std::filesystem::remove(file);
		snprintf(buf,sizeof(buf),"wget --user-agent=\"%s\" -O %s %s","Protra Updator",file.c_str(),url.c_str());
		ret = system(buf);
		return ret;
	}
	static int lha(std::string file,std::string path)
	{
		char buf[1024];
		int ret;
		snprintf(buf, sizeof(buf), "lha x -f -w=%s %s",path.c_str(),file.c_str());
		ret = system(buf);
		return ret;
	}

	static int unzip(std::string file, std::string path)
	{
		char buf[1024];
		int ret;
		snprintf(buf, sizeof(buf), "unzip -o -d %s %s", path.c_str(), file.c_str());
		ret = system(buf);
		return ret;
	}

	DownloadUtil(std::string url_, std::string file_, std::string path_,int type_)
	{
		path = path_;
		file = file_;
		url = url_;
		type = type_;
		if (path == "")path = ".";

	}
	int DownloadAndExtract()
	{
		int ret;
		std::string fn_tmp;
		if (type == COMPTYPE_UNCOMP)
		{
			fn_tmp = file;
		}
		if (type == COMPTYPE_LHA) {
			fn_tmp = "tmp.lzh";
		}
		if(type== COMPTYPE_ZIP)
		{
			fn_tmp = "tmp.zip";
		}
		std::string path_tmp = path + "/" + fn_tmp;
		std::string path_out = path + "/" + file;
		
		if (path!=".." && path!=".") {
			std::filesystem::create_directory(path);
		}
		std::filesystem::remove(path_tmp);
		std::filesystem::remove(path_out);


		ret=wget(url, path_tmp);
		if (ret)return ret;
		if (type == COMPTYPE_LHA) {
			ret = lha(path_tmp, path);
			if (ret)return ret;
		}
		if(type==COMPTYPE_ZIP) {
			ret=unzip(path_tmp, path);
			if (ret)return ret;
		}
		ret=std::filesystem::exists(path_out);
		if (ret == 0)return 1;

		std::filesystem::remove(path_tmp);

		return 0;
	}

};


class PriceDataUpdator {
public:
	static int& getInt()
	{
		static int f = 0;
		return f;
	}
	static void set_stop()
	{
		getInt() = 1;
	}
	static int is_stop()
	{
		return getInt();
	}

	virtual std::string getBaseDir()
	{
		std::string ret = ".";
		return ret;
	}
	virtual int Update() {
		return 0;
	}
};


}
}
}




#endif

