
// DateCalculatorDlg.h : 头文件
//

#pragma once
#include "afxdtctl.h"


// CDateCalculatorDlg 对话框
class CDateCalculatorDlg : public CDialogEx
{
// 构造
public:
	CDateCalculatorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DATECALCULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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


int JudgeYear(int year);//判断平闰年
int JudgeMonth(int year,int month);//判断某月有多少天
int CalculuteDay(int startyear,int startmonth,int startday,int endyear,int endmonth,int endday);//计算两日期相距多少天
int CalculuteDayInOneYear(int year,int month,int day);//计算某一日期为该年的第几天
int JudgeWeek(int year,int month,int day);//判断某一日期星期几
void CalculuteEndDate(int startyear,int startmonth,int startday,int days,int* endyear,int* endmonth,int* endday);//根据相距时间计算结束时间