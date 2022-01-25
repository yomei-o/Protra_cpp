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

#ifndef DF_INDEXUPDATOR_H_
#define DF_INDEXUPDATOR_H_

#include <string>
#include <filesystem>

#include "PriceDataUpdator.h"
#include "DateTime.h"

namespace Protra {
namespace Lib {
namespace Update {


class IndexUpdator:public PriceDataUpdator{
public:
	Protra::Lib::Data::DateTime getIndexDate(std::string fn) {
		Protra::Lib::Data::DateTime dt;
		FILE* fp;
		int yy, mm, dd;
		char buf[256];
		fp = fopen(fn.c_str(), "rb");
		if (fp == NULL)return dt;
		buf[0] = 0;
		fgets(buf, sizeof(buf), fp);
		fclose(fp);
		yy = 0; mm = 0; dd = 0;
		sscanf(buf, "date=%04d%02d%02d", &yy, &mm, &dd);
		dt = Protra::Lib::Data::DateTime(yy, mm, dd);
		return dt;
	}
	int Update() override {
		int ret;
		Protra::Lib::Data::DateTime d_tmp, d_data;
		std::string path_base = getBaseDir();
		std::string fn_index = "index.txt";

		std::string path_tmp = path_base+"/"+"tmp";
		std::string path_data = path_base + "/" + "data";

		std::filesystem::create_directory(path_tmp);
		std::filesystem::create_directory(path_data);

		std::string path_tmp_index = path_tmp + "/" + fn_index;
		std::string path_data_index = path_data + "/" + fn_index;

		DownloadUtil du("http://protra.sourceforge.jp/data/index.txt.lzh", fn_index, path_tmp,COMPTYPE_LHA);
		ret=du.DownloadAndExtract();
		if (ret)return ret;

		d_tmp = getIndexDate(path_tmp_index);
		d_data = getIndexDate(path_data_index);
		if (d_data.Value < d_tmp.Value) {
			std::filesystem::copy_file(path_tmp_index, path_data_index);
		}
		std::filesystem::remove(path_tmp_index);
		ret=0;
		return ret;
	}
};


}
}
}




#endif

