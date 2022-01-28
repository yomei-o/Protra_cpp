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
include("webptsim.exe__QUERY__");
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
var script="# MA Cross.pt -- 10/40移動平均交差システム by Richard Donchian\n# Copyright 2013 panacoran <panacoran@users.sourceforge.jp>\n# This program is licensed under the GPL version 3 or later.\n#\n# MA(10)がMA(40)を上抜いたらentry、下抜いたらexit。-10%の逆指値でexit。\n# ただし、終値50円以下、出来高1000万円以下の場合はentryしない。\n# 価格は翌日の寄り付きか当日の終値。買い数量は約100万円。\n\nrequire \"TIlib\"\n\ndef Num(price)\n	unit = Unit2(price)\n	return (1000000 / (unit * price)) * unit\nend\n\nif !$__INIT__\n	# TIlibのオブジェクトを生成する。\n	$MA_fast = MA_new(10)\n	$MA_slow = MA_new(40)\n	$Cross = Crossover_new(0, 0.0)\n	$__INIT__ = 1\nelse\n	MA_next($MA_fast)\n	MA_next($MA_slow)\nend\n\nma_fast = MA_value($MA_fast)\nma_slow = MA_value($MA_slow)\nprice = {+1}Open\nif !price\n	price = Close\nend\n\nif ma_fast == null || ma_slow == null || !price\n	# 指標の計算に必要な日数を経過していない場合は何もしない。\n	return\nend\ncross = Crossover_next($Cross, ma_fast, ma_slow)\n# entryの条件を判定する。\nif !$long && cross > 0 && Close > 50 && Volume * Close > 10000\n	$long = Num(price)\n	if $long == 0\n		# 100万円で買えないなら何もしない。\n		return\n	end\n	Buy(price, $long)\n	$loss_cut = Yobine(price * 0.90)\nelsif $long\n	if Low && Low <= $loss_cut\n		# 逆指値でexitする。\n		Sell(Min($loss_cut, Open), $long)\n		$long = 0\n	elsif cross < 0\n		# exitする。\n		Sell(price, $long)\n		$long = 0\n	end\nend\n\n# Local Variables:\n# tab-width: 4\n# End:\n";
// debug 
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
downloadString = function(name,str)
{
 const blob = new Blob([str], { type: 'text/plain' });
 const a = document.createElement('a');
 a.href = URL.createObjectURL(blob);
 a.download = name;
 a.click();
}
//
//
//
var ex_chart = null;
function drawGraph(id, lbl_, v1_, v2_)
{
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
}
//
// event
//
onClickDownload = function(param)
{
 var str;
 str=jqbGetVal("#text01");
 downloadString("system.pt", str);
}
onChangeText01 = function(param)
{
 var str;
 str = jqbGetVal("#text01");
 localStorage.setItem(editorKey01,str);
}
onChangeText02 = function(param)
{
 var str;
 str = jqbGetVal("#text02");
 localStorage.setItem(editorKey02, str);
}
onLoadText01 = function(param)
{
 var str;
 str=localStorage.getItem(editorKey01);
 jqbSetVal("#text01",str);
}
onLoadText02 = function(param)
{
 var str;
 str = localStorage.getItem(editorKey02);
 jqbSetVal("#text02", str);
}
onTimeout = function(param)
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
onClickExec = function(param)
{
 var str,t;
 logStr = "";
 resultStr = "";
 execStr = jqbGetVal("#text01");
 codeList = jqbGetVal("#text02");
 jqbSetVal("#text03", "");
 jqbSetVal("#text04", "");
 jqbSetVal("#text05", "");
 setTimeout(onTimeout, 500);
}
onClickPerf = function(param)
{
 var str, t;
 jqbSetVal("#text05", "");
 str = createQueryValue("cmd", "perf");
 t = jqbGetVal("#text04");
 str += appendQueryValue("str", t);
 setQuery(str);
 jumpLocation2(myName());
}
onClickClear = function(param)
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
onClickCopyright = function(param)
{
 println("Webeditor Rev.20220128_002");
}
onJumpLocation2 = function()
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
  setTimeout(onTimeout, 500);
 }
}
//
// main javascript
//
jQuery().ready(function()
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
);
