
// SoftExam.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSoftExamApp:
// �йش����ʵ�֣������ SoftExam.cpp
//

class CSoftExamApp : public CWinApp
{
public:
	CSoftExamApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSoftExamApp theApp;