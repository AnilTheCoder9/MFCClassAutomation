#include "ExampleDlg.h"
#include "afxdlgs.h"
//-----------------------------------------------------------------------------

CExampleDlg::CExampleDlg() :CDialog(IDD), m_toolName(_T("")), m_procName(_T("")),
															  m_stageName(_T(""))
{
}

//-----------------------------------------------------------------------------

CExampleDlg::~CExampleDlg()
{
}

//-----------------------------------------------------------------------------

void CExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_TOOL, m_toolButton);
	DDX_Text(pDX, IDC_EDIT_TOOL, m_toolName);
	DDX_Control(pDX, IDC_EDIT_PROC, m_procButton);
	DDX_Text(pDX, IDC_EDIT_PROC, m_procName);
	DDX_Control(pDX, IDC_EDIT_STAGE, m_stageButton);
	DDX_Text(pDX, IDC_EDIT_STAGE, m_stageName);
	DDX_Control(pDX, IDC_EDIT_PROC_ACIS, m_procAcisFile);
	DDX_Control(pDX, IDC_EDIT_VCXPRJ1, m_vcxProj1);
	DDX_Control(pDX, IDC_EDIT_VCXPROJ2, m_vcxProj2);
}

//-----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CExampleDlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT_TOOL, &CExampleDlg::OnEnChangeEditTool)
	ON_EN_CHANGE(IDC_EDIT_PROC, &CExampleDlg::OnEnChangeEditProc)
	ON_EN_CHANGE(IDC_EDIT_STAGE, &CExampleDlg::OnEnChangeEditStage)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE1, &CExampleDlg::OnBnClickedButtonBrowse1)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE2, &CExampleDlg::OnBnClickedButtonBrowse2)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CExampleDlg::OnBnClickedButtonRun)
	ON_EN_CHANGE(IDC_EDIT_VCXPRJ1, &CExampleDlg::OnEnChangeEditVcxprj1)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------

void CExampleDlg::OnEnChangeEditTool()
{
	
}

//-----------------------------------------------------------------------------


void CExampleDlg::OnEnChangeEditProc()
{

	CString strText;

	// Get text from first edit control (Editable)
	GetDlgItemText(IDC_EDIT_PROC, strText);

	strText.Append(L"_Acis.h");
	// Set text to second edit control (Read-Only)
	SetDlgItemText(IDC_EDIT_PROC_ACIS, strText);
}

//-----------------------------------------------------------------------------

void CExampleDlg::OnEnChangeEditStage()
{
	
}

//-----------------------------------------------------------------------------


void CExampleDlg::OnBnClickedButtonBrowse1()
{
	CFileDialog dlg(TRUE, _T(".vcxproj"), NULL, OFN_FILEMUSTEXIST, _T("VC++ Project Files (*.vcxproj)|*.vcxproj||"));
	if (dlg.DoModal() == IDOK)
	{
		m_vcxProj1.SetWindowText(dlg.GetPathName());
	}
}

//-----------------------------------------------------------------------------

void CExampleDlg::OnBnClickedButtonBrowse2()
{
	CFileDialog dlg(TRUE, _T(".vcxproj"), NULL, OFN_FILEMUSTEXIST, _T("VC++ Project Files (*.vcxproj)|*.vcxproj||"));
	if (dlg.DoModal() == IDOK)
	{
		m_vcxProj2.SetWindowText(dlg.GetPathName());
	}
}

//-----------------------------------------------------------------------------

void CExampleDlg::CreateClass(const CString& fileName)
{
	CString aHeaderFileName = fileName + _T(".h");
	CString aCppFileName = fileName + _T(".cpp");

	CStdioFile file;

	//This create .h file
	if (file.Open(aHeaderFileName, CFile::modeCreate | CFile::modeWrite))
	{
		CString content;
		content.Format(_T("#pragma once\n\nclass %s\n{\npublic:\n	//Default constructor\n		%s();\n		//Destructor\n		~%s();\n};\n"),
			                 fileName, fileName, fileName);
		file.WriteString(content);

		file.Close();

	}

	//This create .cpp file
	if (file.Open(aCppFileName, CFile::modeCreate | CFile::modeWrite))
	{
		CString content;
		content.AppendFormat(_T("#include \"%s.h\"\n\n%s::%s()\n{\n\n}\n\n%s::~%s()\n{\n\n}") 
			                              , fileName, fileName, fileName, fileName, fileName);
		file.WriteString(content);
		file.Close();

	}
	
}

//-----------------------------------------------------------------------------

void CExampleDlg::UpdateVcxProject(const CString& iVcxProjectFilPath, const CString& iClassName)
{
	CString content;
	
	CStdioFile file;

	if (file.Open(iVcxProjectFilPath, CFile::modeRead))
	{
		CString line;
		while (file.ReadString(line))
		{
			content += line + _T("\n");
		}
		file.Close();
	}

	CString aHeaderEntry;
	aHeaderEntry.Format(_T("	<C1Include Include = \"..\src\\%s.h\" / >\n"), iClassName);

	CString subStr = "</ItemGroup>";
	int pos = content.Find(subStr);
	
	pos = content.Find(subStr, pos + subStr.GetLength());

	if (pos != -1)
	{
		content.Insert(pos, aHeaderEntry);
	}

	CString aCppEntry;  
	aCppEntry.Format(_T("	<C1Include Include = \"..\src\\%s.cpp\" / >\n"), iClassName);

	pos = content.Find(subStr, pos + aHeaderEntry.GetLength() + subStr.GetLength());

	if (pos != -1)
	{
		content.Insert(pos, aCppEntry);
	}

	if (file.Open(iVcxProjectFilPath, CFile::modeCreate | CFile::modeWrite))
	{
		file.WriteString(content);
	}

}

//-----------------------------------------------------------------------------

void CExampleDlg::OnBnClickedButtonRun()
{
	CString aVcxProjName1, aVcxProjName2;
	m_vcxProj1.GetWindowTextW(aVcxProjName1);
	m_vcxProj2.GetWindowTextW(aVcxProjName2);
	m_toolButton.GetWindowTextW(m_toolName);
	m_procButton.GetWindowTextW(m_procName);
	m_stageButton.GetWindowTextW(m_stageName);

	if (m_toolName.IsEmpty() || m_procName.IsEmpty() || m_stageName.IsEmpty()
		|| aVcxProjName1.IsEmpty() || aVcxProjName2.IsEmpty())
	{
		AfxMessageBox(L"Please enter valid classes and vcxprojects name");
		return;
	}

	CreateClass(m_toolName);
	CreateClass(m_procName);
	CreateClass(m_stageName);

	;
	
	UpdateVcxProject(aVcxProjName1, m_toolName);

	UpdateVcxProject(aVcxProjName1, m_stageName);
	
	UpdateVcxProject(aVcxProjName2, m_procName);
		
}

//-----------------------------------------------------------------------------

void CExampleDlg::OnEnChangeEditVcxprj1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

//-----------------------------------------------------------------------------

BOOL CExampleDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_MAIN_ICONS);
	if (hIcon == NULL) {
		AfxMessageBox(_T("Failed to load the icon!"));
		return FALSE; // Optionally handle error
	}

	// Set the dialog's large and small icons
	SetIcon(hIcon, TRUE);  // Set large icon
	SetIcon(hIcon, FALSE); // Set small icon

	return TRUE;
}

//-----------------------------------------------------------------------------
