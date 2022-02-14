#ifndef JQ_BRIDGE_H_
#define JQ_BRIDGE_H_



//
// begin of jq_bridge
//

#ifdef JAVASCRIPT
jqbGetText = function(sel)
#else
var jqbGetText(var sel)
#endif
{
	var ret="";
#ifdef JAVASCRIPT
	ret=$(sel).text();
#else
	var str = "jqGetText(";
	str += sel;
	str += ")";
	println(str);
#endif
	return ret;
}

#ifdef JAVASCRIPT
jqbSetText = function(sel,src)
#else
void jqbSetText(var sel,var src)
#endif
{
#ifdef JAVASCRIPT
	$(sel).text(src);
#else
	var str = "jqSetText(";
	str += sel;
	str += ",";
	str += src;
	str += ")";
	println(str);
#endif
}

#ifdef JAVASCRIPT
jqbGetHtml = function(sel)
#else
var jqbGetHtml(var sel)
#endif
{
	var ret="";
#ifdef JAVASCRIPT
	ret = $(sel).html();
#else
	var str = "jqGetHtml(";
	str += sel;
	str += ")";
	println(str);
#endif
	return ret;
}

#ifdef JAVASCRIPT
jqbSetHtml = function(sel, src)
#else
void jqbSetHtml(var sel, var src)
#endif
{
#ifdef JAVASCRIPT
	$(sel).html(src);
#else
	var str = "jqSetHtml(";
	str += sel;
	str += ",";
	str += src;
	str += ")";
	println(str);
#endif
}

//
// event
//

#ifdef JAVASCRIPT
jqbCreateClickEvent = function(sel, func, param)
#else
void jqbCreateClickEvent(var sel, var func, var param)
#endif
{
#ifdef JAVASCRIPT
	$(sel).click(function(){
		var p_ = param;
		var f_ = func;
		f_(p_);
	});
#else
	var str = "jqCreateClickEvent(";
	str += sel;
	str += ",,";
	str += param;
	str += ")";
	println(str);
#endif
}


#ifdef JAVASCRIPT
jqbCreateChangeEvent = function(sel, func, param)
#else
void jqbCreateChangeEvent(var sel, var func, var param)
#endif
{
#ifdef JAVASCRIPT
	$(sel).change(function(){
		var p_ = param;
		var f_ = func;
		f_(p_);
	});
#else
	var str = "jqCreateChangeEvent(";
	str += sel;
	str += ",,";
	str += param;
	str += ")";
	println(str);
#endif
}


//
// setter getter
//

#ifdef JAVASCRIPT
jqbSetAttr = function(sel,name,src)
#else
void jqbSetAttr(var sel,var name, var src)
#endif
{
#ifdef JAVASCRIPT
	$(sel).attr(name,src);
#else
	var str = "jqSetttr(";
	str += sel;
	str += ",";
	str += name;
	str += ",";
	str += src;
	str += ")";
	println(str);
#endif
}


#ifdef JAVASCRIPT
jqbGetProp = function(sel, name)
#else
var jqbGetProp(var sel,var name)
#endif
{
	var ret = "";
#ifdef JAVASCRIPT
	ret = $(sel).prop(name);
#else
	var str = "jqGetProp(";
	str += sel;
	str += ",";
	str += name;
	str += ")";
	println(str);
	ret = name;
#endif
	return ret;
}

#ifdef JAVASCRIPT
jqbSetProp = function(sel, name, value)
#else
void jqbSetProp(var sel, var name, var value)
#endif
{
#ifdef JAVASCRIPT
	$(sel).prop(name, value);
#else
	var str = "jqSetProp(";
	str += sel;
	str += ",";
	str += name;
	str += ",";
	str += value;
	str += ")";
	println(str);
#endif
}

#ifdef JAVASCRIPT
jqbGetVal = function(sel)
#else
var jqbGetVal(var sel)
#endif
{
	var ret = "";
#ifdef JAVASCRIPT
	ret = $(sel).val();
#else
	var str = "jqGetval(";
	str += sel;
	str += ")";
	println(str);
#endif
	return ret;
}

#ifdef JAVASCRIPT
jqbSetVal = function(sel, value)
#else
void jqbSetVal(var sel, var value)
#endif
{
#ifdef JAVASCRIPT
	$(sel).val(value);
#else
	var str = "jqSetProp(";
	str += sel;
	str += ",";
	str += value;
	str += ")";
	println(str);
#endif
}

#ifdef JAVASCRIPT
jqbSetCss = function(sel, name, value)
#else
void jqbSetCss(var sel, var name, var value)
#endif
{
#ifdef JAVASCRIPT
	$(sel).css(name, value);
#else
	var str = "jqSetCss(";
	str += sel;
	str += ",";
	str += name;
	str += ",";
	str += value;
	str += ")";
	println(str);
#endif
}


//
// element
//

#ifdef JAVASCRIPT
jqbGetElement = function(sel)
#else
var jqbGetElement(var sel)
#endif
{
	var ret="";
	ret = jqbGetProp(sel,"outerHTML");
#ifndef JAVASCRIPT
	ret = "<div id=\"tag1\"></div>";
#endif
	return ret;
}

#ifdef JAVASCRIPT
jqbReplaceString = function(str,a,b)
#else
var jqbReplaceString(var str,var a,var b)
#endif
{
	while (str.indexOf(a) != -1){
		str = str.replace(a, "*");
	}
	while (str.indexOf("*") != -1){
		str = str.replace("*", b);
	}
	return str;
}

#ifdef JAVASCRIPT
jqbAppendString = function(sel,str)
#else
void jqbAppendString(var sel,var str)
#endif
{
#ifdef JAVASCRIPT
	ret = $(sel).parent().append(str);
#else
	var s = "jqAppendString(";
	s += sel;
	s += ",";
	s += str;
	s += ")";
	println(s);
#endif
}



#ifdef JAVASCRIPT
jqbCopyElement = function(sel,a,b)
#else
void jqbCopyElement(var sel,var a,var b)
#endif
{
	var str;
	str = jqbGetElement(sel);
	str = jqbReplaceString(str,a, b);
	jqbAppendString(sel, str);
}



//
// Input
//



#ifdef JAVASCRIPT
jqbSetInputRadioVal = function(sel, value)
#else
void jqbSetInputRadioVal(var sel, var value)
#endif
{
	var str;
	str = "input[name=" + sel;
	str += "][value=" + value;
	str+="]";
	jqbSetProp(str,"checked", true);
}

#ifdef JAVASCRIPT
jqbGetInputRadioVal = function(sel)
#else
var jqbGetInputRadioVal(var sel)
#endif
{
	var ret=NaN;
	var str;

	str = "input[name=" + sel;
	str += "]:checked";
	ret=jqbGetVal(str);
	if (typeof(ret) == "undefined")ret = "";
	return ret;
}

#ifdef JAVASCRIPT
jqbSetInputCheckVal = function(sel, value)
#else
void jqbSetInputCheckVal(var sel, var value)
#endif
{
	var str;
	str = "input[name=" + sel;
	str += "]";
	jqbSetProp(str, "checked", value);
}

#ifdef JAVASCRIPT
jqbGetInputCheckVal = function(sel)
#else
var jqbGetInputCheckVal(var sel)
#endif
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



#ifdef JAVASCRIPT
jqbMediaInit = function(sel, value)
#else
void jqbMediaInit(var sel, var value)
#endif
{
#ifdef JAVASCRIPT
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
#else
	var str;
	str = "jqbMediaInit(";
	str += sel;
	str += ",";
	str += value;
	str += ")";
	println(str);
#endif
}

#ifdef JAVASCRIPT
jqbMediaStop = function(sel)
#else
void jqbMediaStop(var sel)
#endif
{
#ifdef JAVASCRIPT
	var s = $(sel);
	try{
		s[0].pause();
	}catch (e){}
#else
	var str;
	str = "jqbMediaPause(";
	str += sel;
	str += ")";
	println(str);
#endif
}

#ifdef JAVASCRIPT
jqbMediaPlay = function(sel)
#else
void jqbMediaPlay(var sel)
#endif
{
#ifdef JAVASCRIPT
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
#else
	var str;
	str = "jqbMediaPlay(";
	str += sel;
	str += ")";
	println(str);
#endif
}


//
// end of jq_bridge
//

#endif /*  jq_bridge.h */

