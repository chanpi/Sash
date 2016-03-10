#ifndef _SA_ENVIRONMENT_VARIABLE_H_
#define _SA_ENVIRONMENT_VARIABLE_H_

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

	// 環境変数名の値を出力します。
	// [引数]
	// LPCTSTR lpName; -- 環境変数名
	// [隠し引数]
	// LPTSTR szBuffer; -- 環境変数の値を格納するバッファのポインタ
	// int nBufferLength; -- バッファサイズ
	void SaGetEnvironmentVariable( const std::vector<void*> params );

#ifdef __cplusplus
}
#endif

#endif