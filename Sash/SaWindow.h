#ifndef _SA_WINDOW_H_
#define _SA_WINDOW_H_

#include <Windows.h>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

	// 対象のウィンドウを最前面に表示します。
	// [引数] なし
	void SaSetForegroundWindow( const std::vector<void*>* params );

	// ウィンドウをアクティブにします。内部でSetActiveWindow()を呼び出します。
	// [引数]
	// BOOL bSet; -- ウィンドウをアクティブにするか、以前アクティブだったウィンドウに戻すか。
	// bSetがTRUEの場合はhWndをアクティブにし、bSetがFALSEの場合は、以前アクティブだったウィンドウを再度アクティブにします。
	// 但し、以前アクティブだったウィンドウを再度アクティブにするのは、同一プロセス内で処理が行われたときのみ可能です。
	void SaSetActiveWindow( const std::vector<void*>* params );

	// メッセージボックスを表示します（オーナーウィンドウなし）。
	// [引数]
	// LPCTSTR lpText; -- 表示するメッセージ。""で囲んでください。
	// LPCTSTR koCaption; -- ダイアログボックスのタイトル。""で囲んでください。
	// UINT uType; -- メッセージボックスの内容と動作。
	//  MB_ICONEXCLAMATION, MB_ICONWARNING		感嘆符（!）アイコンを表示します。
	//  MB_ICONINFORMATION, MB_ICONASTERISK		丸の中に小文字の「i」が描かれたアイコンを表示します。
	//  MB_ICONQUESTION							疑問符（?）アイコンを表示します。
	//  MB_ICONSTOP,MB_ICONERROR,MB_ICONHAND	停止マークアイコンを表示します。
	void SaMessageBox( const std::vector<void*>* params );

	HWND GetWindowHandle( VOID );

#ifdef __cplusplus
}
#endif

#endif