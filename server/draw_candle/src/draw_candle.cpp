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

var data1 = null;
var data2 = null;
var data3 = null;
var data4 = null;
var data_lbl = null;

var data_tit = null;
var data = null;

//
// graph 
// 

#ifdef JAVASCRIPT
var ex_chart = null;
#endif

#ifdef JAVASCRIPT
function drawCandle(id, tit_,dt_)
#else
void drawCandle(var id, var tit_,var dt_)
#endif
{
	var i,sz,t,v;
	if (dt_ == null)return;
	sz = strlength(dt_);
	for (i = 0; i < sz; i++) {
		t=dt_[i]["x"];
#ifdef JAVASCRIPT
		v = 0;
		try {
			v = luxon.DateTime.fromFormat(t, "yyyy/LL/dd");
			v=v.toMillis(); 
		}
		catch (e) {}
		t = v;
#endif
		dt_[i]["x"] = t;
	}
#ifdef JAVASCRIPT
	var ctx = document.getElementById(id);

	var chart = new Chart(ctx, {
	 type: 'candlestick',
	 data : {
	  datasets: [
	   {
		label: tit_,
			//data : candles,
			data : data,
	   }
	  ]
	 },
	 options: {
	  responsive: true,
	  elements : {
	   point: {
	   radius: 0
	   }
	  }
	 }
	});
#else
	println("drawCandle()");
#endif
}

//
//
//

var candles;
var candle;

#ifdef JAVASCRIPT
function test()
#else
void test()
#endif
{

#ifdef JAVASCRIPT
	candles = [];

	candle = new Object();
	candle.x = 86400 * 1000 * 1000;
	candle.o = 100;
	candle.h = 200;
	candle.l = 50;
	candle.c = 120;
	candles[0] = candle;

	candle = new Object();
	candle.x = 86400 * 1000 * 1000 + 86400 * 1000;
	candle.o = 200;
	candle.h = 220;
	candle.l = 100;
	candle.c = 150;
	candles[1] = candle;

	candle = new Object();
	candle.x = 86400 * 1000 * 1000 + 86400 * 1000 * 2;
	candle.o = 200;
	candle.h = 220;
	candle.l = 100;
	candle.c = 150;
	candles[2] = candle;
#endif

}



//
// array 
// 

#ifdef JAVASCRIPT
function getTopixCSV()
#else
var getTopixCSV()
#endif
{
	var str = "";
	str += "日時,Open,High,Low,Close,Quant\n";
	str += "2021/11/01,29330,29666,29267,29647,0\n";
	str += "2021/11/02,29462,29599,29457,29520,0\n";
	str += "2021/11/04,29859,29880,29718,29794,0\n";
	str += "2021/11/05,29840,29840,29504,29611,0\n";
	str += "2021/11/08,29735,29735,29507,29507,0\n";
	str += "2021/11/09,29557,29750,29240,29285,0\n";
	str += "2021/11/10,29209,29296,29079,29106,0\n";
	str += "2021/11/11,29046,29336,29040,29277,0\n";
	str += "2021/11/12,29381,29661,29381,29609,0\n";
	str += "2021/11/15,29807,29861,29718,29776,0\n";
	str += "2021/11/16,29749,29960,29681,29808,0\n";
	str += "2021/11/17,29906,29909,29623,29688,0\n";
	str += "2021/11/18,29597,29715,29402,29598,0\n";
	str += "2021/11/19,29641,29768,29589,29745,0\n";
	str += "2021/11/22,29618,29806,29542,29774,0\n";
	str += "2021/11/24,29663,29758,29212,29302,0\n";
	str += "2021/11/25,29469,29570,29444,29499,0\n";
	str += "2021/11/26,29324,29332,28605,28751,0\n";
	str += "2021/11/29,28337,28776,28187,28283,0\n";
	str += "2021/11/30,28611,28718,27819,27821,0\n";
	str += "2021/12/01,27866,28106,27594,27935,0\n";
	str += "2021/12/02,27716,27938,27644,27753,0\n";
	str += "2021/12/03,27841,28029,27588,28029,0\n";
	str += "2021/12/06,28069,28081,27693,27927,0\n";
	str += "2021/12/07,28138,28618,27961,28455,0\n";
	str += "2021/12/08,28792,28897,28621,28860,0\n";
	str += "2021/12/09,28827,28908,28725,28725,0\n";
	str += "2021/12/10,28542,28699,28392,28437,0\n";
	str += "2021/12/13,28705,28793,28593,28640,0\n";
	str += "2021/12/14,28554,28672,28309,28432,0\n";
	str += "2021/12/15,28358,28525,28358,28459,0\n";
	str += "2021/12/16,28868,29070,28782,29066,0\n";
	str += "2021/12/17,28854,28904,28503,28545,0\n";
	str += "2021/12/20,28325,28441,27893,27937,0\n";
	str += "2021/12/21,28309,28533,28226,28517,0\n";
	str += "2021/12/22,28614,28673,28473,28562,0\n";
	str += "2021/12/23,28703,28798,28640,28798,0\n";
	str += "2021/12/24,28836,28870,28773,28782,0\n";
	str += "2021/12/27,28786,28805,28658,28676,0\n";
	str += "2021/12/28,28953,29121,28879,29069,0\n";
	str += "2021/12/29,28995,29106,28729,28906,0\n";
	str += "2021/12/30,28794,28904,28579,28791,0\n";
	str += "2022/01/04,29098,29323,28954,29301,0\n";
	str += "2022/01/05,29288,29388,29204,29332,0\n";
	str += "2022/01/06,29136,29158,28487,28487,0\n";
	str += "2022/01/07,28711,28813,28293,28478,0\n";
	str += "2022/01/11,28380,28473,28089,28222,0\n";
	str += "2022/01/12,28449,28814,28427,28765,0\n";
	str += "2022/01/13,28658,28660,28444,28489,0\n";
	str += "2022/01/14,28246,28252,27889,28124,0\n";
	str += "2022/01/17,28332,28449,28274,28333,0\n";
	str += "2022/01/18,28451,28690,28129,28257,0\n";
	str += "2022/01/19,27928,27958,27314,27467,0\n";
	str += "2022/01/20,27401,27882,27217,27772,0\n";
	str += "2022/01/21,27404,27586,27129,27522,0\n";
	str += "2022/01/24,27258,27627,27203,27588,0\n";
	str += "2022/01/25,27466,27493,26890,27131,0\n";
	str += "2022/01/26,27105,27184,26858,27011,0\n";
	str += "2022/01/27,27139,27193,26044,26170,0\n";
	str += "2022/01/28,26429,26764,26289,26717,0\n";
	str += "2022/01/31,26690,27134,26541,27001,0\n";
	str += "2022/02/01,27167,27410,27016,27078,0\n";
	str += "2022/02/02,27302,27564,27289,27533,0\n";
	str += "2022/02/03,27330,27357,27165,27241,0\n";
	str += "2022/02/04,27095,27455,27075,27439,0\n";
	str += "2022/02/07,27327,27369,27085,27248,0\n";
	str += "2022/02/08,27318,27461,27280,27284,0\n";
	str += "2022/02/09,27488,27633,27405,27579,0\n";
	str += "2022/02/10,27818,27880,27575,27696,0\n";
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
	var lbl, i,n,tmp;
	lbl = readCSVLabel(str);
	n = strlength(lbl);
	if (n <5) {
		return;
	}

	data1 = null;
	data2 = null;
	data3 = null;
	data4 = null;
	tmp = readCSVData2(str);

	data = new Array();
	data_lbl = arrayCol(tmp, n, 0);
	data1 = arrayCol(tmp,n,1);
	data2 = arrayCol(tmp, n, 2);
	data3 = arrayCol(tmp, n, 3);
	data4 = arrayCol(tmp, n, 4);
	n = strlength(data_lbl);
	for (i = 0; i < n; i++) {
#ifdef JAVASCRIPT
		tmp = {};
#else
		tmp = new Array();
#endif
		tmp["x"] = data_lbl[i];
		tmp["o"] = data1[i];
		tmp["h"] = data2[i];
		tmp["l"] = data3[i];
		tmp["c"] = data4[i];
		data[i] = tmp;
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
	data_tit = "株価";
	data = null;
	str = jqbGetVal("#text01");
	calc(str);
	if (data== null)return;
	drawCandle("ex_chart", data_tit, data);
}

#ifdef JAVASCRIPT
function onClickClearButton(param)
#else
void onClickClearButton(var param)
#endif
{
	var str;
	str= getTopixCSV();
	jqbSetVal("#text01",str);

	data_tit = "株価";
	data = null;
	calc(str);
	if (data == null)return;
	drawCandle("ex_chart", data_tit, data);
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
	str = getTopixCSV();
	jqbSetVal("#text01", str);

	//test();

	data_tit = "株価";
	calc(str);
	if (data_lbl == null)return;
	drawCandle("ex_chart", data_tit, data);
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

