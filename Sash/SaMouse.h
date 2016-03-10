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
	void SaSetCursorPos( const std::vector<void*> params );

	// �}�E�X���{�^�����V���O���N���b�N���܂��B������SendInput()���g�p���܂��B
	// [����]
	// int x;
	// int y;
	void SaLbuttonClick( const std::vector<void*> params );

	// �}�E�X���{�^�����V���O���N���b�N���܂��B������SendInput()���g�p���܂��B
	// [����]
	// int x;
	// int y;
	void SaMbuttonClick( const std::vector<void*> params );

	// �}�E�X�E�{�^�����V���O���N���b�N���܂��B������SendInput()���g�p���܂��B
	// [����]
	// int x;
	// int y;
	void SaRbuttonClick( const std::vector<void*> params );

#ifdef __cplusplus
}
#endif

#endif