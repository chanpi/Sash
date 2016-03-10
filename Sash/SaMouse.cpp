#include "stdafx.h"
#include "SaMouse.h"
#include "SaProcess.h"
#include "SaWindow.h"
#include <Windows.h>

using namespace std;

namespace {
	LPCTSTR g_szSaSetCursorPos = _T("SaSetCursorPos()");
	LPCTSTR g_szSaLButtonClick = _T("SaLButtonClick()");
	LPCTSTR g_szSaMButtonClick = _T("SaMButtonClick()");
	LPCTSTR g_szSaRButtonClick = _T("SaRButtonClick()");
};

static void ClickOnAttachedWindowWithSleep( DWORD downType, DWORD upType, DWORD dwSleepMilliseconds );
static void SendMouseInput( DWORD type );

// �J�[�\�����w��ʒu�Ɉړ����܂��B
// [����]
// int x;
// int y;
void SaSetCursorPos( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError001 );
	} else if ( params->size() < 2 ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError002 );
	} else {
		int x = _ttoi((LPCTSTR)(*params)[0]);
		int y = _ttoi((LPCTSTR)(*params)[1]);
		SetCursorPos( x, y );
	}
}

// �}�E�X�����N���b�N���܂��B������SendInput()���g�p���܂��B
// [����] �Ȃ�
void SaLButtonClick( const vector<void*>* /*params*/ ) {
	SendMouseInput( MOUSEEVENTF_LEFTDOWN );
	SendMouseInput( MOUSEEVENTF_LEFTUP );
}

// �}�E�X�𒆃N���b�N���܂��B������SendInput()���g�p���܂��B
// [����] �Ȃ�
void SaMButtonClick( const vector<void*>* /*params*/ ) {
	SendMouseInput( MOUSEEVENTF_MIDDLEDOWN );
	SendMouseInput( MOUSEEVENTF_MIDDLEUP );
}

// �}�E�X���E�N���b�N���܂��B������SendInput()���g�p���܂��B
// [����] �Ȃ�
void SaRButtonClick( const vector<void*>* /*params*/ ) {
	SendMouseInput( MOUSEEVENTF_MIDDLEDOWN );
	SendMouseInput( MOUSEEVENTF_MIDDLEUP );
}

// �w��E�B���h�E���}�E�X���{�^�����V���O���N���b�N���܂��B
// ������SendInput()���g�p���܂��B�E�B���h�E�n���h���͊��ϐ��Őݒ肵�܂��B
// �{�^���������Ă��痣���܂ł̃~���b�Ԋu���w�肵�܂��i0�~���b�ȏ�j�B
// [����] 
// DWORD dwSleepMilliseconds; -- �}�E�X�_�E������A�b�v�܂ł̌o�ߎ���
void SaLButtonClickOnWindow( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError001 );
	} else if ( params->size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError002 );
	} else {
		DWORD dwSleepMilliseconds = _ttoi((LPCTSTR)(*params)[0]);
		ClickOnAttachedWindowWithSleep( MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP, dwSleepMilliseconds );
	}
}

// �w��E�B���h�E���}�E�X���{�^�����V���O���N���b�N���܂��B
// ������SendInput()���g�p���܂��B�E�B���h�E�n���h���͊��ϐ��Őݒ肵�܂��B
// �{�^���������Ă��痣���܂ł̃~���b�Ԋu���w�肵�܂��i0�~���b�ȏ�j�B
// [����]
// DWORD dwSleepMilliseconds; -- �}�E�X�_�E������A�b�v�܂ł̌o�ߎ���
void SaMButtonClickOnWindow( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError001 );
	} else if ( params->size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError002 );
	} else {
		DWORD dwSleepMilliseconds = _ttoi((LPCTSTR)(*params)[0]);
		ClickOnAttachedWindowWithSleep( MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_MIDDLEUP, dwSleepMilliseconds );
	}
}

// �w��E�B���h�E���}�E�X�E�{�^�����V���O���N���b�N���܂��B
// ������SendInput()���g�p���܂��B�E�B���h�E�n���h���͊��ϐ��Őݒ肵�܂��B
// �{�^���������Ă��痣���܂ł̃~���b�Ԋu���w�肵�܂��i0�~���b�ȏ�j�B
// [����]
// DWORD dwSleepMilliseconds; -- �}�E�X�_�E������A�b�v�܂ł̌o�ߎ���
void SaRButtonClickOnWindow( const vector<void*>* params ) {
	if ( NULL == params ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError001 );
	} else if ( params->size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaSetCursorPos, g_szError002 );
	} else {
		DWORD dwSleepMilliseconds = _ttoi((LPCTSTR)(*params)[0]);
		ClickOnAttachedWindowWithSleep( MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP, dwSleepMilliseconds );
	}
}

// ���͏����@�\��{�v���O�����ɃA�^�b�`��ASleep�������������N���b�N���s���܂��B
// Sleep()���g�p���邱�Ƃŕ����I�ȃN���b�N�ɋ߂Â��܂��B
// [����]
// DWORD downType; -- MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_RIGHTDOWN
// DWORD upType; -- MOUSEEVENTF_LEFTUP | MOUSEEVENTF_MIDDLEUP | MOUSEEVENTF_RIGHTUP
// DWORD dwSleepMilliseconds; -- �}�E�X�_�E������A�b�v�܂ł̌o�ߎ���
void ClickOnAttachedWindowWithSleep( DWORD downType, DWORD upType, DWORD dwSleepMilliseconds ) {
	DWORD dwProcessId = 0;
	DWORD dwThreadId = GetWindowThreadProcessId( GetWindowHandle(), &dwProcessId );
	// ���͂�{�v���O�����̃X���b�h�ɃA�^�b�`
	AttachThreadInput( GetCurrentThreadId(), dwThreadId, TRUE );
	SendMouseInput( downType );
	if ( 1 < dwSleepMilliseconds ) {
		Sleep( dwSleepMilliseconds );
	} else {
		SaYield( NULL );
	}
	SendMouseInput( upType );
	if ( 1 < dwSleepMilliseconds ) {
		Sleep( dwSleepMilliseconds );
	} else {
		SaYield( NULL );
	}
	// ���͂��f�^�b�`
	AttachThreadInput( GetCurrentThreadId(), dwThreadId, FALSE );
}

// SendInput�֐��𗘗p���āA�}�E�X�N���b�N���s���܂��B
void SendMouseInput( DWORD type ) {
	INPUT input[1] = {0};
	MOUSEINPUT mi[1] = {0};

	mi[0].dwFlags = type;
	input[0].type = INPUT_MOUSE;
	input[0].mi = mi[0];
	SendInput(1, input, sizeof(INPUT));
	SaYield( NULL );
}