#ifndef JS_INCLUDE_H_
#define JS_INCLUDE_H_
#ifdef JAVASCRIPT
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
#endif /* JAVASCRIPT */


#ifndef JAVASCRIPT
#define declare_var_begin(b,a) var a; class var_init_##a { public: var_init_##a (){
#define declare_var_end(a) }}; static var_init_##a var_init_##a;
#endif

#endif /* JS_INCLUDE_H_ */
