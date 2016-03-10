#ifndef _SA_CONSOLE_H_
#define _SA_CONSOLE_H_

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif
	
	// 文字列を色付きで標準出力します。
	// [引数]
	// WORD wAttributes; -- テキストカラー。
	// LPCTSTR lpText; -- 標準出力する文字列。スペースを含む場合は""で囲ってください。
	// [色]
	// 文字青：FOREGROUND_BLUE
	// 文字緑：FOREGROUND_GREEN
	// 文字赤：FOREGROUND_RED
	// 文字白：FOREGROUND_WHITE
	void SaPrintfWithColor( const std::vector<void*>* params );

#ifdef __cplusplus
}
#endif

#endif