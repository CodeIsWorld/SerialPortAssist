// SerialPort_NewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SerialPort_New.h"
#include "SerialPort_NewDlg.h"
#include "SerialPort.h"
//#include "DATA_Fomate_Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//rxh2.9.1静态变量必须在类外进行初始化
unsigned char CSerialPort_NewDlg::data_bit=8;//rxh2.9.1
unsigned char CSerialPort_NewDlg::stop_bit=1;//停止位
char CSerialPort_NewDlg::check_bit='N';//奇偶校验位

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialPort_NewDlg dialog

CSerialPort_NewDlg::CSerialPort_NewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSerialPort_NewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSerialPort_NewDlg)
	m_string_receive = _T("");
	m_string_send = _T("");
	m_bool_check_timer_send_period = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


}
//DDX指的是Dialog Data Exchange（对话框数据交换）
void CSerialPort_NewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSerialPort_NewDlg)
	DDX_Control(pDX, IDC_STATIC_THREAD_COUNT_NO_USE, m_static_thread_count_no_use);
	DDX_Control(pDX, IDC_STATIC_RECEIVE_LINE_COUNT, m_static_receive_line_count);
	DDX_Control(pDX, IDC_EDIT_TEMER_PERIOD, m_ctrl_edit_send_period);
	DDX_Control(pDX, IDC_CHECK_TIMER_SEND, m_check_timer_send);
	DDX_Control(pDX, IDC_CHECK_HEX16_SEND, m_ctrlHexSend);
	DDX_Control(pDX, IDC_CHECK_HEX16_DISP, m_check_hex16_disp);
	DDX_Control(pDX, IDC_EDIT_SEND, m_edit_send_data);
	DDX_Control(pDX, IDC_EDIT_RECEIVE, m_edit_receive_data);
	DDX_Control(pDX, IDC_STATIC_SEND_COUNT, m_static_send_control);
	DDX_Control(pDX, IDC_COMBO_COM_NUM, m_combo_com_num);
	DDX_Control(pDX, IDC_COMBO_BANDRATE, m_Combo_bandRate);
	DDX_Control(pDX, IDC_STATIC_RECEIVE_COUNT, m_static_receive_contr);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_button_send_data);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_open_serial_port);
	DDX_Control(pDX, IDC_BUTTON_CLEAN, m_clean_window);
	DDX_Text(pDX, IDC_EDIT_RECEIVE, m_string_receive);
	DDX_Text(pDX, IDC_EDIT_SEND, m_string_send);
	DDX_Check(pDX, IDC_CHECK_TIMER_SEND, m_bool_check_timer_send_period);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSerialPort_NewDlg, CDialog)//消息映射宏
	//{{AFX_MSG_MAP(CSerialPort_NewDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, OnButtonClean)
	ON_MESSAGE(WM_COMM_RXCHAR, OnCommReceivedata) //串口消息处理，只需添加这一行
	ON_MESSAGE(WM_COMM_CLOSE_PORT, OnComErrorAndClose) //rxh2.8
	ON_CBN_SELENDOK(IDC_COMBO_BANDRATE, OnSelendokCOMBOBaudRate)
	ON_CBN_SELENDOK(IDC_COMBO_COM_NUM, OnSelendokComboComNum)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON__CLEAN_COUNT_, OnButtonCleanCount)
	ON_WM_CHAR()
	ON_WM_SIZE()
	ON_CBN_DROPDOWN(IDC_COMBO_COM_NUM, OnDropdownComboComNum)
	ON_BN_CLICKED(IDC_CHECK_TIMER_SEND, OnCheckTimerSend)
	ON_EN_CHANGE(IDC_EDIT_TEMER_PERIOD, OnChangeEditTemerPeriod)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_DATA_FORMAT, OnButtonDataFormat)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON__ABOUT_AUTHOR, OnButtonAboutAuthor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialPort_NewDlg message handlers

BOOL CSerialPort_NewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
///////////*************************************************************/////////////////
//自己的初始化程序
	rxdatacount=0;
	m_bSerialPortOpened=FALSE;
	m_BaudRate=9600;
	data_bit=8;
	stop_bit=1;
	check_bit='N';
	SendDataCount=0;
	timer_send_period=1000;

	tCSerialPort.Hkey2ComboBox(m_combo_com_num);//遍历串口//rxh2.0
	Com_Num=m_nComArray[0];//在遍历函数中从注册表中读取的串口号存储到m_nComArray[]数组中
	m_Combo_bandRate.SetCurSel(5);//波特率默认9600

	//获取控件大小//rxh2.2
	CRect rect;  
	GetClientRect(&rect);  //
	GetClientRect(&m_rect);  
	oSize.x = rect.right - rect.left;  
	oSize.y = rect.bottom - rect.top;
	//rxh2.6设置接收编辑框字体大小,设置完后可以接收显示汉字
	m_editFont.CreatePointFont(90, "新宋体");
	m_edit_receive_data.SetFont(&m_editFont); //设置新字体
	m_edit_receive_data.SetLimitText(-1);//rxh2.7,取消字符个数限制
	line_length=0;//rxh2.6
	line_count=0;
	//rxh2.7曾加接收缓冲区
	receive_buffer=new unsigned char[1024*1024];
	MaxTotalBufNum=1024*1024;//总的字节数
	ctTotalBufNum=0;
	SetTimer(2,55,NULL);//rxh2.7定时刷新显示
	receive_data_flag=0;//用于显示和接收同步的全局变量
	m_DlgBackGroundColor.CreateSolidBrush(RGB(154,205,50));//自定义一个蓝色画刷
	//rxh2.8改变窗口的透明度
	/*SetWindowLong(this->m_hWnd,GWL_EXSTYLE,GetWindowLong(this->m_hWnd,GWL_EXSTYLE)^0x80000);
	HINSTANCE hInst = LoadLibrary(_T("User32.DLL"));
	if(hInst)
	{
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD);  
		MYFUNC fun = NULL; //取得SetLayeredWindowAttributes函数指针
		fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if(fun)
		{  
			fun(this->m_hWnd,0,128,2);
		}
		FreeLibrary(hInst);
	}	*/
//	m_check_timer_send.EnableWindow(FALSE);//rxh2.8使定时发送不可用


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSerialPort_NewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSerialPort_NewDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSerialPort_NewDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//打开/关闭串口
void CSerialPort_NewDlg::OnButtonOpen() 
{
	m_bSerialPortOpened=!m_bSerialPortOpened;//取反标志位

//	tCSerialPort.Hkey2ComboBox(m_combo_com_num);//遍历串口。改在对话框初始化执行
	if(m_bSerialPortOpened)//打开串口
	{
		if(tCSerialPort.InitPort(this->m_hWnd, Com_Num,m_BaudRate,check_bit,data_bit,stop_bit,EV_RXFLAG | EV_RXCHAR,512))//初始化函数如果成功就返回TRUE，可以用来判断
		{
			tCSerialPort.StartMonitoring();///启用串口通信监测线程函数
			m_bSerialPortOpened=TRUE;//
//			m_check_timer_send.EnableWindow(TRUE);//rxh2.8使定时发送可用

			m_open_serial_port.SetWindowText("关闭串口");//在按钮上显示字符串
		}
		else
		{
			m_bSerialPortOpened=FALSE;//标志位取反
			CString str;
			str.Format("COM%d 没有发现或被其它设备占用",Com_Num);//很棒~~~~~~~~~~~~~~~~~~~~~~~
			AfxMessageBox(str);
		}
	}
	else//关闭串口
	{
		close_port_all();

	}
}
//关闭串口总入口
void CSerialPort_NewDlg::close_port_all()
{
	KillTimer(1);
	tCSerialPort.ClosePort();//关闭串口   
	m_bSerialPortOpened=FALSE;		
	m_check_timer_send.SetCheck(FALSE);//rxh2.7//取消选中定时发送
//	m_check_timer_send.EnableWindow(FALSE);//rxh2.8使定时发送不可用
	m_open_serial_port.SetWindowText("打开串口");//在按钮上显示字符串
	//m_open_serial_port.SetForeColor(RGB(0,155,0));  //串口打开后文本颜色变绿
	
}
//串口接收到数据
//ch->接收到的字符数据，port->串口号##########################################
LONG CSerialPort_NewDlg::OnCommReceivedata(WPARAM ch, LPARAM port)
{	
	rxdatacount++;  //该变量用于接收字符计数
	receive_buffer[ctTotalBufNum]=ch;//存入缓冲区
	ctTotalBufNum++;//rxh2.7缓冲区指针+1
	receive_data_flag=1;//接收到数置一
	//传入参数ch就是传进来的字符型数据，可以使用的数据*******************#########


	return 0;
}
//发送数据
void CSerialPort_NewDlg::OnButtonSend() 
{
	if(!m_bSerialPortOpened) 
	{
		CString str;
		str.Format("COM%d 没有打开",Com_Num);//很棒~~~~~~~~~~~~~~~~~~~~~~~
			AfxMessageBox(str);
		return; //检查串口是否打开
	}

	char buf[100];
	memset(buf, 0, sizeof(buf));//对buf进行填充0，进行初始化

	//以下几行程序都是获得编辑框的文本
	//GetDlgItemText(IDC_EDIT_SEND, buf, sizeof(buf));//从编辑框获取要发送的数据
	//GetDlgItem(IDC_EDIT_SEND)->GetWindowText(buf, sizeof(buf));//与上一句同理！！！！！！
	m_edit_send_data.GetWindowText(buf, sizeof(buf));//直接用发送框的控制变量获取文本
	//SendDlgItemMessage(IDC_EDIT_SEND,WM_GETTEXT,sizeof(buf),(LPARAM)buf);//以发送消息到编辑框控件获取文本

	if (strcmp("NOT FOUND", buf) == 0)//比较字符串。若两个字符串相等则返回0，若str1>str2返回整数，反之返回负数
		return;
	m_string_send=buf;
	//检查是否16进制发送
	if(m_ctrlHexSend.GetCheck())//十六进制发送//rxh2.1
	{
		char data[512];
		int len=Str2Hex(m_string_send,data);//十六进制转换
		tCSerialPort.WriteToPort(data,len); //发送数据
		SendDataCount+=(long)((m_string_send.GetLength()+1)/3);//发送个数计数
	}
	else //字符发送
	{
		tCSerialPort.WriteToPort(buf);       //发送数据
		//tCSerialPort.WriteToPort((LPCTSTR)m_string_send);	//发送数据

		SendDataCount+=m_string_send.GetLength();//获取编辑框字符串长度(发送个数)
	}
	//显示发送计数
	CString strTemp;
	strTemp.Format("发送:%d",SendDataCount);
	m_static_send_control.SetWindowText(strTemp);
}
//16进制转换函数//rxh2.1
char CSerialPort_NewDlg::HexChar(char c)
{
	if((c>='0')&&(c<='9'))
		return c-0x30;
	else if((c>='A')&&(c<='F'))
		return c-'A'+10;
	else if((c>='a')&&(c<='f'))
		return c-'a'+10;
	else 
		return 0x10;
}
//将一个字符串作为十六进制串转化为一个字节数组，字节间可用空格分隔，
//返回转换后的字节数组长度，同时字节数组长度自动设置。
int CSerialPort_NewDlg::Str2Hex(CString str, char* data)//rxh2.1
{
	int t,t1;
	int rlen=0,len=str.GetLength();
	//data.SetSize(len/2);
	for(int i=0;i<len;)
	{
		char l,h=str[i];
		if(h==' ')
		{
			i++;
			continue;
		}
		i++;
		if(i>=len)
			break;
		l=str[i];
		t=HexChar(h);
		t1=HexChar(l);
		if((t==16)||(t1==16))
			break;
		else 
			t=t*16+t1;
		i++;
		data[rlen]=(char)t;
		rlen++;
	}
	return rlen;
	
}
//清空接收区
void CSerialPort_NewDlg::OnButtonClean() 
{
//	m_string_receive.Empty();
	m_edit_receive_data.SetSel(0,-1);//rxh2.8重新改正清空方式
	m_edit_receive_data.Clear();
	CString strTemp;
	//获取编辑框内行数
	line_count=m_edit_receive_data.GetLineCount();
	//列数
	line_length=m_edit_receive_data.LineLength(1);//获取第一行长度
	
	//显示行列数
	strTemp.Format("行:%ld列:%ld ",line_count,line_length);
	//	strTemp="行数:"+strTemp;
		m_static_receive_line_count.SetWindowText(strTemp);  //显示接收行数
	
}
//清零计数//rxh2.2
void CSerialPort_NewDlg::OnButtonCleanCount() 
{
	rxdatacount=0;
	CString strTemp;
	strTemp.Format("%ld",rxdatacount);
	strTemp="接收:"+strTemp;
	m_static_receive_contr.SetWindowText(strTemp);
	SendDataCount=0;
	strTemp.Format("%ld",SendDataCount);
	strTemp="发送:"+strTemp;
	m_static_send_control.SetWindowText(strTemp);
	//获取编辑框内行数
	line_count=m_edit_receive_data.GetLineCount();
	//列数
	line_length=m_edit_receive_data.LineLength(1);//获取第一行长度
	
	//显示行列数
	strTemp.Format("行:%ld列:%ld ",line_count,line_length);
	//	strTemp="行数:"+strTemp;
	m_static_receive_line_count.SetWindowText(strTemp);  //显示接收行数
	
}

//波特率组合框
void CSerialPort_NewDlg::OnSelendokCOMBOBaudRate() 
{
	CString temp;
	int i=m_Combo_bandRate.GetCurSel();//将组合框选中的项赋值给i
	switch(i)
	{
	case 0:
		i=300;
		break;
	case 1:
		i=600;
		break;
	case 2:
		i=1200;
		break;
	case 3:
		i=2400;
		break;
	case 4:
		i=4800;
		break;
	case 5:
		i=9600;
		break;
	case 6:
		i=19200;
		break;
	case 7:
		i=38400;
		break;
	case 8:
		i=43000;
		break;
	case 9:
		i=56000;
		break;
	case 10:
		i=57600;
		break;
	case 11:
		i=115200;
		break;
	default:
		break;
		
	}
	m_BaudRate=i;//把i的值赋值给波特率
	//关闭串口 
	close_port_all();
}
//用户单击串口号下拉展开列表框
void CSerialPort_NewDlg::OnDropdownComboComNum() 
{
	//关闭串口 
	close_port_all();
	
	//重新扫描电脑所有串口
	tCSerialPort.Hkey2ComboBox(m_combo_com_num);//遍历串口//rxh2.0
	m_combo_com_num.SetCurSel(0);
	Com_Num=m_nComArray[0];//在遍历函数中从注册表中读取的串口号存储到m_nComArray[]数组中
	
	
}
//选择串口号
void CSerialPort_NewDlg::OnSelendokComboComNum() 
{
	unsigned char i;
	//Com_Num=m_combo_com_num.GetCurSel()+1;//本行程序适用于下拉框中串口号按从小到大排列，即可选中串口号
	i=m_combo_com_num.GetCurSel();
	Com_Num=m_nComArray[i];//在遍历函数中从注册表中读取的串口号存储到m_nComArray[]数组中

}

void CSerialPort_NewDlg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 1:	if(!m_bSerialPortOpened) //rxh2.4
			{
				KillTimer(1);//rxh2.6//将关闭定时器提前到弹窗之前
				CString str;
				str.Format("COM%d 没有打开",Com_Num);//很棒~~~~~~~~~~~~~~~~~~~~~~~
				AfxMessageBox(str);
			
				return; //检查串口是否打开
			}
			OnButtonSend();
			//m_edit_receive_data.PostMessage(WM_VSCROLL, SB_BOTTOM,0);//m_edit_receive_data是跟CRichEdit关联的控件型变量
		break;
	case 2:display_function();break;//可以显示了
	}
	CDialog::OnTimer(nIDEvent);
}

//显示函数
void CSerialPort_NewDlg::display_function()
{
	CString strTemp;
	//接收框显示函数
	if (ctTotalBufNum>0)//必须收到数和定时器时间到才显示
	{
		long unsigned int buff_num_temp=ctTotalBufNum;
		if (receive_data_flag==1)//rxh2.8正在接收
		{
			if (buff_num_temp>300)///最多每次处理显示300个字节
				buff_num_temp=300;
		}
		else //接收完成,但还有待显示数据
		{
			if (buff_num_temp>3000)///最多每次处理显示3000个字节
				buff_num_temp=3000;
		
		}
		for (int i=0;i<buff_num_temp;i++)
		{	
			BYTE bt=*(char*)(receive_buffer+i);
			//十六进制显示
			if(m_check_hex16_disp.GetCheck())
				strTemp.Format("%02X ",bt);
			else 
				strTemp.Format("%c",bt);//将字符送入临时变量strtemp存放
			
			//				strTemp.Format("%c",bt);//将字符送入临时变量strtemp存放
			m_string_receive += strTemp;//将接收到的字符加到字符串
		}
		//总缓冲串移
		memmove(receive_buffer,&receive_buffer[i],ctTotalBufNum-i);
		ctTotalBufNum-=i;//总缓冲指针更新
		
		m_edit_receive_data.SetSel(-1, -1);//选中编辑框中的文本
		m_edit_receive_data.ReplaceSel(m_string_receive);//替换文本
		m_string_receive.Empty();//使用完清零
		//本次显示后还剩下没有显示的数据
		if (ctTotalBufNum>0)
		{
			strTemp.Format("%ld",ctTotalBufNum);
			strTemp="等待:"+strTemp;
			m_static_thread_count_no_use.SetWindowText(strTemp);  //
		}

	}
	else//需要显示的数据已经处理完了，显示一下行列数
	{
		//获取编辑框内行数
		line_count=m_edit_receive_data.GetLineCount();
		
		line_length=m_edit_receive_data.LineLength(1);//获取第一行长度
		
		//显示行列数
		strTemp.Format("行:%ld列:%ld ",line_count,line_length);
		//	strTemp="行数:"+strTemp;
		m_static_receive_line_count.SetWindowText(strTemp);  //*///显示接收行数
		//刷新显示等待数据个数
		strTemp.Format("%ld",ctTotalBufNum);
		strTemp="等待:"+strTemp;
		m_static_thread_count_no_use.SetWindowText(strTemp);  //


	}
	//显示接收计数	
		
	strTemp.Format("%ld",rxdatacount);
	strTemp="接收:"+strTemp;
	m_static_receive_contr.SetWindowText(strTemp);  //显示接收计数


	receive_data_flag=0;//清零接收标志

}

void CSerialPort_NewDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}
//自动调整对话框控件的大小//rxh2.2
void CSerialPort_NewDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
///////////////////////////////////////////////
//网上版本0：改变除静态文本外的所有控件大小
/*    if (nType==SIZE_RESTORED || nType==SIZE_MAXIMIZED)  //如果入口进来的消息是窗口大小调整或者最大化
    {  
		
		float   ratio[2];  
		POINT   newDialogSize;  
		CRect   newRect;  
		
		//获取新的客户区的大小,也就是最新的对话框大小
		GetClientRect(&newRect);  
		newDialogSize.x = newRect.right - newRect.left;  //得到窗口水平大小
		newDialogSize.y = newRect.bottom - newRect.top;  //得到窗口垂直高度
		
		//得现在的对话框与以往对话框的大小比例  
		ratio[0]    = (float)newDialogSize.x / oSize.x;  //水平比例
		ratio[1]    = (float)newDialogSize.y / oSize.y;  //垂直比例
		
		CRect Rect;  
		int woc;  
		
		//左右上下角的数据  
		CPoint OldTLPoint, NewTLPint;  
		CPoint OldBRPoint, NewBRPint;  
		
		//列出所有控件  
		HWND  hwndChild = ::GetWindow(m_hWnd,GW_CHILD);  
		
		while(hwndChild)  
		{  
			//取得ID  
			woc  = ::GetDlgCtrlID(hwndChild);  
			GetDlgItem(woc)->GetWindowRect(Rect);  
			ScreenToClient(Rect);  
			
			OldTLPoint = Rect.TopLeft();  
			NewTLPint.x  = long(OldTLPoint.x*ratio[0]);  
			NewTLPint.y  = long(OldTLPoint.y*ratio[1]);  
			
			OldBRPoint   = Rect.BottomRight();  
			NewBRPint.x  = long(OldBRPoint.x*ratio[0]);  
			NewBRPint.y  = long(OldBRPoint.y*ratio[1]);  
			
			Rect.SetRect(NewTLPint,NewBRPint);  
			GetDlgItem(woc)->MoveWindow(Rect,TRUE);  
			hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);  
		}  
		
		//获取视频窗口父窗口的大小  
		::GetClientRect(this->m_hWnd, Rect);  
		
		oSize   = newDialogSize;      
		
    }  //*/
///////////////////////////////////////
//网上版本1：改变一个控件大小的程序
	
	if(nType!=SIZE_MINIMIZED )  //判断窗口是不是最小化了，因为窗口最小化之后 ，窗口的长和宽会变成0，当前一次变化的时就会出现除以0的错误操作
	{
		CWnd *pWnd_RX= GetDlgItem(IDC_EDIT_RECEIVE); //获取接收框控件句柄
		CWnd *pWnd_TX= GetDlgItem(IDC_EDIT_SEND); //获取发送框控件句柄
		CWnd *pWnd_staticsend= GetDlgItem(IDC_BUTTON_SEND); //获取发送按钮句柄
		CWnd *pWnd_HEXsend= GetDlgItem(IDC_CHECK_HEX16_SEND); //获取HEX发送句柄
		static unsigned char flag=0;
		static LONG send_high_temp,send_length_temp,sendbox_to_dialog_left;


		if(pWnd_RX)//判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建
		{
			CRect receive_rect; //获取发送框控件变化前大小
			pWnd_RX->GetWindowRect(&receive_rect);
			ScreenToClient(&receive_rect);//将控件大小转换为在对话框中的区域坐标
			CRect send_rect; //获取发送框控件大小
			pWnd_TX->GetWindowRect(&send_rect);
			ScreenToClient(&send_rect);//将控件大小转换为在对话框中的区域坐标
			CRect static_send_rect; //获取发送静态文本框控件大小
			pWnd_staticsend->GetWindowRect(&static_send_rect);
			ScreenToClient(&static_send_rect);//将控件大小转换为在对话框中的区域坐标
			CRect hex16_send_rect; //获取16进制发送控件大小
			pWnd_HEXsend->GetWindowRect(&hex16_send_rect);
			ScreenToClient(&hex16_send_rect);//将控件大小转换为在对话框中的区域坐标

			if (flag==0)
			{
				send_high_temp=send_rect.bottom-send_rect.top;//获取发送框的高度
				send_length_temp=send_rect.right-send_rect.left;//发送框宽度

				sendbox_to_dialog_left=send_rect.left-m_rect.left;//获取发送框离对话框左边界的距离
			}
			flag=1;
			
			GetClientRect(&m_rect);//更新对话框大小


			//接收框调整
			receive_rect.left=receive_rect.left;//接收框左边界///调整控件大小
			receive_rect.right=m_rect.right;//接收框右边界
			receive_rect.top=receive_rect.top;//上边界
			receive_rect.bottom=m_rect.bottom-send_high_temp-50;//接收框下边界
			//发送框调整
			CPoint send_edit_TLpoint,send_edit_BRpoint;//获取发送框的左上角坐标
			send_edit_TLpoint.x=m_rect.left+sendbox_to_dialog_left;
			send_edit_TLpoint.y=m_rect.bottom-send_high_temp-10;
			send_edit_BRpoint.x=m_rect.right;
			send_edit_BRpoint.y=m_rect.bottom;
			send_rect.SetRect(send_edit_TLpoint,send_edit_BRpoint);  
			//发送按钮_调整
		//	CPoint send_edit_TLpoint,send_edit_BRpoint;//获取发送框的左上角坐标
			send_edit_TLpoint.x=m_rect.left+sendbox_to_dialog_left;
			send_edit_TLpoint.y=m_rect.bottom-send_high_temp-40;
			send_edit_BRpoint.x=m_rect.left+sendbox_to_dialog_left+90;
			send_edit_BRpoint.y=m_rect.bottom-send_high_temp-15;
			static_send_rect.SetRect(send_edit_TLpoint,send_edit_BRpoint); 
			//16进制发送调整
			send_edit_TLpoint.x=m_rect.left+sendbox_to_dialog_left+120;
			send_edit_TLpoint.y=m_rect.bottom-send_high_temp-37;
			send_edit_BRpoint.x=m_rect.left+sendbox_to_dialog_left+190;
			send_edit_BRpoint.y=m_rect.bottom-send_high_temp-12;
			hex16_send_rect.SetRect(send_edit_TLpoint,send_edit_BRpoint); 


		/*	send_rect.left=send_rect.left;
			send_rect.right=send_rect.right;
			send_rect.top=m_rect.bottom-receive_rect.bottom;
			send_rect.bottom=m_rect.bottom;*/

			pWnd_RX->MoveWindow(receive_rect);//设置控件大小

			pWnd_TX->Invalidate(FALSE);//防止按钮显示出现横条纹//rxh2.4

			pWnd_TX->MoveWindow(send_rect);

			GetDlgItem(IDC_BUTTON_SEND)->Invalidate(FALSE);//防止按钮显示出现横条纹
			pWnd_HEXsend->Invalidate(FALSE);//防止按钮显示出现横条纹

			pWnd_staticsend->MoveWindow(static_send_rect);
			pWnd_HEXsend->MoveWindow(hex16_send_rect);

			line_length=m_edit_receive_data.LineLength(1);//重新获取接收框第一行长度//rxh2.6
			//获取编辑框内文本行数
			line_count=m_edit_receive_data.GetLineCount();	
			//显示行数
			CString strTemp;
			strTemp.Format("行:%ld列:%ld ",line_count,line_length);
			//	strTemp="行数:"+strTemp;
			m_static_receive_line_count.SetWindowText(strTemp);  //显示接收行数
			
			//Invalidate();//rxh2.8使客户区无效，强制调用OnPaint刷新客户区
		}
	}//*/
////////////////////////////////////////////////////////////
//网上版本2
/*	if(nType!=SIZE_MINIMIZED )  //判断窗口是不是最小化了，因为窗口最小化之后 ，窗口的长和宽会变成0，当前一次变化的时就会出现除以0的错误操作
	{
		ChangeSize(IDC_EDIT_RECEIVE,cx,cy);  /对每一个控件依次做调整
	//	ChangeSize(IDC_EDIT_RECEIVE,cx,cy);
	//	ChangeSize(IDC_EDIT_RECEIVE,cx,cy); 
	//	ChangeSize(IDC_EDIT_RECEIVE,cx,cy); 
		GetClientRect(&m_rect);   //最后要更新对话框的大小，当做下一次变化的旧坐标；
     }//*/
////////////////////////////////////////////////////////////////
	
}
//改变控件大小的函数，由OnSize函数调用
void CSerialPort_NewDlg::ChangeSize(UINT nID, int x, int y)  //nID为控件ID，x,y分别为对话框的当前长和宽
{
	CWnd *pWnd;
	pWnd=GetDlgItem(nID); 
	if(pWnd!=NULL)     //判断是否为空，因为在窗口创建的时候也会调用OnSize函数，但是此时各个控件还没有创建，Pwnd为空
	{
		CRect rec; 
		pWnd->GetWindowRect(&rec);  //获取控件变化前的大小
		ScreenToClient(&rec);   //将控件大小装换位在对话框中的区域坐标
		rec.left=rec.left*x/m_rect.Width();  //按照比例调整空间的新位置
		rec.top=rec.top*y/m_rect.Height();
		rec.bottom=rec.bottom*y/m_rect.Height();
		rec.right=rec.right*x/m_rect.Width();
		pWnd->MoveWindow(rec);   //伸缩控件
	}
}


//定时发送
void CSerialPort_NewDlg::OnCheckTimerSend() //rxh2.4,定时发送功能
{
	if(m_check_timer_send.GetCheck())//勾选定时发送
	{
		if(m_bSerialPortOpened)//串口已经打开
		{
			CString strText;
			m_ctrl_edit_send_period.GetWindowText(strText);//获取编辑框内的字符串
			timer_send_period=atoi(strText);
			if (timer_send_period<1)
				KillTimer(1);
			else
			SetTimer(1,timer_send_period,NULL);
		}
		else
		{
			m_check_timer_send.SetCheck(FALSE);//rxh2.7//取消选中定时发送
			CString str;
			str.Format("COM%d 没有打开",Com_Num);//很棒~~~~~~~~~~~~~~~~~~~~~~~
			AfxMessageBox(str);

		//	m_check_timer_send.();
			return; //检查串口是否打开
		}

	}
	else
		KillTimer(1);


	
}
//已经改变定时周期
void CSerialPort_NewDlg::OnChangeEditTemerPeriod() //rxh2.4
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString strText;
	m_ctrl_edit_send_period.GetWindowText(strText);
	timer_send_period=atoi(strText);

	if(m_check_timer_send.GetCheck()&&m_bSerialPortOpened)//rxh2.6//勾选定时发送并且串口已经打开
	{
		if (timer_send_period<1)
			KillTimer(1);
		else
			SetTimer(1,timer_send_period,NULL);
	}	
}
//对话框关闭
void CSerialPort_NewDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if(receive_buffer != NULL)//rxh2.8删除自开辟的内存
    {
        delete [] receive_buffer;
        receive_buffer = NULL;//赋值空指针，防止乱删空间
    }	
}
//串口被突然拔出或者发生读取错误等，采集线程将向对话框发送错误消息，这是响应函数//rxh2.8
void CSerialPort_NewDlg::OnComErrorAndClose()
{	//关闭串口
	close_port_all();
	//重新扫描电脑所有串口
	tCSerialPort.Hkey2ComboBox(m_combo_com_num);//遍历串口//rxh2.0
	m_combo_com_num.SetCurSel(0);
	Com_Num=m_nComArray[0];//在遍历函数中从注册表中读取的串口号存储到m_nComArray[]数组中
}
//改变背景色
/*HBRUSH CSerialPort_NewDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);//rxh2.8不使用默认的画刷
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}*/
//设置通信数据格式按钮//rxh2.9
void CSerialPort_NewDlg::OnButtonDataFormat() 
{
	// TODO: Add your control notification handler code here
	//关闭串口 
	close_port_all();
	
	tDATA_Fomate_Dlg.DoModal();
	
}

//关于作者
void CSerialPort_NewDlg::OnButtonAboutAuthor() 
{

	m_string_receive="\r\n###############################################################\r\n\r\n\
本串口助手是作者花少在休息时间开发的一款高速串口\r\n\r\n\
具有串口号自动扫描、多波特率、数据位、校验位、停止位选择\r\n\r\n\
串口拔出解除互锁，定时发送、十六进制发送、接收、行列计数等功能\r\n\r\n\
接收框不清空、不卡顿，方便查看历史数据，自动随窗口缩放，自动换行。\r\n\r\n\
如有问题或改进建议请加群反馈\r\n\r\n\
串口软件反馈交流群：476174311\r\n\r\n\
作者的高速多通道虚拟示波器正在开发，即将上线！\r\n\r\n\
如果您觉得这款免费串口助手给您的开发工作带来方便\r\n\r\n\
请捐赠开发者     支付宝:861063204@qq.com\r\n\r\n\
您的支持是我继续开发的最强动力！\r\n\
###############################################################\r\n";

	m_edit_receive_data.SetSel(-1, -1);//选中编辑框中的文本
	m_edit_receive_data.ReplaceSel(m_string_receive);//替换文本
	m_string_receive.Empty();//使用完清零	
}
