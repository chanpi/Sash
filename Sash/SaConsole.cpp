#include "stdafx.h"
#include "SaConsole.h"
#include <Windows.h>
#include <conio.h>
#include <map>
#include <string>

using namespace std;

typedef basic_string<TCHAR> tstring;

namespace {
	LPCTSTR g_szSaPrintfWithColor = _T("SaPrintfWithColor()");
};

// �������F�t���ŕW���o�͂��܂��B
// [����]
// WORD wAttributes; -- �e�L�X�g�J���[�B
// LPCTSTR lpText; -- �W���o�͂��镶����B�X�y�[�X���܂ޏꍇ��""�ň͂��Ă��������B
// [�F]
// �����FFOREGROUND_BLUE
// �����΁FFOREGROUND_GREEN
// �����ԁFFOREGROUND_RED
// �������FFOREGROUND_WHITE
void SaPrintfWithColor( const vector<void*>* params ) {
	if ( params->size() < 2 ) {
		_tprintf( g_szFormatErrorS, g_szSaPrintfWithColor, g_szError002 );
	} else {
		typedef map< tstring, WORD > TextAttributes;
		TextAttributes textAttributes;
		textAttributes.insert(make_pair(_T("FOREGROUND_BLUE"), FOREGROUND_BLUE));
		textAttributes.insert(make_pair(_T("FOREGROUND_GREEN"), FOREGROUND_GREEN));
		textAttributes.insert(make_pair(_T("FOREGROUND_RED"), FOREGROUND_RED));
		textAttributes.insert(make_pair(_T("FOREGROUND_WHITE"), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED));

		HANDLE stdHandle;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		WORD wAttributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED; // �f�t�H���g�͕����F��

		TextAttributes::iterator it = textAttributes.find( (LPCTSTR)(*params)[0] );
		if ( it != textAttributes.end() ) {
			wAttributes = it->second;
		}
		stdHandle = GetStdHandle( STD_OUTPUT_HANDLE ); // �W�����o�͂ւ̃n���h���𓾂�
		GetConsoleScreenBufferInfo( stdHandle, &csbi ); // �R���\�[���X�N���[���o�b�t�@�i���݂̏�ԁj�𓾂�
		SetConsoleTextAttribute( stdHandle, FOREGROUND_RED ); // �����F��ԂɕύX

		_tprintf_s( g_szFormatS, (LPCTSTR)(*params)[1] );
	}
}