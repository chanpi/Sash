#include "stdafx.h"
#include "SaKeyboard.h"
#include "SaWindow.h"
#include <Windows.h>

using namespace std;

namespace {
	LPCTSTR g_szSaSetFocus = _T("SaSetFocus()");
};

// �w�肳�ꂽ�E�B���h�E�ɃL�[�{�[�h�t�H�[�J�X��ݒ肵�܂��B������SetFocus()���Ăяo���܂��B
// [����]
// BOOL bSet; -- �L�[�{�[�h�t�H�[�J�X���w��E�B���h�E�ɐݒ肷�邩�A�ȑO�̃E�B���h�E�ɖ߂����B
// bSet��TRUE�̏ꍇ�̓L�[�{�[�h�t�H�[�J�X�����ϐ��ɐݒ肵���E�B���h�E�ɐݒ肵�A
// bSet��FALSE�̏ꍇ�́A�ȑO�L�[�{�[�h�t�H�[�J�X�̂������E�B���h�E�ɍēx�L�[�{�[�h�t�H�[�J�X��ݒ肵�܂��B
// �A���A�ȑO�̃E�B���h�E�ɍēx�L�[�{�[�h�t�H�[�J�X��ݒ肷��̂́A����v���Z�X���ŏ������s��ꂽ�Ƃ��̂݉\�ł��B
void SaSetFocus( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaSetFocus, g_szError001 );
	} else if ( params->size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaSetFocus, g_szError002 );
	} else {
		static HWND hOldWnd = NULL;
		BOOL bSet = (0 == _tcsicmp( (LPCTSTR)(*params)[0], g_szTRUE )) ? TRUE : FALSE;
		if ( bSet ) {
			hOldWnd = SetFocus( GetWindowHandle() );
		} else {
			SetFocus( hOldWnd );
		}
	}
}