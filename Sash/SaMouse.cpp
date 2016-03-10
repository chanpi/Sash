#include "stdafx.h"
#include "SaMouse.h"
#include "SaProcess.h"
#include <Windows.h>

using namespace std;

namespace {
	LPCTSTR g_szSaSetCursorPos = _T("SaSetCursorPos()");
};

static void ActMouse( DWORD type );

// �J�[�\�����w��ʒu�Ɉړ����܂��B
// [����]
// int x;
// int y;
void SaSetCursorPos( const vector<void*> params ) {
	if ( params.size() < 2 ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError002 );
	} else {
		int x = _ttoi((LPCTSTR)params[0]);
		int y = _ttoi((LPCTSTR)params[1]);
		SetCursorPos( x, y );
	}
}

// �}�E�X���{�^�����V���O���N���b�N���܂��B������SendInput()���g�p���܂��B
// [����]
// int x;
// int y;
void SaLbuttonClick( const vector<void*> params ) {
	SaSetCursorPos( params );
	ActMouse( MOUSEEVENTF_LEFTDOWN );
}

// �}�E�X���{�^�����V���O���N���b�N���܂��B������SendInput()���g�p���܂��B
// [����]
// int x;
// int y;
void SaMbuttonClick( const vector<void*> params ) {
	SaSetCursorPos( params );
	ActMouse( MOUSEEVENTF_MIDDLEDOWN );
}

// �}�E�X�E�{�^�����V���O���N���b�N���܂��B������SendInput()���g�p���܂��B
// [����]
// int x;
// int y;
void SaRbuttonClick( const vector<void*> params ) {
	SaSetCursorPos( params );
	ActMouse( MOUSEEVENTF_RIGHTDOWN );
}

// SendInput�֐��𗘗p���āA�}�E�X�N���b�N���s���܂��B
void ActMouse( DWORD type ) {
	INPUT input[1] = {0};
	MOUSEINPUT mi[1] = {0};

	mi[0].dwFlags = type;
	input[0].type = INPUT_MOUSE;
	input[0].mi = mi[0];
	SendInput(1, input, sizeof(INPUT));
	//SaYield( NULL );
	Sleep(0);
}