# Protra_cpp
The Protra Language Interpreter in C++ (Header Only)   
Protra言語のC++実装です。  
ヘッダーオンリーのライブラリなのでヘッダーファイルをイングルードするだけで、使うことができます。  
C++の標準テンプレートと標準ライブラリのみで実装しているので、Windows,Machintosh,Linuxなどあらゆる環境で動作します。  
  
  
### How To Use
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
 
 
### コンパイルと実行方法
g++ -o ProtraLang ProtraLang.cpp  
コマンドラインから上記のコマンドを入力することでProtra言語のインタープリタをビルドすることができます。  
 
 
ProtraLang somefile.pt  
上記のコマンドを入力することでプログラムファイルを実行します。 
 
 
# PtsimConsole
システムトレードの損益シミュレーションを行うソフト、PtSimのC++移植版です。 
コンソールで動くようにしました。 
 
 
### コンパイルと実行方法
g++ -o PtsimConsole PtsimCionsole.cpp 
コマンドラインから上記のコマンドを入力することでPtSimのコンソール版をビルドすることができます。  
 
PtsimConsole system.pt 1301 
上記のようにプログラム名と証券コードをプログラムに渡すことで損益シミュレーションプログラムを実行します。 
 
 
### 企業データと株価データの配置
dataフォルダを作成して、その中にProtraと同じように企業データと株価データを置いてください。 
 
 
# CppSample
システムトレードの損益シミュレーション部分をC言語から呼び出して使うサンプルです。 
 
 
### コンパイルと実行方法
g++ -o CppSmaple CppSample.cpp 
コマンドラインから上記のコマンドを入力することでCppSampleをビルドすることができます。  
   
 
# 未実装項目
Pythonから使えるようにする予定ですが、まだできていません。 
 
 
