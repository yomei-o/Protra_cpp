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
// $Id: Global.cs 389 2010-11-28 06:45:45Z panacoran $

#ifndef DF_ZENGO_H_
#define DF_ZENGO_H_

#include <stdio.h>
#include <string.h>

inline FILE* zengo_open(const char* file, const char* mode, const char* path)
{
	FILE* ret = NULL;
	char buf[4096];
	if (file == NULL || mode == NULL || path == NULL)return ret;

	if (strlen(file) > 1000)return ret;
	if (strlen(path) > 1000)return ret;

	sprintf(buf, "%s/%s", path, file);
	ret = fopen(buf, mode);
	if (ret != NULL)return ret;

	sprintf(buf, "../%s/%s", path, file);
	ret = fopen(buf, mode);
	if (ret != NULL)return ret;

	sprintf(buf, "../../%s/%s", path, file);
	ret = fopen(buf, mode);
	if (ret != NULL)return ret;

	ret = fopen(file, mode);
	if (ret != NULL)return ret;

	sprintf(buf, "../%s", file);
	ret = fopen(buf, mode);
	if (ret != NULL)return ret;

	return ret;
}

inline FILE* zengo_price_open(const char* file, const char* mode, const char* path)
{
	FILE* ret = NULL;
	int t = 0;
	char buf[2028];

	if (file == NULL || mode == NULL || path == NULL)return ret;
	if (strlen(file) > 1000)return ret;
	if (strlen(path) > 1000)return ret;

	sprintf(buf, "%s/price", path);
	ret = zengo_open(file, mode, buf);
	if (ret)return ret;

	sscanf(file, "%d", &t);
	if (t >= 1000 && t <= 9999) {
		sprintf(buf, "%s/price/%c", path,file[0]);
		ret=zengo_open(file, mode, buf);
		if (ret)return ret;
	}
	return zengo_open(file, mode, path);
}


inline FILE* zengo_protra_open(const char* file, const char* mode)
{
	FILE* ret = NULL;
	int t = 0;
	char buf[2028];

	if (file == NULL || mode == NULL)return ret;
	if (strlen(file) > 1000)return ret;

	ret = zengo_open(file, mode, "data");
	if (ret)return ret;

	ret = zengo_open(file, mode,"lib");
	if (ret)return ret;

	ret = zengo_open(file, mode, "system");
	return ret;
}

#endif


