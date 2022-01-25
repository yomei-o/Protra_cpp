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

#ifndef DF_KAKUKAJOHOUPDATOR_H_
#define DF_KAKUKAJOHOUPDATOR_H_

#include <stdio.h>
#include <string>
#include <filesystem>

#include "PriceDataUpdator.h"
#include "DateTime.h"
#include "splitreplace.h"

namespace Protra {
namespace Lib {
namespace Update {


class KabukaJohoUpdator:public PriceDataUpdator{
public:
	static Protra::Lib::Data::DateTime Now() {
		Protra::Lib::Data::DateTime ret;
		time_t t = time(NULL);
		struct tm* tm=localtime(&t);
		ret = Protra::Lib::Data::DateTime(tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
		return ret;
	}
	static int Hour() 
	{
		time_t t = time(NULL);
		struct tm* tm = localtime(&t);
		return tm->tm_hour;
	}
	static Protra::Lib::Data::DateTime getMaxDate(std::string fn) {
		Protra::Lib::Data::DateTime dt;
		FILE* fp;
		unsigned char buf[256];
		int t;
		fp = fopen(fn.c_str(), "rb");
		if (fp == NULL)return dt;
		buf[0] = 0;
		fread(buf, 1, 4, fp);
		fclose(fp);
		t = buf[3];
		t <<= 8;
		t |= buf[2];
		t <<= 8;
		t |= buf[1];
		t <<= 8;
		t |= buf[0];
		dt = Protra::Lib::Data::DateTime(t);
		return dt;
	}
	static int setMaxDate(std::string fn, Protra::Lib::Data::DateTime dt) {
		FILE* fp;
		unsigned char buf[256];
		int t=dt.Value;
		fp = fopen(fn.c_str(), "wb");
		if (fp == NULL)return 1;
		buf[0] = t;
		t >>= 8;
		buf[1] = t;
		t >>= 8;
		buf[2] = t;
		t >>= 8;
		buf[3] = t;

		fwrite(buf, 1, 4, fp);
		fclose(fp);
		return 0;
	}
	static int writeInt(FILE* fp,int i)
	{
		char buf[4];
		buf[0] = i;
		i >>= 8;
		buf[1] = i;
		i >>= 8;
		buf[2] = i;
		i >>= 8;
		buf[3] = i;
		fwrite(buf,1, 4,fp);
		return 0;
	}
	static int writeDouble(FILE* fp,double d)
	{
		char buf[8];
		long long i;
		i = *((long long*)&d);

		buf[0] = i;
		i >>= 8;
		buf[1] = i;
		i >>= 8;
		buf[2] = i;
		i >>= 8;
		buf[3] = i;
		i >>= 8;
		buf[4] = i;
		i >>= 8;
		buf[5] = i;
		i >>= 8;
		buf[6] = i;
		i >>= 8;
		buf[7] = i;
		fwrite(buf, 1, 8, fp);
		return 0;
	}
	int Add(std::string path, std::string code, Protra::Lib::Data::DateTime dt, int d1, int d2, int d3, int d4, double d5) {
		int c=0;
		sscanf(code.c_str(), "%d", &c);
		if (c < 1000 || c>9999)return 1;
		c = c / 1000;
		std::string file = path + "/" + std::to_string(c) + "/" + code;
		FILE* fp = fopen(file.c_str(), "ab");
		if (fp == NULL)return 1;
		writeInt(fp, dt.Value);
		writeInt(fp, d1);
		writeInt(fp, d2);
		writeInt(fp, d3);
		writeInt(fp, d4);
		writeDouble(fp, d5);
		fclose(fp);

		file += ".csv";
		fp = fopen(file.c_str(), "at");
		if (fp == NULL)return 1;
		fprintf(fp,"%04d/%02d/%02d,%d,%d,%d,%d,%d\n",dt.Year,dt.Month,dt.Day,
			d1,d2,d3,d4,(int)d5);
		if (fp == NULL)return 1;
		fclose(fp);
		return 0;
	}
	int Update() override {
		int ret;
		Protra::Lib::Data::DateTime d_maxdate,d_now,d_pos;

		std::string path_base = getBaseDir();
		std::string fn_maxdate = "MaxDate";

		std::string path_tmp = path_base+"/"+"tmp";
		std::string path_data = path_base + "/" + "data";
		std::string path_price = path_data + "/" + "price";

		std::filesystem::create_directory(path_tmp);
		std::filesystem::create_directory(path_data);
		std::filesystem::create_directory(path_price);
		for (int i = 1; i <= 9; i++) {
			std::string path_kabu = path_price + "/"+std::to_string(i);
			std::filesystem::create_directory(path_kabu);
		}

		std::string path_price_maxdate = path_price + "/" + fn_maxdate;

		d_maxdate = getMaxDate(path_price_maxdate);
		d_maxdate = Protra::Lib::Data::DateTime(d_maxdate.Value + 1);
		d_now = Now();
		if (Hour() < 16)d_now = Protra::Lib::Data::DateTime(d_now.Value - 1);

		Protra::Lib::Data::DateTime dt_first(2001, 1, 4);
		//Protra::Lib::Data::DateTime dt_first(2020, 3, 4);
		if (d_maxdate.Value < dt_first.Value)d_maxdate = dt_first;

		while (d_maxdate.Value <= d_now.Value) {
			std::string url = "";
			std::string file = "";
			std::string path_csv;
			int yy, mm, dd;
			char buf_url[256];
			char buf_file[256];

			if (is_stop())break;

			if(d_maxdate.Value)
			if (d_maxdate.DayOfWeek == 0 || d_maxdate.DayOfWeek == 6) {
				goto next;
			}
			printf("####  %04d-%02d-%02d\n",d_maxdate.Year,d_maxdate.Month,d_maxdate.Day);
			yy = d_maxdate.Year % 100;
			mm = d_maxdate.Month;
			dd = d_maxdate.Day;

			if (d_maxdate.Year < 2006) {
				//http://www.edatalab.sakura.ne.jp/data2005/20050303.LZH
				sprintf(buf_url,"http://www.edatalab.sakura.ne.jp/data20%02d/20%02d%02d%02d.LZH",yy,yy,mm,dd);
				sprintf(buf_file, "20%02d%02d%02d.csv",yy, mm, dd);
			}
			else {
				//http://www.edatalab.sakura.ne.jp/data2020/D200304.LZH
				sprintf(buf_url, "http://www.edatalab.sakura.ne.jp/data20%02d/D%02d%02d%02d.LZH", yy, yy, mm, dd);
				sprintf(buf_file, "D%02d%02d%02d.csv", yy, mm, dd);
			}
			url = buf_url;
			file = buf_file;

			{
				DownloadUtil du(url, file, path_tmp, COMPTYPE_LHA);
				ret = du.DownloadAndExtract();
				if (ret) {
					goto next;
				}
			}

			path_csv = path_tmp + "/" + file;
			{
				int y, m, d, c;
				double d1, d2, d3, d4, d5;
				char name[256];
				FILE* fp = fopen(path_csv.c_str(), "rb");
				if (fp == NULL)goto next;
				while (1) {
					buf_file[0]=0;
					fgets(buf_file, sizeof(buf_file), fp);
					if (buf_file[0] == 0)break;
					std::string line = buf_file;
					std::vector<std::string>entries = split(line, ",");
					if (entries.size() < 8)continue;
					c = 0; y = 0; m = 0; d = 0;
					d1 = 0; d2 = 0; d3 = 0; d4 = 0; d5 = 0;
					sscanf(entries[0].c_str(), "%d/%d/%d", &y, &m, &d);
					sscanf(entries[1].c_str(), "%d", &c);
					sscanf(entries[3].c_str(), "%lf", &d1);
					sscanf(entries[4].c_str(), "%lf", &d2);
					sscanf(entries[5].c_str(), "%lf", &d3);
					sscanf(entries[6].c_str(), "%lf", &d4);
					sscanf(entries[7].c_str(), "%lf", &d5);
					if (d != dd || m != mm || y%100 != yy)continue;
					d5 /= 1000;
					Add(path_price,entries[1],d_maxdate, d1, d2, d3, d4, d5);
				}
				fclose(fp);
			}

			std::filesystem::remove(path_csv);
			setMaxDate(path_price_maxdate,d_maxdate);

next:
			d_maxdate = Protra::Lib::Data::DateTime(d_maxdate.Value + 1);
		}



		ret=0;
		return ret;
	}
};


}
}
}




#endif

