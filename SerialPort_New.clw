; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSerialPort_NewDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SerialPort_New.h"

ClassCount=4
Class1=CSerialPort_NewApp
Class2=CSerialPort_NewDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_SERIALPORT_NEW_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=DATA_Fomate_Dlg
Resource4=IDD_DIALOG_DATA_FORMAT

[CLS:CSerialPort_NewApp]
Type=0
HeaderFile=SerialPort_New.h
ImplementationFile=SerialPort_New.cpp
Filter=N
LastObject=CSerialPort_NewApp

[CLS:CSerialPort_NewDlg]
Type=0
HeaderFile=SerialPort_NewDlg.h
ImplementationFile=SerialPort_NewDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_STATIC_RECEIVE_COUNT

[CLS:CAboutDlg]
Type=0
HeaderFile=SerialPort_NewDlg.h
ImplementationFile=SerialPort_NewDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SERIALPORT_NEW_DIALOG]
Type=1
Class=CSerialPort_NewDlg
ControlCount=21
Control1=IDC_BUTTON_OPEN,button,1342242816
Control2=IDC_BUTTON_CLEAN,button,1342242816
Control3=IDC_BUTTON_SEND,button,1342246657
Control4=IDC_EDIT_RECEIVE,edit,1352732740
Control5=IDC_EDIT_SEND,edit,1352732740
Control6=IDC_STATIC_RECEIVE_COUNT,static,1342308876
Control7=IDC_STATIC,static,1342308864
Control8=IDC_COMBO_BANDRATE,combobox,1344339970
Control9=IDC_COMBO_COM_NUM,combobox,1344339970
Control10=IDC_STATIC,static,1342308864
Control11=IDC_STATIC_SEND_COUNT,static,1342308876
Control12=IDC_CHECK_HEX16_DISP,button,1342242819
Control13=IDC_CHECK_HEX16_SEND,button,1342245891
Control14=IDC_BUTTON__CLEAN_COUNT_,button,1342242816
Control15=IDC_CHECK_TIMER_SEND,button,1342242819
Control16=IDC_EDIT_TEMER_PERIOD,edit,1350631552
Control17=IDC_STATIC,static,1342308353
Control18=IDC_STATIC_RECEIVE_LINE_COUNT,static,1342308864
Control19=IDC_STATIC_THREAD_COUNT_NO_USE,static,1073872896
Control20=IDC_BUTTON_DATA_FORMAT,button,1342242816
Control21=IDC_BUTTON__ABOUT_AUTHOR,button,1342242816

[DLG:IDD_DIALOG_DATA_FORMAT]
Type=1
Class=DATA_Fomate_Dlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDC_COMBO_DATA_BIT,combobox,1344339970
Control3=IDC_COMBO_STOP_BIT,combobox,1344339970
Control4=IDC_COMBO_CHECK_BIT,combobox,1344339970
Control5=IDC_STATIC_DATA_BIT,static,1342308865
Control6=IDC_STATIC_STOP_BIT,static,1342308352
Control7=IDC_STATIC_CHECK_BIT,static,1342308352
Control8=IDC_STATIC,static,1342308353

[CLS:DATA_Fomate_Dlg]
Type=0
HeaderFile=DATA_Fomate_Dlg.h
ImplementationFile=DATA_Fomate_Dlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_COMBO_CHECK_BIT
VirtualFilter=dWC

