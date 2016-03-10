#ifndef _SA_MEMORY_H_
#define _SA_MEMORY_H_

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

	// プロセスのメモリ領域をダンプします。
	// [引数]
	// DWORD dwProcessId; -- 対象のプロセスID
	// その他のオプション
	// [使用例]
	// Sash sadumpmemory 1234 /rw /H
	// Sash sadumpmemory 1234 /FR 3000000 /TO 4000000
	void SaDumpMemory( const std::vector<void*> params );

#ifdef __cplusplus
}
#endif

#endif