#ifndef _SA_MEMORY_H_
#define _SA_MEMORY_H_

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

	// �v���Z�X�̃������̈���_���v���܂��B
	// [����]
	// DWORD dwProcessId; -- �Ώۂ̃v���Z�XID
	// ���̑��̃I�v�V����
	// [�g�p��]
	// Sash sadumpmemory 1234 /rw /H
	// Sash sadumpmemory 1234 /FR 3000000 /TO 4000000
	void SaDumpMemory( const std::vector<void*>* params );

#ifdef __cplusplus
}
#endif

#endif