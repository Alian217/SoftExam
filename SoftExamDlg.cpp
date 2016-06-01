
// SoftExamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SoftExam.h"
#include "SoftExamDlg.h"
#include "afxdialogex.h"
#include <io.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char *cXZTFileName = "XZT.txt";
char *cTKTFileName = "TKT.txt";
char *cJDTFileName = "JDT.txt";
char *cJCTFileName = "JCT.txt";
char *cBCTFileName = "BCT.txt";
char *pStartFlag   = "<START>";
char *pEndFlag     = "<END>";
char *pANSWERFlag  = "<ANSWER>";

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSoftExamDlg 对话框




CSoftExamDlg::CSoftExamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSoftExamDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSoftExamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSoftExamDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSoftExamDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSoftExamDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSoftExamDlg 消息处理程序

BOOL CSoftExamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//出题数不能大于题库总数
	ASSERT( SUM_XZT<=MAX_XZT && SUM_TKT<=MAX_TKT && SUM_JDT<=MAX_JDT && SUM_JCT<=MAX_JCT && SUM_BCT<=MAX_BCT );
	//标记长度不能大于标记堆积验证行长度
	ASSERT( strlen(pStartFlag)<=ROW && strlen(pEndFlag)<=ROW && strlen(pANSWERFlag)<=ROW );
	iLenOPFpath = 0;

	memset( &stRandNum, 0x00, sizeof(RANDNUM) );
	memset( &stTitleAswer, '\0', sizeof(TITLE_ASWER) );

	//导出题目库内容到内存中
	if ( 0 == GetTMfromExamDB( &stTitleAswer ) )
	{
		AfxMessageBox(_T("Get title from DB fail!"));
		exit(0);
	}

	//设置题目数量，默认题目数量
	char pTitleSum[25] = {0};
	memset( pTitleSum, '\0', sizeof(pTitleSum) );
	sprintf( pTitleSum, "%d", SUM_XZT );
	SetDlgItemText( IDC_EDIT1, pTitleSum );
	memset( pTitleSum, '\0', sizeof(pTitleSum) );
	sprintf( pTitleSum, "%d", SUM_TKT );
	SetDlgItemText( IDC_EDIT2, pTitleSum );
	memset( pTitleSum, '\0', sizeof(pTitleSum) );
	sprintf( pTitleSum, "%d", SUM_JDT );
	SetDlgItemText( IDC_EDIT3, pTitleSum );
	memset( pTitleSum, '\0', sizeof(pTitleSum) );
	sprintf( pTitleSum, "%d", SUM_JCT );
	SetDlgItemText( IDC_EDIT4, pTitleSum );
	memset( pTitleSum, '\0', sizeof(pTitleSum) );
	sprintf( pTitleSum, "%d", SUM_BCT );
	SetDlgItemText( IDC_EDIT5, pTitleSum );
	//从文件中获取到的题目总数
	memset( pTitleSum, '\0', sizeof(pTitleSum) );
	sprintf( pTitleSum, "%3d", stTitleAswer.iSumTleXzt );
	SetDlgItemText( IDC_STATIC1, pTitleSum );
	memset( pTitleSum, '\0', sizeof(pTitleSum) );
	sprintf( pTitleSum, "%3d", stTitleAswer.iSumTleTkt );
	SetDlgItemText( IDC_STATIC2, pTitleSum );
	memset( pTitleSum, '\0', sizeof(pTitleSum) );
	sprintf( pTitleSum, "%3d", stTitleAswer.iSumTleJdt );
	SetDlgItemText( IDC_STATIC3, pTitleSum );
	memset( pTitleSum, '\0', sizeof(pTitleSum) );
	sprintf( pTitleSum, "%3d", stTitleAswer.iSumTleJct );
	SetDlgItemText( IDC_STATIC4, pTitleSum );
	memset( pTitleSum, '\0', sizeof(pTitleSum) );
	sprintf( pTitleSum, "%3d", stTitleAswer.iSumTleBct );
	SetDlgItemText( IDC_STATIC5, pTitleSum );

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSoftExamDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSoftExamDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSoftExamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSoftExamDlg::GetRandomNumber( P_RANDNUM pRandNum )
{
	int *TmCom = NULL;
	int Max=0,Sum=0;
	int iSumTM=0,iSumGet=0,iCnt=0;
	srand((unsigned)time(NULL));

	//不同条件下的随机数
	for ( iSumTM=0; iSumTM<SUM_TM; iSumTM++ )
	{
		//配置各类型题目数据
		switch (iSumTM)
		{
		case 0:
			TmCom = pRandNum->XZT;Max = stTitleAswer.iSumTleXzt;Sum = pRandNum->Sum_XZT;
			break;
		case 1:
			TmCom = pRandNum->TKT;Max = stTitleAswer.iSumTleTkt;Sum = pRandNum->Sum_TKT;
			break;
		case 2:
			TmCom = pRandNum->JDT;Max = stTitleAswer.iSumTleJdt;Sum = pRandNum->Sum_JDT;
			break;
		case 3:
			TmCom = pRandNum->JCT;Max = stTitleAswer.iSumTleJct;Sum = pRandNum->Sum_JCT;
			break;
		case 4:
			TmCom = pRandNum->BCT;Max = stTitleAswer.iSumTleBct;Sum = pRandNum->Sum_BCT;
			break;
		default:
			break;
		}
		//获取随机数
		while(iSumGet<Sum)
		{
			//随机数生成器
			TmCom[iSumGet] = rand()%Max;
			//判断获取的随机数重复？
			for( iCnt=0; iCnt<iSumGet; iCnt++ )
			{
				//重复随机数跳出重取
				if( TmCom[iCnt] == TmCom[iSumGet] )
				{
					break;
				}
			}
			//取到随机数和之前的都不重复
			if( iSumGet == iCnt )
			{
				iSumGet++;
			}
		}
		//获取完一种类型题目随机数，清除临时记录变量
		iSumGet = iCnt = 0;
	}
}


//堆积验证从文件中读取的内容属于验证堆积数组的哪一个下标
int CSoftExamDlg::TOOL_VerifyFlagFromFile( char v_pVerifyFlag[COL][ROW], char v_cInputFlag, char v_pAccumBuf[ROW+1], int *v_iLenAccumBuf )
{
	int iRes = -1;
	int iCnt = 0;

	//堆积缓冲区的数据
	v_pAccumBuf[(*v_iLenAccumBuf)++] = v_cInputFlag;

	//和堆积二维数组内容进行判断
	for( iCnt=0; iCnt<COL; iCnt++ )
	{
		if( 0 == memcmp( v_pVerifyFlag[iCnt], v_pAccumBuf, *v_iLenAccumBuf ) )
		{
			//如果某一项完全匹配，直接跳出，返回下标
			if ( strlen(v_pVerifyFlag[iCnt]) == *v_iLenAccumBuf )
			{
				iRes = iCnt;
				memset( v_pAccumBuf, '\0', sizeof(char)*(ROW+1) );
				*v_iLenAccumBuf = 0;
			}
			break;
		}
	}
	//如果没有从堆积二维数组中找到对应标记，重启堆积运算
	if ( COL == iCnt )
	{
		memset( v_pAccumBuf, '\0', sizeof(char)*(ROW+1) );
		*v_iLenAccumBuf = 0;
	}

	return iRes;
}


int CSoftExamDlg::GetTMfromExamDB( P_TITLE_ASWER pTleAsw )
{
    FILE *fp = NULL;
	char cGetChar;
	int iFlagFromFile = -1;
	int  iLenGetData = 0;    //-1没有开始读取 0读取到<start> 1读取到<END> 2读取到<ANSWER>
	char pGetDateBuf[LENTH_TITLE+1] = {0};
	char pVerifyFlag[COL][ROW] = {0};
	char pAccumBuf[ROW+1] = {0};
	int  iLenAccumBuf = 0;
	char *TitleType = NULL;
	int  iFlagTurn = 2;    //跳转标志位

	//导入验证堆积二维数组内容
	memset( pVerifyFlag, '\0', sizeof(char)*COL*ROW );
	memcpy( &pVerifyFlag[0], pStartFlag, strlen(pStartFlag) );
	memcpy( &pVerifyFlag[1], pEndFlag,   strlen(pEndFlag)   );
	memcpy( &pVerifyFlag[2], pANSWERFlag,strlen(pANSWERFlag) );

	//清空临时缓存及变量
	memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
	memset( pAccumBuf, '\0', sizeof(char)*(ROW+1) );
	iLenAccumBuf = 0; iFlagTurn = 2; iFlagFromFile = -1;

	//1.打开选择题库,进行读取
	TitleType = cXZTFileName;
	if ( 0 == access(TitleType,0) )
	{
		fp = fopen( TitleType, "a+" );
		if( fp == NULL ) 
		{
			AfxMessageBox(_T("无法打开选择题库文件"));
			return 0;
		}
		//循环读取文件
		while( fread( &cGetChar, 1, 1, fp ) )
		{
			//读取题目标志位 <START>——0 <END>——1 <ANSWER>——2
			iFlagFromFile = TOOL_VerifyFlagFromFile( pVerifyFlag, cGetChar, pAccumBuf, &iLenAccumBuf );

			//只有找到对应标记位的时候开始取数据
			if ( 0 == iFlagTurn || 1 == iFlagTurn )
			{
				pGetDateBuf[iLenGetData++] = cGetChar;
			}
			//状态操作
			if( 2 == iFlagTurn && 0 == iFlagFromFile )
			{
				iFlagTurn = 0;
			}
			else if( 0 == iFlagTurn && 1 == iFlagFromFile )
			{
				memcpy( pTleAsw->szXZTTitle[(pTleAsw->iSumTleXzt)++], pGetDateBuf, iLenGetData-strlen(pEndFlag) );
				memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
				iLenGetData = 0;
				iFlagTurn = 1;
			}
			else if( 1 == iFlagTurn && 2 == iFlagFromFile )
			{
				memcpy( pTleAsw->szXZTAnser[(pTleAsw->iSumAnsXzt)++], pGetDateBuf, iLenGetData-strlen(pANSWERFlag) );
				memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
				iLenGetData = 0;
				iFlagTurn = 2;
				// 从题目库里面读出的题目超过缓存区上限，不再读取
				if ( pTleAsw->iSumTleXzt>=MAX_XZT || pTleAsw->iSumAnsXzt>=MAX_XZT )
				{
					break;
				}
			}
		}
		fclose(fp);
		fp = NULL;
	}
	else
	{
		AfxMessageBox(_T("未找到选择题库文件"));
		return 0;
	}
	
	//清空临时缓存及变量
	memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
	memset( pAccumBuf, '\0', sizeof(char)*(ROW+1) );
	iLenAccumBuf = 0; iFlagTurn = 2; iFlagFromFile = -1;

	//2.打开填空题库,进行读取
	TitleType = cTKTFileName;
	if ( 0 == access(TitleType,0) )
	{
		fp = fopen( TitleType, "a+" );
		if( fp == NULL ) 
		{
			AfxMessageBox(_T("无法打开填空题库文件"));
			return 0;
		}
		//循环读取文件
		while( fread( &cGetChar, 1, 1, fp ) )
		{
			//读取题目标志位 <START>——0 <END>——1 <ANSWER>——2
			iFlagFromFile = TOOL_VerifyFlagFromFile( pVerifyFlag, cGetChar, pAccumBuf, &iLenAccumBuf );

			//只有找到对应标记位的时候开始取数据
			if ( 0 == iFlagTurn || 1 == iFlagTurn )
			{
				pGetDateBuf[iLenGetData++] = cGetChar;
			}
			//状态操作
			if( 2 == iFlagTurn && 0 == iFlagFromFile )
			{
				iFlagTurn = 0;
			}
			else if( 0 == iFlagTurn && 1 == iFlagFromFile )
			{
				memcpy( pTleAsw->szTKTTitle[(pTleAsw->iSumTleTkt)++], pGetDateBuf, iLenGetData-strlen(pEndFlag) );
				memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
				iLenGetData = 0;
				iFlagTurn = 1;
			}
			else if( 1 == iFlagTurn && 2 == iFlagFromFile )
			{
				memcpy( pTleAsw->szTKTAnser[(pTleAsw->iSumAnsTkt)++], pGetDateBuf, iLenGetData-strlen(pANSWERFlag) );
				memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
				iLenGetData = 0;
				iFlagTurn = 2;
				// 从题目库里面读出的题目超过缓存区上限，不再读取
				if ( pTleAsw->iSumTleTkt>=MAX_TKT || pTleAsw->iSumAnsTkt>=MAX_TKT )
				{
					break;
				}
			}
		}
		fclose(fp);
		fp = NULL;
	}
	else
	{
		AfxMessageBox(_T("未找到填空题库文件"));
		return 0;
	}

	//清空临时缓存及变量
	memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
	memset( pAccumBuf, '\0', sizeof(char)*(ROW+1) );
	iLenAccumBuf = 0; iFlagTurn = 2; iFlagFromFile = -1;

	//3.打开简答题库,进行读取
	TitleType = cJDTFileName;
	if ( 0 == access(TitleType,0) )
	{
		fp = fopen( TitleType, "a+" );
		if( fp == NULL ) 
		{
			AfxMessageBox(_T("无法打开简答题库文件"));
			return 0;
		}
		//循环读取文件
		while( fread( &cGetChar, 1, 1, fp ) )
		{
			//读取题目标志位 <START>——0 <END>——1 <ANSWER>——2
			iFlagFromFile = TOOL_VerifyFlagFromFile( pVerifyFlag, cGetChar, pAccumBuf, &iLenAccumBuf );

			//只有找到对应标记位的时候开始取数据
			if ( 0 == iFlagTurn || 1 == iFlagTurn )
			{
				pGetDateBuf[iLenGetData++] = cGetChar;
			}
			//状态操作
			if( 2 == iFlagTurn && 0 == iFlagFromFile )
			{
				iFlagTurn = 0;
			}
			else if( 0 == iFlagTurn && 1 == iFlagFromFile )
			{
				memcpy( pTleAsw->szJDTTitle[(pTleAsw->iSumTleJdt)++], pGetDateBuf, iLenGetData-strlen(pEndFlag) );
				memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
				iLenGetData = 0;
				iFlagTurn = 1;
			}
			else if( 1 == iFlagTurn && 2 == iFlagFromFile )
			{
				memcpy( pTleAsw->szJDTAnser[(pTleAsw->iSumAnsJdt)++], pGetDateBuf, iLenGetData-strlen(pANSWERFlag) );
				memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
				iLenGetData = 0;
				iFlagTurn = 2;
				// 从题目库里面读出的题目超过缓存区上限，不再读取
				if ( pTleAsw->iSumTleJdt>=MAX_JDT || pTleAsw->iSumAnsJdt>=MAX_JDT )
				{
					break;
				}
			}
		}
		fclose(fp);
		fp = NULL;
	}
	else
	{
		AfxMessageBox(_T("未找到简答题库文件"));
		return 0;
	}

	//清空临时缓存及变量
	memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
	memset( pAccumBuf, '\0', sizeof(char)*(ROW+1) );
	iLenAccumBuf = 0; iFlagTurn = 2; iFlagFromFile = -1;

	//4.打开简答题库,进行读取
	TitleType = cJCTFileName;
	if ( 0 == access(TitleType,0) )
	{
		fp = fopen( TitleType, "a+" );
		if( fp == NULL ) 
		{
			AfxMessageBox(_T("无法打开纠错题库文件"));
			return 0;
		}
		//循环读取文件
		while( fread( &cGetChar, 1, 1, fp ) )
		{
			//读取题目标志位 <START>——0 <END>——1 <ANSWER>——2
			iFlagFromFile = TOOL_VerifyFlagFromFile( pVerifyFlag, cGetChar, pAccumBuf, &iLenAccumBuf );

			//只有找到对应标记位的时候开始取数据
			if ( 0 == iFlagTurn || 1 == iFlagTurn )
			{
				pGetDateBuf[iLenGetData++] = cGetChar;
			}
			//状态操作
			if( 2 == iFlagTurn && 0 == iFlagFromFile )
			{
				iFlagTurn = 0;
			}
			else if( 0 == iFlagTurn && 1 == iFlagFromFile )
			{
				memcpy( pTleAsw->szJCTTitle[(pTleAsw->iSumTleJct)++], pGetDateBuf, iLenGetData-strlen(pEndFlag) );
				memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
				iLenGetData = 0;
				iFlagTurn = 1;
			}
			else if( 1 == iFlagTurn && 2 == iFlagFromFile )
			{
				memcpy( pTleAsw->szJCTAnser[(pTleAsw->iSumAnsJct)++], pGetDateBuf, iLenGetData-strlen(pANSWERFlag) );
				memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
				iLenGetData = 0;
				iFlagTurn = 2;
				// 从题目库里面读出的题目超过缓存区上限，不再读取
				if ( pTleAsw->iSumTleJct>=MAX_JCT || pTleAsw->iSumAnsJct>=MAX_JCT )
				{
					break;
				}
			}
		}
		fclose(fp);
		fp = NULL;
	}
	else
	{
		AfxMessageBox(_T("未找到纠错题库文件"));
		return 0;
	}

	//清空临时缓存及变量
	memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
	memset( pAccumBuf, '\0', sizeof(char)*(ROW+1) );
	iLenAccumBuf = 0; iFlagTurn = 2; iFlagFromFile = -1;

	//5.打开编程题库,进行读取
	TitleType = cBCTFileName;
	if ( 0 == access(TitleType,0) )
	{
		fp = fopen( TitleType, "a+" );
		if( fp == NULL ) 
		{
			AfxMessageBox(_T("无法打开编程题库文件"));
			return 0;
		}
		//循环读取文件
		while( fread( &cGetChar, 1, 1, fp ) )
		{
			//读取题目标志位 <START>——0 <END>——1 <ANSWER>——2
			iFlagFromFile = TOOL_VerifyFlagFromFile( pVerifyFlag, cGetChar, pAccumBuf, &iLenAccumBuf );

			//只有找到对应标记位的时候开始取数据
			if ( 0 == iFlagTurn || 1 == iFlagTurn )
			{
				pGetDateBuf[iLenGetData++] = cGetChar;
			}
			//状态操作
			if( 2 == iFlagTurn && 0 == iFlagFromFile )
			{
				iFlagTurn = 0;
			}
			else if( 0 == iFlagTurn && 1 == iFlagFromFile )
			{
				memcpy( pTleAsw->szBCTTitle[(pTleAsw->iSumTleBct)++], pGetDateBuf, iLenGetData-strlen(pEndFlag) );
				memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
				iLenGetData = 0;
				iFlagTurn = 1;
			}
			else if( 1 == iFlagTurn && 2 == iFlagFromFile )
			{
				memcpy( pTleAsw->szBCTAnser[(pTleAsw->iSumAnsBct)++], pGetDateBuf, iLenGetData-strlen(pANSWERFlag) );
				memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
				iLenGetData = 0;
				iFlagTurn = 2;
				// 从题目库里面读出的题目超过缓存区上限，不再读取
				if ( pTleAsw->iSumTleBct>=MAX_BCT || pTleAsw->iSumAnsBct>=MAX_BCT )
				{
					break;
				}
			}
		}
		fclose(fp);
		fp = NULL;
	}
	else
	{
		AfxMessageBox(_T("未找到编程题库文件"));
		return 0;
	}
	return 1;
}


//获取系统当前时间
void CSoftExamDlg::TOOL_GetLocalTime( char v_cLocalTime[15] )
{
	int year, month, day, hour, min, sec;
	struct tm *timeinfo;			//定义时间结构体 
	time_t nowtime;  
	time( &nowtime );				//获取时间   
	timeinfo = localtime( &nowtime );	//转化为当地时间  
	year = timeinfo->tm_year + 1900;	//从1900年开始计数，所以+1900 
	month = timeinfo->tm_mon + 1;		//从0开始计数，所以+1 
	day = timeinfo->tm_mday; 
	hour = timeinfo->tm_hour; 
	min = timeinfo->tm_min; 
	sec = timeinfo->tm_sec; 
	memset(v_cLocalTime,0x00,sizeof(v_cLocalTime));
	sprintf( v_cLocalTime, "%04d%02d%02d%02d%02d%02d",year ,month ,day ,hour ,min ,sec );  
}

void CSoftExamDlg::TOOL_IgnoreChar( char *pSrc, int iLenSrc, char IgnoreChar, char cPosition )
{
	int iSumChar = 0;
	char pTemp[LENTH_TITLE] = {0};

	//拷贝原数据到缓冲区中
	memset( pTemp, '\0', sizeof(char)*LENTH_TITLE );
	memcpy( pTemp, pSrc, iLenSrc );

	if ( STRING_BEGIN == cPosition )
	{
		while (1)
		{
			if ( IgnoreChar!=pTemp[iSumChar] )
			{
				break;
			}
			else
			{
				iSumChar++;
			}
		}
		
		//需要清理就整理原字符串，没有就返回
		if ( 0!=iSumChar )
		{
			memcpy( pSrc, pTemp+iSumChar, iLenSrc );
		} 
	}
}

int CSoftExamDlg::TOOL_CheckSetting()
{
	int iRes = 0;
	int TempBufLen = 0;
	char TempBuf[200] = {0};
	char SumTitle[20] = {0};  //获取各个题目编辑框中的数字
	char OverMax[SUM_TM][LENTH_FILENAME] = {
												"选择题 超 总数!\n",
												"填空题 超 总数!\n",
												"简答题 超 总数!\n",
												"纠错题 超 总数!\n",
												"编程题 超 总数!\n"
											 };
	memset( TempBuf, '\0', sizeof(TempBuf) );
	memset( SumTitle, '\0', sizeof(SumTitle) );
	GetDlgItemText( IDC_EDIT1, SumTitle, 10 );
	stRandNum.Sum_XZT = atoi( SumTitle );
	if( stRandNum.Sum_XZT>stTitleAswer.iSumTleXzt )
	{
		sprintf( TempBuf+TempBufLen, OverMax[0], strlen(OverMax[0]) );
		TempBufLen +=strlen(OverMax[0]);
	}

	memset( SumTitle, '\0', sizeof(SumTitle) );
	GetDlgItemText( IDC_EDIT2, SumTitle, 3 );
	stRandNum.Sum_TKT = atoi( SumTitle );
	if( stRandNum.Sum_TKT>stTitleAswer.iSumTleTkt )
	{
		sprintf( TempBuf+TempBufLen, OverMax[1], strlen(OverMax[1]) );
		TempBufLen +=strlen(OverMax[1]);
	}

	memset( SumTitle, '\0', sizeof(SumTitle) );
	GetDlgItemText( IDC_EDIT3, SumTitle, 3 );
	stRandNum.Sum_JDT = atoi( SumTitle );	
	if( stRandNum.Sum_JDT>stTitleAswer.iSumTleJdt )
	{
		sprintf( TempBuf+TempBufLen, OverMax[2], strlen(OverMax[2]) );
		TempBufLen +=strlen(OverMax[2]);
	}

	memset( SumTitle, '\0', sizeof(SumTitle) );
	GetDlgItemText( IDC_EDIT4, SumTitle, 3 );
	stRandNum.Sum_JCT = atoi( SumTitle );
	if( stRandNum.Sum_JCT>stTitleAswer.iSumTleJct )
	{
		sprintf( TempBuf+TempBufLen, OverMax[3], strlen(OverMax[3]) );
		TempBufLen +=strlen(OverMax[3]);
	}

	memset( SumTitle, '\0', sizeof(SumTitle) );
	GetDlgItemText( IDC_EDIT5, SumTitle, 3 );
	stRandNum.Sum_BCT = atoi( SumTitle );
	if( stRandNum.Sum_BCT>stTitleAswer.iSumTleBct )
	{
		sprintf( TempBuf+TempBufLen, OverMax[4], strlen(OverMax[4]) );
		TempBufLen +=strlen(OverMax[4]);
	}

	if ( 0!=strlen(TempBuf) )
	{
		AfxMessageBox( _T(TempBuf) );
		iRes = 1;
	}
	return iRes;
}


int CSoftExamDlg::CreateExam( P_RANDNUM pRandNum, P_TITLE_ASWER pTleAsw )
{
	FILE *fp = NULL;
	int iCnt = 0, iCntEmptyLine = 0;
	//申请空间，使用完成后释放掉
	char cTempNum[10] = {0};
	char cItemTitle[SUM_TM][LENTH_FILENAME] = {
													"一.",
													"二.",
													"三.",
													"四.",
													"五."
												};
	int  nItemTitle = 0;
	int  nTempLen = 0;
	int  nWDataLen = 0, nNumTitle = 0;
	int  nWDataAnswerlen = 0, nNumAnswerTitle = 0;
	char *cWDataBuf = (char *)malloc(LENTH_EXAM*sizeof(char));         //不带答案试卷缓存
	char *cWDataAnswerBuf = (char *)malloc(LENTH_EXAM*sizeof(char));  //带答案试卷缓存
	memset( cWDataBuf, '\0', sizeof(char)*LENTH_EXAM );
	memset( cWDataAnswerBuf, '\0', sizeof(char)*LENTH_EXAM );

	//导入随机选择题
	//打入题目类
	if ( 0!=pRandNum->Sum_XZT )
	{
		sprintf(cWDataBuf+nWDataLen, "%s",cItemTitle[nItemTitle]);
		nWDataLen += 3;
		sprintf(cWDataBuf+nWDataLen, "选择题\n");
		nWDataLen += 7;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "%s",cItemTitle[nItemTitle++]);
		nWDataAnswerlen += 3;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "选择题\n");
		nWDataAnswerlen += 7;
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		//循环导入题目
		nNumTitle = 1;
		for ( iCnt=0; iCnt<pRandNum->Sum_XZT; iCnt++ )
		{
			//序号
			memset( cTempNum, '\0', (sizeof(char)*10) );
			sprintf( cTempNum, "%d.", nNumTitle++ );
			memcpy( cWDataBuf+nWDataLen, cTempNum, strlen(cTempNum) );
			nWDataLen += strlen(cTempNum);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, cTempNum, strlen(cTempNum) );
			nWDataAnswerlen += strlen(cTempNum);

			//过滤掉开始的连续的换行键
			TOOL_IgnoreChar( pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])], strlen(pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])]), 0x0A, STRING_BEGIN );

			//题目
			memcpy( cWDataBuf+nWDataLen, pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])], strlen(pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])]) );
			nWDataLen += strlen(pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])]);
			ADD_ENTER(cWDataBuf,nWDataLen);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])], strlen(pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])]);

			//答案
			memcpy( cWDataAnswerBuf+nWDataAnswerlen-1, pTleAsw->szXZTAnser[(pRandNum->XZT[iCnt])], strlen(pTleAsw->szXZTAnser[(pRandNum->XZT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szXZTAnser[(pRandNum->XZT[iCnt])]);
			ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		}
	}

	if ( 0!=pRandNum->Sum_TKT )
	{
		//导入随机填空题
		//打入题目类
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);		
		sprintf(cWDataBuf+nWDataLen, "%s",cItemTitle[nItemTitle]);
		nWDataLen += 3;
		sprintf(cWDataBuf+nWDataLen, "填空题\n");
		nWDataLen += 7;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "%s",cItemTitle[nItemTitle++]);
		nWDataAnswerlen += 3;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "填空题\n");
		nWDataAnswerlen += 7;
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		//循环导入填空题
		nNumTitle = 1;
		for ( iCnt=0; iCnt<pRandNum->Sum_TKT; iCnt++ )
		{
			//序号
			memset( cTempNum, '\0', (sizeof(char)*10) );
			sprintf( cTempNum, "%d.", nNumTitle++ );
			memcpy( cWDataBuf+nWDataLen, cTempNum, strlen(cTempNum) );
			nWDataLen += strlen(cTempNum);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, cTempNum, strlen(cTempNum) );
			nWDataAnswerlen += strlen(cTempNum);

			//过滤掉开始的连续的换行键
			TOOL_IgnoreChar( pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])], strlen(pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])]), 0x0A, STRING_BEGIN );

			//题目
			memcpy( cWDataBuf+nWDataLen, pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])], strlen(pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])]) );
			nWDataLen += strlen(pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])]);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])], strlen(pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])]);
		
			//答案
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szTKTAnser[(pRandNum->TKT[iCnt])], strlen(pTleAsw->szTKTAnser[(pRandNum->TKT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szTKTAnser[(pRandNum->TKT[iCnt])]);
		}
	}

	if ( 0!=pRandNum->Sum_JDT )
	{
		//导入随机简答题
		//打入简答类
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		sprintf(cWDataBuf+nWDataLen, "%s",cItemTitle[nItemTitle]);
		nWDataLen += 3;
		sprintf(cWDataBuf+nWDataLen, "简答题\n");
		nWDataLen += 7;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "%s",cItemTitle[nItemTitle++]);
		nWDataAnswerlen += 3;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "简答题\n");
		nWDataAnswerlen += 7;
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		//循环导入简答题
		nNumTitle = 1;
		for ( iCnt=0; iCnt<pRandNum->Sum_JDT; iCnt++ )
		{
			//序号
			memset( cTempNum, '\0', (sizeof(char)*10) );
			sprintf( cTempNum, "%d.", nNumTitle++ );
			memcpy( cWDataBuf+nWDataLen, cTempNum, strlen(cTempNum) );
			nWDataLen += strlen(cTempNum);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, cTempNum, strlen(cTempNum) );
			nWDataAnswerlen += strlen(cTempNum);

			//过滤掉开始的连续的换行键
			TOOL_IgnoreChar( pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])], strlen(pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])]), 0x0A, STRING_BEGIN );

			//题目
			memcpy( cWDataBuf+nWDataLen, pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])], strlen(pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])]) );
			nWDataLen += strlen(pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])]);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])], strlen(pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])]);

			//答案
			//给试卷添加答案空格行
			for( iCntEmptyLine=0; iCntEmptyLine<SUM_JDT_EMPTY_LINE; iCntEmptyLine++ )
			{
				sprintf(cWDataBuf+nWDataLen, "\n" );
				nWDataLen += 1;
			}
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szJDTAnser[(pRandNum->JDT[iCnt])], strlen(pTleAsw->szJDTAnser[(pRandNum->JDT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szJDTAnser[(pRandNum->JDT[iCnt])]);
			ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		}
	}

	if ( 0!=pRandNum->Sum_JCT )
	{
		//导入随机纠错题
		//打入纠错类
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		sprintf(cWDataBuf+nWDataLen, "%s",cItemTitle[nItemTitle]);
		nWDataLen += 3;
		sprintf(cWDataBuf+nWDataLen, "纠错题\n");
		nWDataLen += 7;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "%s",cItemTitle[nItemTitle++]);
		nWDataAnswerlen += 3;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "纠错题\n");
		nWDataAnswerlen += 7;
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		//循环导入纠错题
		nNumTitle = 1;
		for ( iCnt=0; iCnt<pRandNum->Sum_JCT; iCnt++ )
		{
			//序号
			memset( cTempNum, '\0', (sizeof(char)*10) );
			sprintf( cTempNum, "%d.", nNumTitle++ );
			memcpy( cWDataBuf+nWDataLen, cTempNum, strlen(cTempNum) );
			nWDataLen += strlen(cTempNum);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, cTempNum, strlen(cTempNum) );
			nWDataAnswerlen += strlen(cTempNum);

			//过滤掉开始的连续的换行键
			TOOL_IgnoreChar( pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])], strlen(pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])]), 0x0A, STRING_BEGIN );

			//题目
			memcpy( cWDataBuf+nWDataLen, pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])], strlen(pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])]) );
			nWDataLen += strlen(pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])]);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])], strlen(pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])]);

			//答案
			//给试卷添加答案空格行
			for( iCntEmptyLine=0; iCntEmptyLine<SUM_JCT_EMPTY_LINE; iCntEmptyLine++ )
			{
				sprintf(cWDataBuf+nWDataLen, "\n" );
				nWDataLen += 1;
			}
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szJCTAnser[(pRandNum->JCT[iCnt])], strlen(pTleAsw->szJCTAnser[(pRandNum->JCT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szJCTAnser[(pRandNum->JCT[iCnt])]);
			ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		}
	}

	if ( 0!=pRandNum->Sum_BCT )
	{
		//导入随机编程题
		//打入编程类
		ADD_ENTER(cWDataBuf,nWDataLen);
		sprintf(cWDataBuf+nWDataLen, "%s",cItemTitle[nItemTitle]);
		nWDataLen += 3;
		sprintf(cWDataBuf+nWDataLen, "编程题\n");
		nWDataLen += 7;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "%s",cItemTitle[nItemTitle++]);
		nWDataAnswerlen += 3;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "编程题\n");
		nWDataAnswerlen += 7;
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		nNumTitle = 1;
		//循环导入编程题
		for ( iCnt=0; iCnt<pRandNum->Sum_BCT; iCnt++ )
		{
			//序号
			memset( cTempNum, '\0', (sizeof(char)*10) );
			sprintf( cTempNum, "%d.", nNumTitle++ );
			memcpy( cWDataBuf+nWDataLen, cTempNum, strlen(cTempNum) );
			nWDataLen += strlen(cTempNum);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, cTempNum, strlen(cTempNum) );
			nWDataAnswerlen += strlen(cTempNum);

			//过滤掉开始的连续的换行键
			TOOL_IgnoreChar( pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])], strlen(pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])]), 0x0A, STRING_BEGIN );

			//题目
			memcpy( cWDataBuf+nWDataLen, pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])], strlen(pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])]) );
			nWDataLen += strlen(pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])]);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])], strlen(pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])]);

			//答案
			//给试卷添加答案空格行
			for( iCntEmptyLine=0; iCntEmptyLine<SUM_BCT_EMPTY_LINE; iCntEmptyLine++ )
			{
				sprintf(cWDataBuf+nWDataLen, "\n" );
				nWDataLen += 1;
			}
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szBCTAnser[(pRandNum->BCT[iCnt])], strlen(pTleAsw->szBCTAnser[(pRandNum->BCT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szBCTAnser[(pRandNum->BCT[iCnt])]);
			ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		}
	}

	//试卷存储(生成考试和带答案两份试卷)
	//记录时间
	char cLocalTime[15] = {0};
    memset(cLocalTime,0x00,sizeof(cLocalTime));
	TOOL_GetLocalTime( cLocalTime );

	//生成试卷名
	char ExamFileName[MAX_PATH] = {0};
	char ExamFileAnswerName[MAX_PATH] = {0};
	memset( ExamFileName, '\0', sizeof(ExamFileName) );
	memset( ExamFileAnswerName, '\0', sizeof(ExamFileAnswerName) );

	//导入路径
	GetDlgItemText( IDC_EDIT6, ExamFileName, iLenOPFpath+1 );
	GetDlgItemText( IDC_EDIT6, ExamFileAnswerName, iLenOPFpath+1 );
	if ( 0 ==strlen(ExamFileName) )
	{
		AfxMessageBox(_T("CreateExam Path is NULL!"));
		free(cWDataBuf);
		free(cWDataAnswerBuf);
		return 2;
	}
	sprintf( ExamFileName+iLenOPFpath,"\\Exam%s%s",cLocalTime ,".txt" );
	sprintf( ExamFileAnswerName+iLenOPFpath,"\\Exam%s(Answer)%s",cLocalTime ,".txt" );

	//打开文件(不带答案)
	fp = fopen( ExamFileName, "a+" );
	if( fp == NULL ) 
	{
		free(cWDataBuf);
		free(cWDataAnswerBuf);
		return 0;
	}

	//写入文件
	if (fp != NULL) 
	{
		fseek( fp, 0, SEEK_END );
		fwrite( cWDataBuf, nWDataLen, 1, fp );
	}

	//写完文件，准备退出函数时要释放申请的缓存空间
	free(cWDataBuf);
	fclose(fp);
	fp = NULL;

	//打开文件(带答案)
	fp = fopen( ExamFileAnswerName, "a+" );
	if( fp == NULL ) 
	{
		free(cWDataAnswerBuf);
		return 0;
	}

	//写入文件
	if (fp != NULL) 
	{
		fseek( fp, 0, SEEK_END );
		fwrite( cWDataAnswerBuf, nWDataAnswerlen, 1, fp );
	}

	//写完文件，准备退出函数时要释放申请的缓存空间
	free(cWDataAnswerBuf);
	fclose(fp);
	fp = NULL;

	return 1;
}


void CSoftExamDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//验证用户设置题目数是否超过总数
	if ( 1==TOOL_CheckSetting() )
	{
		return;
	}

	//获取所有题目下标
	GetRandomNumber( &stRandNum );
	
	//生成试卷
	int res = CreateExam( &stRandNum, &stTitleAswer );
	if ( 0 == res )
	{
		AfxMessageBox(_T("Create exam fail!"));
	} 
	else if ( 1 == res )
	{
		AfxMessageBox(_T("Create exam success!"));
	}
}


void CSoftExamDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码 
	char szPath[MAX_PATH];     //存放选择的目录路径
	CString str;
	memset(szPath, '\0', sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "请选择需要打包的目录：";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if(lp && SHGetPathFromIDList(lp, szPath))
	{
		SetDlgItemText(IDC_EDIT6,szPath);
		iLenOPFpath = strlen( szPath );
	}
	else
	{
		AfxMessageBox("Browse Dir Error!");
	}
}




