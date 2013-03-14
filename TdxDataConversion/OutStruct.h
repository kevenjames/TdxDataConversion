#ifndef OUTSTRUCT_H_
#define OUTSTRUCT_H_

#pragma pack(push,1) //�����һ�ֽڶ���

typedef struct tag_NTime
{
	unsigned short year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
}NTime;

typedef struct tag_HISDAT
{
	NTime Time;			//ʱ��
	float Open;			//��λ���̼�
	float High;			//��λ��߼�
	float Low;			//��λ��ͼ�
	float Close;		//��λ���̼�
	float Amount;
	DWORD Volume;       //��λ�ɽ���,ָ���޳ɽ���
	union 
	{ 
		float YClose;
		struct
		{   
			WORD up;                // ���Ǽ���
			WORD down;              // �µ�����
		}zd;						// ��λǰ���̼�(��Ȩ��)���ڻ��ĳֲ���
	};
}HISDAT,*LPHISDAT;

typedef struct ExDayInfo
{
	DWORD dwDate;     //����               
	short nStockNum;  //���콻�׹�Ʊ��     
	short nUpIdx;     //�����Ƿ�����       
	DWORD dwInVol;    //���̳ɽ���         
	DWORD dwFirstVol; //���Ͼ��۳ɽ���     
	float fLast5ZDFD; //���5�����񶯷���  
	WORD  wNoCjMinute;//û�гɽ��ķ�����   
	WORD  wCjbs;      //�ܳɽ�����
	union
	{
		float Yjlx;	  //����ǹ�ծ,�ǵ�����Ϣ
		float Lead;	  //�����ָ��,�ǵ������ʱ�̵�����ֵ
		float Other;  //����AB��,��δ��
	};
	char  strNoUsed[4];//�����ֶ�
}EXDAYINFO;

typedef struct tag_REPORTDAT
{
	WORD           ItemNum;              // ��������
	float          Close;                // ǰ���̼�
	float          Open;                 // ���̼�
	float          Max;                  // ��߼�
	float          Min;                  // ��ͼ�
	float          Now;                  // �ּ�
	DWORD          Volume;               // ����
	DWORD          NowVol;               // ����(���ֲ�)
	float          Amount;               // �ܳɽ����
	DWORD          Inside;               // ����
	DWORD          Outside;              // ����
	float          TickDiff;             // ���ǵ�(��λ��)
	BYTE		   InOutFlag;			 // �����̱�־ 0:Buy 1:Sell 2:None
	union
	{
		struct	//����
		{
			float          Buy;			// ��߽����
			float          Sell;        // ��ͽ�����
			float          Buyp[3];		// ���������
			DWORD          Buyv[3];		// ��Ӧ��������۵���������
			float          Sellp[3];	// ����������
			DWORD          Sellv[3];	// ��Ӧ���������۵���������
		}Ggpv;
		struct	//ָ��
		{
			float			LxValue;	// ����ָ��
			float			Yield;		// ������Ȩ��ָ��
			long			UpHome;		// ���Ǽ���
			long			DownHome;	// �µ�����
			float			JJAmount;	// ����ɽ����
			float			ZQAmount;	// ծȯ�ɽ����
			float			GZAmount;	// ��ծ�ɽ����
			float			QZAmount;	// Ȩ֤�ɽ����
			float			QTAmount;	// ָ�������ɽ����
		}Zspv;
	}Other;
}REPORTDAT,*LPREPORTDAT;	

typedef struct tag_STOCKINFO 
{
	char        Name[9];			// ֤ȯ����

	short       Unit;               // ���׵�λ	
	long		VolBase;			// ���ȵĻ���
	float       cdp;				// �����м�
	float       nh;					// ����
	float       nl;					// ���
	float       ah;					// �߼�ͻ�Ƶ�
	float       al;					// �ͼ�ͻ�Ƶ�
 	short       dkflag;				// �ʺ����������
	float       tbp;				// ���ƽ���
	float       stoplost;			// ֹ���
	float       leave;				// �˽��

	float       ActiveCapital;		// ��ͨ�ɱ�
    long        J_start;			//��������
	short       J_addr;				//����ʡ��
	short       J_hy;				//������ҵ
    float       J_zgb;				//�ܹɱ�
    float       J_gjg;				//���ҹ�
    float       J_fqrfrg;			//�����˷��˹�
    float       J_frg;				//���˹�
    float       J_bg;				//B��
    float       J_hg;				//H��
    float       J_zgg;				//ְ����
    float       J_zzc;				//���ʲ�(Ԫ)
    float       J_ldzc;				//�����ʲ�
    float       J_gdzc;				//�̶��ʲ�
    float       J_wxzc;				//�����ʲ�
    float       J_cqtz;				//����Ͷ��
    float       J_ldfz;				//������ծ
    float       J_cqfz;				//���ڸ�ծ
    float       J_zbgjj;			//�ʱ�������
    float       J_jzc;				//�ɶ�Ȩ��(���Ǿ��ʲ�)
    float       J_zysy;				//��Ӫ����
    float       J_zyly;				//��Ӫ����
    float       J_qtly;				//Ӧ���ʿ�
    float       J_yyly;				//Ӫҵ����
    float       J_tzsy;				//Ͷ������
    float       J_btsy;				//��Ӫ�ֽ�����
    float       J_yywsz;			//���ֽ�����
    float       J_snsytz;			//���
    float       J_lyze;				//�����ܶ�
    float       J_shly;				//˰������
    float       J_jly;				//������
    float       J_wfply;			//δ��������
    float       J_tzmgjz;			//����ÿ�ɾ��ʲ� ��������:  ���ʲ�/��������ܹɱ�
	//���Ӳ���
	float		J_jyl;				//������%
	float		J_mgwfp;			//ÿ��δ����
	float		J_mgsy;				//ÿ������
	float		J_mggjj;			//ÿ�ɹ�����
	float		J_mgjzc;			//ÿ�ɾ��ʲ�
	float		J_gdqyb;			//�ɶ�Ȩ���
}STOCKINFO,*LPSTOCKINFO;

typedef struct tag_TICKDAT
{ 
	NTime	Time;
	float   Now;            //�ּ�(Ԫ)
	DWORD   NowVol;         //����(��)
	float 	Amount;		    //�ɽ����(Ԫ)
	short   InOutFlag;      //������־
}TICKDAT,*LPTICKDAT;

typedef struct tag_BSPDAT
{
	NTime	Time;
	float   Now;
	unsigned long NowAmount;	//���ʳɽ����(��Ԫ)
	long	NowVol;
	float   BuyP[3];
	long    BuyV[3];
	float   SellP[3];
	long    SellV[3];
	char    InOutFlag;
	char    MaxFlag;//��߼۱�־ 0����߼���ǰ���ѳ��ֻ���Now��Ϊ��߼�1:��߼۴����Max��
	char    MinFlag;
	float   Max;
	float   Min;
}BSPDAT,*LPBSPDAT;

typedef struct tag_GBInfo	//�ɱ��ܹɱ���Ϣ
{
	float Zgb;
	float Ltgb;
}GBINFO,*LPGBINFO;

typedef struct tag_OtherInfo
{
	short RelativeMin;	//�뿪�е���Է�����
}OTHERINFO,*LPOTHERINFO;

typedef struct tag_ALLGPInfo
{
	short StockNum;			//ÿ�ַ���Ĺ�Ʊ��
	char  buf[1];			//���г�[1],����[6],����[8]˳����
}ALLGPINFO,*LPALLGPINFO;

typedef struct tag_FLInfo
{
	char  FLNum;			//���100������
	char  FLName[100][20];	//������
	short FLStockNum[100];	//ÿ�ַ���Ĺ�Ʊ��
	char  buf[1];			//���г�[1],����[6],����[8]˳����
}FLINFO,*LPFLINFO;

typedef struct tag_TPPrice
{
	float Close;
	float TPTop;
	float TPBottom;
}TPPRICE,*LPTPPRICE;

/////���Ǽ���
#define PER_MIN5     0		//5��������,��Ҫ����5��������
#define PER_MIN15    1		//15��������,��Ҫ����5��������
#define PER_MIN30    2		//30��������,��Ҫ����5��������
#define PER_HOUR     3		//1Сʱ����,��Ҫ����5��������
#define PER_DAY      4		//��������,��Ҫ������������
#define PER_WEEK     5		//��������,��Ҫ������������
#define PER_MONTH    6		//��������,��Ҫ������������
/////////////////////
#define PER_MIN1     7		//ͨ����ȯ�̼��ɰ��ݲ�֧��
#define PER_MINN	 8		//ͨ����ȯ�̼��ɰ��ݲ�֧��
#define PER_DAYN     9		//����������,��Ҫ������������
#define PER_SEASON	 10		//����,��Ҫ������������
#define PER_YEAR	 11		//����,��Ҫ������������

#define PER_EXDAY	20		//��չ���ߵ�����,ͨ����ȯ�̼��ɰ��ݲ�֧��

#define TICK_DAT    100		//�ֱ�����,ͨ����ȯ�̼��ɰ��ݲ�֧��
#define	MINUTE_DAT  101		//��ʱ����,ͨ����ȯ�̼��ɰ��ݲ�֧��
#define	BSP_DAT		102		//������,  ͨ����ȯ�̼��ɰ��ݲ�֧��
#define GBINFO_DAT	103		//�ɱ���Ϣ
#define	REPORT_DAT	104		//��������
#define	STKINFO_DAT	105		//��Ʊ�������

#define ALLGPINFO_DAT	106		//���й�Ʊ�����Ϣ
#define FLGINFO_DAT		107		//�������Ϣ
#define DYGINFO_DAT		108		//���������Ϣ
#define HYGINFO_DAT		109		//��ҵ�����Ϣ
#define GNGINFO_DAT		110		//��������Ϣ
#define ZDGINFO_DAT		111		//�Զ�������Ϣ
#define ZHGINFO_DAT		112		//��ϰ����Ϣ

#define REMOTEHQ_DAT	120		//Զ����������
#define TPPRICE_DAT		121		//�ǵ�ͣ����
#define OTHER_DAT		130		//����

/////////////
#define ASK_ALL			-1


//�����л�������
#define SWITCH_TOZST			11
#define SWITCH_TOVIP			12
#define SWITCH_ADDBLOCK			13
#define SWITCH_SAVENEWBLOCK		14
#define SWITCH_OPENURL			15
#define SWITCH_USERINFO			16
#define SWITCH_TOZSGPC			17
#define SWITCH_TOWARNWT			18

#define SWITCH_JYGETHQ			22
#define SWITCH_SETKEY			23
#define SWITCH_SHIFTCJZX		24
#define SWITCH_CLOSECJZX		25
#define SWITCH_CLOSEASSISWND	26
#define SWITCH_REFRESHTITLE		27
#define SWITCH_LOGINEMBWT		28
#define SWITCH_QUITEMBWT		29
#define SWITCH_MAXASSISWND		30
#define SWITCH_TQNOTIFY			32
#define SWITCH_OPENEMBWT		33
//////////////////////////////////////////////////////////////////////

typedef struct tag_OP_Scheme_Color
{ 
	COLORREF	BACKCOLOR;			//����
	COLORREF	BACKCOLOR2;			//����2
	COLORREF	TXTCOLOR;			//ͼ������

	//����ͼ���
	COLORREF	AXISCOLOR;			//�������
	COLORREF	TIMECOLOR;			//��������(����ʮ���ߡ��α��)
	
	COLORREF	KPCOLOR;			//�����߼�������
	COLORREF	KNCOLOR;			//������
	COLORREF	DOWNCOLOR;			//�µ���
	COLORREF	LEVELCOLOR;			//ƽ��

	COLORREF	VOLCOLOR;			//�ɽ�����ɫ
	COLORREF	BIGTITLECOLOR;		//�����
	COLORREF	FLOATCURSORCOLOR;	//������ɫ

	//�б����
	COLORREF	Grid_CodeName_Color;//����������ɫ
	COLORREF	GridLineColor;		//�б�ķָ�����ɫ
	COLORREF	GridHighLineColor;	//����ѡ���ߵ���ɫ
	COLORREF	GridTitleTextColor;	//��Ŀ������ɫ
	COLORREF	GridTitleArrowColor;//��Ŀ�������ɫ
	COLORREF	Grid_Spec_Color;	//�ر���ɫ�����������ΪTXTCOLOR

	//��Ѷ��ɫ
	COLORREF	ZxColor;
	COLORREF	ZxTitleColor;
	COLORREF	MineTitleTxtColor;
	COLORREF	MineTitleSelColor;
	COLORREF	MineTitleSpeColor;
	COLORREF	F10TitleColor;
	COLORREF	F10TitleSelColor;
			
	//��ҳ���
	COLORREF	LinkColor;
	COLORREF	ActiveLinkColor;
	COLORREF	VisitedLinkColor;
	COLORREF	WebSpecColor;

	COLORREF	OTHERCOLOR[11];		//������ɫ,����ָ���ʮ��ɶ��ı�ͼ
}SCHEME_COLOR;

typedef struct tag_OP_Scheme_Font
{ 
	char		ListFontName[40];
	short		ListFontSize;
	char		GraphFontName[40];
	short		GraphFontSize;
	char		ZxFontName[40];
	short		ZxFontSize;
}SCHEME_FONT;

typedef struct tag_OP_Scheme_Menu
{ 
	short	nMenuMode; 		//0:��ͳ��� 1:XP���
	short	bExtendXPStyle; //�Ƿ�����ǿ�͵�XP��� 
	long	Reserved;
}SCHEME_MENU;

//////////////////////////////////////////////////////////////////////


#pragma pack(pop)

#endif
