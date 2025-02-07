#pragma once
//User includes
#include "resource.h"

//Windows includes
#include <afxwin.h>


// CExampleDlg dialog
class CExampleDlg : public CDialog
{
    // Declare the message map for handling messages
    DECLARE_MESSAGE_MAP()

protected:

    // Used for mapping control variables with dialog controls
    virtual void DoDataExchange(CDataExchange* pDX);  

public:
    // This enum is for dialog class ID, which identifies the dialog template
    enum { IDD = IDD_DIALOG_APP };

    // Default constructor
    CExampleDlg();

    // Destructor
    ~CExampleDlg();

    // This method initializes the dialog with the initial values
    BOOL OnInitDialog();

    // Variables for storing the names of tool, proc, and stages
    CString m_toolName;
    CString m_procName;
    CString m_stageName;

    // Buttons for adding tool, Proc, stages, and ProcAcis file 
    CEdit m_toolButton;
    CEdit m_procButton;
    CEdit m_stageButton;
    CEdit m_procAcisFile;

    // Buttons for vcxProjec1 and 2
    CEdit m_vcxProj1;
    CEdit m_vcxProj2;

    // Functions for creating class headers and cpp files, updating VCX project
    void CreateClass(const CString& fileName);
    void UpdateVcxProject(const CString& iVcxProjectFilPath, const CString& iClassName);

    // Event handlers for UI actions
    afx_msg void OnEnChangeEditTool();
    afx_msg void OnEnChangeEditProc();
    afx_msg void OnEnChangeEditStage();
    afx_msg void OnBnClickedButtonBrowse1();
    afx_msg void OnBnClickedButtonBrowse2();
    afx_msg void OnBnClickedButtonRun();
    afx_msg void OnEnChangeEditVcxprj1();
};
