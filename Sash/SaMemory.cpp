#include "stdafx.h"
#include "SaMemory.h"
#include <Windows.h>
#include <TlHelp32.h>

using namespace std;

namespace {
	LPCTSTR g_szSaDumpMemory = _T("SaDumpMemory()");

	LPCTSTR g_szReadOnly	= _T("/R");
	LPCTSTR g_szReadWrite	= _T("/RW");
	LPCTSTR g_szHeapList	= _T("/H");
	LPCTSTR g_szModuleList	= _T("/M");
	LPCTSTR g_szThreadList	= _T("/T");
	LPCTSTR g_szDumpFrom	= _T("/FR");
	LPCTSTR g_szDumpTo		= _T("/TO");
	LPCTSTR g_szRedirect	= _T(">");
	LPCTSTR g_szPipe		= _T("|");

	const SIZE_T g_nMaxListCount = 4096;

	const DWORD g_dwAddressStart = 0x10000;
	const DWORD g_dwAddressEnd = 0x7FFFFFFF;
};

static SIZE_T EnumMemoryEntry( DWORD dwProcessId, DWORD dwProtect, DWORD dwListType, DWORD dwDumpFrom, DWORD dwDumpTo, MEMORY_BASIC_INFORMATION* pMbi, INT* pnMbiList, BOOL bDumpWithRange );
static VOID Dump( DWORD dwProcessId, MEMORY_BASIC_INFORMATION* pMbi, SIZE_T nMbiList );
static INT SortFunc(const void* a, const void* b);

// プロセスのメモリ領域をダンプします。
// [引数]
// DWORD dwProcessId; -- 対象のプロセスID
// その他のオプション
// [使用例]
// Sash sadumpmemory 1234 /rw /H
// Sash sadumpmemory 1234 /FR 3000000 /TO 4000000
void SaDumpMemory( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaDumpMemory, g_szError001 );
	} else if ( params->size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaDumpMemory, g_szError002 );
	} else {
		DWORD dwProcessId = 0;
		DWORD dwProtect = 0;
		DWORD dwListType = 0;
		DWORD dwDumpFrom = 0;
		DWORD dwDumpTo = 0;

		MEMORY_BASIC_INFORMATION mbi[g_nMaxListCount] = {0};
		INT nMbiList = 0;

		INT nCount = params->size();
		if ( nCount > 0 ) {
			dwProcessId = _ttol((LPCTSTR)(*params)[0]);

			DWORD* pAddress = NULL;
			for ( INT i = 1; i < nCount; i++ ) {
				if ( !_tcscmp((LPCTSTR)(*params)[i], g_szReadOnly) ) {
					dwProtect = PAGE_READONLY;
				} else if ( !_tcscmp((LPCTSTR)(*params)[i], g_szReadWrite) ) {
					dwProtect = PAGE_READWRITE;
				} else if ( !_tcscmp((LPCTSTR)(*params)[i], g_szHeapList) ) {
					dwListType |= TH32CS_SNAPHEAPLIST;
				} else if ( !_tcscmp((LPCTSTR)(*params)[i], g_szModuleList) ) {
					dwListType |= TH32CS_SNAPMODULE;
				} else if ( !_tcscmp((LPCTSTR)(*params)[i], g_szThreadList) ) {
					dwListType |= TH32CS_SNAPTHREAD;
				} else if ( !_tcscmp((LPCTSTR)(*params)[i], g_szDumpFrom) ) {
					pAddress = &dwDumpFrom;
				} else if ( !_tcscmp((LPCTSTR)(*params)[i], g_szDumpTo) ) {
					pAddress = &dwDumpTo;
				} else if ( !_tcscmp((LPCTSTR)(*params)[i], g_szRedirect) || !_tcscmp((LPCTSTR)(*params)[i], g_szPipe) ) {
					break;
				} else {
					if ( NULL != pAddress ) {
						_stscanf_s( (LPCTSTR)(*params)[i], g_szFormatX, pAddress, sizeof(DWORD) );
					}
				}
			}
		}

		if ( dwProcessId != 0 ) {
			BOOL bDumpWidthRange = dwDumpFrom != 0 || dwDumpTo != 0;
			if ( 0 == dwListType ) {
				dwListType = TH32CS_SNAPALL;
			}
			if ( 0 == dwDumpFrom ) {
				dwDumpFrom = g_dwAddressStart;
			}
			if ( 0 == dwDumpTo ) {
				dwDumpTo = g_dwAddressEnd;
			}

			// ダンプ領域をリストアップ
			EnumMemoryEntry( dwProcessId, dwProtect, dwListType, dwDumpFrom, dwDumpTo, mbi, &nMbiList, bDumpWidthRange );
			// アドレスをソート
			qsort( mbi, nMbiList, sizeof(MEMORY_BASIC_INFORMATION), SortFunc );
			// ダンプ
			Dump( dwProcessId, mbi, nMbiList );
		}
	}
}

//
// コマンドライン引数で指定された属性のメモリ領域のアドレスをリストアップします。
//
SIZE_T EnumMemoryEntry( DWORD dwProcessId, DWORD dwProtect, DWORD dwListType, DWORD dwDumpFrom, DWORD dwDumpTo, MEMORY_BASIC_INFORMATION* pMbi, INT* pnMbiList, BOOL bDumpWithRange )
{
	HEAPENTRY32 he;
	HEAPLIST32 hl;
	MODULEENTRY32 me;
	//THREADENTRY32 te;
	SIZE_T n = 0;

	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessId );
	SIZE_T sizeMB = sizeof( MEMORY_BASIC_INFORMATION );
	MEMORY_BASIC_INFORMATION mbi;

	HANDLE hSnapshot = CreateToolhelp32Snapshot( dwListType, dwProcessId );
	if ( hSnapshot == NULL || hSnapshot == INVALID_HANDLE_VALUE ) {
		return 0;
	}

	// ヒープリスト
	if ( dwListType & TH32CS_SNAPHEAPLIST && !bDumpWithRange ) {
		hl.dwSize = sizeof(HEAPLIST32);
		if ( Heap32ListFirst( hSnapshot, &hl ) ) {
		
			do {
				he.dwSize = sizeof(HEAPENTRY32);
				if (!Heap32First(&he, hl.th32ProcessID, hl.th32HeapID)) {
					break;
				}
				VirtualQueryEx( hProcess, (LPCVOID)hl.th32HeapID, &mbi, sizeMB );
				pMbi[(*pnMbiList)++] = mbi;

				{
					TCHAR szBuf[128];
					_stprintf_s( szBuf, _countof(szBuf), g_szFormatMemList, mbi.BaseAddress, mbi.RegionSize, g_szHeap );
					OutputDebugString(szBuf);
				}
			} while ( Heap32ListNext( hSnapshot, &hl ) );
		}
	}

	// スタックリスト

	// モジュールリスト
	if ( dwListType & TH32CS_SNAPMODULE && !bDumpWithRange ) {
		me.dwSize = sizeof( MODULEENTRY32 );
		if ( Module32First( hSnapshot, &me ) ) {

			do {
				VirtualQueryEx( hProcess, (LPCVOID)me.modBaseAddr, &mbi, sizeMB );
				pMbi[(*pnMbiList)++] = mbi;

				{
					TCHAR szBuf[128] = {0};
					_stprintf_s( szBuf, _countof(szBuf), g_szFormatMemList, me.modBaseAddr, me.dwSize, me.szModule );
					OutputDebugString(szBuf);
				}
			} while ( Module32Next( hSnapshot, &me ) );
		}
	}

	// そのほかのメモリ領域をリストアップ
	if ( dwListType == TH32CS_SNAPALL ) {
		DWORD dwAddress = dwDumpFrom;

		while ( dwAddress <= dwDumpTo ) {
			TCHAR szBuf[128] = {0};
			VirtualQueryEx( hProcess, (LPCVOID)dwAddress, &mbi, sizeMB );	// TODO dwAddressは次のページ境界に切り下げられる
			_stprintf_s( szBuf, _countof(szBuf), g_szFormatMemList, mbi.BaseAddress, mbi.RegionSize, mbi.Protect==PAGE_READONLY ? _T("-R--") : mbi.Protect==PAGE_READWRITE ? _T("-RW-") : _T("-??-") );
			OutputDebugString(szBuf);

			// PAGE_GUARDの領域は読み込めない？
			if ( mbi.Protect == dwProtect || (dwProtect == 0 && !(mbi.Protect & PAGE_GUARD)) ) {
				pMbi[(*pnMbiList)++] = mbi;
			}

			dwAddress += mbi.RegionSize;
		}
	}

	CloseHandle(hProcess);
	hProcess = NULL;

	CloseHandle(hSnapshot);
	hSnapshot = NULL;
	return n;
}

//
// 特定のメモリ領域をダンプします。
//
VOID Dump( DWORD dwProcessId, MEMORY_BASIC_INFORMATION* pMbi, SIZE_T nMbiList )
{
	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessId );
	SIZE_T nRead = 0;
	UCHAR* buffer = (UCHAR*)malloc(pMbi[0].RegionSize);
	SIZE_T nBufferSize = pMbi[0].RegionSize;
	if ( NULL == buffer ) {
		MessageBox( NULL, g_szError003, g_szTitle, MB_OK );
		CloseHandle( hProcess );
		hProcess = NULL;
		return;
	}
	for ( int i = 0; i < (int)nMbiList; i++ ) {
		if ( nBufferSize < pMbi[i].RegionSize ) {
			UCHAR* tmp = (UCHAR*)realloc( buffer, pMbi[i].RegionSize );
			if ( NULL != tmp ) {
				nBufferSize = pMbi[i].RegionSize;
				buffer = tmp;
			} else {
				OutputDebugString( _T("realloc() failed.\n") );
			}
		}
		if ( !ReadProcessMemory( hProcess, (LPCVOID)pMbi[i].BaseAddress, buffer, min(pMbi[i].RegionSize, nBufferSize), &nRead ) ) {
			OutputDebugString(_T("An error occuered.\n")); // 現状無視
		}
		for ( int j = 0; j < (int)nRead; j++ ) {
			printf(g_szFormatC, isprint(buffer[j]) ? buffer[j] : ' ');
		}
	}
	CloseHandle( hProcess );
	hProcess = NULL;
	free( buffer );
	buffer = NULL;
}

INT SortFunc(const void* a, const void* b)
{
	MEMORY_BASIC_INFORMATION* mbiA = (MEMORY_BASIC_INFORMATION*)a;
	MEMORY_BASIC_INFORMATION* mbiB = (MEMORY_BASIC_INFORMATION*)b;
	if ( mbiA->BaseAddress < mbiB->BaseAddress ) {
		return -1;
	} else if ( mbiA->BaseAddress > mbiB->BaseAddress ) {
		return 1;
	}
	return 0;
}