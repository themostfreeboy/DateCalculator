
// DateCalculator.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDateCalculatorApp:
// �йش����ʵ�֣������ DateCalculator.cpp
//

class CDateCalculatorApp : public CWinApp
{
public:
	CDateCalculatorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDateCalculatorApp theApp;