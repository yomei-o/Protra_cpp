// these should be top
#include "js_include.h"
#ifndef JAVASCRIPT
#include "variant.h"
#endif

// cgi include are 2rd 
#if 0
#ifdef JAVASCRIPT
include("webptsim.exe__QUERY__");
#else
#include "webptsim.h"
#endif
#endif

//#include "result.h"

// jquery should be 3rd
#ifdef JAVASCRIPT
include("jquery-1.11.3.js");
#endif

// other headers
#include "js_query.h"
#include "jq_bridge.h"

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

var data = null;
var data2 = null;
var data_lbl = null;
var data_tit = null;


//
// graph 
// 

#ifdef JAVASCRIPT
var ex_chart = null;
#endif

#ifdef JAVASCRIPT
function drawGraph(id, lbl_, v1_, v2_,tit)
#else
void drawGraph(var id, var lbl_, var v1_, var v2_,var tit)
#endif
{
	var dt,dtsets,ct=0;
		
	dtsets = new Array();

#ifdef JAVASCRIPT
	dt = {};
#else
	dt = new Array();
#endif
	dt["label"] = tit[0];
	dt["data"] = v1_;
	dt["borderColor"] = "rgba(100, 255, 100, 1)";
	dtsets[0] = dt;

	if (v2_ != null && strlength(v2_) > 0) {
#ifdef JAVASCRIPT
		dt = {};
#else
		dt = new Array();
#endif
		dt["label"] = tit[1];
		dt["data"] = v2_;
		dt["borderColor"] = "rgba(255, 100, 100, 1)";
		dtsets[1] = dt;
	}

#ifdef JAVASCRIPT
	var ctx = document.getElementById(id);
	var data = {
	labels: lbl_,
#if 1
	datasets : dtsets,
#endif
#if 0
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
#endif
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
// array 
// 

#ifdef JAVASCRIPT
function getKabukaCSV()
#else
var getKabukaCSV()
#endif
{
	var str="";
	str += "日付,簿価,時価\n";
	str += "01/03/2000,0,0\n";
	str += "17/03/2000,0,0\n";
	str += "06/04/2000,0,0\n";
	str += "24/04/2000,0,0\n";
	str += "16/05/2000,0,0\n";
	str += "01/06/2000,0,0\n";
	str += "20/06/2000,0,0\n";
	str += "06/07/2000,0,0\n";
	str += "26/07/2000,0,0\n";
	str += "11/08/2000,0,0\n";
	str += "30/08/2000,0,0\n";
	str += "18/09/2000,0,0\n";
	str += "05/10/2000,0,0\n";
	str += "24/10/2000,0,0\n";
	str += "13/11/2000,0,0\n";
	str += "30/11/2000,0,0\n";
	str += "19/12/2000,0,0\n";
	str += "10/01/2001,0,0\n";
	str += "29/01/2001,0,0\n";
	str += "15/02/2001,0,-52500\n";
	str += "06/03/2001,-96600,-96600\n";
	str += "23/03/2001,-96600,-96600\n";
	str += "11/04/2001,-96600,-96600\n";
	str += "27/04/2001,-96600,-96600\n";
	str += "21/05/2001,-96600,-96600\n";
	str += "06/06/2001,-96600,-96600\n";
	str += "25/06/2001,-96600,-96600\n";
	str += "11/07/2001,-96600,-96600\n";
	str += "31/07/2001,-96600,-96600\n";
	str += "16/08/2001,-96600,-96600\n";
	str += "04/09/2001,-96600,-96600\n";
	str += "21/09/2001,-96600,-96600\n";
	str += "11/10/2001,-96600,-96600\n";
	str += "30/10/2001,-96600,-96600\n";
	str += "15/11/2001,-96600,-96600\n";
	str += "05/12/2001,-96600,-96600\n";
	str += "21/12/2001,-96600,-96600\n";
	str += "17/01/2002,-96600,-96600\n";
	str += "04/02/2002,-96600,-96600\n";
	str += "22/02/2002,-96600,-96600\n";
	str += "12/03/2002,-96600,-96600\n";
	str += "01/04/2002,-96600,-96600\n";
	str += "17/04/2002,-96600,-96600\n";
	str += "09/05/2002,-96600,-96600\n";
	str += "27/05/2002,-96600,-96600\n";
	str += "13/06/2002,-96600,-139800\n";
	str += "01/07/2002,-96600,-125400\n";
	str += "18/07/2002,-96600,-125400\n";
	str += "05/08/2002,-96600,-156600\n";
	str += "22/08/2002,-171000,-171000\n";
	str += "09/09/2002,-171000,-171000\n";
	str += "30/09/2002,-171000,-171000\n";
	str += "17/10/2002,-171000,-171000\n";
	str += "06/11/2002,-171000,-171000\n";
	str += "22/11/2002,-171000,-171000\n";
	str += "11/12/2002,-171000,-171000\n";
	str += "30/12/2002,-171000,-171000\n";
	str += "23/01/2003,-171000,-171000\n";
	str += "10/02/2003,-171000,-171000\n";
	str += "28/02/2003,-171000,-171000\n";
	str += "19/03/2003,-171000,-171000\n";
	str += "07/04/2003,-171000,-171000\n";
	str += "24/04/2003,-171000,-171000\n";
	str += "14/05/2003,-171000,-171000\n";
	str += "02/06/2003,-171000,-182600\n";
	str += "18/06/2003,-171000,-188400\n";
	str += "07/07/2003,-171000,-115900\n";
	str += "24/07/2003,-171000,-197100\n";
	str += "12/08/2003,-197100,-197100\n";
	str += "28/08/2003,-197100,-264300\n";
	str += "17/09/2003,-255900,-255900\n";
	str += "06/10/2003,-255900,-255900\n";
	str += "24/10/2003,-255900,-255900\n";
	str += "12/11/2003,-255900,-255900\n";
	str += "02/12/2003,-255900,-255900\n";
	str += "18/12/2003,-255900,-255900\n";
	str += "13/01/2004,-255900,-255900\n";
	str += "29/01/2004,-255900,-255900\n";
	str += "18/02/2004,-255900,-255900\n";
	str += "05/03/2004,-255900,-255900\n";
	str += "24/03/2004,-255900,-255900\n";
	str += "09/04/2004,-255900,-255900\n";
	str += "28/04/2004,-255900,-255900\n";
	str += "20/05/2004,-255900,-255900\n";
	str += "08/06/2004,-255900,-255900\n";
	str += "24/06/2004,-255900,-255900\n";
	str += "13/07/2004,-255900,-266700\n";
	str += "30/07/2004,-255900,130200\n";
	str += "18/08/2004,-255900,122100\n";
	str += "03/09/2004,16800,16800\n";
	str += "24/09/2004,16800,16800\n";
	str += "14/10/2004,16800,16800\n";
	str += "01/11/2004,16800,48300\n";
	str += "19/11/2004,16800,144900\n";
	str += "08/12/2004,16800,79800\n";
	str += "28/12/2004,10500,10500\n";
	str += "18/01/2005,10500,10500\n";
	str += "04/02/2005,10500,-10500\n";
	str += "23/02/2005,-12600,-12600\n";
	str += "14/03/2005,-12600,-12600\n";
	str += "31/03/2005,-12600,-44600\n";
	str += "19/04/2005,-64600,-64600\n";
	str += "11/05/2005,-64600,-64600\n";
	str += "30/05/2005,-64600,-64600\n";
	str += "15/06/2005,-64600,-64600\n";
	str += "04/07/2005,-64600,-64600\n";
	str += "21/07/2005,-64600,-64600\n";
	str += "09/08/2005,-64600,-64600\n";
	str += "25/08/2005,-64600,-64600\n";
	str += "13/09/2005,-64600,-43600\n";
	str += "03/10/2005,-64600,-41500\n";
	str += "21/10/2005,-64600,-43600\n";
	str += "09/11/2005,-75100,-75100\n";
	str += "29/11/2005,-75100,-75100\n";
	str += "15/12/2005,-75100,-75100\n";
	str += "06/01/2006,-75100,-75100\n";
	str += "25/01/2006,-83900,-83900\n";
	str += "13/02/2006,-83900,-83900\n";
	str += "01/03/2006,-83900,-83900\n";
	str += "20/03/2006,-83900,-83900\n";
	str += "07/04/2006,-83900,-83900\n";
	str += "25/04/2006,-83900,-116900\n";
	str += "17/05/2006,-83900,-130100\n";
	str += "02/06/2006,-110300,-110300\n";
	str += "21/06/2006,-110300,-110300\n";
	str += "07/07/2006,-110300,-110300\n";
	str += "27/07/2006,-110300,-110300\n";
	str += "14/08/2006,-110300,-110300\n";
	str += "31/08/2006,-110300,-122300\n";
	str += "19/09/2006,-110300,-127100\n";
	str += "06/10/2006,-129500,-129500\n";
	str += "25/10/2006,-129500,-129500\n";
	str += "14/11/2006,-129500,-129500\n";
	str += "01/12/2006,-129500,-129500\n";
	str += "20/12/2006,-129500,-129500\n";
	str += "11/01/2007,-129500,-129500\n";
	str += "30/01/2007,-129500,-129500\n";
	str += "16/02/2007,-129500,-129500\n";
	str += "07/03/2007,-129500,-129500\n";
	str += "26/03/2007,-129500,-129500\n";
	str += "12/04/2007,-129500,-129500\n";
	str += "01/05/2007,-129500,-129500\n";
	str += "22/05/2007,-129500,-129500\n";
	str += "07/06/2007,-129500,-129500\n";
	str += "26/06/2007,-129500,-129500\n";
	str += "12/07/2007,-129500,-129500\n";
	str += "01/08/2007,-129500,-129500\n";
	str += "17/08/2007,-129500,-129500\n";
	str += "05/09/2007,-129500,-129500\n";
	str += "25/09/2007,-129500,-129500\n";
	str += "15/10/2007,-129500,-129500\n";
	str += "01/11/2007,-129500,-129500\n";
	str += "19/11/2007,-129500,-129500\n";
	str += "07/12/2007,-129500,-129500\n";
	str += "26/12/2007,-129500,-129500\n";
	str += "21/01/2008,-129500,-129500\n";
	str += "06/02/2008,-129500,-129500\n";
	str += "26/02/2008,-129500,-129500\n";
	str += "13/03/2008,-129500,-129500\n";
	str += "02/04/2008,-129500,-129500\n";
	str += "18/04/2008,-129500,-129500\n";
	str += "12/05/2008,-129500,-129500\n";
	str += "28/05/2008,-129500,-129500\n";
	str += "16/06/2008,-129500,-129500\n";
	str += "02/07/2008,-129500,-129500\n";
	str += "22/07/2008,-129500,-129500\n";
	str += "07/08/2008,-129500,-129500\n";
	str += "26/08/2008,-129500,-148700\n";
	str += "11/09/2008,-129500,-155100\n";
	str += "02/10/2008,-187100,-187100\n";
	str += "21/10/2008,-187100,-187100\n";
	str += "10/11/2008,-187100,-203600\n";
	str += "27/11/2008,-187100,-249800\n";
	str += "16/12/2008,-243200,-243200\n";
	str += "07/01/2009,-243200,-243200\n";
	str += "27/01/2009,-243200,-243200\n";
	str += "13/02/2009,-243200,-216000\n";
	str += "04/03/2009,-243200,-219400\n";
	str += "23/03/2009,-243200,-73200\n";
	str += "09/04/2009,-243200,-107200\n";
	str += "28/04/2009,-243200,-1800\n";
	str += "20/05/2009,-243200,-32400\n";
	str += "08/06/2009,-243200,25400\n";
	str += "24/06/2009,32200,32200\n";
	str += "13/07/2009,32200,32200\n";
	str += "30/07/2009,32200,32200\n";
	str += "18/08/2009,32200,59700\n";
	str += "03/09/2009,32200,152200\n";
	str += "25/09/2009,32200,94700\n";
	str += "14/10/2009,72200,72200\n";
	str += "02/11/2009,72200,72200\n";
	str += "19/11/2009,72200,72200\n";
	str += "09/12/2009,72200,72200\n";
	str += "28/12/2009,72200,72200\n";
	str += "19/01/2010,72200,72200\n";
	str += "04/02/2010,72200,72200\n";
	str += "24/02/2010,72200,72200\n";
	str += "12/03/2010,72200,72200\n";
	str += "01/04/2010,72200,72200\n";
	str += "19/04/2010,72200,72200\n";
	str += "12/05/2010,72200,72200\n";
	str += "28/05/2010,72200,72200\n";
	str += "16/06/2010,72200,72200\n";
	str += "02/07/2010,29000,29000\n";
	str += "22/07/2010,11900,11900\n";
	str += "09/08/2010,11900,11900\n";
	str += "26/08/2010,11900,11900\n";
	str += "13/09/2010,11900,11900\n";
	str += "04/10/2010,11900,11900\n";
	str += "21/10/2010,11900,11900\n";
	str += "10/11/2010,11900,15700\n";
	str += "30/11/2010,11900,38500\n";
	str += "16/12/2010,11900,48000\n";
	str += "07/01/2011,11900,74600\n";
	str += "26/01/2011,11900,127800\n";
	str += "15/02/2011,57500,57500\n";
	str += "03/03/2011,57500,57500\n";
	str += "23/03/2011,57500,57500\n";
	str += "08/04/2011,57500,57500\n";
	str += "27/04/2011,57500,57500\n";
	str += "19/05/2011,57500,57500\n";
	str += "07/06/2011,57500,57500\n";
	str += "23/06/2011,57500,57500\n";
	str += "12/07/2011,57500,57500\n";
	str += "29/07/2011,57500,57500\n";
	str += "17/08/2011,57500,57500\n";
	str += "02/09/2011,57500,57500\n";
	str += "22/09/2011,57500,57500\n";
	str += "12/10/2011,57500,57500\n";
	str += "31/10/2011,57500,57500\n";
	str += "17/11/2011,57500,57500\n";
	str += "07/12/2011,57500,57500\n";
	str += "26/12/2011,57500,57500\n";
	str += "17/01/2012,57500,57500\n";
	str += "02/02/2012,57500,57500\n";
	str += "21/02/2012,57500,57500\n";
	str += "08/03/2012,57500,72000\n";
	str += "28/03/2012,57500,54600\n";
	str += "13/04/2012,51700,51700\n";
	str += "07/05/2012,51700,51700\n";
	str += "24/05/2012,51700,51700\n";
	str += "11/06/2012,51700,51700\n";
	str += "28/06/2012,51700,51700\n";
	str += "17/07/2012,51700,51700\n";
	str += "03/08/2012,51700,51700\n";
	str += "21/08/2012,51700,51700\n";
	str += "07/09/2012,51700,51700\n";
	str += "26/09/2012,51700,51700\n";
	str += "16/10/2012,51700,51700\n";
	str += "01/11/2012,51700,51700\n";
	str += "20/11/2012,51700,51700\n";
	str += "07/12/2012,51700,51700\n";
	str += "27/12/2012,51700,51700\n";
	str += "21/01/2013,51700,51700\n";
	str += "07/02/2013,51700,51700\n";
	str += "26/02/2013,51700,51700\n";
	str += "15/03/2013,51700,51700\n";
	str += "03/04/2013,51700,51700\n";
	str += "22/04/2013,51700,51700\n";
	str += "13/05/2013,51700,51700\n";
	str += "30/05/2013,51700,-29900\n";
	str += "17/06/2013,-46900,-46900\n";
	str += "04/07/2013,-46900,-46900\n";
	str += "23/07/2013,-46900,-46900\n";
	str += "09/08/2013,-46900,-46900\n";
	str += "27/08/2013,-46900,-46900\n";
	str += "13/09/2013,-46900,-46900\n";
	str += "03/10/2013,-46900,-46900\n";
	str += "23/10/2013,-46900,-46900\n";
	str += "11/11/2013,-46900,-46900\n";
	str += "28/11/2013,-46900,-46900\n";
	str += "17/12/2013,-46900,-59800\n";
	str += "09/01/2014,-46900,52000\n";
	str += "29/01/2014,-46900,4700\n";
	str += "17/02/2014,-72700,-72700\n";
	str += "06/03/2014,-72700,-72700\n";
	str += "25/03/2014,-72700,-72700\n";
	str += "11/04/2014,-72700,-72700\n";
	str += "30/04/2014,-72700,-72700\n";
	str += "21/05/2014,-72700,-72700\n";
	str += "06/06/2014,-72700,-72700\n";
	str += "25/06/2014,-72700,-72700\n";
	str += "11/07/2014,-72700,-72700\n";
	str += "31/07/2014,-72700,-72700\n";
	str += "18/08/2014,-72700,-72700\n";
	str += "04/09/2014,-72700,-72700\n";
	str += "24/09/2014,-72700,-72700\n";
	str += "14/10/2014,-72700,-72700\n";
	str += "30/10/2014,-72700,-72700\n";
	str += "19/11/2014,-72700,-72700\n";
	str += "08/12/2014,-72700,-72700\n";
	str += "26/12/2014,-72700,-72700\n";
	str += "19/01/2015,-72700,-72700\n";
	str += "05/02/2015,-72700,-72700\n";
	str += "24/02/2015,-72700,-28700\n";
	str += "13/03/2015,-72700,-68700\n";
	str += "31/03/2015,-72700,-72700\n";
	str += "17/04/2015,-84700,-84700\n";
	str += "11/05/2015,-84700,-84700\n";
	str += "28/05/2015,-84700,-84700\n";
	return str;
}


#ifdef JAVASCRIPT
function readCSVLabel(str)
#else
var readCSVLabel(var& str)
#endif
{
	var idx;
	var tmp,t;
	var ret = new Array();
	var pos=0,ct=0;
	idx = str.indexOf("\n");
	if (idx == -1)return ret;
	tmp = str.substring(0, idx);
	if (tmp.indexOf(",")==-1)return ret;
	while (true) {
		if (tmp == "")break;
		idx = tmp.indexOf(",",pos);
		if (idx != -1) {
			t = tmp.substring(pos, idx);
		}
		else t = tmp.substring(pos);
		if (t.indexOf("#") == -1) {
			ret[ct] = t;
			ct++;
		}
		if (idx == -1)break;
		pos = idx + 1;
	}
	return ret;
}

#ifdef JAVASCRIPT
function readCSVFlag(str)
#else
var readCSVFlag(var& str)
#endif
{
	var idx;
	var tmp, t;
	var ret = new Array();
	var pos = 0, ct = 0;
	idx = str.indexOf("\n");
	if (idx == -1)return ret;
	tmp = str.substring(0, idx);
	if (tmp.indexOf(",") == -1)return ret;
	while (true) {
		if (tmp == "")break;
		idx = tmp.indexOf(",", pos);
		if (idx != -1) {
			t = tmp.substring(pos, idx);
		}
		else t = tmp.substring(pos);
		if (t.indexOf("#") == -1) {
			ret[ct] = 1;
			ct++;
		}
		else {
			ret[ct] = 0;
			ct++;
		}
		if (idx == -1)break;
		pos = idx + 1;
	}
	return ret;
}

#ifdef JAVASCRIPT
function readCSVData2(str)
#else
var readCSVData2(var& str)
#endif
{
	var idx,idx2,i,sz;
	var tmp, t;
	var ret = new Array();
	var ret2;
	var pos = 0,pos2=0, ct = 0,ct2=0,ct3=0;

	var isl,isl2;


	isl = readCSVFlag(str);
	isl2 = readCSVLabel(str);
	sz = strlength(isl2);

	idx = str.indexOf("\n");
	if (idx == -1)return ret;
	pos2 = idx + 1;
	while (true) {
		idx2 = str.indexOf("\n",pos2);
		if (idx2 != -1) {
			tmp = str.substring(pos2, idx2);
		}
		else {
			tmp = str.substring(pos2);
		}
		if (tmp.indexOf(",") == -1)return ret;
		ret2 = new Array();
		while (true) {
			if (tmp == "")break;
			idx = tmp.indexOf(",", pos);
			if (idx != -1) {
				t = tmp.substring(pos, idx);
			}
			else t = tmp.substring(pos);
			if (t == "") {
				t = "0";
			}
			if (isl[ct] == 1) {
				if (ct2 == 0) {
					ret2[ct2] = t;
				}
				else{
					ret2[ct2] = parseFloat(t);
				}
				ct2++;
			}
			ct++;
			if (idx == -1)break;
			pos = idx + 1;
		}
		if (ct2 == sz) {
			for (i = 0; i < ct2; i++) {
				ret[ct3] = ret2[i];
				ct3++;
			}
		}
		if (idx2 == -1)break;
		ct = 0; ct2 = 0;
		pos2 = idx2 + 1;
		pos = 0;
		
	}
	return ret;
}

#ifdef JAVASCRIPT
function arrayCol(arr,w,pos)
#else
var arrayCol(var& arr,var w,var pos)
#endif
{
	var sz;
	var ret;
	var ct = 0;
	ret = new Array();
	sz = strlength(arr);

	while (pos < sz) {
		ret[ct] = arr[pos];
		ct++;
		pos += w;
	}
	return ret;
}

#ifdef JAVASCRIPT
function arrayMean(arr)
#else
var arrayMean(var& arr)
#endif
{
	var sz,i;
	var ret=0;
	sz = strlength(arr);
	for (i = 0; i < sz; i++) {
		ret += arr[i];
	}
	return parseFloat(ret)/sz;
}

#ifdef JAVASCRIPT
function arrayVariance(arr)
#else
var arrayVariance(var& arr)
#endif
{
	var sz, i,t;
	var mean;
	var ret = 0.0;
	mean = arrayMean(arr);
	sz = strlength(arr);
	for (i = 0; i < sz; i++) {
		t= arr[i]-mean;
		t = t * t;
		ret += t;
	}
	ret /= parseFloat(sz);
	return ret;
}

#ifdef JAVASCRIPT
function arraySD(arr)
#else
var arraySD(var& arr)
#endif
{
	var ret;
	ret=arrayVariance(arr);
	ret = Math.sqrt(ret);
	return ret;
}

#ifdef JAVASCRIPT
function arrayCovariance(arr,arr2)
#else
var arrayCovariance(var& arr, var& arr2)
#endif
{
	var sz, i, t;
	var m1,m2;
	var ret = 0.0;
	m1 = arrayMean(arr);
	m2 = arrayMean(arr2);
	sz = strlength(arr);
	for (i = 0; i < sz; i++) {
		t = (arr[i] - m1);
		t *=arr2[i]-m2;
		ret += t;
	}
	ret /= parseFloat(sz);
	return ret;
}

#ifdef JAVASCRIPT
function arrayCorrel(arr, arr2)
#else
var arrayCorrel(var& arr, var& arr2)
#endif
{
	var ret;
	ret = arrayCovariance(arr, arr2);
	ret /= arraySD(arr);
	ret /= arraySD(arr2);
	return ret;
}



#ifdef JAVASCRIPT
function calc(str)
#else
void calc(var str)
#endif
{
	var lbl, n,tmp;
	lbl = readCSVLabel(str);
	n = strlength(lbl);
	if (n <2) {
		return;
	}

	data = null;
	data2 = null;
	tmp = readCSVData2(str);
	data_lbl = arrayCol(tmp, n, 0);
	data = arrayCol(tmp,n,1);
	data_tit = new Array();
	data_tit[0] = lbl[1];
	if (n >= 3) {
		data2 = arrayCol(tmp, n, 2);
		data_tit[1] = lbl[2];
	}
}

//
// event 
// 

#ifdef JAVASCRIPT
function evalString(str)
#else
void evalString(var str)
#endif
{
#ifdef JAVASCRIPT
	try {
		(0, eval)(str);
	}
	catch (e) {

	}
#endif
}


#ifdef JAVASCRIPT
function onClickExecButton(param)
#else
void onClickExecButton(var param)
#endif
{
	var str,str2;
	data_tit = null;
	data = null;
	data2 = null;
	data_lbl = null;
	str = jqbGetVal("#text01");
	calc(str);
	if (data_lbl == null)return;
	drawGraph("ex_chart", data_lbl, data,data2,data_tit);
}

#ifdef JAVASCRIPT
function onClickClearButton(param)
#else
void onClickClearButton(var param)
#endif
{
	var str;
	str= getKabukaCSV();
	jqbSetVal("#text01",str);

	data_tit = null;
	data_lbl = null;
	data = null;
	data2 = null;
	calc(str);
	if (data_lbl == null)return;
	drawGraph("ex_chart", data_lbl, data, data2,data_tit);
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
	var str;
	jqbCreateClickEvent("#btn01", onClickExecButton, "");
	jqbCreateClickEvent("#btn02", onClickClearButton, "");
	str = getKabukaCSV();
	jqbSetVal("#text01", str);
	calc(str);
	if (data_lbl == null)return;
	drawGraph("ex_chart",data_lbl,data,data2,data_tit);
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
	return 0;
}
#endif

