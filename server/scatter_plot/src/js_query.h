#ifndef JS_QUERY_H_
#define JS_QUERY_H_

//
//begin of js_query
//


#ifndef JAVASCRIPT
#define null 0
#define true 1
#define false 0
#endif

#ifdef JAVASCRIPT 
#define BEGIN_TRY() try{
#define END_TRY() }catch(e){}
#else
#define BEGIN_TRY()
#define END_TRY()
#endif

#ifdef JAVASCRIPT 
#define _delete(a,b) delete a[b]
#else
#define _delete(a,b) a.delete_(b)
#endif

//
//
//

#ifndef JAVASCRIPT 
#define __QUERY__ "?i=iii&p=ppp&s=1&=000"
//#define __QUERY__ null
#endif
//
// Debufg print
//

#ifdef JAVASCRIPT
println = function(src)
#else
void println(var src)
#endif
{
#ifdef JAVASCRIPT
	alert(src);
#else
	printf("%s\n", ((std::string)src).c_str());
#endif
}

#ifndef JAVASCRIPT
void println(const char* a)
{
	var aa;
	aa = a;
	println(aa);
}
#endif

//
// length
//


#ifdef JAVASCRIPT
strlength = function(src)
#else
var strlength(var src)
#endif
{
	var ret = 0;
	if (src == null || src == "")return ret;
#ifdef JAVASCRIPT
	ret = src.length;
#else
	ret = src.length();
#endif
	return ret;
}

#ifndef JAVASCRIPT
void strlength(const char* a)
{
	var aa;
	aa = a;
	strlength(aa);
}
#endif


//
// QUERY
//


#ifdef JAVASCRIPT
setQuery = function(src)
#else
void setQuery(var src)
#endif
{
	if (src == null || src.indexOf("?") != 0)return;
	if (typeof(sessionStorage) != "undefined"){
#ifdef JAVASCRIPT
		// support for safari private mode
		try{
#endif
			sessionStorage.setItem("__QUERY__", src);
			return;
#ifdef JAVASCRIPT
		}catch (e){}
#endif
	}
#ifdef JAVASCRIPT
	__QUERY__ = src;
#endif
}

#ifdef JAVASCRIPT
clearQuery = function()
#else
void clearQuery()
#endif
{
	if (typeof(sessionStorage) != "undefined"){
#ifdef JAVASCRIPT
		// support for safari private mode
		try{
#endif
			sessionStorage.removeItem("__QUERY__");
			return;
#ifdef JAVASCRIPT
		}catch (e){}
#endif
	}
#ifdef JAVASCRIPT
	__QUERY__ = null;
#endif
}

var s_query = null;

#ifdef JAVASCRIPT
getQuery = function()
#else
var getQuery()
#endif
{
	var ret;
	ret = "";
#ifdef JAVASCRIPT
	if (location.search){
		ret = location.search;
		return ret;
	}
#endif
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
#ifndef JAVASCRIPT
#ifdef __QUERY__
	ret = __QUERY__;
#endif
#endif
	return ret;
}

//
// location
//


#ifdef JAVASCRIPT
jumpLocation = function(src)
#else
void jumpLocation(var src)
#endif
{
	if (src == null)return;
#ifdef JAVASCRIPT
	if (typeof(__QUERY__) != "undefined")src += __QUERY__;
	location.href = src;
#else
	println("jumpLocation()");
	println(src);
#endif
}


#ifdef JAVASCRIPT
myName = function()
#else
var myName()
#endif
{
	var ret = "";
	var idx = -1;

#ifdef JAVASCRIPT
	ret = location.href;
#else
	ret = __FILE__;
#endif
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

#ifdef JAVASCRIPT
getQueryValue = function(src, key)
#else
var getQueryValue(var src, var key)
#endif
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

#ifdef JAVASCRIPT
createQueryValue = function(key, val)
#else
var createQueryValue(var key, var val)
#endif
{
	var ret = "";
	if (key == null || key == "")return ret;
	if (val == null || val == "")key = "";
	ret = "?";
	ret += key + "=";
	ret += encodeURIComponent(val);
	return ret;
}

#ifdef JAVASCRIPT
appendQueryValue = function(key, val)
#else
var appendQueryValue(var key, var val)
#endif
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

#ifdef JAVASCRIPT
getQueryLocationSearch = function()
#else
var getQueryLocationSearch()
#endif
{
	var ret = null;
#ifdef JAVASCRIPT
	if (location.search){
		ret = location.search;
	}
#endif
	return ret;
}

#ifdef JAVASCRIPT
getQuerySessionStorage = function()
#else
var getQuerySessionStorage()
#endif
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


#ifdef JAVASCRIPT
printPage = function()
#else
void printPage()
#endif
{
	BEGIN_TRY();
#ifdef JAVASCRIPT
	print();
#else
	println("printPage()");
#endif
	END_TRY();
}

#ifdef JAVASCRIPT
openPage = function(src)
#else
void openPage(var src)
#endif
{
	// This function should be called from onClick events
	BEGIN_TRY();
#ifdef JAVASCRIPT
	window.open(src);
#else
	println("openPage()");
	println(src);
#endif
	END_TRY();
}

#ifdef JAVASCRIPT
mailTo = function(addr, subject, body)
#else
void mailTo(var addr, var subject, var body)
#endif
{
	BEGIN_TRY();
#ifdef JAVASCRIPT
	location.href = 'mailto:' + addr + '?subject=' + subject + '&body=' + body;
#else
	var str;
	println("mailTo()");
	str = "address:";
	str += addr;
	println(str);
	str = "subject:";
	str += subject;
	println(str);
	str = "body:";
	str += body;
	println(str);
#endif
	END_TRY();
}


#ifdef JAVASCRIPT
jumpLocation2 = function(src)
#else
void jumpLocation2(var src)
#endif
{
	if (src != myName()){
		jumpLocation(src);
		return;
	}
#ifdef JAVASCRIPT
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
#else
	println("jumpLocation2()");
	println(src);
#endif
}


//
// end of js_query
//

#endif /*  JS_QUERY_H_ */

