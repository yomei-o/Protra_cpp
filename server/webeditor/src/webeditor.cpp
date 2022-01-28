// these should be top
#include "js_include.h"
#ifndef JAVASCRIPT
#include "variant.h"
#endif

// cgi include are 2rd 
#ifdef JAVASCRIPT
include("webptsim.exe__QUERY__");
#else
#include "webptsim.h"
#endif

// jquery should be 3rd
#ifdef JAVASCRIPT
include("jquery-1.11.3.js");
#endif

// other headers
#include "js_query.h"
#include "jq_bridge.h"
#include "script.h"

// debug 
#ifndef JAVASCRIPT
#if defined(_WIN32) && !defined(__GNUC__)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif /* _WIN32 */
#endif

//
// 
// 

var editorKey01 = "editorKey01";
var editorKey02 = "editorKey02";
var logStr = "";
var resultStr = "";
var codeList = "";
var execStr = "";
var defCode = "1301\n1333\n1378";
//
//
//
#ifdef JAVASCRIPT 
downloadString = function(name,str)
#else
void downloadString(var name,var str)
#endif
{
#ifdef JAVASCRIPT 
	const blob = new Blob([str], { type: 'text/plain' });
	const a = document.createElement('a');
	a.href = URL.createObjectURL(blob);
	a.download = name;
	a.click();
#else
#endif
}
 
//
//
//
#ifdef JAVASCRIPT
var ex_chart = null;
#endif

#ifdef JAVASCRIPT
function drawGraph(id, lbl_, v1_, v2_)
#else
void drawGraph(var id, var lbl_, var v1_, var v2_)
#endif
{
#ifdef JAVASCRIPT
	var ctx = document.getElementById(id);
	var data = {
	labels: lbl_,
	datasets : [
		{
		label: '簿価',
		data : v1_,
		borderColor : 'rgba(100, 255, 100, 1)'
		},
		{
		label: '時価',
		data : v2_,
		borderColor : 'rgba(255, 100, 100, 1)'
		}
	]
	};

	var options = {};
	if (ex_chart != null) {
		ex_chart.destroy();
	}
	ex_chart = new Chart(ctx, {
	type: 'line',
	data : data,
	options : options
		});
#else
	println("drawGrapg()");
#endif
}


//
// event
//


#ifdef JAVASCRIPT 
onClickDownload = function(param)
#else
void onClickDownload(var param)
#endif
{
	var str;
	str=jqbGetVal("#text01");
	downloadString("system.pt", str);
}

#ifdef JAVASCRIPT 
onChangeText01 = function(param)
#else
void onChangeText01(var param)
#endif
{
	var str;
	str = jqbGetVal("#text01");
	localStorage.setItem(editorKey01,str);
}

#ifdef JAVASCRIPT 
onChangeText02 = function(param)
#else
void onChangeText02(var param)
#endif
{
	var str;
	str = jqbGetVal("#text02");
	localStorage.setItem(editorKey02, str);
}



#ifdef JAVASCRIPT 
onLoadText01 = function(param)
#else
void onLoadText01(var param)
#endif
{
	var str;
	str=localStorage.getItem(editorKey01);
	jqbSetVal("#text01",str);
}

#ifdef JAVASCRIPT 
onLoadText02 = function(param)
#else
void onLoadText02(var param)
#endif
{
	var str;
	str = localStorage.getItem(editorKey02);
	jqbSetVal("#text02", str);
}

#ifdef JAVASCRIPT 
onTimeout = function(param)
#else
void onTimeout(var param)
#endif
{
	var str, code,idx;
	//println("onTimeOut");

	idx = codeList.indexOf("\n");
	if (idx != -1) {
		code = codeList.substring(0, idx);
		codeList = codeList.substring(idx + 1);
	}
	else {
		code = codeList;
		codeList = "";
	}
	if (code == "") {
		codeList = "";
		return;
	}
	//println("code=" + code);

	str = createQueryValue("cmd", "exec");
	str += appendQueryValue("code", code);
	str += appendQueryValue("str", execStr);
	setQuery(str);
	jumpLocation2(myName());
}

#ifdef JAVASCRIPT 
onClickExec = function(param)
#else
void onClickExec(var param)
#endif
{
	var str,t;

	logStr = "";
	resultStr = "";
	execStr = jqbGetVal("#text01");
	codeList = jqbGetVal("#text02");
	jqbSetVal("#text03", "");
	jqbSetVal("#text04", "");
	jqbSetVal("#text05", "");
#ifdef JAVASCRIPT 
	setTimeout(onTimeout, 500);
#endif
}

#ifdef JAVASCRIPT 
onClickPerf = function(param)
#else
void onClickPerf(var param)
#endif
{
	var str, t;

	jqbSetVal("#text05", "");
	str = createQueryValue("cmd", "perf");
	t = jqbGetVal("#text04");
	str += appendQueryValue("str", t);
	setQuery(str);
	jumpLocation2(myName());
}

#ifdef JAVASCRIPT 
onClickClear = function(param)
#else
void onClickClear(var param)
#endif
{
	jqbSetVal("#text01", script);
	jqbSetVal("#text02", defCode);
	jqbSetVal("#text03", "");
	jqbSetVal("#text04", "");
	jqbSetVal("#text05", "");
	lbl = new Array();
	v1 = new Array();
	v2 = new Array();
	drawGraph("ex_chart", lbl, v1, v2);
}

#ifdef JAVASCRIPT 
onClickCopyright = function(param)
#else
void onClickCopyright(var param)
#endif
{
	println("Webeditor Rev.20220128_002");
}



#ifdef JAVASCRIPT
onJumpLocation2 = function()
#else
void onJumpLocation2()
#endif
{
	//println("kita");
	if (result != "") {
		resultStr = resultStr + result;
		jqbSetVal("#text03", resultStr);
	}
	if (result2 != "") {
		logStr = logStr + result2;
		jqbSetVal("#text04", logStr);
	}
	if (result3 != "") {
		jqbSetVal("#text05", result3);
	}
	if (lbl != "" && v1 != "" && v2 != "") {
		drawGraph("ex_chart", lbl, v1, v2);
	}
	if (codeList != "") {
#ifdef JAVASCRIPT 
		setTimeout(onTimeout, 500);
#endif
	}
}

//
// main javascript
//


#ifndef JAVASCRIPT
void main_main() {
#endif




#ifndef JAVASCRIPT
}
#endif

#ifdef JAVASCRIPT 
jQuery().ready(function()
#else
void jquery_ready()
#endif
{
	jqbCreateChangeEvent("#text01", onChangeText01, 0);
	jqbCreateChangeEvent("#text02", onChangeText02, 0);
	jqbCreateClickEvent("#btn03", onClickDownload, 0);
	jqbCreateClickEvent("#btn04", onClickExec, 0);
	jqbCreateClickEvent("#btn05", onClickPerf, 0);
	jqbCreateClickEvent("#btn06", onClickClear, 0);
	jqbCreateClickEvent("#copyright", onClickCopyright, 0);
	onLoadText01("");
	onLoadText02("");

	if (jqbGetVal("#text01") == "") {
		jqbSetVal("#text01", script);
	}
	if (jqbGetVal("#text02") == "") {
		jqbSetVal("#text02", defCode);
	}

}
#ifdef JAVASCRIPT 
);
#endif



#ifndef JAVASCRIPT
int main(int argc, char* argv[])
{
	println("---- init----");
	main_main();
	println("---- ready ----");
	jquery_ready();
	//test();
	return 0;
}
#endif

