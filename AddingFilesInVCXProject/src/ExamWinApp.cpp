#include "ExamWinApp.h"

//User includes
#include "ExampleDlg.h"

//MFC includes


//Standard Includes


//-----------------------------------------------------------------------------

BOOL CExamWinApp::InitInstance()
{
	CExampleDlg aExampleDlg;
	m_pMainWnd = &aExampleDlg;
	aExampleDlg.DoModal();

	return TRUE;
}

//-----------------------------------------------------------------------------
