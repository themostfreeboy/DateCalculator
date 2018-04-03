
// DateCalculatorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxdtctl.h"


// CDateCalculatorDlg �Ի���
class CDateCalculatorDlg : public CDialogEx
{
// ����
public:
	CDateCalculatorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DATECALCULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBsave();
	afx_msg void OnBnClickedBchoosefile();
	afx_msg void OnBnClickedBreadfile();
	afx_msg void OnBnClickedBcalculate();
	afx_msg void OnBnClickedBexit();
	CString EditChoosePath;
	afx_msg void OnEnChangeEfilepath();
	int StartDateChoice;
	int EndDateChoice;
	CString EditApartTime;
	afx_msg void OnEnChangeEaparttime();
	CMonthCalCtrl CMonth_StartDate;
	CMonthCalCtrl CMonth_EndDate;
	afx_msg void OnBnClickedRstartdate();
	afx_msg void OnBnClickedRenddate();
	int CalculatorChoice;
	afx_msg void OnBnClickedRcalculatorchoice();
};


int JudgeYear(int year);//�ж�ƽ����
int JudgeMonth(int year,int month);//�ж�ĳ���ж�����
int CalculuteDay(int startyear,int startmonth,int startday,int endyear,int endmonth,int endday);//������������������
int CalculuteDayInOneYear(int year,int month,int day);//����ĳһ����Ϊ����ĵڼ���
int JudgeWeek(int year,int month,int day);//�ж�ĳһ�������ڼ�
void CalculuteEndDate(int startyear,int startmonth,int startday,int days,int* endyear,int* endmonth,int* endday);//�������ʱ��������ʱ��