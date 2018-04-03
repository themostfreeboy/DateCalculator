
// DateCalculatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DateCalculator.h"
#include "DateCalculatorDlg.h"
#include "afxdialogex.h"

#include "MyMFC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDateCalculatorDlg �Ի���




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


// CDateCalculatorDlg ��Ϣ�������

BOOL CDateCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CEdit *edit = (CEdit*)GetDlgItem(IDC_SFILEPATH);
	edit->ShowWindow(FALSE);//�ļ�·����ʾ���ɼ�

	edit = (CEdit*)GetDlgItem(IDC_EFILEPATH);
	edit->ShowWindow(FALSE);//�ļ�·���༭�򲻿ɼ�

	edit = (CEdit*)GetDlgItem(IDC_BCHOOSEFILE);
	edit->ShowWindow(FALSE);//ѡ���ļ���ť���ɼ�

	edit = (CEdit*)GetDlgItem(IDC_BREADFILE);
	edit->ShowWindow(FALSE);//��ȡ�ļ���ť���ɼ�

	edit = (CEdit*)GetDlgItem(IDC_EAPARTTIME);
	edit->SetReadOnly(TRUE);//���ʱ��༭��ֻ��

	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);//��ȡϵͳʱ��

	CMonth_StartDate.EnableWindow(TRUE);//���ÿ�ʼ���������ؼ�
	CMonth_StartDate.SetCurrentView(0);//���ÿ�ʼ����������ͼΪ����ͼ
	CMonth_StartDate.SetCurSel(&SystemTime);//���ÿ�ʼ���������ؼ��ϵ�����Ϊ��ǰ����

	CMonth_EndDate.EnableWindow(TRUE);//���ý������������ؼ�
	CMonth_EndDate.SetCurrentView(0);//���ý�������������ͼΪ����ͼ
	CMonth_EndDate.SetCurSel(&SystemTime);//���ý������������ؼ��ϵ�����Ϊ��ǰ����
	CMonth_EndDate.EnableWindow(FALSE);//���ý������������ؼ�

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDateCalculatorDlg::OnPaint()
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
HCURSOR CDateCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDateCalculatorDlg::OnBnClickedBsave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SYSTEMTIME SystemTime;
	CMonth_StartDate.GetCurSel(&SystemTime);//��ȡ��ʼ���������ؼ���ѡ�������

	errno_t err_write;
	FILE *fp_write = NULL;
	err_write = fopen_s(&fp_write, "D:\\DateSave.txt", "wb");
	if (err_write != 0)//�ļ���ʧ��
	{
		AfxMessageBox(_T("����ʧ��"),MB_OK,NULL);
		return;
	}

	fprintf(fp_write,"%04d��%02d��%02d������",SystemTime.wYear,SystemTime.wMonth,SystemTime.wDay);
	int week=JudgeWeek(SystemTime.wYear,SystemTime.wMonth,SystemTime.wDay);
	switch(week)
	{
	    case 1:{fprintf(fp_write,"һ");break;}
	    case 2:{fprintf(fp_write,"��");break;}
	    case 3:{fprintf(fp_write,"��");break;}
		case 4:{fprintf(fp_write,"��");break;}
		case 5:{fprintf(fp_write,"��");break;}
		case 6:{fprintf(fp_write,"��");break;}
		case 7:{fprintf(fp_write,"��");break;}
		default:{break;}//��������
	}
	
    fclose(fp_write);
	AfxMessageBox(_T("����ɹ�����ǰ��ʼ�����Ѿ����浽D:\\DateSave.txt��"),MB_OK,NULL);
}


void CDateCalculatorDlg::OnBnClickedBchoosefile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString szPath = _T("");

	//CFileDialog::CFileDialog( BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL, DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL);
    //�����������£�
    //bOpenFileDialog��ΪTRUE����ʾ�򿪶Ի���ΪFALSE����ʾ����Ի��ļ��Ի��� 
    //lpszDefExt��ָ��Ĭ�ϵ��ļ���չ���� 
    //lpszFileName��ָ��Ĭ�ϵ��ļ����� 
    //dwFlags��ָ��һЩ�ض���� 
    //lpszFilter��������Ҫ��һ����������ָ���ɹ�ѡ����ļ����ͺ���Ӧ����չ����

    CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||"), NULL);

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
        //AfxMessageBox(_T("��Ч���ļ���������ѡ��"),MB_OK,NULL);
	}
}


void CDateCalculatorDlg::OnBnClickedBreadfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(EditChoosePath.IsEmpty())
	{
		AfxMessageBox(_T("�ļ�·������Ϊ��"),MB_OK,NULL);
		return;
	}

	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, MyCStringToConstChar(EditChoosePath), "rb");
	if (err_read != 0)//�ļ���ʧ��
	{
		AfxMessageBox(_T("�ļ���ȡʧ��"),MB_OK,NULL);
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
			if(i>=8)//���ٶ�ȡ����
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
	if(year>=1601&&year<=9999&&month>=1&&month<=12&&day>=1&&day<=JudgeMonth(year,month))//У�����ڸ�ʽ
	{
		SYSTEMTIME SystemTime;
		SystemTime.wYear=year;
		SystemTime.wMonth=month;
		SystemTime.wDay=day;
	    CMonth_StartDate.SetCurSel(&SystemTime);//��ȡ��ʼ���������ؼ���ѡ�������
		AfxMessageBox(_T("��ȡ�ļ��ɹ����ѳɹ����ÿ�ʼ����Ϊ�ļ��ڼ�¼������"),MB_OK,NULL);
		return;
	}
	else
	{
		AfxMessageBox(_T("���ڸ�ʽ���󣬶�ȡʧ��"),MB_OK,NULL);
		return;
	}    
}


void CDateCalculatorDlg::OnBnClickedBcalculate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(CalculatorChoice==0)//ͨ����ʼ���ںͽ������ڼ������ʱ��
	{
		SYSTEMTIME SystemTime;
	    CMonth_StartDate.GetCurSel(&SystemTime);//��ȡ��ʼ���������ؼ���ѡ�������
		int startyear=SystemTime.wYear;
		int startmonth=SystemTime.wMonth;
		int startday=SystemTime.wDay;
		CMonth_EndDate.GetCurSel(&SystemTime);//��ȡ�������������ؼ���ѡ�������
		int endyear=SystemTime.wYear;
		int endmonth=SystemTime.wMonth;
		int endday=SystemTime.wDay;

		int apartday=CalculuteDay(startyear,startmonth,startday,endyear,endmonth,endday);
		if(apartday==-1)//������������
		{
			SetDlgItemText(IDC_EAPARTTIME,_T("0"));//���ʱ��༭��������Ϊ0
			AfxMessageBox(_T("���������ڿ�ʼ����֮ǰ��������������"),MB_OK,NULL);
			return;
		}

		CString cstr=_T("");
		cstr.Format(_T("%d"),apartday);
		SetDlgItemText(IDC_EAPARTTIME,cstr);
		cstr.Format(_T("���%d��"),apartday);
		AfxMessageBox(cstr,MB_OK,NULL);
	}
	else if(CalculatorChoice==1)//ͨ����ʼ���ں����ʱ������������
	{
		SYSTEMTIME SystemTime;
	    CMonth_StartDate.GetCurSel(&SystemTime);//��ȡ��ʼ���������ؼ���ѡ�������
		int startyear=SystemTime.wYear;
		int startmonth=SystemTime.wMonth;
		int startday=SystemTime.wDay;
		const char* char_days=MyCStringToConstChar(EditApartTime);
		int nLength=strlen(char_days);
		int days=0;
		for(int i=0;i<nLength;i++)
		{
			if(i>6)//���ݹ���(���7λ��)
			{
				SetDlgItemText(IDC_EAPARTTIME,_T("0"));//���ʱ��༭��������Ϊ0
				AfxMessageBox(_T("���ݹ��󣬼���ʧ��"),MB_OK,NULL);
				return;
			}
			if(char_days[i]>='0'&&char_days[i]<='9')//У�����ݸ�ʽ
			{
				days=days*10+(char_days[i]-'0');
			}
			else
			{
				SetDlgItemText(IDC_EAPARTTIME,_T("0"));//���ʱ��༭��������Ϊ0
				AfxMessageBox(_T("��������������ʽ����"),MB_OK,NULL);
				return;
			}
		}
		int endyear=0,endmonth=0,endday=0;
		CalculuteEndDate(startyear,startmonth,startday,days,&endyear,&endmonth,&endday);
		SystemTime.wYear=endyear;
		SystemTime.wMonth=endmonth;
		SystemTime.wDay=endday;
		CMonth_EndDate.SetCurSel(&SystemTime);//���ý������������ؼ��ϵ�����
		int week=JudgeWeek(endyear,endmonth,endday);
		CString cstr=_T("");
	    switch(week)
	    {
	        case 1:{cstr.Format(_T("ʱ��Ϊ��%04d��%02d��%02d������һ"),endyear,endmonth,endday);break;}
	        case 2:{cstr.Format(_T("ʱ��Ϊ��%04d��%02d��%02d�����ڶ�"),endyear,endmonth,endday);break;}
	        case 3:{cstr.Format(_T("ʱ��Ϊ��%04d��%02d��%02d��������"),endyear,endmonth,endday);break;}
		    case 4:{cstr.Format(_T("ʱ��Ϊ��%04d��%02d��%02d��������"),endyear,endmonth,endday);break;}
		    case 5:{cstr.Format(_T("ʱ��Ϊ��%04d��%02d��%02d��������"),endyear,endmonth,endday);break;}
		    case 6:{cstr.Format(_T("ʱ��Ϊ��%04d��%02d��%02d��������"),endyear,endmonth,endday);break;}
		    case 7:{cstr.Format(_T("ʱ��Ϊ��%04d��%02d��%02d��������"),endyear,endmonth,endday);break;}
		    default:{break;}//��������
	    }
		AfxMessageBox(cstr,MB_OK,NULL);
	}
	else//����ģʽѡ������
	{
		AfxMessageBox(_T("����ģʽѡ������"),MB_OK,NULL);
	}
}


void CDateCalculatorDlg::OnBnClickedBexit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


void CDateCalculatorDlg::OnEnChangeEfilepath()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CDateCalculatorDlg::OnEnChangeEaparttime()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CDateCalculatorDlg::OnBnClickedRstartdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(StartDateChoice==0)//�ֶ���������
	{
		CEdit *edit = (CEdit*)GetDlgItem(IDC_SFILEPATH);
		edit->ShowWindow(FALSE);//�ļ�·����ʾ���ɼ�

		edit = (CEdit*)GetDlgItem(IDC_EFILEPATH);
		edit->ShowWindow(FALSE);//�ļ�·���༭�򲻿ɼ�

		edit = (CEdit*)GetDlgItem(IDC_BCHOOSEFILE);
		edit->ShowWindow(FALSE);//ѡ���ļ���ť���ɼ�

		edit = (CEdit*)GetDlgItem(IDC_BREADFILE);
		edit->ShowWindow(FALSE);//��ȡ�ļ���ť���ɼ�

		CMonth_StartDate.EnableWindow(TRUE);//���ÿ�ʼ���������ؼ�
		CMonth_StartDate.SetCurrentView(0);//���ÿ�ʼ����������ͼΪ����ͼ
	}
	else if(StartDateChoice==1)//���ļ���������
	{
		CEdit *edit = (CEdit*)GetDlgItem(IDC_SFILEPATH);
		edit->ShowWindow(TRUE);//�ļ�·����ʾ�ɼ�

		edit = (CEdit*)GetDlgItem(IDC_EFILEPATH);
		edit->ShowWindow(TRUE);//�ļ�·���༭��ɼ�

		edit = (CEdit*)GetDlgItem(IDC_BCHOOSEFILE);
		edit->ShowWindow(TRUE);//ѡ���ļ���ť�ɼ�

		edit = (CEdit*)GetDlgItem(IDC_BREADFILE);
		edit->ShowWindow(TRUE);//��ȡ�ļ���ť�ɼ�

		CMonth_StartDate.SetCurrentView(0);//���ÿ�ʼ����������ͼΪ����ͼ
		CMonth_StartDate.EnableWindow(FALSE);//���ÿ�ʼ���������ؼ�
	}
	else//��ʼ��������ģʽѡ������
	{
		AfxMessageBox(_T("��ʼ��������ģʽѡ������"),MB_OK,NULL);
	}
}


void CDateCalculatorDlg::OnBnClickedRenddate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(EndDateChoice==0)//����
	{
		SYSTEMTIME SystemTime;
		GetLocalTime(&SystemTime);//��ȡϵͳʱ��
		CMonth_EndDate.SetCurrentView(0);//���ý�������������ͼΪ����ͼ
		CMonth_EndDate.SetCurSel(&SystemTime);//���ý������������ؼ��ϵ�����Ϊ��ǰ����
		CMonth_EndDate.EnableWindow(FALSE);//���ý������������ؼ�
	}
	else if(EndDateChoice==1)//�ֶ���������
	{
		CMonth_EndDate.EnableWindow(TRUE);//���ý������������ؼ�
		CMonth_EndDate.SetCurrentView(0);//���ý�������������ͼΪ����ͼ
	}
	else//������������ģʽѡ������
	{
		AfxMessageBox(_T("������������ģʽѡ������"),MB_OK,NULL);
	}
}


void CDateCalculatorDlg::OnBnClickedRcalculatorchoice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(CalculatorChoice==0)//ͨ����ʼ���ںͽ������ڼ������ʱ��
	{
		CEdit *edit = (CEdit*)GetDlgItem(IDC_EAPARTTIME);
		edit->SetReadOnly(TRUE);//���ʱ��༭��ֻ��

		edit = (CEdit*)GetDlgItem(IDC_RENDDATE_0);
		edit->EnableWindow(TRUE);//���ý��������С����족��ѡ�ؼ�

		edit = (CEdit*)GetDlgItem(IDC_RENDDATE_1);
		edit->EnableWindow(TRUE);//���ý��������С��ֶ��������ڡ���ѡ�ؼ�

		CDateCalculatorDlg::OnBnClickedRenddate();
	}
	else if(CalculatorChoice==1)//ͨ����ʼ���ں����ʱ������������
	{
		CEdit *edit = (CEdit*)GetDlgItem(IDC_EAPARTTIME);
		edit->SetReadOnly(FALSE);//���ʱ��༭��ֻ��

		CMonth_EndDate.SetCurrentView(0);//���ý�������������ͼΪ����ͼ
		CMonth_EndDate.EnableWindow(FALSE);//���ý������������ؼ�

		edit = (CEdit*)GetDlgItem(IDC_RENDDATE_0);
		edit->EnableWindow(FALSE);//���ý��������С����족��ѡ�ؼ�

		edit = (CEdit*)GetDlgItem(IDC_RENDDATE_1);
		edit->EnableWindow(FALSE);//���ý��������С��ֶ��������ڡ���ѡ�ؼ�
	}
	else//����ģʽѡ������
	{
		AfxMessageBox(_T("����ģʽѡ������"),MB_OK,NULL);
	}
}


int JudgeYear(int year)//�ж�ƽ����
{
	if(year%400==0)		            return 1;//����
	    else if(year%100==0)		return 0;//ƽ��
	    else if(year%4==0)		    return 1;//����
	    else		                return 0;//ƽ��
}

int JudgeMonth(int year,int month)//�ж�ĳ���ж�����
{
	switch(month)
	{
	       case 1:{return 31;}
		   case 2:
		   {
			   if(JudgeYear(year)==1)   return 29;//����
			       else                 return 28;//ƽ��
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

int CalculuteDay(int startyear,int startmonth,int startday,int endyear,int endmonth,int endday)//������������������
{
	if(endyear<startyear)                                                           return -1;//��������
	    else if((endyear==startyear)&&(endmonth<startmonth))                        return -1;//��������
	    else if((endyear==startyear)&&(endmonth==startmonth)&&(endday<startday))    return -1;//��������
	int days=0;
	if(endyear>startyear)
	{
		int startyearday=0;
		if(JudgeYear(startyear)==1)       startyearday=366;//����
		    else                          startyearday=365;//ƽ��
		days+=startyearday-CalculuteDayInOneYear(startyear,startmonth,startday);
		int tempyearday=0;
		for(int i=startyear+1;i<endyear;i++)
		{
			if(JudgeYear(i)==1)           tempyearday=366;//����
		        else                      tempyearday=365;//ƽ��
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

int CalculuteDayInOneYear(int year,int month,int day)//����ĳһ����Ϊ����ĵڼ���
{
	int sumdays=0;
	for(int i=1;i<month;i++)
	{
		sumdays+=JudgeMonth(year,i);
	}
	sumdays+=day;
	return sumdays;
}

int JudgeWeek(int year,int month,int day)//�ж�ĳһ�������ڼ�
{
	//1601��1��1������һ
	int days=CalculuteDay(1601,1,1,year,month,day);
	return (days%7+1);
}

void CalculuteEndDate(int startyear,int startmonth,int startday,int days,int* endyear,int* endmonth,int* endday)//�������ʱ��������ʱ��
{
	int startyearday=0;
	if(JudgeYear(startyear)==1)       startyearday=366;//����
		else                          startyearday=365;//ƽ��
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
	    if(JudgeYear(*endyear)==1)        endyearday=366;//����
		    else                          endyearday=365;//ƽ��
		while(leftdays-endyearday>0)
		{
			leftdays-=endyearday;
			(*endyear)++;
			if(JudgeYear(*endyear)==1)        endyearday=366;//����
		        else                          endyearday=365;//ƽ��
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