// SerialPort_NewDlg.h : header file
//
#include "SerialPort.h"
#include "DATA_Fomate_Dlg.h"

#if !defined(AFX_SERIALPORT_NEWDLG_H__D283CD43_0616_40D8_AE0A_9C6656A2A0F4__INCLUDED_)
#define AFX_SERIALPORT_NEWDLG_H__D283CD43_0616_40D8_AE0A_9C6656A2A0F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSerialPort_NewDlg dialog

class CSerialPort_NewDlg : public CDialog
{
// Construction
public:
	CSerialPort_NewDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSerialPort_NewDlg)
	enum { IDD = IDD_SERIALPORT_NEW_DIALOG };
	CStatic	m_static_thread_count_no_use;
	CStatic	m_static_receive_line_count;
	CEdit	m_ctrl_edit_send_period;
	CButton	m_check_timer_send;
	CButton	m_ctrlHexSend;
	CButton	m_check_hex16_disp;
	CEdit	m_edit_send_data;
	CEdit	m_edit_receive_data;
	CStatic	m_static_send_control;
	CComboBox	m_combo_com_num;
	CComboBox	m_Combo_bandRate;
	CStatic	m_static_receive_contr;
	CButton	m_button_send_data;
	CButton	m_open_serial_port;
	CButton	m_clean_window;
	CString	m_string_receive;
	CString	m_string_send;
	BOOL	m_bool_check_timer_send_period;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialPort_NewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CSerialPort tCSerialPort;
	BOOL  m_bSerialPortOpened; //标志串口是否打开
	long rxdatacount;  //该变量用于接收字符计数
	long SendDataCount;
	unsigned int m_BaudRate;//波特率
	unsigned char Com_Num;//串口号
	int timer_send_period;
	int Str2Hex(CString str, char* data);
	char HexChar(char );
	void ChangeSize(UINT nID, int x, int y);
	CRect m_rect;
	POINT oSize;
	CFont m_editFont;
	int line_length,line_count;
	unsigned char *receive_buffer;
	int MaxTotalBufNum;
	long unsigned int ctTotalBufNum;
	void display_function();
	unsigned char receive_data_flag;//接收到数据标志位
	CBrush m_DlgBackGroundColor;//对话框背景色
	void close_port_all();//rxh2.8关闭串口总入口
	DATA_Fomate_Dlg tDATA_Fomate_Dlg;

	static unsigned char data_bit;//rxh2.9.1
	static unsigned char stop_bit;//停止位
	static char check_bit;//奇偶校验位

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSerialPort_NewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonSend();
	afx_msg void OnButtonClean();
	afx_msg LONG OnCommReceivedata(WPARAM ch, LPARAM port); //串口事件消息响应函数
	afx_msg	void OnComErrorAndClose();//rxh2.8
	afx_msg void OnSelendokCOMBOBaudRate();
	afx_msg void OnSelendokComboComNum();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonCleanCount();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDropdownComboComNum();
	afx_msg void OnCheckTimerSend();
	afx_msg void OnChangeEditTemerPeriod();
	afx_msg void OnDestroy();
	afx_msg void OnButtonDataFormat();
	afx_msg void OnButtonAboutAuthor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALPORT_NEWDLG_H__D283CD43_0616_40D8_AE0A_9C6656A2A0F4__INCLUDED_)
