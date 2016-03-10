#ifndef _SA_KEYBOARD_H_
#define _SA_KEYBOARD_H_

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

	// 指定されたウィンドウにキーボードフォーカスを設定します。内部でSetFocus()を呼び出します。
	// 引数
	// BOOL bSet; -- キーボードフォーカスを指定ウィンドウに設定するか、以前のウィンドウに戻すか。
	// bSetがTRUEの場合はキーボードフォーカスを環境変数に設定したウィンドウに設定し、
	// bSetがFALSEの場合は、以前キーボードフォーカスのあったウィンドウに再度キーボードフォーカスを設定します。
	// 但し、以前のウィンドウに再度キーボードフォーカスを設定するのは、同一プロセス内で処理が行われたときのみ可能です。
	void SaSetFocus( const std::vector<void*> params );

#ifdef __cplusplus
}
#endif

#endif