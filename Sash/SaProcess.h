#ifndef _SA_THREAD_H_
#define _SA_THREAD_H_

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

	// Sleep(0)�̑���ɍ��p�t�H�[�}���X�̃R���e�L�X�g�X�C�b�`���s�����߂̊֐��ł��B
	// �����D�揇�ʂ̑��̃X���b�h�̎��s�̋@���^���܂��B
	// �A���A�C���e��SSE2�ɑΉ����Ă��Ȃ�x86 �A�[�L�e�N�`���[�ł� no-op �ƂȂ�A���̏������s��Ȃ����߂����s����邩�A�t�H���g���������܂��B
	// [����] �Ȃ�
	void SaYield( const std::vector<void*>* params );

	// �w��~���bSleep()�����s���܂��B
	// �A���A�I�[�o�[�w�b�h���傫�����߁ASleep(0)��Sleep(1)�Ȃǂ͈Ӑ}�����Ƃ���ɓ��삵�Ȃ��\��������܂��B
	// [����]
	// DWORD dwMilliseconds; -- �X���[�v���鎞�ԁi�~���b�j
	void SaSleep( const std::vector<void*>* params );

#ifdef __cplusplus
}
#endif

#endif