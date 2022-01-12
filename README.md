# Protra_cpp
The Protra Language Interpreter in C++ (Header Only)   
Protra言語のC++実装です。  
ヘッダーオンリーのライブラリなのでヘッダーファイルをイングルードするだけで、ビルドせずに使うことができます。  

# How To Use
使い方
プログラムの先頭で、#define PROTRA_LANG_IMPLをして、#include "Protra.h"をしてください。

簡単な実装例:

#define PROTRA_LANG_IMPL
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


