
// SoftExamDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSoftExamDlg �Ի���




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


// CSoftExamDlg ��Ϣ�������

BOOL CSoftExamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//���������ܴ����������
	ASSERT( SUM_XZT<=MAX_XZT && SUM_TKT<=MAX_TKT && SUM_JDT<=MAX_JDT && SUM_JCT<=MAX_JCT && SUM_BCT<=MAX_BCT );
	//��ǳ��Ȳ��ܴ��ڱ�Ƕѻ���֤�г���
	ASSERT( strlen(pStartFlag)<=ROW && strlen(pEndFlag)<=ROW && strlen(pANSWERFlag)<=ROW );
	iLenOPFpath = 0;

	memset( &stRandNum, 0x00, sizeof(RANDNUM) );
	memset( &stTitleAswer, '\0', sizeof(TITLE_ASWER) );

	//������Ŀ�����ݵ��ڴ���
	if ( 0 == GetTMfromExamDB( &stTitleAswer ) )
	{
		AfxMessageBox(_T("Get title from DB fail!"));
		exit(0);
	}

	//������Ŀ������Ĭ����Ŀ����
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
	//���ļ��л�ȡ������Ŀ����
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSoftExamDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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

	//��ͬ�����µ������
	for ( iSumTM=0; iSumTM<SUM_TM; iSumTM++ )
	{
		//���ø�������Ŀ����
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
		//��ȡ�����
		while(iSumGet<Sum)
		{
			//�����������
			TmCom[iSumGet] = rand()%Max;
			//�жϻ�ȡ��������ظ���
			for( iCnt=0; iCnt<iSumGet; iCnt++ )
			{
				//�ظ������������ȡ
				if( TmCom[iCnt] == TmCom[iSumGet] )
				{
					break;
				}
			}
			//ȡ���������֮ǰ�Ķ����ظ�
			if( iSumGet == iCnt )
			{
				iSumGet++;
			}
		}
		//��ȡ��һ��������Ŀ������������ʱ��¼����
		iSumGet = iCnt = 0;
	}
}


//�ѻ���֤���ļ��ж�ȡ������������֤�ѻ��������һ���±�
int CSoftExamDlg::TOOL_VerifyFlagFromFile( char v_pVerifyFlag[COL][ROW], char v_cInputFlag, char v_pAccumBuf[ROW+1], int *v_iLenAccumBuf )
{
	int iRes = -1;
	int iCnt = 0;

	//�ѻ�������������
	v_pAccumBuf[(*v_iLenAccumBuf)++] = v_cInputFlag;

	//�Ͷѻ���ά�������ݽ����ж�
	for( iCnt=0; iCnt<COL; iCnt++ )
	{
		if( 0 == memcmp( v_pVerifyFlag[iCnt], v_pAccumBuf, *v_iLenAccumBuf ) )
		{
			//���ĳһ����ȫƥ�䣬ֱ�������������±�
			if ( strlen(v_pVerifyFlag[iCnt]) == *v_iLenAccumBuf )
			{
				iRes = iCnt;
				memset( v_pAccumBuf, '\0', sizeof(char)*(ROW+1) );
				*v_iLenAccumBuf = 0;
			}
			break;
		}
	}
	//���û�дӶѻ���ά�������ҵ���Ӧ��ǣ������ѻ�����
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
	int  iLenGetData = 0;    //-1û�п�ʼ��ȡ 0��ȡ��<start> 1��ȡ��<END> 2��ȡ��<ANSWER>
	char pGetDateBuf[LENTH_TITLE+1] = {0};
	char pVerifyFlag[COL][ROW] = {0};
	char pAccumBuf[ROW+1] = {0};
	int  iLenAccumBuf = 0;
	char *TitleType = NULL;
	int  iFlagTurn = 2;    //��ת��־λ

	//������֤�ѻ���ά��������
	memset( pVerifyFlag, '\0', sizeof(char)*COL*ROW );
	memcpy( &pVerifyFlag[0], pStartFlag, strlen(pStartFlag) );
	memcpy( &pVerifyFlag[1], pEndFlag,   strlen(pEndFlag)   );
	memcpy( &pVerifyFlag[2], pANSWERFlag,strlen(pANSWERFlag) );

	//�����ʱ���漰����
	memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
	memset( pAccumBuf, '\0', sizeof(char)*(ROW+1) );
	iLenAccumBuf = 0; iFlagTurn = 2; iFlagFromFile = -1;

	//1.��ѡ�����,���ж�ȡ
	TitleType = cXZTFileName;
	if ( 0 == access(TitleType,0) )
	{
		fp = fopen( TitleType, "a+" );
		if( fp == NULL ) 
		{
			AfxMessageBox(_T("�޷���ѡ������ļ�"));
			return 0;
		}
		//ѭ����ȡ�ļ�
		while( fread( &cGetChar, 1, 1, fp ) )
		{
			//��ȡ��Ŀ��־λ <START>����0 <END>����1 <ANSWER>����2
			iFlagFromFile = TOOL_VerifyFlagFromFile( pVerifyFlag, cGetChar, pAccumBuf, &iLenAccumBuf );

			//ֻ���ҵ���Ӧ���λ��ʱ��ʼȡ����
			if ( 0 == iFlagTurn || 1 == iFlagTurn )
			{
				pGetDateBuf[iLenGetData++] = cGetChar;
			}
			//״̬����
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
				// ����Ŀ�������������Ŀ�������������ޣ����ٶ�ȡ
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
		AfxMessageBox(_T("δ�ҵ�ѡ������ļ�"));
		return 0;
	}
	
	//�����ʱ���漰����
	memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
	memset( pAccumBuf, '\0', sizeof(char)*(ROW+1) );
	iLenAccumBuf = 0; iFlagTurn = 2; iFlagFromFile = -1;

	//2.��������,���ж�ȡ
	TitleType = cTKTFileName;
	if ( 0 == access(TitleType,0) )
	{
		fp = fopen( TitleType, "a+" );
		if( fp == NULL ) 
		{
			AfxMessageBox(_T("�޷����������ļ�"));
			return 0;
		}
		//ѭ����ȡ�ļ�
		while( fread( &cGetChar, 1, 1, fp ) )
		{
			//��ȡ��Ŀ��־λ <START>����0 <END>����1 <ANSWER>����2
			iFlagFromFile = TOOL_VerifyFlagFromFile( pVerifyFlag, cGetChar, pAccumBuf, &iLenAccumBuf );

			//ֻ���ҵ���Ӧ���λ��ʱ��ʼȡ����
			if ( 0 == iFlagTurn || 1 == iFlagTurn )
			{
				pGetDateBuf[iLenGetData++] = cGetChar;
			}
			//״̬����
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
				// ����Ŀ�������������Ŀ�������������ޣ����ٶ�ȡ
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
		AfxMessageBox(_T("δ�ҵ��������ļ�"));
		return 0;
	}

	//�����ʱ���漰����
	memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
	memset( pAccumBuf, '\0', sizeof(char)*(ROW+1) );
	iLenAccumBuf = 0; iFlagTurn = 2; iFlagFromFile = -1;

	//3.�򿪼�����,���ж�ȡ
	TitleType = cJDTFileName;
	if ( 0 == access(TitleType,0) )
	{
		fp = fopen( TitleType, "a+" );
		if( fp == NULL ) 
		{
			AfxMessageBox(_T("�޷��򿪼������ļ�"));
			return 0;
		}
		//ѭ����ȡ�ļ�
		while( fread( &cGetChar, 1, 1, fp ) )
		{
			//��ȡ��Ŀ��־λ <START>����0 <END>����1 <ANSWER>����2
			iFlagFromFile = TOOL_VerifyFlagFromFile( pVerifyFlag, cGetChar, pAccumBuf, &iLenAccumBuf );

			//ֻ���ҵ���Ӧ���λ��ʱ��ʼȡ����
			if ( 0 == iFlagTurn || 1 == iFlagTurn )
			{
				pGetDateBuf[iLenGetData++] = cGetChar;
			}
			//״̬����
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
				// ����Ŀ�������������Ŀ�������������ޣ����ٶ�ȡ
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
		AfxMessageBox(_T("δ�ҵ��������ļ�"));
		return 0;
	}

	//�����ʱ���漰����
	memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
	memset( pAccumBuf, '\0', sizeof(char)*(ROW+1) );
	iLenAccumBuf = 0; iFlagTurn = 2; iFlagFromFile = -1;

	//4.�򿪼�����,���ж�ȡ
	TitleType = cJCTFileName;
	if ( 0 == access(TitleType,0) )
	{
		fp = fopen( TitleType, "a+" );
		if( fp == NULL ) 
		{
			AfxMessageBox(_T("�޷��򿪾�������ļ�"));
			return 0;
		}
		//ѭ����ȡ�ļ�
		while( fread( &cGetChar, 1, 1, fp ) )
		{
			//��ȡ��Ŀ��־λ <START>����0 <END>����1 <ANSWER>����2
			iFlagFromFile = TOOL_VerifyFlagFromFile( pVerifyFlag, cGetChar, pAccumBuf, &iLenAccumBuf );

			//ֻ���ҵ���Ӧ���λ��ʱ��ʼȡ����
			if ( 0 == iFlagTurn || 1 == iFlagTurn )
			{
				pGetDateBuf[iLenGetData++] = cGetChar;
			}
			//״̬����
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
				// ����Ŀ�������������Ŀ�������������ޣ����ٶ�ȡ
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
		AfxMessageBox(_T("δ�ҵ���������ļ�"));
		return 0;
	}

	//�����ʱ���漰����
	memset( pGetDateBuf, '\0', sizeof(char)*(LENTH_TITLE+1) );
	memset( pAccumBuf, '\0', sizeof(char)*(ROW+1) );
	iLenAccumBuf = 0; iFlagTurn = 2; iFlagFromFile = -1;

	//5.�򿪱�����,���ж�ȡ
	TitleType = cBCTFileName;
	if ( 0 == access(TitleType,0) )
	{
		fp = fopen( TitleType, "a+" );
		if( fp == NULL ) 
		{
			AfxMessageBox(_T("�޷��򿪱������ļ�"));
			return 0;
		}
		//ѭ����ȡ�ļ�
		while( fread( &cGetChar, 1, 1, fp ) )
		{
			//��ȡ��Ŀ��־λ <START>����0 <END>����1 <ANSWER>����2
			iFlagFromFile = TOOL_VerifyFlagFromFile( pVerifyFlag, cGetChar, pAccumBuf, &iLenAccumBuf );

			//ֻ���ҵ���Ӧ���λ��ʱ��ʼȡ����
			if ( 0 == iFlagTurn || 1 == iFlagTurn )
			{
				pGetDateBuf[iLenGetData++] = cGetChar;
			}
			//״̬����
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
				// ����Ŀ�������������Ŀ�������������ޣ����ٶ�ȡ
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
		AfxMessageBox(_T("δ�ҵ��������ļ�"));
		return 0;
	}
	return 1;
}


//��ȡϵͳ��ǰʱ��
void CSoftExamDlg::TOOL_GetLocalTime( char v_cLocalTime[15] )
{
	int year, month, day, hour, min, sec;
	struct tm *timeinfo;			//����ʱ��ṹ�� 
	time_t nowtime;  
	time( &nowtime );				//��ȡʱ��   
	timeinfo = localtime( &nowtime );	//ת��Ϊ����ʱ��  
	year = timeinfo->tm_year + 1900;	//��1900�꿪ʼ����������+1900 
	month = timeinfo->tm_mon + 1;		//��0��ʼ����������+1 
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

	//����ԭ���ݵ���������
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
		
		//��Ҫ���������ԭ�ַ�����û�оͷ���
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
	char SumTitle[20] = {0};  //��ȡ������Ŀ�༭���е�����
	char OverMax[SUM_TM][LENTH_FILENAME] = {
												"ѡ���� �� ����!\n",
												"����� �� ����!\n",
												"����� �� ����!\n",
												"������ �� ����!\n",
												"����� �� ����!\n"
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
	//����ռ䣬ʹ����ɺ��ͷŵ�
	char cTempNum[10] = {0};
	char cItemTitle[SUM_TM][LENTH_FILENAME] = {
													"һ.",
													"��.",
													"��.",
													"��.",
													"��."
												};
	int  nItemTitle = 0;
	int  nTempLen = 0;
	int  nWDataLen = 0, nNumTitle = 0;
	int  nWDataAnswerlen = 0, nNumAnswerTitle = 0;
	char *cWDataBuf = (char *)malloc(LENTH_EXAM*sizeof(char));         //�������Ծ���
	char *cWDataAnswerBuf = (char *)malloc(LENTH_EXAM*sizeof(char));  //�����Ծ���
	memset( cWDataBuf, '\0', sizeof(char)*LENTH_EXAM );
	memset( cWDataAnswerBuf, '\0', sizeof(char)*LENTH_EXAM );

	//�������ѡ����
	//������Ŀ��
	if ( 0!=pRandNum->Sum_XZT )
	{
		sprintf(cWDataBuf+nWDataLen, "%s",cItemTitle[nItemTitle]);
		nWDataLen += 3;
		sprintf(cWDataBuf+nWDataLen, "ѡ����\n");
		nWDataLen += 7;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "%s",cItemTitle[nItemTitle++]);
		nWDataAnswerlen += 3;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "ѡ����\n");
		nWDataAnswerlen += 7;
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		//ѭ��������Ŀ
		nNumTitle = 1;
		for ( iCnt=0; iCnt<pRandNum->Sum_XZT; iCnt++ )
		{
			//���
			memset( cTempNum, '\0', (sizeof(char)*10) );
			sprintf( cTempNum, "%d.", nNumTitle++ );
			memcpy( cWDataBuf+nWDataLen, cTempNum, strlen(cTempNum) );
			nWDataLen += strlen(cTempNum);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, cTempNum, strlen(cTempNum) );
			nWDataAnswerlen += strlen(cTempNum);

			//���˵���ʼ�������Ļ��м�
			TOOL_IgnoreChar( pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])], strlen(pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])]), 0x0A, STRING_BEGIN );

			//��Ŀ
			memcpy( cWDataBuf+nWDataLen, pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])], strlen(pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])]) );
			nWDataLen += strlen(pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])]);
			ADD_ENTER(cWDataBuf,nWDataLen);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])], strlen(pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szXZTTitle[(pRandNum->XZT[iCnt])]);

			//��
			memcpy( cWDataAnswerBuf+nWDataAnswerlen-1, pTleAsw->szXZTAnser[(pRandNum->XZT[iCnt])], strlen(pTleAsw->szXZTAnser[(pRandNum->XZT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szXZTAnser[(pRandNum->XZT[iCnt])]);
			ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		}
	}

	if ( 0!=pRandNum->Sum_TKT )
	{
		//������������
		//������Ŀ��
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);		
		sprintf(cWDataBuf+nWDataLen, "%s",cItemTitle[nItemTitle]);
		nWDataLen += 3;
		sprintf(cWDataBuf+nWDataLen, "�����\n");
		nWDataLen += 7;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "%s",cItemTitle[nItemTitle++]);
		nWDataAnswerlen += 3;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "�����\n");
		nWDataAnswerlen += 7;
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		//ѭ�����������
		nNumTitle = 1;
		for ( iCnt=0; iCnt<pRandNum->Sum_TKT; iCnt++ )
		{
			//���
			memset( cTempNum, '\0', (sizeof(char)*10) );
			sprintf( cTempNum, "%d.", nNumTitle++ );
			memcpy( cWDataBuf+nWDataLen, cTempNum, strlen(cTempNum) );
			nWDataLen += strlen(cTempNum);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, cTempNum, strlen(cTempNum) );
			nWDataAnswerlen += strlen(cTempNum);

			//���˵���ʼ�������Ļ��м�
			TOOL_IgnoreChar( pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])], strlen(pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])]), 0x0A, STRING_BEGIN );

			//��Ŀ
			memcpy( cWDataBuf+nWDataLen, pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])], strlen(pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])]) );
			nWDataLen += strlen(pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])]);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])], strlen(pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szTKTTitle[(pRandNum->TKT[iCnt])]);
		
			//��
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szTKTAnser[(pRandNum->TKT[iCnt])], strlen(pTleAsw->szTKTAnser[(pRandNum->TKT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szTKTAnser[(pRandNum->TKT[iCnt])]);
		}
	}

	if ( 0!=pRandNum->Sum_JDT )
	{
		//������������
		//��������
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		sprintf(cWDataBuf+nWDataLen, "%s",cItemTitle[nItemTitle]);
		nWDataLen += 3;
		sprintf(cWDataBuf+nWDataLen, "�����\n");
		nWDataLen += 7;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "%s",cItemTitle[nItemTitle++]);
		nWDataAnswerlen += 3;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "�����\n");
		nWDataAnswerlen += 7;
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		//ѭ����������
		nNumTitle = 1;
		for ( iCnt=0; iCnt<pRandNum->Sum_JDT; iCnt++ )
		{
			//���
			memset( cTempNum, '\0', (sizeof(char)*10) );
			sprintf( cTempNum, "%d.", nNumTitle++ );
			memcpy( cWDataBuf+nWDataLen, cTempNum, strlen(cTempNum) );
			nWDataLen += strlen(cTempNum);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, cTempNum, strlen(cTempNum) );
			nWDataAnswerlen += strlen(cTempNum);

			//���˵���ʼ�������Ļ��м�
			TOOL_IgnoreChar( pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])], strlen(pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])]), 0x0A, STRING_BEGIN );

			//��Ŀ
			memcpy( cWDataBuf+nWDataLen, pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])], strlen(pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])]) );
			nWDataLen += strlen(pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])]);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])], strlen(pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szJDTTitle[(pRandNum->JDT[iCnt])]);

			//��
			//���Ծ���Ӵ𰸿ո���
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
		//�������������
		//���������
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		sprintf(cWDataBuf+nWDataLen, "%s",cItemTitle[nItemTitle]);
		nWDataLen += 3;
		sprintf(cWDataBuf+nWDataLen, "������\n");
		nWDataLen += 7;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "%s",cItemTitle[nItemTitle++]);
		nWDataAnswerlen += 3;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "������\n");
		nWDataAnswerlen += 7;
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		//ѭ�����������
		nNumTitle = 1;
		for ( iCnt=0; iCnt<pRandNum->Sum_JCT; iCnt++ )
		{
			//���
			memset( cTempNum, '\0', (sizeof(char)*10) );
			sprintf( cTempNum, "%d.", nNumTitle++ );
			memcpy( cWDataBuf+nWDataLen, cTempNum, strlen(cTempNum) );
			nWDataLen += strlen(cTempNum);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, cTempNum, strlen(cTempNum) );
			nWDataAnswerlen += strlen(cTempNum);

			//���˵���ʼ�������Ļ��м�
			TOOL_IgnoreChar( pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])], strlen(pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])]), 0x0A, STRING_BEGIN );

			//��Ŀ
			memcpy( cWDataBuf+nWDataLen, pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])], strlen(pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])]) );
			nWDataLen += strlen(pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])]);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])], strlen(pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szJCTTitle[(pRandNum->JCT[iCnt])]);

			//��
			//���Ծ���Ӵ𰸿ո���
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
		//������������
		//��������
		ADD_ENTER(cWDataBuf,nWDataLen);
		sprintf(cWDataBuf+nWDataLen, "%s",cItemTitle[nItemTitle]);
		nWDataLen += 3;
		sprintf(cWDataBuf+nWDataLen, "�����\n");
		nWDataLen += 7;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "%s",cItemTitle[nItemTitle++]);
		nWDataAnswerlen += 3;
		sprintf(cWDataAnswerBuf+nWDataAnswerlen, "�����\n");
		nWDataAnswerlen += 7;
		ADD_ENTER(cWDataBuf,nWDataLen);
		ADD_ENTER(cWDataAnswerBuf,nWDataAnswerlen);
		nNumTitle = 1;
		//ѭ����������
		for ( iCnt=0; iCnt<pRandNum->Sum_BCT; iCnt++ )
		{
			//���
			memset( cTempNum, '\0', (sizeof(char)*10) );
			sprintf( cTempNum, "%d.", nNumTitle++ );
			memcpy( cWDataBuf+nWDataLen, cTempNum, strlen(cTempNum) );
			nWDataLen += strlen(cTempNum);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, cTempNum, strlen(cTempNum) );
			nWDataAnswerlen += strlen(cTempNum);

			//���˵���ʼ�������Ļ��м�
			TOOL_IgnoreChar( pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])], strlen(pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])]), 0x0A, STRING_BEGIN );

			//��Ŀ
			memcpy( cWDataBuf+nWDataLen, pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])], strlen(pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])]) );
			nWDataLen += strlen(pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])]);
			memcpy( cWDataAnswerBuf+nWDataAnswerlen, pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])], strlen(pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])]) );
			nWDataAnswerlen += strlen(pTleAsw->szBCTTitle[(pRandNum->BCT[iCnt])]);

			//��
			//���Ծ���Ӵ𰸿ո���
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

	//�Ծ�洢(���ɿ��Ժʹ��������Ծ�)
	//��¼ʱ��
	char cLocalTime[15] = {0};
    memset(cLocalTime,0x00,sizeof(cLocalTime));
	TOOL_GetLocalTime( cLocalTime );

	//�����Ծ���
	char ExamFileName[MAX_PATH] = {0};
	char ExamFileAnswerName[MAX_PATH] = {0};
	memset( ExamFileName, '\0', sizeof(ExamFileName) );
	memset( ExamFileAnswerName, '\0', sizeof(ExamFileAnswerName) );

	//����·��
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

	//���ļ�(������)
	fp = fopen( ExamFileName, "a+" );
	if( fp == NULL ) 
	{
		free(cWDataBuf);
		free(cWDataAnswerBuf);
		return 0;
	}

	//д���ļ�
	if (fp != NULL) 
	{
		fseek( fp, 0, SEEK_END );
		fwrite( cWDataBuf, nWDataLen, 1, fp );
	}

	//д���ļ���׼���˳�����ʱҪ�ͷ�����Ļ���ռ�
	free(cWDataBuf);
	fclose(fp);
	fp = NULL;

	//���ļ�(����)
	fp = fopen( ExamFileAnswerName, "a+" );
	if( fp == NULL ) 
	{
		free(cWDataAnswerBuf);
		return 0;
	}

	//д���ļ�
	if (fp != NULL) 
	{
		fseek( fp, 0, SEEK_END );
		fwrite( cWDataAnswerBuf, nWDataAnswerlen, 1, fp );
	}

	//д���ļ���׼���˳�����ʱҪ�ͷ�����Ļ���ռ�
	free(cWDataAnswerBuf);
	fclose(fp);
	fp = NULL;

	return 1;
}


void CSoftExamDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//��֤�û�������Ŀ���Ƿ񳬹�����
	if ( 1==TOOL_CheckSetting() )
	{
		return;
	}

	//��ȡ������Ŀ�±�
	GetRandomNumber( &stRandNum );
	
	//�����Ծ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ���������� 
	char szPath[MAX_PATH];     //���ѡ���Ŀ¼·��
	CString str;
	memset(szPath, '\0', sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "��ѡ����Ҫ�����Ŀ¼��";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//����ѡ��Ŀ¼�Ի���
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




