#include "stdafx.h"
#include "SaWindow.h"
#include "SaEnvironmentVariable.h"
#include <map>
#include <string>

using namespace std;
typedef basic_string<TCHAR> tstring;

static BOOL CALLBACK EnumChildProc( HWND hWnd , LPARAM lParam );

namespace {
	// 子ウィンドウを取得する場合のクラス名およびウィンドウ名を格納するバッファ。
	// EnumChildWindows()のコールバック関数と呼び出し元との間でデータを共有します。
	TCHAR g_szClassNameChild[ g_nName ] = {0};
	TCHAR g_szWindowNameChild[ g_nName ] = {0};

	LPCTSTR g_szSaSetActiveWindow = _T("SaSetActiveWindow()");
	LPCTSTR g_szSaMessageBox = _T("SaMessageBox()");
};

// 対象のウィンドウを最前面に表示します。
// [引数] なし
void SaSetForegroundWindow( const vector<void*> params ) {
	// ウィンドウハンドルは環境変数から検索するためコメントアウト
	//HWND hWnd = (HWND)params[0];
	SetForegroundWindow( GetWindowHandle() );
}

// ウィンドウをアクティブにします。内部でSetActiveWindow()を呼び出します。
// [引数]
// BOOL bSet;
// bSetがTRUEの場合はhWndをアクティブにし、bSetがFALSEの場合は、以前アクティブだったウィンドウを再度アクティブにします。
// 但し、以前アクティブだったウィンドウを再度アクティブにするのは、同一プロセス内で処理が行われたときのみ可能です。
void SaSetActiveWindow( const vector<void*> params ) {
	if ( params.size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaSetActiveWindow, g_szError002 );
	} else {
		static HWND hOldWnd = NULL;
		BOOL bSet = (0 == _tcsicmp( (LPCTSTR)params[0], g_szTRUE )) ? TRUE : FALSE;

		if ( bSet ) {
			hOldWnd = SetActiveWindow( GetWindowHandle() );
		} else if ( hOldWnd ) {
			SetActiveWindow( hOldWnd );
		}
	}
}

// メッセージボックスを表示します（オーナーウィンドウなし）。
// [引数]
// LPCTSTR lpText; -- 表示するメッセージ。
// LPCTSTR lpCaption; -- ダイアログボックスのタイトル。
// UINT uType; -- メッセージボックスの内容と動作。
//  MB_ICONEXCLAMATION, MB_ICONWARNING		感嘆符（!）アイコンを表示します。
//  MB_ICONINFORMATION, MB_ICONASTERISK		丸の中に小文字の「i」が描かれたアイコンを表示します。
//  MB_ICONQUESTION							疑問符（?）アイコンを表示します。
//  MB_ICONSTOP,MB_ICONERROR,MB_ICONHAND	停止マークアイコンを表示します。
void SaMessageBox( const vector<void*> params ) {
	if ( params.size() < 3 ) {
		_tprintf( g_szFormatErrorS, g_szSaMessageBox, g_szError002 );
	} else {
		UINT uType = MB_OK;
		TCHAR szUtype[ g_nName ] = {0};
		LPTSTR pNext = NULL;

		typedef map< tstring, UINT > MessageBoxType;
		MessageBoxType mboxType;
		mboxType.insert(make_pair(_T("MB_ICONEXCLAMATION"), MB_ICONEXCLAMATION));
		mboxType.insert(make_pair(_T("MB_ICONWARNING"), MB_ICONWARNING));
		mboxType.insert(make_pair(_T("MB_ICONINFORMATION"), MB_ICONINFORMATION));
		mboxType.insert(make_pair(_T("MB_ICONASTERISK"), MB_ICONASTERISK));
		mboxType.insert(make_pair(_T("MB_ICONQUESTION"), MB_ICONQUESTION));
		mboxType.insert(make_pair(_T("MB_ICONSTOP"), MB_ICONSTOP));
		mboxType.insert(make_pair(_T("MB_ICONERROR"), MB_ICONERROR));
		mboxType.insert(make_pair(_T("MB_ICONHAND"), MB_ICONHAND));
		mboxType.insert(make_pair(_T("MB_OK"), MB_OK));
		//mboxType.insert(make_pair(_T(""), ));

		_tcscpy_s( szUtype, _countof(szUtype), (LPCTSTR)params[2] );
		LPCTSTR pType = _tcstok_s( szUtype, g_szBar, &pNext );
		MessageBoxType::iterator it;
		while ( NULL != pType ) {
			it = mboxType.find( pType );
			if ( it != mboxType.end() ) {
				uType |= it->second;
			}
			pType = _tcstok_s( NULL, g_szBar, &pNext );
		}

		MessageBox( NULL, (LPCTSTR)params[0], (LPCTSTR)params[1], uType );
	}
}

// ウィンドウハンドルを取得します。
// 環境変数の"SA_HWND_CLASSNAME_PARENT", "SA_HWND_WINDOWNAME_PARENT", "SA_HWND_CLASSNAME_CHILD", "SA_HWND_WINDOWNAME_CHILD"を参照します。
// 環境変数に"SA_HWND_CLASSNAME_CHILD", "SA_HWND_WINDOWNAME_CHILD"のいずれも設定されていない場合には親ウィンドウのウィンドウハンドルを、
// そうでない場合には子ウィンドウのウィンドウハンドルを返します。
HWND GetWindowHandle( VOID ) {
	TCHAR szClassNameParent[ g_nName ] = {0};
	TCHAR szWindowNameParent[ g_nName ] = {0};
	HWND hWndParent = NULL;
	HWND hWndChild = NULL;
	
	vector<void*> params;
	int nBuf = _countof(szClassNameParent);
	// 親ウィンドウを検索
	params.push_back( (void*)g_szSaHwndClassNameParent );
	params.push_back( szClassNameParent );
	params.push_back( &nBuf );
	SaGetEnvironmentVariable( params );
	params.clear();
	params.push_back( (void*)g_szSaHwndWindowNameParent );
	params.push_back( szWindowNameParent );
	nBuf = _countof(szWindowNameParent);
	params.push_back( &nBuf );
	SaGetEnvironmentVariable( params );

	hWndParent = FindWindow( szClassNameParent, szWindowNameParent );
	if ( NULL != hWndParent ) {
		// 子ウィンドウの指定があるか確認
		params.clear();
		params.push_back( (void*)g_szSaHwndClassNameChild );
		params.push_back( g_szClassNameChild );
		nBuf = _countof(g_szClassNameChild);
		params.push_back( &nBuf );
		SaGetEnvironmentVariable( params );

		params.clear();
		params.push_back( (void*)g_szSaHwndWindowNameChild );
		params.push_back( g_szWindowNameChild );
		nBuf = _countof(g_szWindowNameChild);
		params.push_back( &nBuf );
		SaGetEnvironmentVariable( params );
		if ( 0 == _tcslen( g_szClassNameChild ) && 0 == _tcslen( g_szWindowNameChild ) ) {
			// 子ウィンドウの指定なし
			return hWndParent;
		} else {
			EnumChildWindows( hWndParent, EnumChildProc, (LPARAM)&hWndChild );
			return hWndChild;
		}
	}
	return NULL;
}

// 子ウィンドウを列挙するコールバック関数です。
// 指定したクラス名及びウィンドウキャプションに合致する場合、LPARAMを介してウィンドウハンドルを返します。
BOOL CALLBACK EnumChildProc( HWND hWnd , LPARAM lParam )
{
	TCHAR szClassName[ g_nName ] = {0};
	TCHAR szWindowName[ g_nName ] = {0};
	GetClassName( hWnd, szClassName, _countof(szClassName) );
	GetWindowText( hWnd, szWindowName, _countof(szWindowName) );
	if ( !_tcscmp( szClassName, g_szClassNameChild ) && !_tcscmp( szWindowName, g_szWindowNameChild ) ) {
		HWND* hWndTarget = (HWND*)lParam;
		*hWndTarget = hWnd;
		return FALSE;
	}
	return TRUE;
}