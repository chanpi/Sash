#include "stdafx.h"
#include "SaEnvironmentVariable.h"
#include <Windows.h>

using namespace std;

namespace {
	LPCTSTR g_szSaGetEnvironmentVariable = _T("SaGetEnvironmentVariable()");
};

// ���ϐ����̒l���o�͂��܂��B
// [����]
// LPCTSTR lpName; -- ���ϐ���
// [�B������]
// LPTSTR szBuffer; -- ���ϐ��̒l���i�[����o�b�t�@�̃|�C���^
// int nBufferLength; -- �o�b�t�@�T�C�Y
void SaGetEnvironmentVariable( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaGetEnvironmentVariable, g_szError001 );
	} else if ( params->size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaGetEnvironmentVariable, g_szError002 );
	} else {
		LPCTSTR lpName = (LPCTSTR)(*params)[0];
		if ( NULL == lpName ) {
			_tprintf_s( g_szFormatErrorS, g_szSaGetEnvironmentVariable, g_szError001 );
		} else {
			TCHAR szBuffer[g_nBufferSize] = {0};
			GetEnvironmentVariable( lpName, szBuffer, _countof(szBuffer));
			_tprintf_s( g_szFormatS, szBuffer );

			// �v���O���������ł̂݊��ϐ��̒l���󂯎���
			if ( params->size() == 3 ) {
				TCHAR* pBuffer = (TCHAR*)(*params)[1];
				int nBuffer = *((int*)(*params)[2]);
				_tcscpy_s( pBuffer, nBuffer, szBuffer );
			}
		}
	}
}

