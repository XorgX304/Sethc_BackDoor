
// SethcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Sethc.h"
#include "SethcDlg.h"
#include "SystemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSethcDlg 对话框

const static int g_nMaxCount = 3;


CSethcDlg::CSethcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSethcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nCurCount = 0;
}

void CSethcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSethcDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CSethcDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSethcDlg 消息处理程序

BOOL CSethcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSethcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSethcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSethcDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strInputPwd = _T("");  //用户输入的密码
	GetDlgItemText(IDC_EDIT_PWD, strInputPwd);
	if (strInputPwd.IsEmpty())  //密码为空
	{
		MessageBox(_T("Please Enter the Password!"), _T("Error"), MB_ICONWARNING);
		return;
	}
	TCHAR szPassWord[MAX_PATH] = _T("AAAAAAAAAAAAAAAA");
	if (0 == wcscmp(szPassWord, strInputPwd))
	{
		OnOK();
		CSystemDlg systemDlg;
		systemDlg.DoModal();
	}
	else
	{
		m_nCurCount++;
		CString strMsg = _T("");
		strMsg.Format(_T("Password Error, you have %d chances!"), g_nMaxCount - m_nCurCount);
		MessageBox(strMsg, _T("Error"), MB_ICONWARNING);
		SetDlgItemText(IDC_EDIT_PWD, _T(""));
		if (m_nCurCount >= g_nMaxCount)  //超过输入的错误次数
		{
			OnOK();
		}
	}
}
