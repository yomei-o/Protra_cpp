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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <vector>
#include <filesystem>

#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif /* _WIN32 */

#ifdef _WIN32
#include<fcntl.h>
#include <io.h>
#endif

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#define PREAD "rb"
#else
#define PREAD "r"
#endif

#ifdef _MSC_VER
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#pragma warning( disable : 4819 )
#endif
#endif

#include "kanji.h"
#include "mutex.h"

//
//  binarymode
//
static void setstdoutmode()
{
#ifdef WIN32
	_setmode(_fileno(stdout), _O_BINARY);
#endif

}

//
//
//

void mygetenv(char* buf, const char* moji, int sz)
{
	char* p;
	if (buf == NULL || moji == NULL || sz < 1)return;
	p = getenv(moji);
	if (p == NULL)p = (char*)"";

	buf[0] = 0;
	strncpy(buf, p, sz);
	buf[sz - 1] = 0;

}

void urldecode2(char* dst, const char* src)
{
	char a, b;
	while (*src) {
		if ((*src == '%') &&
			((a = src[1]) && (b = src[2])) &&
			(isxdigit(a) && isxdigit(b))) {
			if (a >= 'a')
				a -= 'a' - 'A';
			if (a >= 'A')
				a -= ('A' - 10);
			else
				a -= '0';
			if (b >= 'a')
				b -= 'a' - 'A';
			if (b >= 'A')
				b -= ('A' - 10);
			else
				b -= '0';
			*dst++ = 16 * a + b;
			src += 3;
		}
		else if (*src == '+') {
			*dst++ = ' ';
			src++;
		}
		else {
			*dst++ = *src++;
		}
	}
	*dst++ = '\0';
}

//
// query
//

int get_query_val_int(const char* query, const char* str)
{
	char* p;
	int ret = -1;
	char tmp[128];
	int len;

	if (query == NULL || str == NULL)return ret;
	len = strlen(str);
	if (len > 100)return ret;

	strcpy(tmp, str);
	strcat(tmp, "=");
	p = (char*)strstr(query, tmp);
	if (p != query) {
		strcpy(tmp, "&");
		strcat(tmp, str);
		strcat(tmp, "=");
		p = (char*)strstr(query, tmp);
	}
	if (p) {
		sscanf(p + strlen(tmp), "%d", &ret);
		return ret;
	}
	return ret;
}

void get_query_val_string(const char* query, const char* str, char* buf, int sz)
{
	char* p;
	int ret = -1;
	char tmp[128];
	int len;
	if (query == NULL || str == NULL || buf == NULL || sz < 1)return;
	len = strlen(str);
	buf[0] = 0;
	if (len > 100)return;

	strcpy(tmp, str);
	strcat(tmp, "=");
	p = (char*)strstr(query, tmp);
	if (p != query) {
		strcpy(tmp, "&");
		strcat(tmp, str);
		strcat(tmp, "=");
		p = (char*)strstr(query, tmp);
	}
	if (p) {
		strncpy(buf, p + strlen(tmp), sz);
		buf[sz - 1] = 0;
	}
	p = strstr(buf, "&");
	if (p)*p = 0;


	urldecode2(buf, buf);
}

//
// print
//

static void print(const char* p)
{
	if (p == NULL)return;
	printf("%s\r\n", p);
}
static void printheader(const char* p)
{
	char buf[256];
	if (p == NULL)return;
	sprintf(buf, "Content-Type: %s", p);
	print(buf);
	print((char*)"");
}

//
// 
// 

void cmd_hello()
{
	printheader("text/javascript");

	print("declare_var_begin(result = null, result);");
	printf("result=\"%s\";\n", "hello");
	print("declare_var_end(result);");
	printf("\n");

}

std::string ReplaceString(std::string String1,std::string String2,std::string String3)
{
	std::string::size_type  Pos(String1.find(String2));

	while (Pos != std::string::npos)
	{
		String1.replace(Pos, String2.length(), String3);
		Pos = String1.find(String2, Pos + String3.length());
	}
	return String1;
}

FILE* zengo_open(const char* file, const char* mode, const char* path)
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

FILE* zengo_remove(const char* file,const char* path)
{
	FILE* ret = NULL;
	char buf[4096];
	if (file == NULL ||  path == NULL)return ret;

	if (strlen(file) > 1000)return ret;
	if (strlen(path) > 1000)return ret;

	sprintf(buf, "%s/%s", path, file);
	remove(buf);
	remove(file);

	return ret;
}

void cmd_exec(const char* str,const char* code)
{
	printheader("text/javascript");
	unsigned char buf[1024 * 64];
	unsigned short buf2[1024 * 64];
	char cmd[1024];
	FILE* fp;

	zengo_remove("protra.pt","data");
	zengo_remove("log.csv", "data");

	fp = fopen("protra.pt","wt");
	if (fp) {
		fwrite(str, 1, strlen(str), fp);
		fclose(fp);
	}
	memset(buf, 0, sizeof(buf));
	sprintf(cmd,"PtsimConsole -a log.csv protra.pt %s", code);
	fp = popen(cmd,PREAD);
	if (fp) {
		fread(buf, 1, sizeof(buf) - 1,fp);
		pclose(fp);
	}
	memset(buf2, 0, sizeof(buf2));
	kj_cp932_to_unicode(buf, buf2);
	memset(buf, 0, sizeof(buf));
	kj_unicode_to_utf8_n(buf2,buf,sizeof(buf));
	std::string s = (char*)buf;

	s = ReplaceString(s, "\r", "");
	s = ReplaceString(s, "\n", "\\n");
	s = ReplaceString(s, "\"", "\\\"");

	memset(buf, 0, sizeof(buf));
	fp = zengo_open("log.csv", "rb","data");
	if (fp) {
		fread(buf, 1, sizeof(buf) - 1, fp);
		fclose(fp);
	}

	memset(buf2, 0, sizeof(buf2));
	kj_cp932_to_unicode(buf, buf2);
	memset(buf, 0, sizeof(buf));
	kj_unicode_to_utf8_n(buf2, buf, sizeof(buf));
	std::string s2 = (char*)buf;

	s2 = ReplaceString(s2, "\r", "");
	s2 = ReplaceString(s2, "\n", "\\n");
	s2 = ReplaceString(s2, "\"", "\\\"");

	print("declare_var_begin(result = null, result);");
	printf("result=\"%s\";\n",s.c_str());
	print("declare_var_end(result);");
	printf("\n");

	print("declare_var_begin(result2 = null, result2);");
	printf("result2=\"%s\";\n", s2.c_str());
	print("declare_var_end(result2);");
	printf("\n");

	print("declare_var_begin(result3 = null, result3);");
	printf("result3=\"%s\";\n", "");
	print("declare_var_end(result3);");
	printf("\n");

	print("declare_var_begin(lbl = null, lbl);");
	printf("lbl=\"%s\";\n", "");
	print("declare_var_end(lbl);");
	printf("\n");

	print("declare_var_begin(v1 = null, v1);");
	printf("v1=\"%s\";\n", "");
	print("declare_var_end(v1);");
	printf("\n");

	print("declare_var_begin(v2 = null, v2);");
	printf("v2=\"%s\";\n", "");
	print("declare_var_end(v2);");
	printf("\n");
}

void print_gtaph_js(const char* fn)
{
	char buf[256];
	char buf2[256];
	std::vector<std::string> lbl;
	std::vector<int> v1;
	std::vector<int> v2;

	FILE* fp;
	int t1, t2;
	fp = zengo_open(fn, "rt","data");
	if (fp == NULL)return;
	while (1) {
		buf[0] = 0;
		fgets(buf, sizeof(buf), fp);
		if (buf[0] == 0)break;
		buf2[0] = 0; t1 = 0; t2 = 0;
		sscanf(buf, "%[^,],%d,%d", buf2, &t1, &t2);
		lbl.push_back(buf2);
		v1.push_back(t1);
		v2.push_back(t2);
	}
	fclose(fp);

	int kosu = 300;
	int sz, n;

	sz = lbl.size();
	printf("declare_var_begin(lbl = null, lbl);\n");
	printf("var lbl=new Array();\n");
	if (sz)for (int i = 0; i < kosu; i++) {
		n = sz * i / kosu;
		printf("lbl[%d]=\"%s\";\n", i, lbl[n].c_str());
	}
	printf("declare_var_end(lbl);\n");
	printf("\n");

	sz = v1.size();
	printf("declare_var_begin(v1 = null, v1);\n");
	printf("var v1=new Array();\n");
	if (sz)for (int i = 0; i < kosu; i++) {
		n = sz * i / kosu;
		printf("v1[%d]=%d;\n", i, v1[n]);
	}
	printf("declare_var_end(v1);\n");
	printf("\n");

	sz = v2.size();
	printf("declare_var_begin(v2 = null, v2);\n");
	printf("var v2=new Array();\n");
	if (sz)for (int i = 0; i < kosu; i++) {
		n = sz * i / kosu;
		printf("v2[%d]=%d;\n", i, v2[n]);
	}
	printf("declare_var_end(v2);\n");
	printf("\n");

}


void cmd_perf(const char* str, const char* code)
{
	printheader("text/javascript");
	unsigned char buf[1024 * 64];
	unsigned short buf2[1024 * 64];
	char cmd[1024];
	FILE* fp;

	zengo_remove("protra.pt","data");
	zengo_remove("log.csv", "data");
	zengo_remove("graph.csv", "data");

	fp = fopen("log.csv", "wt");
	if (fp) {
		fwrite(str, 1, strlen(str), fp);
		fclose(fp);
	}
	memset(buf, 0, sizeof(buf));
	sprintf(cmd, "PtsimConsole -l log.csv -g graph.csv");
	fp = popen(cmd, PREAD);
	if (fp) {
		fread(buf, 1, sizeof(buf) - 1, fp);
		pclose(fp);
	}
	memset(buf2, 0, sizeof(buf2));
	kj_cp932_to_unicode(buf, buf2);
	memset(buf, 0, sizeof(buf));
	kj_unicode_to_utf8_n(buf2, buf, sizeof(buf));
	std::string s = (char*)buf;

	s = ReplaceString(s, "\r", "");
	s = ReplaceString(s, "\\", "\\\\");
	s = ReplaceString(s, "\n", "\\n");
	s = ReplaceString(s, "\"", "\\\"");

	print("declare_var_begin(result = null, result);");
	printf("result=\"%s\";\n", "");
	print("declare_var_end(result);");
	printf("\n");

	print("declare_var_begin(result2 = null, result2);");
	printf("result2=\"%s\";\n", "");
	print("declare_var_end(result2);");
	printf("\n");

	print("declare_var_begin(result3 = null, result3);");
	printf("result3=\"%s\";\n", s.c_str());
	print("declare_var_end(result3);");
	printf("\n");

	print_gtaph_js("graph.csv");
	
}


//
//
//
int main(int argc,char* argv[], char* envp[])
{
#if defined(_WIN32) && !defined(__GNUC__)
	//	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
	//	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
	//	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	setstdoutmode();
	char query[1024 * 64];
	char str[1024 * 64];
	char cmd[1024];
	char code[1024];

	query[0] = 0;
	str[0] = 0;
	cmd[0] = 0;
	code[0] = 0;

	mygetenv(query, "QUERY_STRING", sizeof(query));
	get_query_val_string(query, "cmd", cmd, sizeof(cmd));
	get_query_val_string(query, "str", str, sizeof(str));
	get_query_val_string(query, "code", code, sizeof(code));

	mutex_t mt = create_mutex((char*)"ptoraweb");
	if (mt)get_mutex(mt);
	if (strcmp(cmd, "exec") == 0) {
		cmd_exec(str,code);
	}
	else if (strcmp(cmd, "perf") == 0) {
		cmd_perf(str, code);
	}
	else {
		cmd_hello();
	}

	if (mt)release_mutex(mt);
	if (mt)close_mutex(mt);

	return 0;
}


