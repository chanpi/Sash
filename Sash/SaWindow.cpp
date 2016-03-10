#include "stdafx.h"
#include "SaWindow.h"
#include "SaEnvironmentVariable.h"
#include <map>
#include <string>

using namespace std;
typedef basic_string<TCHAR> tstring;

static BOOL CALLBACK EnumChildProc( HWND hWnd , LPARAM lParam );

namespace {
	// �q�E�B���h�E���擾����ꍇ�̃N���X������уE�B���h�E�����i�[����o�b�t�@�B
	// EnumChildWindows()�̃R�[���o�b�N�֐��ƌĂяo�����Ƃ̊ԂŃf�[�^�����L���܂��B
	TCHAR g_szClassNameChild[ g_nName ] = {0};
	TCHAR g_szWindowNameChild[ g_nName ] = {0};

	LPCTSTR g_szSaSetActiveWindow = _T("SaSetActiveWindow()");
	LPCTSTR g_szSaMessageBox = _T("SaMessageBox()");
};

// �Ώۂ̃E�B���h�E���őO�ʂɕ\�����܂��B
// [����] �Ȃ�
void SaSetForegroundWindow( const vector<void*>* /*params*/ ) {
	// �E�B���h�E�n���h���͊��ϐ����猟�����邽�߃R�����g�A�E�g
	//HWND hWnd = (HWND)(*params)[0];
	SetForegroundWindow( GetWindowHandle() );
}

// �E�B���h�E���A�N�e�B�u�ɂ��܂��B������SetActiveWindow()���Ăяo���܂��B
// [����]
// BOOL bSet;
// bSet��TRUE�̏ꍇ��hWnd���A�N�e�B�u�ɂ��AbSet��FALSE�̏ꍇ�́A�ȑO�A�N�e�B�u�������E�B���h�E���ēx�A�N�e�B�u�ɂ��܂��B
// �A���A�ȑO�A�N�e�B�u�������E�B���h�E���ēx�A�N�e�B�u�ɂ���̂́A����v���Z�X���ŏ������s��ꂽ�Ƃ��̂݉\�ł��B
void SaSetActiveWindow( const vector<void*>* params ) {
	if ( params->size() < 1 ) {
		_tprintf( g_szFormatErrorS, g_szSaSetActiveWindow, g_szError002 );
	} else {
		static HWND hOldWnd = NULL;
		BOOL bSet = (0 == _tcsicmp( (LPCTSTR)(*params)[0], g_szTRUE )) ? TRUE : FALSE;

		if ( bSet ) {
			hOldWnd = SetActiveWindow( GetWindowHandle() );
		} else if ( hOldWnd ) {
			SetActiveWindow( hOldWnd );
		}
	}
}

// ���b�Z�[�W�{�b�N�X��\�����܂��i�I�[�i�[�E�B���h�E�Ȃ��j�B
// [����]
// LPCTSTR lpText; -- �\�����郁�b�Z�[�W�B
// LPCTSTR lpCaption; -- �_�C�A���O�{�b�N�X�̃^�C�g���B
// UINT uType; -- ���b�Z�[�W�{�b�N�X�̓��e�Ɠ���B
//  MB_ICONEXCLAMATION, MB_ICONWARNING		���Q���i!�j�A�C�R����\�����܂��B
//  MB_ICONINFORMATION, MB_ICONASTERISK		�ۂ̒��ɏ������́ui�v���`���ꂽ�A�C�R����\�����܂��B
//  MB_ICONQUESTION							�^�╄�i?�j�A�C�R����\�����܂��B
//  MB_ICONSTOP,MB_ICONERROR,MB_ICONHAND	��~�}�[�N�A�C�R����\�����܂��B
void SaMessageBox( const vector<void*>* params ) {
	if ( params->size() < 3 ) {
		_tprintf( g_szFormatErrorS, g_szSaMessageBox, g_szError002 );
	} else {
		UINT uType = MB_OK;
		TCHAR szUtype[ g_nName ] = {0};
		LPTSTR pNext = NULL;

		typedef map< tstring, UINT > MessageBoxType;
		MessageBoxType mboxType;
		mboxType.insert(make_pair(_T("MB_ICONEXCLAMATION"), MB_ICONEXCLAMATION));
		mboxType.insert(make_pair(_T("MB_ICONWARNING"), MB_ICONWARNING));
		mboxType.insert(make_pair(_T("MB_ICONINFORMATION"), MB_ICONINFORMATION));
		mboxType.insert(make_pair(_T("MB_ICONASTERISK"), MB_ICONASTERISK));
		mboxType.insert(make_pair(_T("MB_ICONQUESTION"), MB_ICONQUESTION));
		mboxType.insert(make_pair(_T("MB_ICONSTOP"), MB_ICONSTOP));
		mboxType.insert(make_pair(_T("MB_ICONERROR"), MB_ICONERROR));
		mboxType.insert(make_pair(_T("MB_ICONHAND"), MB_ICONHAND));
		mboxType.insert(make_pair(_T("MB_OK"), MB_OK));
		//mboxType.insert(make_pair(_T(""), ));

		_tcscpy_s( szUtype, _countof(szUtype), (LPCTSTR)(*params)[2] );
		LPCTSTR pType = _tcstok_s( szUtype, g_szBar, &pNext );
		MessageBoxType::iterator it;
		while ( NULL != pType ) {
			it = mboxType.find( pType );
			if ( it != mboxType.end() ) {
				uType |= it->second;
			}
			pType = _tcstok_s( NULL, g_szBar, &pNext );
		}

		MessageBox( NULL, (LPCTSTR)(*params)[0], (LPCTSTR)(*params)[1], uType );
	}
}

// �E�B���h�E�n���h�����擾���܂��B
// ���ϐ���"SA_HWND_CLASSNAME_PARENT", "SA_HWND_WINDOWNAME_PARENT", "SA_HWND_CLASSNAME_CHILD", "SA_HWND_WINDOWNAME_CHILD"���Q�Ƃ��܂��B
// ���ϐ���"SA_HWND_CLASSNAME_CHILD", "SA_HWND_WINDOWNAME_CHILD"�̂�������ݒ肳��Ă��Ȃ��ꍇ�ɂ͐e�E�B���h�E�̃E�B���h�E�n���h�����A
// �����łȂ��ꍇ�ɂ͎q�E�B���h�E�̃E�B���h�E�n���h����Ԃ��܂��B
HWND GetWindowHandle( VOID ) {
	TCHAR szClassNameParent[ g_nName ] = {0};
	TCHAR szWindowNameParent[ g_nName ] = {0};
	HWND hWndParent = NULL;
	HWND hWndChild = NULL;
	
	vector<void*> params;
	int nBuf = _countof(szClassNameParent);
	// �e�E�B���h�E������
	params.push_back( (void*)g_szSaHwndClassNameParent );
	params.push_back( szClassNameParent );
	params.push_back( &nBuf );
	SaGetEnvironmentVariable( &params );
	params.clear();
	params.push_back( (void*)g_szSaHwndWindowNameParent );
	params.push_back( szWindowNameParent );
	nBuf = _countof(szWindowNameParent);
	params.push_back( &nBuf );
	SaGetEnvironmentVariable( &params );

	hWndParent = FindWindow( szClassNameParent, szWindowNameParent );
	if ( NULL != hWndParent ) {
		// �q�E�B���h�E�̎w�肪���邩�m�F
		params.clear();
		params.push_back( (void*)g_szSaHwndClassNameChild );
		params.push_back( g_szClassNameChild );
		nBuf = _countof(g_szClassNameChild);
		params.push_back( &nBuf );
		SaGetEnvironmentVariable( &params );

		params.clear();
		params.push_back( (void*)g_szSaHwndWindowNameChild );
		params.push_back( g_szWindowNameChild );
		nBuf = _countof(g_szWindowNameChild);
		params.push_back( &nBuf );
		SaGetEnvironmentVariable( &params );
		if ( 0 == _tcslen( g_szClassNameChild ) && 0 == _tcslen( g_szWindowNameChild ) ) {
			// �q�E�B���h�E�̎w��Ȃ�
			return hWndParent;
		} else {
			EnumChildWindows( hWndParent, EnumChildProc, (LPARAM)&hWndChild );
			return hWndChild;
		}
	}
	return NULL;
}

// �q�E�B���h�E��񋓂���R�[���o�b�N�֐��ł��B
// �w�肵���N���X���y�уE�B���h�E�L���v�V�����ɍ��v����ꍇ�ALPARAM����ăE�B���h�E�n���h����Ԃ��܂��B
BOOL CALLBACK EnumChildProc( HWND hWnd , LPARAM lParam )
{
	TCHAR szClassName[ g_nName ] = {0};
	TCHAR szWindowName[ g_nName ] = {0};
	GetClassName( hWnd, szClassName, _countof(szClassName) );
	GetWindowText( hWnd, szWindowName, _countof(szWindowName) );
	if ( !_tcscmp( szClassName, g_szClassNameChild ) && !_tcscmp( szWindowName, g_szWindowNameChild ) ) {
		HWND* hWndTarget = (HWND*)lParam;
		*hWndTarget = hWnd;
		return FALSE;
	}
	return TRUE;
}