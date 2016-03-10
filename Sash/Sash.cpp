// Sash.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "SaConsole.h"
#include "SaEnvironmentVariable.h"
#include "SaKeyboard.h"
#include "SaMemory.h"
#include "SaMouse.h"
#include "SaProcess.h"
#include "SaWindow.h"
#include <Windows.h>
#include <map>
#include <string>

#include <conio.h>

using namespace std;
typedef basic_string<TCHAR> tstring;

//int _tmain(int argc, _TCHAR* argv[])
int WINAPI WinMain( HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, INT /*nCmdShow*/ )
{
	int nArgs;
	LPTSTR* lpArgs = CommandLineToArgvW(GetCommandLine(), &nArgs);
	typedef map< tstring, void (*)( const vector<void*>* ) > SaFuncType;
	
	_tsetlocale( LC_ALL, g_szLocale );

	if ( nArgs < 2 || !_tcscmp(lpArgs[1], g_szHelp) ) {
		_tprintf_s( g_szFormatS, g_szUsage );
		return EXIT_SUCCESS;
	}

	SaFuncType functions;
	// キー（関数名はすべて小文字で登録すること）
	functions.insert( make_pair( _T("saprintfwithcolor"), SaPrintfWithColor ) );
	functions.insert( make_pair( _T("sagetenvironmentvariable"), SaGetEnvironmentVariable ) );
	functions.insert( make_pair( _T("sasetfocus"), SaSetFocus ) );
	functions.insert( make_pair( _T("sadumpmemory"), SaDumpMemory ) );
	functions.insert( make_pair( _T("sasetcursorpos"), SaSetCursorPos ) );
	functions.insert( make_pair( _T("sayield"), SaYield ) );
	functions.insert( make_pair( _T("sasleep"), SaSleep ) );
	functions.insert( make_pair( _T("sasetforegroundwindow"), SaSetForegroundWindow ) );
	functions.insert( make_pair( _T("sasetactivewindow"), SaSetActiveWindow ) );
	functions.insert( make_pair( _T("samessagebox"), SaMessageBox ) );

	// 引数に指定された関数を検索
	TCHAR szFunctionName[ g_nName ] = {0};
	INT nLength = (INT)_tcslen( lpArgs[1] );
	for ( INT i = 0; i < nLength; i++ ) {
		szFunctionName[i] = _totlower( lpArgs[1][i] );
	}

	SaFuncType::iterator it = functions.find( szFunctionName );
	if ( it != functions.end() ) {
		// 該当したら、残りの引数をvectorに格納し関数を呼び出す
		vector<void*> params;
		for ( INT i = 2; i < nArgs; i++ ) {
			params.push_back( lpArgs[i] );
		}
		it->second( &params );
	} else {
		_tprintf( g_szError000 );
	}

	return EXIT_SUCCESS;
}
