#ifndef _SA_MOUSE_H_
#define _SA_MOUSE_H_

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

	// �J�[�\�����w��ʒu�Ɉړ����܂��B
	// ����
	// int x;
	// int y;
	void SaSetCursorPos( const std::vector<void*>* params );

	// �}�E�X���{�^�����V���O���N���b�N���܂��B������SendInput()���g�p���܂��B
	// [����] �Ȃ�
	void SaLButtonClick( const std::vector<void*>* params );

	// �}�E�X���{�^�����V���O���N���b�N���܂��B������SendInput()���g�p���܂��B
	// [����] �Ȃ�
	void SaMButtonClick( const std::vector<void*>* params );

	// �}�E�X�E�{�^�����V���O���N���b�N���܂��B������SendInput()���g�p���܂��B
	// [����] �Ȃ�
	void SaRButtonClick( const std::vector<void*>* params );

	// �w��E�B���h�E���}�E�X���{�^�����V���O���N���b�N���܂��B
	// ������SendInput()���g�p���܂��B�E�B���h�E�n���h���͊��ϐ��Őݒ肵�܂��B
	// �{�^���������Ă��痣���܂ł̃~���b�Ԋu���w�肵�܂��i0�~���b�ȏ�j�B
	// [����] 
	// DWORD dwSleepMilliseconds; -- �}�E�X�_�E������A�b�v�܂ł̌o�ߎ���
	void SaLButtonClickOnWindow( const std::vector<void*>* params );

	// �w��E�B���h�E���}�E�X���{�^�����V���O���N���b�N���܂��B
	// ������SendInput()���g�p���܂��B�E�B���h�E�n���h���͊��ϐ��Őݒ肵�܂��B
	// �{�^���������Ă��痣���܂ł̃~���b�Ԋu���w�肵�܂��i0�~���b�ȏ�j�B
	// [����]
	// DWORD dwSleepMilliseconds; -- �}�E�X�_�E������A�b�v�܂ł̌o�ߎ���
	void SaMButtonClickOnWindow( const std::vector<void*>* params );

	// �w��E�B���h�E���}�E�X�E�{�^�����V���O���N���b�N���܂��B
	// ������SendInput()���g�p���܂��B�E�B���h�E�n���h���͊��ϐ��Őݒ肵�܂��B
	// �{�^���������Ă��痣���܂ł̃~���b�Ԋu���w�肵�܂��i0�~���b�ȏ�j�B
	// [����]
	// DWORD dwSleepMilliseconds; -- �}�E�X�_�E������A�b�v�܂ł̌o�ߎ���
	void SaRButtonClickOnWindow( const std::vector<void*>* params );

#ifdef __cplusplus
}
#endif

#endif