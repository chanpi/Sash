#ifndef _SA_KEYBOARD_H_
#define _SA_KEYBOARD_H_

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

	// �w�肳�ꂽ�E�B���h�E�ɃL�[�{�[�h�t�H�[�J�X��ݒ肵�܂��B������SetFocus()���Ăяo���܂��B
	// ����
	// BOOL bSet; -- �L�[�{�[�h�t�H�[�J�X���w��E�B���h�E�ɐݒ肷�邩�A�ȑO�̃E�B���h�E�ɖ߂����B
	// bSet��TRUE�̏ꍇ�̓L�[�{�[�h�t�H�[�J�X�����ϐ��ɐݒ肵���E�B���h�E�ɐݒ肵�A
	// bSet��FALSE�̏ꍇ�́A�ȑO�L�[�{�[�h�t�H�[�J�X�̂������E�B���h�E�ɍēx�L�[�{�[�h�t�H�[�J�X��ݒ肵�܂��B
	// �A���A�ȑO�̃E�B���h�E�ɍēx�L�[�{�[�h�t�H�[�J�X��ݒ肷��̂́A����v���Z�X���ŏ������s��ꂽ�Ƃ��̂݉\�ł��B
	void SaSetFocus( const std::vector<void*> params );

#ifdef __cplusplus
}
#endif

#endif