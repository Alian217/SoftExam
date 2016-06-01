
// SoftExamDlg.h : 头文件
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

//题目类型数量
#define SUM_TM    5

//试卷文件名
#define LENTH_FILENAME    30

//题目和答案的长度   取最长的那个
#define LENTH_TITLE        1024

//堆积验证二维数组行列数
#define ROW				10    //列数
#define COL				10    //行数

//试卷答案空行数量
#define SUM_JDT_EMPTY_LINE	 6    //简答题空行数
#define SUM_JCT_EMPTY_LINE	 6    //纠错题空行数
#define SUM_BCT_EMPTY_LINE	 10   //编程题空行数

//字符在字符串的位置
#define STRING_BEGIN	     -1   //字符串开始连续
#define STRING_MIDDLE	      0   //字符串中间连续
#define STRING_BACK  	      1   //字符串后端连续

//代码宏
#define ADD_ENTER( POINT, SETOFF )      { sprintf(POINT+SETOFF, "\n"); SETOFF += 1; }

//试卷内容数据缓冲区长度
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

// CSoftExamDlg 对话框
class CSoftExamDlg : public CDialogEx
{
// 构造
public:
	CSoftExamDlg(CWnd* pParent = NULL);	// 标准构造函数
	void GetRandomNumber( P_RANDNUM pRandNum );   //题目随机数获取
	int GetTMfromExamDB( P_TITLE_ASWER pTleAsw );   //将题库中题目导入到试卷中
	int TOOL_VerifyFlagFromFile( char v_pVerifyFlag[COL][ROW], char v_cInputFlag, char v_pAccumBuf[ROW+1], int *v_iLenAccumBuf );  //堆积二维数组验证函数，返回下标
	int CreateExam(  P_RANDNUM pRandNum, P_TITLE_ASWER pTleAsw );   //生成试卷
	void TOOL_GetLocalTime( char v_cLocalTime[15] );                //获取本地时间
	void TOOL_IgnoreChar( char *pSrc, int iLenSrc, char IgnoreChar, char cPosition );   //cPosition -1—最初连续(完成) 0—中间连续 1—最后连续的
	int TOOL_CheckSetting(void);                //确认题目设置数量是否超过题目总数量

	int  iLenOPFpath;
	TITLE_ASWER stTitleAswer;	//用于存储提取题库的题目的缓冲区
	RANDNUM stRandNum;          //出题随机数组

// 对话框数据
	enum { IDD = IDD_SOFTEXAM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
