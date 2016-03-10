#ifndef _SA_WINDOW_H_
#define _SA_WINDOW_H_

#include <Windows.h>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

	// �Ώۂ̃E�B���h�E���őO�ʂɕ\�����܂��B
	// [����] �Ȃ�
	void SaSetForegroundWindow( const std::vector<void*> params );

	// �E�B���h�E���A�N�e�B�u�ɂ��܂��B������SetActiveWindow()���Ăяo���܂��B
	// [����]
	// BOOL bSet; -- �E�B���h�E���A�N�e�B�u�ɂ��邩�A�ȑO�A�N�e�B�u�������E�B���h�E�ɖ߂����B
	// bSet��TRUE�̏ꍇ��hWnd���A�N�e�B�u�ɂ��AbSet��FALSE�̏ꍇ�́A�ȑO�A�N�e�B�u�������E�B���h�E���ēx�A�N�e�B�u�ɂ��܂��B
	// �A���A�ȑO�A�N�e�B�u�������E�B���h�E���ēx�A�N�e�B�u�ɂ���̂́A����v���Z�X���ŏ������s��ꂽ�Ƃ��̂݉\�ł��B
	void SaSetActiveWindow( const std::vector<void*> params );

	// ���b�Z�[�W�{�b�N�X��\�����܂��i�I�[�i�[�E�B���h�E�Ȃ��j�B
	// [����]
	// LPCTSTR lpText; -- �\�����郁�b�Z�[�W�B""�ň͂�ł��������B
	// LPCTSTR koCaption; -- �_�C�A���O�{�b�N�X�̃^�C�g���B""�ň͂�ł��������B
	// UINT uType; -- ���b�Z�[�W�{�b�N�X�̓��e�Ɠ���B
	//  MB_ICONEXCLAMATION, MB_ICONWARNING		���Q���i!�j�A�C�R����\�����܂��B
	//  MB_ICONINFORMATION, MB_ICONASTERISK		�ۂ̒��ɏ������́ui�v���`���ꂽ�A�C�R����\�����܂��B
	//  MB_ICONQUESTION							�^�╄�i?�j�A�C�R����\�����܂��B
	//  MB_ICONSTOP,MB_ICONERROR,MB_ICONHAND	��~�}�[�N�A�C�R����\�����܂��B
	void SaMessageBox( const std::vector<void*> params );

	HWND GetWindowHandle( VOID );

#ifdef __cplusplus
}
#endif

#endif