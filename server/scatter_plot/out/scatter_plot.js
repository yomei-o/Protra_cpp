// these should be top
//// JavaScript include library  Rev 0.05 ----BEGIN----
if (typeof include == "undefined"){
 var t, q = "__QUERY__"; include_list = {}; include = function(s){
  if (typeof($) != "undefined" && s.indexOf("jquery-") == 0)return; if (s.indexOf(q) != -1){
   if (typeof sessionStorage != "undefined" && (t = sessionStorage.getItem(q)))s = s.replace(q, t);
   else s = s.replace(q, location.search);
  }
  var xhr = null; if (include_list[s])return; include_list[s] = 1; if (window.XMLHttpRequest)xhr = new XMLHttpRequest();
  else if (window.ActiveXObject)try{ xhr = new ActiveXObject("Msxml2.XMLHTTP"); }
  catch (e){ xhr = new ActiveXObject("Microsoft.XMLHTTP"); }
  try{ xhr.open("GET", s, false); xhr.send(""); (0, eval)(xhr.responseText); }
  catch (e){}
 }
}declare_var_begin = declare_var_end = function(){};
//// JavaScript include library ----END----
// cgi include are 2rd 
//#include "result.h"
// jquery should be 3rd
include("jquery-1.11.3.js");
// other headers
//
//begin of js_query
//
//
//
//
//
// Debufg print
//
println = function(src)
{
 alert(src);
}
//
// length
//
strlength = function(src)
{
 var ret = 0;
 if (src == null || src == "")return ret;
 ret = src.length;
 return ret;
}
//
// QUERY
//
setQuery = function(src)
{
 if (src == null || src.indexOf("?") != 0)return;
 if (typeof(sessionStorage) != "undefined"){
  // support for safari private mode
  try{
   sessionStorage.setItem("__QUERY__", src);
   return;
  }catch (e){}
 }
 __QUERY__ = src;
}
clearQuery = function()
{
 if (typeof(sessionStorage) != "undefined"){
  // support for safari private mode
  try{
   sessionStorage.removeItem("__QUERY__");
   return;
  }catch (e){}
 }
 __QUERY__ = null;
}
var s_query = null;
getQuery = function()
{
 var ret;
 ret = "";
 if (location.search){
  ret = location.search;
  return ret;
 }
 if (typeof(sessionStorage) != "undefined"){
  if (s_query == null){
   ret = sessionStorage.getItem("__QUERY__");
   clearQuery();
   s_query = ret;
  }
  else{
   ret = s_query;
  }
  if (ret != null)return ret;
 }
 return ret;
}
//
// location
//
jumpLocation = function(src)
{
 if (src == null)return;
 if (typeof(__QUERY__) != "undefined")src += __QUERY__;
 location.href = src;
}
myName = function()
{
 var ret = "";
 var idx = -1;
 ret = location.href;
 idx = ret.lastIndexOf("/");
 if (idx != -1)ret = ret.substring(idx + 1);
 idx = ret.lastIndexOf("\\");
 if (idx != -1)ret = ret.substring(idx + 1);
 idx = ret.lastIndexOf("?");
 if (idx != -1)ret = ret.substring(0, idx);
 return ret;
}
//
// query value
//
getQueryValue = function(src, key)
{
 var ret = "";
 var idx;
 if (src == null || src == "")return ret;
 if (key == null || key == "")return ret;
 do{
  idx = src.indexOf("+");
  if (idx == -1)break;
  src = src.replace("+", "%20");
 } while (true);
 key = key + "=";
 idx = src.indexOf(key);
 if (idx == -1)return ret;
 ret = src.substring(idx + strlength(key));
 idx = ret.indexOf("&");
 if (idx != -1)ret = ret.substring(0, idx);
 ret = decodeURIComponent(ret);
 return ret;
}
createQueryValue = function(key, val)
{
 var ret = "";
 if (key == null || key == "")return ret;
 if (val == null || val == "")key = "";
 ret = "?";
 ret += key + "=";
 ret += encodeURIComponent(val);
 return ret;
}
appendQueryValue = function(key, val)
{
 var ret = "";
 if (key == null || key == "")return ret;
 if (val == null || val == "")key = "";
 ret = "&";
 ret += key + "=";
 ret += encodeURIComponent(val);
 return ret;
}
//
// query debug
//
getQueryLocationSearch = function()
{
 var ret = null;
 if (location.search){
  ret = location.search;
 }
 return ret;
}
getQuerySessionStorage = function()
{
 var ret = null;
 if (typeof(sessionStorage) != "undefined"){
  ret = sessionStorage.getItem("__QUERY__");
 }
 return ret;
}
//
// print,mail,open new window 
//
printPage = function()
{
 try{;
 print();
 }catch(e){};
}
openPage = function(src)
{
 // This function should be called from onClick events
 try{;
 window.open(src);
 }catch(e){};
}
mailTo = function(addr, subject, body)
{
 try{;
 location.href = 'mailto:' + addr + '?subject=' + subject + '&body=' + body;
 }catch(e){};
}
jumpLocation2 = function(src)
{
 if (src != myName()){
  jumpLocation(src);
  return;
 }
 var s,p,u,q;
 var li={};
 s_query=null;
 q=getQuery();
 for(s in include_list){
  li[s] = 1;
 }
 for (s in li){
  p=s.indexOf("?");
  if (p == -1) {
   p = s.indexOf(".exe");
   if (p == -1)continue;
   p += 4;
  }
  u=s.substr(0, p);
  u += q;
  delete include_list[s];
  include(u);
 }
 try{
  onJumpLocation2();
 }catch (e){}
}
//
// end of js_query
//
//
// begin of jq_bridge
//
jqbGetText = function(sel)
{
 var ret="";
 ret=$(sel).text();
 return ret;
}
jqbSetText = function(sel,src)
{
 $(sel).text(src);
}
jqbGetHtml = function(sel)
{
 var ret="";
 ret = $(sel).html();
 return ret;
}
jqbSetHtml = function(sel, src)
{
 $(sel).html(src);
}
//
// event
//
jqbCreateClickEvent = function(sel, func, param)
{
 $(sel).click(function(){
  var p_ = param;
  var f_ = func;
  f_(p_);
 });
}
jqbCreateChangeEvent = function(sel, func, param)
{
 $(sel).change(function(){
  var p_ = param;
  var f_ = func;
  f_(p_);
 });
}
//
// setter getter
//
jqbSetAttr = function(sel,name,src)
{
 $(sel).attr(name,src);
}
jqbGetProp = function(sel, name)
{
 var ret = "";
 ret = $(sel).prop(name);
 return ret;
}
jqbSetProp = function(sel, name, value)
{
 $(sel).prop(name, value);
}
jqbGetVal = function(sel)
{
 var ret = "";
 ret = $(sel).val();
 return ret;
}
jqbSetVal = function(sel, value)
{
 $(sel).val(value);
}
jqbSetCss = function(sel, name, value)
{
 $(sel).css(name, value);
}
//
// element
//
jqbGetElement = function(sel)
{
 var ret="";
 ret = jqbGetProp(sel,"outerHTML");
 return ret;
}
jqbReplaceString = function(str,a,b)
{
 while (str.indexOf(a) != -1){
  str = str.replace(a, "*");
 }
 while (str.indexOf("*") != -1){
  str = str.replace("*", b);
 }
 return str;
}
jqbAppendString = function(sel,str)
{
 ret = $(sel).parent().append(str);
}
jqbCopyElement = function(sel,a,b)
{
 var str;
 str = jqbGetElement(sel);
 str = jqbReplaceString(str,a, b);
 jqbAppendString(sel, str);
}
//
// Input
//
jqbSetInputRadioVal = function(sel, value)
{
 var str;
 str = "input[name=" + sel;
 str += "][value=" + value;
 str+="]";
 jqbSetProp(str,"checked", true);
}
jqbGetInputRadioVal = function(sel)
{
 var ret=NaN;
 var str;
 str = "input[name=" + sel;
 str += "]:checked";
 ret=jqbGetVal(str);
 if (typeof(ret) == "undefined")ret = "";
 return ret;
}
jqbSetInputCheckVal = function(sel, value)
{
 var str;
 str = "input[name=" + sel;
 str += "]";
 jqbSetProp(str, "checked", value);
}
jqbGetInputCheckVal = function(sel)
{
 var ret = false;
 var str;
 str = "input[name=" + sel;
 str += "]";
 ret = jqbGetProp(str,"checked");
 return ret;
}
//
// Media
//
jqbMediaInit = function(sel, value)
{
 var s=$(sel);
 try{
  s[0].pause();
 }catch (e){}
 try{
  s[0].preload = "none";
 }catch (e){}
 try{
  s[0].src = value;
 }catch (e){}
 try{
  s[0].currentTime = 0;
 }
 catch (e){}
}
jqbMediaStop = function(sel)
{
 var s = $(sel);
 try{
  s[0].pause();
 }catch (e){}
}
jqbMediaPlay = function(sel)
{
 var s = $(sel);
 try{
  s[0].pause();
 }catch (e){}
 try{
  s[0].currentTime=0;
 }catch (e){}
 try{
  s[0].play();
 }catch (e){}
}
//
// end of jq_bridge
//
// debug 
//
//
// 
var data = null;
var data_lbl = null;
var data2 = null;
//
// graph 
// 
var ex_chart = null;
function drawScatterPlot(id, lbl_, v1_, v2_)
{
 var plotData,ct=0;
 var dataset;
 dataset = new Array();
 if (v1_ != null && strlength(v1_) > 0) {
  plotData = {};
  plotData["label"] = "?????????1";
  plotData["data"] = v1_;
  plotData["backgroundColor"] = "rgba(0, 159, 255, 0.45)";
  plotData["borderColor"] = "rgba(0, 159, 255, 0.5)";
  plotData["pointRadius"] = 5;
  dataset[ct] = plotData;
  ct++;
 }
 if (v2_ != null && strlength(v2_) > 0) {
  plotData = {};
  plotData["label"] = "?????????2";
  plotData["data"] = v2_;
  plotData["backgroundColor"] = "rgba(255, 48, 32, 0.45)";
  plotData["borderColor"] = "rgba(255, 48, 32, 0.5)";
  plotData["pointRadius"] = 5;
  dataset[ct] = plotData;
  ct++;
 }
 var ctx = document.getElementById(id);
 var options = {
  //responsive: false,
  title : {
    display: true,
    fontSize : 14,
    fontStyle : 'normal', // ??????????????????
    padding : 20,
    text : '???????????????????????????????????????????????????'
  },
  legend: {
   align: 'start',
   position : 'right',
   labels : {
    padding: 15
   }
  },
  scales: {
   xAxes: [{
    scaleLabel: {
     display: true,
     labelString : lbl_[0],
    },
    gridLines : {
     color: '#f3f3f3',
     zeroLineColor : '#ddd'
    },
    ticks : {
     fontColor: '#333',
     min : 0,
     stepSize : 2,
    },
   }],
   yAxes: [{
    scaleLabel: {
     display: true,
     labelString : lbl_[1],
    },
    gridLines : {
     color: '#f3f3f3',
     zeroLineColor : '#ddd'
    },
    ticks : {
     fontColor: '#333',
     min : 0,
     stepsize : 25,
    }
   }]
  }
 };
 var data = {
 datasets: dataset
 }
 if (ex_chart != null) {
  ex_chart.destroy();
 }
 ex_chart = new Chart(ctx, {
  type: 'scatter',
  data : data,
  options : options,
  });
}
//
// array 
// 
function getBostonPredictCSV()
{
 var str = "";
 str += "#no,predict,#correct,difference\n";
 str += "0,32.881113,34.700001,-1.818888\n";
 str += "1,20.898760,21.700001,-0.801241\n";
 str += "2,16.871422,17.500000,-0.628578\n";
 str += "3,17.653302,20.200001,-2.546699\n";
 str += "4,13.125818,13.600000,-0.474183\n";
 str += "5,13.670934,13.100000,0.570934\n";
 str += "6,20.465681,21.000000,-0.534319\n";
 str += "7,28.619811,30.799999,-2.180188\n";
 str += "8,33.079273,34.900002,-1.820729\n";
 str += "9,20.533455,16.600000,3.933455\n";
 str += "10,18.668503,14.400000,4.268503\n";
 str += "11,21.988517,20.500000,1.488517\n";
 str += "12,26.077179,25.000000,1.077179\n";
 str += "13,20.184577,19.600000,0.584576\n";
 str += "14,20.717730,16.000000,4.717730\n";
 str += "15,23.988477,25.000000,-1.011523\n";
 str += "16,27.409218,23.500000,3.909218\n";
 str += "17,19.951515,21.700001,-1.748486\n";
 str += "18,25.333367,24.100000,1.233367\n";
 str += "19,24.267938,24.799999,-0.532062\n";
 str += "20,23.735843,22.200001,1.535843\n";
 str += "21,29.301600,23.600000,5.701600\n";
 str += "22,23.795997,22.600000,1.195996\n";
 str += "23,25.409371,28.400000,-2.990629\n";
 str += "24,25.793984,27.500000,-1.706016\n";
 str += "25,18.439785,19.500000,-1.060215\n";
 str += "26,19.712547,20.400000,-0.687453\n";
 str += "27,22.098375,22.799999,-0.701624\n";
 str += "28,19.454986,18.799999,0.654987\n";
 str += "29,19.214381,19.200001,0.014381\n";
 str += "30,20.984364,19.299999,1.684365\n";
 str += "31,20.783530,22.000000,-1.216470\n";
 str += "32,19.966908,18.799999,1.166909\n";
 str += "33,15.974185,14.300000,1.674185\n";
 str += "34,19.624143,23.000000,-3.375857\n";
 str += "35,18.684092,17.400000,1.284092\n";
 str += "36,14.433827,14.600000,-0.166174\n";
 str += "37,19.635957,19.600000,0.035957\n";
 str += "38,16.860745,13.100000,3.760744\n";
 str += "39,30.597736,27.000000,3.597736\n";
 str += "40,48.941848,50.000000,-1.058152\n";
 str += "41,22.475625,22.700001,-0.224376\n";
 str += "42,20.790624,17.400000,3.390625\n";
 str += "43,23.287291,23.200001,0.087290\n";
 str += "44,29.465703,29.900000,-0.434296\n";
 str += "45,45.702575,50.000000,-4.297425\n";
 str += "46,36.129428,34.900002,1.229426\n";
 str += "47,35.730801,36.400002,-0.669201\n";
 str += "48,30.767938,34.900002,-4.132064\n";
 str += "49,21.103016,22.400000,-1.296983\n";
 str += "50,26.000225,28.100000,-2.099775\n";
 str += "51,18.427032,23.700001,-5.272969\n";
 str += "52,21.882373,21.500000,0.382373\n";
 str += "53,29.900664,31.500000,-1.599336\n";
 str += "54,18.476116,18.500000,-0.023884\n";
 str += "55,21.393522,24.299999,-2.906477\n";
 str += "56,21.525542,24.500000,-2.974458\n";
 str += "57,44.725338,43.099998,1.625339\n";
 str += "58,36.813779,36.500000,0.313779\n";
 str += "59,30.442011,30.700001,-0.257990\n";
 str += "60,48.804546,43.500000,5.304546\n";
 str += "61,25.232198,24.400000,0.832199\n";
 str += "62,30.911452,33.200001,-2.288549\n";
 str += "63,33.094742,35.099998,-2.005256\n";
 str += "64,47.233602,45.400002,1.833600\n";
 str += "65,47.491135,50.000000,-2.508865\n";
 str += "66,26.811748,22.500000,4.311748\n";
 str += "67,27.833277,24.799999,3.033278\n";
 str += "68,23.842110,26.400000,-2.557890\n";
 str += "69,29.314483,33.099998,-3.785515\n";
 str += "70,27.762066,28.400000,-0.637934\n";
 str += "71,17.908006,20.299999,-2.391993\n";
 str += "72,18.287219,19.400000,-1.112780\n";
 str += "73,22.644937,23.799999,-1.155062\n";
 str += "74,20.144544,21.100000,-0.955457\n";
 str += "75,19.414477,18.500000,0.914477\n";
 str += "76,27.120765,23.900000,3.220765\n";
 str += "77,23.584585,24.100000,-0.515415\n";
 str += "78,16.185767,17.799999,-1.614233\n";
 str += "79,17.491258,16.799999,0.691259\n";
 str += "80,23.437914,27.500000,-4.062086\n";
 str += "81,37.516124,50.000000,-12.483876\n";
 str += "82,36.827671,50.000000,-13.172329\n";
 str += "83,25.521813,50.000000,-24.478187\n";
 str += "84,11.918752,13.900000,-1.981248\n";
 str += "85,10.840794,10.200000,0.640794\n";
 str += "86,7.025749,10.900000,-3.874251\n";
 str += "87,12.372634,11.300000,1.072634\n";
 str += "88,7.525162,7.200000,0.325163\n";
 str += "89,11.040665,12.700000,-1.659335\n";
 str += "90,6.141004,5.600000,0.541004\n";
 str += "91,10.686937,7.200000,3.486937\n";
 str += "92,12.041990,17.900000,-5.858009\n";
 str += "93,12.375626,9.500000,2.875626\n";
 str += "94,14.337221,14.500000,-0.162779\n";
 str += "95,14.760324,14.100000,0.660324\n";
 str += "96,19.359194,16.100000,3.259193\n";
 str += "97,8.967305,8.400000,0.567306\n";
 str += "98,12.100655,12.800000,-0.699345\n";
 str += "99,12.409006,14.900000,-2.490994\n";
 str += "100,12.365702,19.100000,-6.734299\n";
 str += "101,17.861596,19.900000,-2.038403\n";
 str += "102,21.617071,19.600000,2.017071\n";
 str += "103,19.218538,23.200001,-3.981463\n";
 str += "104,11.397379,12.000000,-0.602621\n";
 str += "105,21.690381,23.000000,-1.309619\n";
 str += "106,14.999619,7.000000,7.999619\n";
 str += "107,15.453616,8.100000,7.353616\n";
 str += "108,27.511735,23.900000,3.611735\n";
 return str;
}
function getBostonPredictCSV2()
{
 var str = "";
 str += "#no,predict,#correct,difference\n";
 str += "0,25.449636,24.000000,1.449636\n";
 str += "1,21.356976,21.600000,-0.243024\n";
 str += "2,33.529306,33.400002,0.129304\n";
 str += "3,35.561823,36.200001,-0.638178\n";
 str += "4,27.957540,28.700001,-0.742460\n";
 str += "5,22.121153,22.900000,-0.778847\n";
 str += "6,23.060879,27.100000,-4.039122\n";
 str += "7,16.722154,16.500000,0.222154\n";
 str += "8,19.291379,18.900000,0.391379\n";
 str += "9,17.627155,15.000000,2.627155\n";
 str += "10,19.902912,18.900000,1.002913\n";
 str += "11,19.716853,20.400000,-0.683147\n";
 str += "12,18.059331,18.200001,-0.140670\n";
 str += "13,20.133221,19.900000,0.233221\n";
 str += "14,22.229945,23.100000,-0.870055\n";
 str += "15,18.221728,18.200001,0.021727\n";
 str += "16,18.684710,19.600000,-0.915290\n";
 str += "17,16.092672,15.200000,0.892672\n";
 str += "18,14.620539,14.500000,0.120539\n";
 str += "19,15.852401,15.600000,0.252400\n";
 str += "20,14.199684,13.900000,0.299684\n";
 str += "21,16.273912,16.600000,-0.326089\n";
 str += "22,15.111152,14.800000,0.311152\n";
 str += "23,18.275449,18.400000,-0.124551\n";
 str += "24,20.737683,21.000000,-0.262317\n";
 str += "25,13.024000,12.700000,0.324001\n";
 str += "26,16.628579,14.500000,2.128579\n";
 str += "27,13.289242,13.200000,0.089242\n";
 str += "28,13.817318,13.500000,0.317318\n";
 str += "29,19.637609,18.900000,0.737610\n";
 str += "30,20.343510,20.000000,0.343510\n";
 str += "31,23.971055,24.700001,-0.728946\n";
 str += "32,27.511304,26.600000,0.911304\n";
 str += "33,24.763118,25.299999,-0.536881\n";
 str += "34,24.569971,24.700001,-0.130030\n";
 str += "35,20.836322,21.200001,-0.363679\n";
 str += "36,19.687155,19.299999,0.387155\n";
 str += "37,20.223972,20.000000,0.223972\n";
 str += "38,19.510193,19.400000,0.110194\n";
 str += "39,20.402803,19.700001,0.702802\n";
 str += "40,22.396163,23.400000,-1.003837\n";
 str += "41,18.753394,18.900000,-0.146606\n";
 str += "42,34.715036,35.400002,-0.684965\n";
 str += "43,23.136472,24.700001,-1.563529\n";
 str += "44,31.427997,31.600000,-0.172004\n";
 str += "45,23.186619,23.299999,-0.113380\n";
 str += "46,18.719771,18.700001,0.019771\n";
 str += "47,21.974641,22.200001,-0.225360\n";
 str += "48,32.987491,33.000000,-0.012509\n";
 str += "49,19.443450,19.400000,0.043450\n";
 str += "50,20.875148,22.000000,-1.124852\n";
 str += "51,18.454881,17.400000,1.054881\n";
 str += "52,20.495707,20.900000,-0.404293\n";
 str += "53,23.952762,24.200001,-0.247239\n";
 str += "54,22.880148,22.799999,0.080149\n";
 str += "55,23.632040,23.400000,0.232041\n";
 str += "56,21.774715,21.400000,0.374715\n";
 str += "57,20.328870,20.000000,0.328870\n";
 str += "58,21.258000,20.799999,0.458001\n";
 str += "59,20.802655,21.200001,-0.397345\n";
 str += "60,20.569478,20.299999,0.269479\n";
 str += "61,27.584905,28.000000,-0.415095\n";
 str += "62,23.532864,23.900000,-0.367135\n";
 str += "63,22.646932,22.900000,-0.253068\n";
 str += "64,23.952628,23.900000,0.052628\n";
 str += "65,26.231612,26.600000,-0.368389\n";
 str += "66,21.916191,22.500000,-0.583809\n";
 str += "67,30.728905,28.700001,2.028904\n";
 str += "68,22.630426,22.000000,0.630426\n";
 str += "69,23.837427,22.900000,0.937427\n";
 str += "70,24.802145,25.000000,-0.197855\n";
 str += "71,20.438595,20.600000,-0.161405\n";
 str += "72,21.728289,21.400000,0.328289\n";
 str += "73,40.148137,38.700001,1.448136\n";
 str += "74,43.382175,43.799999,-0.417824\n";
 str += "75,31.515338,33.200001,-1.684663\n";
 str += "76,25.739012,26.500000,-0.760988\n";
 str += "77,18.230857,18.600000,-0.369144\n";
 str += "78,19.506369,19.299999,0.206370\n";
 str += "79,20.048851,20.100000,-0.051149\n";
 str += "80,18.472947,19.500000,-1.027053\n";
 str += "81,19.799642,19.799999,-0.000358\n";
 str += "82,18.990363,19.400000,-0.409636\n";
 str += "83,21.882616,21.700001,0.182616\n";
 str += "84,19.567300,18.700001,0.867300\n";
 str += "85,19.184085,18.500000,0.684085\n";
 str += "86,18.541893,18.299999,0.241894\n";
 str += "87,21.382195,21.200001,0.182194\n";
 str += "88,19.405239,20.400000,-0.994760\n";
 str += "89,21.200501,20.299999,0.900502\n";
 str += "90,20.242056,20.500000,-0.257944\n";
 str += "91,17.094366,17.299999,-0.205633\n";
 str += "92,20.846122,21.400000,-0.553877\n";
 str += "93,16.441061,15.700000,0.741061\n";
 str += "94,15.588475,16.200001,-0.611526\n";
 str += "95,17.116931,18.000000,-0.883069\n";
 str += "96,19.080414,19.200001,-0.119587\n";
 str += "97,19.136357,19.600000,-0.463644\n";
 str += "98,18.093717,18.400000,-0.306282\n";
 str += "99,15.112292,15.600000,-0.487708\n";
 str += "100,18.020823,18.100000,-0.079177\n";
 str += "101,17.680041,17.100000,0.580040\n";
 str += "102,14.181681,13.300000,0.881681\n";
 str += "103,16.995102,17.799999,-0.804897\n";
 str += "104,15.703222,14.000000,1.703222\n";
 str += "105,16.963697,14.400000,2.563698\n";
 str += "106,13.940130,13.400000,0.540131\n";
 str += "107,15.200482,15.600000,-0.399519\n";
 str += "108,13.680738,11.800000,1.880738\n";
 str += "109,14.973782,13.800000,1.173782\n";
 str += "110,16.160821,15.600000,0.560821\n";
 str += "111,15.646062,17.799999,-2.153937\n";
 str += "112,15.277513,15.400000,-0.122487\n";
 str += "113,21.682442,21.500000,0.182442\n";
 str += "114,18.453982,15.300000,3.153982\n";
 str += "115,17.204942,19.400000,-2.195058\n";
 str += "116,16.771367,17.000000,-0.228633\n";
 str += "117,15.619625,15.600000,0.019624\n";
 str += "118,38.156207,41.299999,-3.143792\n";
 str += "119,26.038655,24.299999,1.738656\n";
 str += "120,24.218665,23.299999,0.918666\n";
 str += "121,49.022527,50.000000,-0.977473\n";
 str += "122,48.873927,50.000000,-1.126073\n";
 str += "123,24.453598,25.000000,-0.546402\n";
 str += "124,49.643037,50.000000,-0.356963\n";
 str += "125,22.500212,23.799999,-1.299787\n";
 str += "126,23.590024,23.799999,-0.209975\n";
 str += "127,23.018722,22.299999,0.718723\n";
 str += "128,21.039501,19.100000,1.939501\n";
 str += "129,22.138135,23.100000,-0.961865\n";
 str += "130,25.172124,23.600000,1.572123\n";
 str += "131,23.130750,22.600000,0.530750\n";
 str += "132,28.723572,29.400000,-0.676428\n";
 str += "133,23.715043,24.600000,-0.884957\n";
 str += "134,37.374147,37.200001,0.174147\n";
 str += "135,41.449290,39.799999,1.649291\n";
 str += "136,33.093782,36.200001,-3.106219\n";
 str += "137,36.814327,37.900002,-1.085674\n";
 str += "138,32.529239,32.500000,0.029239\n";
 str += "139,26.548679,26.400000,0.148679\n";
 str += "140,28.513847,29.600000,-1.086153\n";
 str += "141,31.232920,32.000000,-0.767080\n";
 str += "142,29.916483,29.799999,0.116483\n";
 str += "143,34.837625,37.000000,-2.162375\n";
 str += "144,30.674323,30.500000,0.174323\n";
 str += "145,30.166229,31.100000,-0.933771\n";
 str += "146,28.589577,29.100000,-0.510423\n";
 str += "147,48.865934,50.000000,-1.134066\n";
 str += "148,35.584214,33.299999,2.284215\n";
 str += "149,31.127339,30.299999,0.827340\n";
 str += "150,32.956124,34.599998,-1.643874\n";
 str += "151,32.535774,32.900002,-0.364228\n";
 str += "152,23.846802,24.100000,-0.253198\n";
 str += "153,44.872294,42.299999,2.572295\n";
 str += "154,49.044238,48.500000,0.544238\n";
 str += "155,49.044238,50.000000,-0.955762\n";
 str += "156,23.130682,22.600000,0.530681\n";
 str += "157,24.002614,24.400000,-0.397385\n";
 str += "158,21.746050,22.500000,-0.753950\n";
 str += "159,23.739233,24.400000,-0.660767\n";
 str += "160,19.494961,20.000000,-0.505039\n";
 str += "161,21.168652,21.700001,-0.531348\n";
 str += "162,19.374204,19.299999,0.074204\n";
 str += "163,25.361965,25.000000,0.361965\n";
 str += "164,23.425747,23.299999,0.125748\n";
 str += "165,27.106189,28.700001,-1.593812\n";
 str += "166,23.123895,23.000000,0.123895\n";
 str += "167,27.315171,26.700001,0.615171\n";
 str += "168,21.558305,21.700001,-0.141696\n";
 str += "169,27.011934,27.500000,-0.488066\n";
 str += "170,28.329716,30.100000,-1.770284\n";
 str += "171,44.622707,44.799999,-0.177292\n";
 str += "172,46.807596,50.000000,-3.192404\n";
 str += "173,42.766194,37.599998,5.166196\n";
 str += "174,31.628357,31.600000,0.028356\n";
 str += "175,45.245413,46.700001,-1.454587\n";
 str += "176,24.475475,24.299999,0.175475\n";
 str += "177,32.027402,31.700001,0.327401\n";
 str += "178,43.363608,41.700001,1.663608\n";
 str += "179,45.788573,48.299999,-2.511427\n";
 str += "180,28.776449,29.000000,-0.223551\n";
 str += "181,24.742710,24.000000,0.742710\n";
 str += "182,25.360064,25.100000,0.260064\n";
 str += "183,32.330054,31.500000,0.830054\n";
 str += "184,24.252910,23.700001,0.552910\n";
 str += "185,23.849568,23.299999,0.549569\n";
 str += "186,23.255034,22.000000,1.255034\n";
 str += "187,19.749785,20.100000,-0.350215\n";
 str += "188,20.701593,22.200001,-1.498408\n";
 str += "189,23.570261,23.700001,-0.129740\n";
 str += "190,17.405567,17.600000,-0.194433\n";
 str += "191,19.907252,20.500000,-0.592748\n";
 str += "192,26.170174,26.200001,-0.029827\n";
 str += "193,24.054783,24.400000,-0.345217\n";
 str += "194,26.188434,24.799999,1.388434\n";
 str += "195,29.578620,29.600000,-0.021381\n";
 str += "196,41.701924,42.799999,-1.098075\n";
 str += "197,22.224948,21.900000,0.324948\n";
 str += "198,20.326507,20.900000,-0.573493\n";
 str += "199,44.443991,44.000000,0.443991\n";
 str += "200,48.640044,50.000000,-1.359956\n";
 str += "201,35.610915,36.000000,-0.389085\n";
 str += "202,32.052477,30.100000,1.952477\n";
 str += "203,34.563960,33.799999,0.763961\n";
 str += "204,46.387637,48.799999,-2.412362\n";
 str += "205,32.208304,31.000000,1.208304\n";
 str += "206,23.848212,22.799999,1.048213\n";
 str += "207,47.292620,50.000000,-2.707380\n";
 str += "208,20.652373,20.700001,-0.047627\n";
 str += "209,20.947664,21.100000,-0.152336\n";
 str += "210,25.577483,25.200001,0.377483\n";
 str += "211,37.417885,35.200001,2.217884\n";
 str += "212,32.105511,32.400002,-0.294491\n";
 str += "213,32.549494,32.000000,0.549494\n";
 str += "214,31.328583,33.099998,-1.771415\n";
 str += "215,29.076818,29.100000,-0.023183\n";
 str += "216,35.300134,35.400002,-0.099868\n";
 str += "217,46.692828,46.000000,0.692828\n";
 str += "218,31.850970,32.200001,-0.349030\n";
 str += "219,22.056216,22.000000,0.056216\n";
 str += "220,20.180324,20.100000,0.080324\n";
 str += "221,24.008555,23.200001,0.808554\n";
 str += "222,22.806800,22.299999,0.506801\n";
 str += "223,23.849550,24.799999,-0.950449\n";
 str += "224,31.373665,28.500000,2.873665\n";
 str += "225,34.322495,37.299999,-2.977504\n";
 str += "226,27.868170,27.900000,-0.031830\n";
 str += "227,24.854920,23.900000,0.954921\n";
 str += "228,21.687946,21.700001,-0.012055\n";
 str += "229,28.123362,28.600000,-0.476638\n";
 str += "230,26.166734,27.100000,-0.933266\n";
 str += "231,20.498108,20.299999,0.198109\n";
 str += "232,31.554654,29.000000,2.554654\n";
 str += "233,23.437117,22.000000,1.437117\n";
 str += "234,34.644243,36.099998,-1.455755\n";
 str += "235,32.938368,33.400002,-0.461634\n";
 str += "236,29.743004,28.200001,1.543003\n";
 str += "237,24.869196,22.799999,2.069197\n";
 str += "238,17.032433,16.100000,0.932432\n";
 str += "239,23.398425,22.100000,1.298424\n";
 str += "240,20.926069,21.600000,-0.673932\n";
 str += "241,16.541094,16.200001,0.341093\n";
 str += "242,18.181966,17.799999,0.381967\n";
 str += "243,19.014092,19.799999,-0.785907\n";
 str += "244,22.376729,23.100000,-0.723272\n";
 str += "245,21.502184,21.000000,0.502184\n";
 str += "246,23.670713,23.799999,-0.129286\n";
 str += "247,23.217863,23.100000,0.117863\n";
 str += "248,20.839514,20.400000,0.439515\n";
 str += "249,18.189250,18.500000,-0.310750\n";
 str += "250,24.127542,25.000000,-0.872458\n";
 str += "251,25.646671,24.600000,1.046670\n";
 str += "252,23.278479,23.000000,0.278479\n";
 str += "253,21.732990,22.200001,-0.467011\n";
 str += "254,19.742749,19.299999,0.442749\n";
 str += "255,22.769221,22.600000,0.169221\n";
 str += "256,20.655337,19.799999,0.855338\n";
 str += "257,17.802732,17.100000,0.702731\n";
 str += "258,19.190496,19.400000,-0.209504\n";
 str += "259,22.324759,22.200001,0.124758\n";
 str += "260,20.847765,20.700001,0.147764\n";
 str += "261,19.137337,19.500000,-0.362663\n";
 str += "262,19.865978,20.600000,-0.734022\n";
 str += "263,19.663542,19.000000,0.663542\n";
 str += "264,19.573494,18.700001,0.873493\n";
 str += "265,32.427574,32.700001,-0.272427\n";
 str += "266,17.932320,16.500000,1.432320\n";
 str += "267,30.354337,31.200001,-0.845664\n";
 str += "268,17.804838,17.500000,0.304838\n";
 str += "269,16.933132,17.200001,-0.266869\n";
 str += "270,23.690848,23.100000,0.590848\n";
 str += "271,25.655523,24.500000,1.155523\n";
 str += "272,26.184596,26.600000,-0.415405\n";
 str += "273,22.622764,22.900000,-0.277236\n";
 str += "274,19.033857,18.600000,0.433857\n";
 str += "275,30.942555,30.100000,0.842554\n";
 str += "276,18.271063,18.200001,0.071063\n";
 str += "277,20.802935,20.600000,0.202935\n";
 str += "278,21.157801,21.700001,-0.542200\n";
 str += "279,21.645890,22.700001,-1.054111\n";
 str += "280,22.088407,22.600000,-0.511593\n";
 str += "281,26.183787,25.000000,1.183787\n";
 str += "282,19.504461,19.900000,-0.395538\n";
 str += "283,21.548634,20.799999,0.748635\n";
 str += "284,29.101079,21.900000,7.201080\n";
 str += "285,20.702593,21.900000,-1.197407\n";
 str += "286,24.543003,23.100000,1.443003\n";
 str += "287,39.539311,50.000000,-10.460689\n";
 str += "288,36.241273,50.000000,-13.758727\n";
 str += "289,14.831239,13.800000,1.031239\n";
 str += "290,10.926006,13.800000,-2.873995\n";
 str += "291,19.819056,15.000000,4.819056\n";
 str += "292,14.270316,13.300000,0.970316\n";
 str += "293,9.428981,13.100000,-3.671019\n";
 str += "294,14.495977,10.400000,4.095977\n";
 str += "295,11.781735,12.300000,-0.518265\n";
 str += "296,9.101002,8.800000,0.301002\n";
 str += "297,8.713455,10.500000,-1.786545\n";
 str += "298,7.109374,7.400000,-0.290626\n";
 str += "299,10.980660,10.200000,0.780660\n";
 str += "300,11.436436,11.500000,-0.063564\n";
 str += "301,15.136711,15.100000,0.036710\n";
 str += "302,21.062233,23.200001,-2.137768\n";
 str += "303,10.027142,9.700000,0.327143\n";
 str += "304,13.519857,13.800000,-0.280143\n";
 str += "305,11.721167,13.100000,-1.378833\n";
 str += "306,12.729299,12.500000,0.229299\n";
 str += "307,9.191702,8.500000,0.691702\n";
 str += "308,8.167245,5.000000,3.167245\n";
 str += "309,9.500357,6.300000,3.200357\n";
 str += "310,13.331165,12.100000,1.231164\n";
 str += "311,8.997222,8.300000,0.697221\n";
 str += "312,7.097590,8.500000,-1.402410\n";
 str += "313,8.289952,5.000000,3.289952\n";
 str += "314,13.194097,11.900000,1.294097\n";
 str += "315,24.975684,27.900000,-2.924315\n";
 str += "316,16.799755,17.200001,-0.400245\n";
 str += "317,26.603868,27.500000,-0.896132\n";
 str += "318,20.338716,15.000000,5.338716\n";
 str += "319,17.201815,17.200001,0.001814\n";
 str += "320,14.016785,16.299999,-2.283214\n";
 str += "321,7.506394,7.000000,0.506394\n";
 str += "322,6.988408,7.200000,-0.211592\n";
 str += "323,8.796407,7.500000,1.296407\n";
 str += "324,9.257068,10.400000,-1.142931\n";
 str += "325,8.316944,8.800000,-0.483056\n";
 str += "326,7.879701,8.400000,-0.520298\n";
 str += "327,16.432064,16.700001,-0.267936\n";
 str += "328,14.429706,14.200000,0.229706\n";
 str += "329,19.784555,20.799999,-1.015444\n";
 str += "330,13.785960,13.400000,0.385960\n";
 str += "331,12.566276,11.700000,0.866276\n";
 str += "332,7.881836,8.300000,-0.418164\n";
 str += "333,11.107929,10.200000,0.907929\n";
 str += "334,10.509742,10.900000,-0.390258\n";
 str += "335,11.133072,11.000000,0.133072\n";
 str += "336,14.241591,14.300000,-0.058409\n";
 str += "337,11.884707,11.700000,0.184707\n";
 str += "338,12.445319,13.400000,-0.954681\n";
 str += "339,9.698946,9.600000,0.098946\n";
 str += "340,9.177150,8.700000,0.477151\n";
 str += "341,8.970794,10.500000,-1.529206\n";
 str += "342,15.544512,17.100000,-1.555488\n";
 str += "343,17.826148,18.400000,-0.573852\n";
 str += "344,14.544992,15.400000,-0.855008\n";
 str += "345,10.416664,10.800000,-0.383336\n";
 str += "346,11.686294,11.800000,-0.113706\n";
 str += "347,15.103038,14.900000,0.203038\n";
 str += "348,14.222939,12.600000,1.622939\n";
 str += "349,14.276327,14.100000,0.176326\n";
 str += "350,13.535643,13.000000,0.535643\n";
 str += "351,13.016505,13.400000,-0.383495\n";
 str += "352,14.372445,15.200000,-0.827555\n";
 str += "353,17.302839,16.100000,1.202838\n";
 str += "354,18.414604,17.799999,0.614604\n";
 str += "355,14.091795,14.100000,-0.008206\n";
 str += "356,14.825131,12.700000,2.125131\n";
 str += "357,13.462563,13.500000,-0.037437\n";
 str += "358,14.509455,14.900000,-0.390544\n";
 str += "359,20.260249,20.000000,0.260249\n";
 str += "360,15.654679,16.400000,-0.745321\n";
 str += "361,18.574930,17.700001,0.874929\n";
 str += "362,19.931619,19.500000,0.431619\n";
 str += "363,19.252027,20.200001,-0.947973\n";
 str += "364,22.289758,21.400000,0.889759\n";
 str += "365,20.306961,19.900000,0.406961\n";
 str += "366,18.129877,19.000000,-0.870123\n";
 str += "367,17.169303,19.100000,-1.930697\n";
 str += "368,19.250933,20.100000,-0.849068\n";
 str += "369,28.655723,29.799999,-1.144276\n";
 str += "370,13.817537,13.800000,0.017537\n";
 str += "371,14.343118,13.300000,1.043118\n";
 str += "372,17.412306,16.700001,0.712305\n";
 str += "373,15.832158,14.600000,1.232157\n";
 str += "374,21.573107,21.400000,0.173107\n";
 str += "375,24.175960,23.700001,0.475959\n";
 str += "376,25.820733,25.000000,0.820733\n";
 str += "377,21.359313,21.799999,-0.440686\n";
 str += "378,20.585756,20.600000,-0.014245\n";
 str += "379,21.005013,21.200001,-0.194988\n";
 str += "380,19.103374,19.100000,0.003374\n";
 str += "381,21.233504,20.600000,0.633504\n";
 str += "382,15.727222,15.200000,0.527222\n";
 str += "383,14.741744,13.600000,1.141744\n";
 str += "384,18.892083,20.100000,-1.207918\n";
 str += "385,21.411358,21.799999,-0.388641\n";
 str += "386,23.162876,24.500000,-1.337124\n";
 str += "387,22.273787,23.100000,-0.826213\n";
 str += "388,19.141343,19.700001,-0.558658\n";
 str += "389,19.417941,18.299999,1.117942\n";
 str += "390,21.356549,21.200001,0.156548\n";
 str += "391,18.572092,17.500000,1.072092\n";
 str += "392,17.414211,16.799999,0.614212\n";
 str += "393,22.239251,22.400000,-0.160748\n";
 str += "394,18.821989,20.600000,-1.778012\n";
 str += "395,22.470600,22.000000,0.470600\n";
 str += "396,15.260768,11.900000,3.360769\n";
 return str;
}
function readCSVLabel(str)
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
function readCSVFlag(str)
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
function readCSVData(str)
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
    ret2[ct2] = parseFloat(t);
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
function arrayCol(arr,w,pos)
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
function arrayMean(arr)
{
 var sz,i;
 var ret=0;
 sz = strlength(arr);
 for (i = 0; i < sz; i++) {
  ret += arr[i];
 }
 return parseFloat(ret)/sz;
}
function arrayVariance(arr)
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
function arraySD(arr)
{
 var ret;
 ret=arrayVariance(arr);
 ret = Math.sqrt(ret);
 return ret;
}
function arrayCovariance(arr,arr2)
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
function arrayCorrel(arr, arr2)
{
 var ret;
 ret = arrayCovariance(arr, arr2);
 ret /= arraySD(arr);
 ret /= arraySD(arr2);
 return ret;
}
function calc(str,str2)
{
 var lbl, n,i,sz;
 var tmp, tmp1, tmp2,x,y;
 lbl = readCSVLabel(str);
 n = strlength(lbl);
 if (n != 2) {
  lbl = readCSVLabel(str2);
  n = strlength(lbl);
 }
 if (n != 2) {
  return;
 }
 tmp1 = new Array();
 if (str != null && str != "" && str.indexOf(",") != -1) {
  tmp = readCSVData(str);
  x = arrayCol(tmp, 2, 0);
  y = arrayCol(tmp, 2, 1);
  sz = strlength(x);
  tmp1 = new Array();
  for (i = 0; i < sz; i++) {
   tmp = {}
   tmp["x"] = x[i];
   tmp["y"] = y[i];
   tmp1[i] = tmp;
  }
 }
 tmp2 = new Array();
 if (str2 != null && str2 != "" && str2.indexOf(",")!=-1){
  tmp = readCSVData(str2);
  x = arrayCol(tmp, 2, 0);
  y = arrayCol(tmp, 2, 1);
  sz = strlength(x);
  tmp2 = new Array();
  for (i = 0; i < sz; i++) {
   tmp = {}
   tmp["x"] = x[i];
   tmp["y"] = y[i];
   tmp2[i] = tmp;
  }
 }
 data = tmp1;
 data2 = tmp2;
 data_lbl = lbl;
}
//
// event 
// 
function evalString(str)
{
 try {
  (0, eval)(str);
 }
 catch (e) {
 }
}
function onClickExecButton(param)
{
 var str,str2;
 data = null;
 data2 = null;
 data_lbl = null;
 str = jqbGetVal("#text01");
 str2 = jqbGetVal("#text02");
 calc(str,str2);
 if (data_lbl == null)return;
 drawScatterPlot("ex_chart", data_lbl, data,data2);
}
function onClickClearButton(param)
{
 var str,str2;
 str= getBostonPredictCSV();
 jqbSetVal("#text01",str);
 str2 = getBostonPredictCSV2();
 jqbSetVal("#text02", str2);
 data_lbl = null;
 data = null;
 data2 = null;
 calc(str, str2);
 if (data_lbl == null)return;
 drawScatterPlot("ex_chart", data_lbl, data, data2);
}
//
// main javascript
//
jQuery().ready(function()
{
 var str,str2;
 jqbCreateClickEvent("#btn01", onClickExecButton, "");
 jqbCreateClickEvent("#btn02", onClickClearButton, "");
 str = getBostonPredictCSV();
 jqbSetVal("#text01", str);
 str2 = getBostonPredictCSV2();
 jqbSetVal("#text02", str2);
 calc(str,str2);
 if (data_lbl == null)return;
 drawScatterPlot("ex_chart",data_lbl,data,data2);
}
);
