#ifndef _SA_ENVIRONMENT_VARIABLE_H_
#define _SA_ENVIRONMENT_VARIABLE_H_

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

	// ���ϐ����̒l���o�͂��܂��B
	// [����]
	// LPCTSTR lpName; -- ���ϐ���
	// [�B������]
	// LPTSTR szBuffer; -- ���ϐ��̒l���i�[����o�b�t�@�̃|�C���^
	// int nBufferLength; -- �o�b�t�@�T�C�Y
	void SaGetEnvironmentVariable( const std::vector<void*> params );

#ifdef __cplusplus
}
#endif

#endif