#ifndef _SA_THREAD_H_
#define _SA_THREAD_H_

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

	// Sleep(0)の代わりに高パフォーマンスのコンテキストスイッチを行うための関数です。
	// 同じ優先順位の他のスレッドの実行の機会を与えます。
	// 但し、インテルSSE2に対応していないx86 アーキテクチャーでは no-op となり、何の処理も行わない命令が実行されるか、フォルトが発生します。
	// [引数] なし
	void SaYield( const std::vector<void*>* params );

	// 指定ミリ秒Sleep()を実行します。
	// 但し、オーバーヘッドが大きいため、Sleep(0)やSleep(1)などは意図したとおりに動作しない可能性があります。
	// [引数]
	// DWORD dwMilliseconds; -- スリープする時間（ミリ秒）
	void SaSleep( const std::vector<void*>* params );

#ifdef __cplusplus
}
#endif

#endif