#include "stdafx.h"
#include "SaKeyboard.h"
#include "SaWindow.h"
#include <Windows.h>

using namespace std;

namespace {
	LPCTSTR g_szSaSetFocus = _T("SaSetFocus()");
};

// 指定されたウィンドウにキーボードフォーカスを設定します。内部でSetFocus()を呼び出します。
// [引数]
// BOOL bSet; -- キーボードフォーカスを指定ウィンドウに設定するか、以前のウィンドウに戻すか。
// bSetがTRUEの場合はキーボードフォーカスを環境変数に設定したウィンドウに設定し、
// bSetがFALSEの場合は、以前キーボードフォーカスのあったウィンドウに再度キーボードフォーカスを設定します。
// 但し、以前のウィンドウに再度キーボードフォーカスを設定するのは、同一プロセス内で処理が行われたときのみ可能です。
void SaSetFocus( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaSetFocus, g_szError001 );
	} else if ( params->size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaSetFocus, g_szError002 );
	} else {
		static HWND hOldWnd = NULL;
		BOOL bSet = (0 == _tcsicmp( (LPCTSTR)(*params)[0], g_szTRUE )) ? TRUE : FALSE;
		if ( bSet ) {
			hOldWnd = SetFocus( GetWindowHandle() );
		} else {
			SetFocus( hOldWnd );
		}
	}
}