#ifndef _SA_CONSOLE_H_
#define _SA_CONSOLE_H_

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif
	
	// �������F�t���ŕW���o�͂��܂��B
	// [����]
	// WORD wAttributes; -- �e�L�X�g�J���[�B
	// LPCTSTR lpText; -- �W���o�͂��镶����B�X�y�[�X���܂ޏꍇ��""�ň͂��Ă��������B
	// [�F]
	// �����FFOREGROUND_BLUE
	// �����΁FFOREGROUND_GREEN
	// �����ԁFFOREGROUND_RED
	// �������FFOREGROUND_WHITE
	void SaPrintfWithColor( const std::vector<void*> params );

#ifdef __cplusplus
}
#endif

#endif