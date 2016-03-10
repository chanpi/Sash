#include "stdafx.h"
#include "SaProcess.h"
#include <Windows.h>

using namespace std;

namespace {
	LPCTSTR g_szSaSleep = _T("SaSleep()");
};

// Sleep(0)�̑���ɍ��p�t�H�[�}���X�̃R���e�L�X�g�X�C�b�`���s�����߂̊֐��ł��B
// �����D�揇�ʂ̑��̃X���b�h�̎��s�̋@���^���܂��B
// �A���A�C���e��SSE2�ɑΉ����Ă��Ȃ�x86 �A�[�L�e�N�`���[�ł� no-op �ƂȂ�A���̏������s��Ȃ����߂����s����邩�A�t�H���g���������܂��B
// [����] �Ȃ�
// http://www.isus.jp/article/parallel-special/benefitting-sleep-loops/
void SaYield( const vector<void*> params ) {
	_mm_pause();
}

// �w��~���bSleep()�����s���܂��B
// �A���A�I�[�o�[�w�b�h���傫�����߁ASleep(0)��Sleep(1)�Ȃǂ͈Ӑ}�����Ƃ���ɓ��삵�Ȃ��\��������܂��B
// [����]
// DWORD dwMilliseconds; -- �X���[�v���鎞�ԁi�~���b�j
// http://www.isus.jp/article/parallel-special/benefitting-sleep-loops/
void SaSleep( const vector<void*> params ) {
	if ( params.size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaSleep, g_szError002 );
	} else {
		DWORD dwMilliseconds = _ttoi((LPCTSTR)params[0]);
		if ( dwMilliseconds <= 1 ) {
			SaYield( params );
		} else {
			Sleep( dwMilliseconds );
		}
	}
}