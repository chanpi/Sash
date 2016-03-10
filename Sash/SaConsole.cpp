#include "stdafx.h"
#include "SaConsole.h"
#include <Windows.h>
#include <conio.h>
#include <map>
#include <string>

using namespace std;

typedef basic_string<TCHAR> tstring;

namespace {
	LPCTSTR g_szSaPrintfWithColor = _T("SaPrintfWithColor()");
};

// 文字列を色付きで標準出力します。
// [引数]
// WORD wAttributes; -- テキストカラー。
// LPCTSTR lpText; -- 標準出力する文字列。スペースを含む場合は""で囲ってください。
// [色]
// 文字青：FOREGROUND_BLUE
// 文字緑：FOREGROUND_GREEN
// 文字赤：FOREGROUND_RED
// 文字白：FOREGROUND_WHITE
void SaPrintfWithColor( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaPrintfWithColor, g_szError001 );
	} else if ( params->size() < 2 ) {
		_tprintf( g_szFormatErrorS, g_szSaPrintfWithColor, g_szError002 );
	} else {
		typedef map< tstring, WORD > TextAttributes;
		TextAttributes textAttributes;
		textAttributes.insert(make_pair(_T("FOREGROUND_BLUE"), FOREGROUND_BLUE));
		textAttributes.insert(make_pair(_T("FOREGROUND_GREEN"), FOREGROUND_GREEN));
		textAttributes.insert(make_pair(_T("FOREGROUND_RED"), FOREGROUND_RED));
		textAttributes.insert(make_pair(_T("FOREGROUND_WHITE"), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED));

		HANDLE stdHandle;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		WORD wAttributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED; // デフォルトは文字色白

		TextAttributes::iterator it = textAttributes.find( (LPCTSTR)(*params)[0] );
		if ( it != textAttributes.end() ) {
			wAttributes = it->second;
		}
		stdHandle = GetStdHandle( STD_OUTPUT_HANDLE ); // 標準入出力へのハンドルを得る
		GetConsoleScreenBufferInfo( stdHandle, &csbi ); // コンソールスクリーンバッファ（現在の状態）を得る
		SetConsoleTextAttribute( stdHandle, FOREGROUND_RED ); // 文字色を赤に変更

		_tprintf_s( g_szFormatS, (LPCTSTR)(*params)[1] );
	}
}