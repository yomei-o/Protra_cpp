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
var data2 = null;
var data_lbl = null;
var data_tit = null;
//
// graph 
// 
var ex_chart = null;
function drawGraph(id, lbl_, v1_, v2_,tit)
{
 var dt,dtsets,ct=0;
 dtsets = new Array();
 dt = {};
 dt["label"] = tit[0];
 dt["data"] = v1_;
 dt["borderColor"] = "rgba(100, 255, 100, 1)";
 dtsets[0] = dt;
 if (v2_ != null && strlength(v2_) > 0) {
  dt = {};
  dt["label"] = tit[1];
  dt["data"] = v2_;
  dt["borderColor"] = "rgba(255, 100, 100, 1)";
  dtsets[1] = dt;
 }
 var ctx = document.getElementById(id);
 var data = {
 labels: lbl_,
 datasets : dtsets,
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
}
//
// array 
// 
function getKabukaCSV()
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
function readCSVData2(str)
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
function calc(str)
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
 data_tit = null;
 data = null;
 data2 = null;
 data_lbl = null;
 str = jqbGetVal("#text01");
 calc(str);
 if (data_lbl == null)return;
 drawGraph("ex_chart", data_lbl, data,data2,data_tit);
}
function onClickClearButton(param)
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
jQuery().ready(function()
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
);
