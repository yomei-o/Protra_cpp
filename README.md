# Protra_cpp
The Protra Language Interpreter in C++ (Header Only)   
Protra言語のC++実装です。  
ヘッダーオンリーのライブラリなのでヘッダーファイルをイングルードするだけで、使うことができます。  
C++の標準テンプレートと標準ライブラリのみで実装しているので、Windows,Machintosh,Linuxなどあらゆる環境で動作します。  
  
  
# How To Use
使い方  
プログラムの先頭で、#include "Protra.h"をしてください。  
  
簡単な実装例:  
 
#include "Protra.h"  
  
int main(int argc,char* argv[])  
{  
	if (argc < 2) {  
		printf("ProtraLang [filename.pt]  \n");  
		return 1;  
	}  
	std::string file = argv[1];  
	Protra::Lib::Lang::Interpreter ip(file);  
	if (ip.initialized==0) {  
		return 2;  
	}  
	ip.Execute();  
	if (ip.executed == 0) {  
		return 3;  
	}  
	return 0;  
}  
  
# コンパイルと実行方法
>g++ -o ProtraLang ProtraLang.cpp  
コマンドラインから上記のコマンドを入力することでProtra言語のインタープリタをビルドすることができます。  
  
>ProtraLang somefile.pt  
上記のコマンドを入力することでプログラムファイルを実行します。


# 未実装項目
Pythonから使えるようにする予定ですが、まだできていません。  
株価系のビルトイン関数もまだ実装できていません。  


