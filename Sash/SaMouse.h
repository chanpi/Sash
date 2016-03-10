#ifndef _SA_MOUSE_H_
#define _SA_MOUSE_H_

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

	// カーソルを指定位置に移動します。
	// 引数
	// int x;
	// int y;
	void SaSetCursorPos( const std::vector<void*>* params );

	// マウス左ボタンをシングルクリックします。内部でSendInput()を使用します。
	// [引数] なし
	void SaLButtonClick( const std::vector<void*>* params );

	// マウス中ボタンをシングルクリックします。内部でSendInput()を使用します。
	// [引数] なし
	void SaMButtonClick( const std::vector<void*>* params );

	// マウス右ボタンをシングルクリックします。内部でSendInput()を使用します。
	// [引数] なし
	void SaRButtonClick( const std::vector<void*>* params );

	// 指定ウィンドウをマウス左ボタンをシングルクリックします。
	// 内部でSendInput()を使用します。ウィンドウハンドルは環境変数で設定します。
	// ボタンを押してから離すまでのミリ秒間隔を指定します（0ミリ秒以上）。
	// [引数] 
	// DWORD dwSleepMilliseconds; -- マウスダウンからアップまでの経過時間
	void SaLButtonClickOnWindow( const std::vector<void*>* params );

	// 指定ウィンドウをマウス中ボタンをシングルクリックします。
	// 内部でSendInput()を使用します。ウィンドウハンドルは環境変数で設定します。
	// ボタンを押してから離すまでのミリ秒間隔を指定します（0ミリ秒以上）。
	// [引数]
	// DWORD dwSleepMilliseconds; -- マウスダウンからアップまでの経過時間
	void SaMButtonClickOnWindow( const std::vector<void*>* params );

	// 指定ウィンドウをマウス右ボタンをシングルクリックします。
	// 内部でSendInput()を使用します。ウィンドウハンドルは環境変数で設定します。
	// ボタンを押してから離すまでのミリ秒間隔を指定します（0ミリ秒以上）。
	// [引数]
	// DWORD dwSleepMilliseconds; -- マウスダウンからアップまでの経過時間
	void SaRButtonClickOnWindow( const std::vector<void*>* params );

#ifdef __cplusplus
}
#endif

#endif