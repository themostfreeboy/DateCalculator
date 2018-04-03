
// DateCalculatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DateCalculator.h"
#include "DateCalculatorDlg.h"
#include "afxdialogex.h"

#include "MyMFC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDateCalculatorDlg 对话框




CDateCalculatorDlg::CDateCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDateCalculatorDlg::IDD, pParent)
	, EditChoosePath(_T(""))
	, StartDateChoice(0)
	, EndDateChoice(0)
	, EditApartTime(_T("0"))
	, CalculatorChoice(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDateCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EFILEPATH, EditChoosePath);
	DDX_Radio(pDX, IDC_RSTARTDATE_0, StartDateChoice);
	DDX_Radio(pDX, IDC_RENDDATE_0, EndDateChoice);
	DDX_Text(pDX, IDC_EAPARTTIME, EditApartTime);
	DDX_Control(pDX, IDC_MSTARTDATE, CMonth_StartDate);
	DDX_Control(pDX, IDC_MENDDATE, CMonth_EndDate);
	DDX_Radio(pDX, IDC_RCALCULATORCHOICE_0, CalculatorChoice);
}

BEGIN_MESSAGE_MAP(CDateCalculatorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BSAVE, &CDateCalculatorDlg::OnBnClickedBsave)
	ON_BN_CLICKED(IDC_BCHOOSEFILE, &CDateCalculatorDlg::OnBnClickedBchoosefile)
	ON_BN_CLICKED(IDC_BREADFILE, &CDateCalculatorDlg::OnBnClickedBreadfile)
	ON_BN_CLICKED(IDC_BCALCULATE, &CDateCalculatorDlg::OnBnClickedBcalculate)
	ON_BN_CLICKED(IDC_BEXIT, &CDateCalculatorDlg::OnBnClickedBexit)
	ON_EN_CHANGE(IDC_EFILEPATH, &CDateCalculatorDlg::OnEnChangeEfilepath)
	ON_EN_CHANGE(IDC_EAPARTTIME, &CDateCalculatorDlg::OnEnChangeEaparttime)
	ON_BN_CLICKED(IDC_RSTARTDATE_0, &CDateCalculatorDlg::OnBnClickedRstartdate)
	ON_BN_CLICKED(IDC_RSTARTDATE_1, &CDateCalculatorDlg::OnBnClickedRstartdate)
	ON_BN_CLICKED(IDC_RENDDATE_0, &CDateCalculatorDlg::OnBnClickedRenddate)
	ON_BN_CLICKED(IDC_RENDDATE_1, &CDateCalculatorDlg::OnBnClickedRenddate)
	ON_BN_CLICKED(IDC_RCALCULATORCHOICE_0, &CDateCalculatorDlg::OnBnClickedRcalculatorchoice)
	ON_BN_CLICKED(IDC_RCALCULATORCHOICE_1, &CDateCalculatorDlg::OnBnClickedRcalculatorchoice)
END_MESSAGE_MAP()


// CDateCalculatorDlg 消息处理程序

BOOL CDateCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CEdit *edit = (CEdit*)GetDlgItem(IDC_SFILEPATH);
	edit->ShowWindow(FALSE);//文件路径提示不可见

	edit = (CEdit*)GetDlgItem(IDC_EFILEPATH);
	edit->ShowWindow(FALSE);//文件路径编辑框不可见

	edit = (CEdit*)GetDlgItem(IDC_BCHOOSEFILE);
	edit->ShowWindow(FALSE);//选择文件按钮不可见

	edit = (CEdit*)GetDlgItem(IDC_BREADFILE);
	edit->ShowWindow(FALSE);//读取文件按钮不可见

	edit = (CEdit*)GetDlgItem(IDC_EAPARTTIME);
	edit->SetReadOnly(TRUE);//相距时间编辑框只读

	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);//获取系统时间

	CMonth_StartDate.EnableWindow(TRUE);//启用开始日期日历控件
	CMonth_StartDate.SetCurrentView(0);//设置开始日期日历视图为月视图
	CMonth_StartDate.SetCurSel(&SystemTime);//设置开始日期日历控件上的日期为当前日期

	CMonth_EndDate.EnableWindow(TRUE);//启用结束日期日历控件
	CMonth_EndDate.SetCurrentView(0);//设置结束日期日历视图为月视图
	CMonth_EndDate.SetCurSel(&SystemTime);//设置结束日期日历控件上的日期为当前日期
	CMonth_EndDate.EnableWindow(FALSE);//禁用结束日期日历控件

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDateCalculatorDlg::OnPaint()
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
HCURSOR CDateCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDateCalculatorDlg::OnBnClickedBsave()
{
	// TODO: 在此添加控件通知处理程序代码
	SYSTEMTIME SystemTime;
	CMonth_StartDate.GetCurSel(&SystemTime);//读取开始日期日历控件上选择的日期

	errno_t err_write;
	FILE *fp_write = NULL;
	err_write = fopen_s(&fp_write, "D:\\DateSave.txt", "wb");
	if (err_write != 0)//文件打开失败
	{
		AfxMessageBox(_T("保存失败"),MB_OK,NULL);
		return;
	}

	fprintf(fp_write,"%04d年%02d月%02d日星期",SystemTime.wYear,SystemTime.wMonth,SystemTime.wDay);
	int week=JudgeWeek(SystemTime.wYear,SystemTime.wMonth,SystemTime.wDay);
	switch(week)
	{
	    case 1:{fprintf(fp_write,"一");break;}
	    case 2:{fprintf(fp_write,"二");break;}
	    case 3:{fprintf(fp_write,"三");break;}
		case 4:{fprintf(fp_write,"四");break;}
		case 5:{fprintf(fp_write,"五");break;}
		case 6:{fprintf(fp_write,"六");break;}
		case 7:{fprintf(fp_write,"日");break;}
		default:{break;}//数据有误
	}
	
    fclose(fp_write);
	AfxMessageBox(_T("保存成功，当前开始日期已经保存到D:\\DateSave.txt中"),MB_OK,NULL);
}


void CDateCalculatorDlg::OnBnClickedBchoosefile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString szPath = _T("");

	//CFileDialog::CFileDialog( BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL, DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL);
    //参数意义如下：
    //bOpenFileDialog：为TRUE则显示打开对话框，为FALSE则显示保存对话文件对话框。 
    //lpszDefExt：指定默认的文件扩展名。 
    //lpszFileName：指定默认的文件名。 
    //dwFlags：指明一些特定风格。 
    //lpszFilter：是最重要的一个参数，它指明可供选择的文件类型和相应的扩展名。

    CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||"), NULL);

    if (dlgFile.DoModal())
    {
        szPath = dlgFile.GetPathName();
    }
	if(!szPath.IsEmpty())
	{
	    SetDlgItemText(IDC_EFILEPATH,szPath);
	}
	else
	{
		//SetDlgItemText(IDC_EFILEPATH,_T(""));
        //AfxMessageBox(_T("无效的文件，请重新选择"),MB_OK,NULL);
	}
}


void CDateCalculatorDlg::OnBnClickedBreadfile()
{
	// TODO: 在此添加控件通知处理程序代码
	if(EditChoosePath.IsEmpty())
	{
		AfxMessageBox(_T("文件路径不能为空"),MB_OK,NULL);
		return;
	}

	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, MyCStringToConstChar(EditChoosePath), "rb");
	if (err_read != 0)//文件打开失败
	{
		AfxMessageBox(_T("文件读取失败"),MB_OK,NULL);
		return;
	}

	char tempchar=0;
	char tempchar_date[8];
	int year=0,month=0,day=0;
	int i=0;

	while(fscanf(fp_read,"%c",&tempchar)!=EOF)
	{
		if(tempchar>='0'&&tempchar<='9')
		{
			tempchar_date[i++]=tempchar;
			if(i>=8)//不再读取数据
			{
				break;
			}
		}
	}
	fclose(fp_read);
	if(i==8)
	{
		year=(tempchar_date[0]-'0')*1000+(tempchar_date[1]-'0')*100+(tempchar_date[2]-'0')*10+(tempchar_date[3]-'0');
		month=(tempchar_date[4]-'0')*10+(tempchar_date[5]-'0');
		day=(tempchar_date[6]-'0')*10+(tempchar_date[7]-'0');
	}
	if(year>=1601&&year<=9999&&month>=1&&month<=12&&day>=1&&day<=JudgeMonth(year,month))//校检日期格式
	{
		SYSTEMTIME SystemTime;
		SystemTime.wYear=year;
		SystemTime.wMonth=month;
		SystemTime.wDay=day;
	    CMonth_StartDate.SetCurSel(&SystemTime);//读取开始日期日历控件上选择的日期
		AfxMessageBox(_T("读取文件成功，已成功设置开始日期为文件内记录的日期"),MB_OK,NULL);
		return;
	}
	else
	{
		AfxMessageBox(_T("日期格式有误，读取失败"),MB_OK,NULL);
		return;
	}    
}


void CDateCalculatorDlg::OnBnClickedBcalculate()
{
	// TODO: 在此添加控件通知处理程序代码
	if(CalculatorChoice==0)//通过开始日期和结束日期计算相距时间
	{
		SYSTEMTIME SystemTime;
	    CMonth_StartDate.GetCurSel(&SystemTime);//读取开始日期日历控件上选择的日期
		int startyear=SystemTime.wYear;
		int startmonth=SystemTime.wMonth;
		int startday=SystemTime.wDay;
		CMonth_EndDate.GetCurSel(&SystemTime);//读取结束日期日历控件上选择的日期
		int endyear=SystemTime.wYear;
		int endmonth=SystemTime.wMonth;
		int endday=SystemTime.wDay;

		int apartday=CalculuteDay(startyear,startmonth,startday,endyear,endmonth,endday);
		if(apartday==-1)//日期输入有误
		{
			SetDlgItemText(IDC_EAPARTTIME,_T("0"));//相距时间编辑框内容置为0
			AfxMessageBox(_T("结束日期在开始日期之前，日期输入有误"),MB_OK,NULL);
			return;
		}

		CString cstr=_T("");
		cstr.Format(_T("%d"),apartday);
		SetDlgItemText(IDC_EAPARTTIME,cstr);
		cstr.Format(_T("相距%d天"),apartday);
		AfxMessageBox(cstr,MB_OK,NULL);
	}
	else if(CalculatorChoice==1)//通过开始日期和相距时间计算结束日期
	{
		SYSTEMTIME SystemTime;
	    CMonth_StartDate.GetCurSel(&SystemTime);//读取开始日期日历控件上选择的日期
		int startyear=SystemTime.wYear;
		int startmonth=SystemTime.wMonth;
		int startday=SystemTime.wDay;
		const char* char_days=MyCStringToConstChar(EditApartTime);
		int nLength=strlen(char_days);
		int days=0;
		for(int i=0;i<nLength;i++)
		{
			if(i>6)//数据过大(最多7位数)
			{
				SetDlgItemText(IDC_EAPARTTIME,_T("0"));//相距时间编辑框内容置为0
				AfxMessageBox(_T("数据过大，计算失败"),MB_OK,NULL);
				return;
			}
			if(char_days[i]>='0'&&char_days[i]<='9')//校检数据格式
			{
				days=days*10+(char_days[i]-'0');
			}
			else
			{
				SetDlgItemText(IDC_EAPARTTIME,_T("0"));//相距时间编辑框内容置为0
				AfxMessageBox(_T("输入的相距天数格式错误"),MB_OK,NULL);
				return;
			}
		}
		int endyear=0,endmonth=0,endday=0;
		CalculuteEndDate(startyear,startmonth,startday,days,&endyear,&endmonth,&endday);
		SystemTime.wYear=endyear;
		SystemTime.wMonth=endmonth;
		SystemTime.wDay=endday;
		CMonth_EndDate.SetCurSel(&SystemTime);//设置结束日期日历控件上的日期
		int week=JudgeWeek(endyear,endmonth,endday);
		CString cstr=_T("");
	    switch(week)
	    {
	        case 1:{cstr.Format(_T("时间为：%04d年%02d月%02d日星期一"),endyear,endmonth,endday);break;}
	        case 2:{cstr.Format(_T("时间为：%04d年%02d月%02d日星期二"),endyear,endmonth,endday);break;}
	        case 3:{cstr.Format(_T("时间为：%04d年%02d月%02d日星期三"),endyear,endmonth,endday);break;}
		    case 4:{cstr.Format(_T("时间为：%04d年%02d月%02d日星期四"),endyear,endmonth,endday);break;}
		    case 5:{cstr.Format(_T("时间为：%04d年%02d月%02d日星期五"),endyear,endmonth,endday);break;}
		    case 6:{cstr.Format(_T("时间为：%04d年%02d月%02d日星期六"),endyear,endmonth,endday);break;}
		    case 7:{cstr.Format(_T("时间为：%04d年%02d月%02d日星期日"),endyear,endmonth,endday);break;}
		    default:{break;}//数据有误
	    }
		AfxMessageBox(cstr,MB_OK,NULL);
	}
	else//计算模式选择有误
	{
		AfxMessageBox(_T("计算模式选择有误"),MB_OK,NULL);
	}
}


void CDateCalculatorDlg::OnBnClickedBexit()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CDateCalculatorDlg::OnEnChangeEfilepath()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CDateCalculatorDlg::OnEnChangeEaparttime()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CDateCalculatorDlg::OnBnClickedRstartdate()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(StartDateChoice==0)//手动设置日期
	{
		CEdit *edit = (CEdit*)GetDlgItem(IDC_SFILEPATH);
		edit->ShowWindow(FALSE);//文件路径提示不可见

		edit = (CEdit*)GetDlgItem(IDC_EFILEPATH);
		edit->ShowWindow(FALSE);//文件路径编辑框不可见

		edit = (CEdit*)GetDlgItem(IDC_BCHOOSEFILE);
		edit->ShowWindow(FALSE);//选择文件按钮不可见

		edit = (CEdit*)GetDlgItem(IDC_BREADFILE);
		edit->ShowWindow(FALSE);//读取文件按钮不可见

		CMonth_StartDate.EnableWindow(TRUE);//启用开始日期日历控件
		CMonth_StartDate.SetCurrentView(0);//设置开始日期日历视图为月视图
	}
	else if(StartDateChoice==1)//从文件载入日期
	{
		CEdit *edit = (CEdit*)GetDlgItem(IDC_SFILEPATH);
		edit->ShowWindow(TRUE);//文件路径提示可见

		edit = (CEdit*)GetDlgItem(IDC_EFILEPATH);
		edit->ShowWindow(TRUE);//文件路径编辑框可见

		edit = (CEdit*)GetDlgItem(IDC_BCHOOSEFILE);
		edit->ShowWindow(TRUE);//选择文件按钮可见

		edit = (CEdit*)GetDlgItem(IDC_BREADFILE);
		edit->ShowWindow(TRUE);//读取文件按钮可见

		CMonth_StartDate.SetCurrentView(0);//设置开始日期日历视图为月视图
		CMonth_StartDate.EnableWindow(FALSE);//禁用开始日期日历控件
	}
	else//开始日期设置模式选择有误
	{
		AfxMessageBox(_T("开始日期设置模式选择有误"),MB_OK,NULL);
	}
}


void CDateCalculatorDlg::OnBnClickedRenddate()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(EndDateChoice==0)//今天
	{
		SYSTEMTIME SystemTime;
		GetLocalTime(&SystemTime);//获取系统时间
		CMonth_EndDate.SetCurrentView(0);//设置结束日期日历视图为月视图
		CMonth_EndDate.SetCurSel(&SystemTime);//设置结束日期日历控件上的日期为当前日期
		CMonth_EndDate.EnableWindow(FALSE);//禁用结束日期日历控件
	}
	else if(EndDateChoice==1)//手动设置日期
	{
		CMonth_EndDate.EnableWindow(TRUE);//启用结束日期日历控件
		CMonth_EndDate.SetCurrentView(0);//设置结束日期日历视图为月视图
	}
	else//结束日期设置模式选择有误
	{
		AfxMessageBox(_T("结束日期设置模式选择有误"),MB_OK,NULL);
	}
}


void CDateCalculatorDlg::OnBnClickedRcalculatorchoice()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(CalculatorChoice==0)//通过开始日期和结束日期计算相距时间
	{
		CEdit *edit = (CEdit*)GetDlgItem(IDC_EAPARTTIME);
		edit->SetReadOnly(TRUE);//相距时间编辑框只读

		edit = (CEdit*)GetDlgItem(IDC_RENDDATE_0);
		edit->EnableWindow(TRUE);//启用结束日期中“今天”单选控件

		edit = (CEdit*)GetDlgItem(IDC_RENDDATE_1);
		edit->EnableWindow(TRUE);//启用结束日期中“手动设置日期”单选控件

		CDateCalculatorDlg::OnBnClickedRenddate();
	}
	else if(CalculatorChoice==1)//通过开始日期和相距时间计算结束日期
	{
		CEdit *edit = (CEdit*)GetDlgItem(IDC_EAPARTTIME);
		edit->SetReadOnly(FALSE);//相距时间编辑框不只读

		CMonth_EndDate.SetCurrentView(0);//设置结束日期日历视图为月视图
		CMonth_EndDate.EnableWindow(FALSE);//禁用结束日期日历控件

		edit = (CEdit*)GetDlgItem(IDC_RENDDATE_0);
		edit->EnableWindow(FALSE);//禁用结束日期中“今天”单选控件

		edit = (CEdit*)GetDlgItem(IDC_RENDDATE_1);
		edit->EnableWindow(FALSE);//禁用结束日期中“手动设置日期”单选控件
	}
	else//计算模式选择有误
	{
		AfxMessageBox(_T("计算模式选择有误"),MB_OK,NULL);
	}
}


int JudgeYear(int year)//判断平闰年
{
	if(year%400==0)		            return 1;//闰年
	    else if(year%100==0)		return 0;//平年
	    else if(year%4==0)		    return 1;//闰年
	    else		                return 0;//平年
}

int JudgeMonth(int year,int month)//判断某月有多少天
{
	switch(month)
	{
	       case 1:{return 31;}
		   case 2:
		   {
			   if(JudgeYear(year)==1)   return 29;//闰年
			       else                 return 28;//平年
		   }
		   case 3:{return 31;}
		   case 4:{return 30;}
		   case 5:{return 31;}
		   case 6:{return 30;}
		   case 7:{return 31;}
		   case 8:{return 31;}
		   case 9:{return 30;}
		   case 10:{return 31;}
		   case 11:{return 30;}
		   case 12:{return 31;}
		   default:{return -1;}
	}
}

int CalculuteDay(int startyear,int startmonth,int startday,int endyear,int endmonth,int endday)//计算两日期相距多少天
{
	if(endyear<startyear)                                                           return -1;//数据有误
	    else if((endyear==startyear)&&(endmonth<startmonth))                        return -1;//数据有误
	    else if((endyear==startyear)&&(endmonth==startmonth)&&(endday<startday))    return -1;//数据有误
	int days=0;
	if(endyear>startyear)
	{
		int startyearday=0;
		if(JudgeYear(startyear)==1)       startyearday=366;//闰年
		    else                          startyearday=365;//平年
		days+=startyearday-CalculuteDayInOneYear(startyear,startmonth,startday);
		int tempyearday=0;
		for(int i=startyear+1;i<endyear;i++)
		{
			if(JudgeYear(i)==1)           tempyearday=366;//闰年
		        else                      tempyearday=365;//平年
			days+=tempyearday;
		}
		days+=CalculuteDayInOneYear(endyear,endmonth,endday);
	}
	else//endyear==startyear
	{
		days=CalculuteDayInOneYear(endyear,endmonth,endday)-CalculuteDayInOneYear(startyear,startmonth,startday);
	}
	return days;
}

int CalculuteDayInOneYear(int year,int month,int day)//计算某一日期为该年的第几天
{
	int sumdays=0;
	for(int i=1;i<month;i++)
	{
		sumdays+=JudgeMonth(year,i);
	}
	sumdays+=day;
	return sumdays;
}

int JudgeWeek(int year,int month,int day)//判断某一日期星期几
{
	//1601年1月1日星期一
	int days=CalculuteDay(1601,1,1,year,month,day);
	return (days%7+1);
}

void CalculuteEndDate(int startyear,int startmonth,int startday,int days,int* endyear,int* endmonth,int* endday)//根据相距时间计算结束时间
{
	int startyearday=0;
	if(JudgeYear(startyear)==1)       startyearday=366;//闰年
		else                          startyearday=365;//平年
	if(CalculuteDayInOneYear(startyear,startmonth,startday)+days<=startyearday)
	{
		*endyear=startyear;
		if(startday+days<=JudgeMonth(startyear,startmonth))
		{
			*endmonth=startmonth;
			*endday=startday+days;
		}
		else
		{
			int leftdays=days-(JudgeMonth(startyear,startmonth)-startday);
			*endmonth=startmonth+1;
			while(leftdays-JudgeMonth(startyear,*endmonth)>0)
			{
				leftdays-=JudgeMonth(startyear,*endmonth);
				(*endmonth)++;
			}
			if(leftdays-JudgeMonth(startyear,*endmonth)==0)
			{
				*endday=JudgeMonth(startyear,*endmonth);
				return;
			}
			*endday=leftdays;
		}
	}
	else
	{
		int leftdays=days-(startyearday-CalculuteDayInOneYear(startyear,startmonth,startday));
		*endyear=startyear+1;
		int endyearday=0;
	    if(JudgeYear(*endyear)==1)        endyearday=366;//闰年
		    else                          endyearday=365;//平年
		while(leftdays-endyearday>0)
		{
			leftdays-=endyearday;
			(*endyear)++;
			if(JudgeYear(*endyear)==1)        endyearday=366;//闰年
		        else                          endyearday=365;//平年
		}
		if(leftdays-endyearday==0)
		{
			*endmonth=12;
			*endday=31;
			return;
		}
		*endmonth=1;
		while(leftdays-JudgeMonth(*endyear,*endmonth)>0)
		{
			leftdays-=JudgeMonth(*endyear,*endmonth);
			(*endmonth)++;
		}
		if(leftdays-JudgeMonth(*endyear,*endmonth)==0)
		{
			*endday=JudgeMonth(*endyear,*endmonth);
			return;
		}
		*endday=leftdays;
	}
}