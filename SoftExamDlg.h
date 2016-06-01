
// SoftExamDlg.h : ͷ�ļ�
//

#pragma once

#define SUM_XZT   10
#define SUM_TKT   5
#define SUM_JDT   3
#define SUM_JCT   2
#define SUM_BCT   2
#define MAX_XZT   200
#define MAX_TKT   150
#define MAX_JDT   50
#define MAX_JCT   30
#define MAX_BCT   20

//��Ŀ��������
#define SUM_TM    5

//�Ծ��ļ���
#define LENTH_FILENAME    30

//��Ŀ�ʹ𰸵ĳ���   ȡ����Ǹ�
#define LENTH_TITLE        1024

//�ѻ���֤��ά����������
#define ROW				10    //����
#define COL				10    //����

//�Ծ�𰸿�������
#define SUM_JDT_EMPTY_LINE	 6    //����������
#define SUM_JCT_EMPTY_LINE	 6    //�����������
#define SUM_BCT_EMPTY_LINE	 10   //����������

//�ַ����ַ�����λ��
#define STRING_BEGIN	     -1   //�ַ�����ʼ����
#define STRING_MIDDLE	      0   //�ַ����м�����
#define STRING_BACK  	      1   //�ַ����������

//�����
#define ADD_ENTER( POINT, SETOFF )      { sprintf(POINT+SETOFF, "\n"); SETOFF += 1; }

//�Ծ��������ݻ���������
#define LENTH_EXAM      1024*100

typedef struct  
{
	int XZT[MAX_XZT];  int Sum_XZT;
	int TKT[MAX_TKT];  int Sum_TKT;
	int JDT[MAX_JDT];  int Sum_JDT;
	int JCT[MAX_JCT];  int Sum_JCT;
	int BCT[MAX_BCT];  int Sum_BCT;
}RANDNUM,*P_RANDNUM;

typedef struct  
{
	char szXZTTitle[MAX_XZT][LENTH_TITLE];
	char szXZTAnser[MAX_XZT][LENTH_TITLE];
	int  iSumTleXzt;   int  iSumAnsXzt;
	char szTKTTitle[MAX_TKT][LENTH_TITLE];
	char szTKTAnser[MAX_TKT][LENTH_TITLE];
	int  iSumTleTkt;   int  iSumAnsTkt;
	char szJDTTitle[MAX_JDT][LENTH_TITLE];
	char szJDTAnser[MAX_JDT][LENTH_TITLE];
	int  iSumTleJdt;   int  iSumAnsJdt;
	char szJCTTitle[MAX_JCT][LENTH_TITLE];
	char szJCTAnser[MAX_JCT][LENTH_TITLE];
	int  iSumTleJct;   int  iSumAnsJct;
	char szBCTTitle[MAX_BCT][LENTH_TITLE];
	char szBCTAnser[MAX_BCT][LENTH_TITLE];
	int  iSumTleBct;   int  iSumAnsBct;
}TITLE_ASWER,*P_TITLE_ASWER;

// CSoftExamDlg �Ի���
class CSoftExamDlg : public CDialogEx
{
// ����
public:
	CSoftExamDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void GetRandomNumber( P_RANDNUM pRandNum );   //��Ŀ�������ȡ
	int GetTMfromExamDB( P_TITLE_ASWER pTleAsw );   //���������Ŀ���뵽�Ծ���
	int TOOL_VerifyFlagFromFile( char v_pVerifyFlag[COL][ROW], char v_cInputFlag, char v_pAccumBuf[ROW+1], int *v_iLenAccumBuf );  //�ѻ���ά������֤�����������±�
	int CreateExam(  P_RANDNUM pRandNum, P_TITLE_ASWER pTleAsw );   //�����Ծ�
	void TOOL_GetLocalTime( char v_cLocalTime[15] );                //��ȡ����ʱ��
	void TOOL_IgnoreChar( char *pSrc, int iLenSrc, char IgnoreChar, char cPosition );   //cPosition -1���������(���) 0���м����� 1�����������
	int TOOL_CheckSetting(void);                //ȷ����Ŀ���������Ƿ񳬹���Ŀ������

	int  iLenOPFpath;
	TITLE_ASWER stTitleAswer;	//���ڴ洢��ȡ������Ŀ�Ļ�����
	RANDNUM stRandNum;          //�����������

// �Ի�������
	enum { IDD = IDD_SOFTEXAM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
