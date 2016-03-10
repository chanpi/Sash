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
	// [引数]
	// int x;
	// int y;
	void SaLButtonClick( const std::vector<void*>* params );

	// マウス中ボタンをシングルクリックします。内部でSendInput()を使用します。
	// [引数]
	// int x;
	// int y;
	void SaMButtonClick( const std::vector<void*>* params );

	// マウス右ボタンをシングルクリックします。内部でSendInput()を使用します。
	// [引数]
	// int x;
	// int y;
	void SaRButtonClick( const std::vector<void*>* params );

#ifdef __cplusplus
}
#endif

#endif