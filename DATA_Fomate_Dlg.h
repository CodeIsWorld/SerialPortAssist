#if !defined(AFX_DATA_FOMATE_DLG_H__84932DDD_189E_45C9_8E3B_F12ABA88BFC4__INCLUDED_)
#define AFX_DATA_FOMATE_DLG_H__84932DDD_189E_45C9_8E3B_F12ABA88BFC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DATA_Fomate_Dlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// DATA_Fomate_Dlg dialog



class DATA_Fomate_Dlg : public CDialog
{
	// Construction
public:
	DATA_Fomate_Dlg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(DATA_Fomate_Dlg)
	enum { IDD = IDD_DIALOG_DATA_FORMAT };
	CComboBox	m_combo_stop_bit;
	CComboBox	m_combo_check_bit;
	CComboBox	m_combo_data_bit;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DATA_Fomate_Dlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(DATA_Fomate_Dlg)
	afx_msg void OnSelendokComboDataBit();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokComboStopBit();
	afx_msg void OnSelendokComboCheckBit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATA_FOMATE_DLG_H__84932DDD_189E_45C9_8E3B_F12ABA88BFC4__INCLUDED_)
