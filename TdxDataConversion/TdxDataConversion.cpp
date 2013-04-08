// choice1.cpp : Defines the entry point for the DLL application.
// ���ʵ��

#define PLUGIN_EXPORTS

#include "stdafx.h"
#include "plugin.h"
#include "log.h"
#include "DataConstructor.h"
#include <fstream>
#include <atlstr.h>

PDATAIOFUNC	 m_pfn;
CLog& m_log = CLog::Instance();

void RegisterDataInterface(PDATAIOFUNC pfn)
{
	m_pfn = pfn;
}

////////////////////////////////////////////////////////////////////////////////
//ע������Ϣ
void GetCopyRightInfo(LPPLUGIN info)
{
	//��д������Ϣ
	strcpy(info->Name,"��ȡ����");
	strcpy(info->Dy,"����");
	strcpy(info->Author,"����");
	strcpy(info->Period,"");
	strcpy(info->Descript,"");
	strcpy(info->OtherInfo,"");
	//��д������Ϣ
	info->ParamNum = 2;
	strcpy(info->ParamInfo[0].acParaName,"��������");
	info->ParamInfo[0].nMin=1;
	info->ParamInfo[0].nMax=100;
	info->ParamInfo[0].nDefault=1;
	strcpy(info->ParamInfo[1].acParaName,"��������");
	info->ParamInfo[1].nMin=1;
	info->ParamInfo[1].nMax=100000;
	info->ParamInfo[1].nDefault=100000;
}

////////////////////////////////////////////////////////////////////////////////
const	BYTE	g_nAvoidMask[]={0xF8,0xF8,0xF8,0xF8};	// ��Ч���ݱ�־(ϵͳ����)

WORD   AfxRightData(float*pData,WORD nMaxData)	//��ȡ��Ч����λ��
{	
	WORD nIndex=0;
	for(;nIndex<nMaxData&&!memcmp(&pData[nIndex],g_nAvoidMask,4);nIndex++);
	return(nIndex);
}
////////////////////////////////////////////////////////////////////////////////
//�Զ���ʵ��ϸ�ں���(�ɸ���ѡ����Ҫ���)

CString GetCode(char* Code)
{
	CString strCode = _T("");
	char* pChar = Code;
	while (*pChar != '\0')
	{
		strCode.AppendFormat(_T("%c"), *pChar);
		pChar++;
	}

	return strCode;
}

///////////////////////////////////////////////////////////////////////////////////
//
BOOL InputInfoThenCalc1(char * Code,		//��Ʊ����
						short nSetCode,		//�г����࣬0Ϊ���� 1Ϊ����
						int Value[4],		//���ò���
						short DataType,		//�����������ͣ�ȱʡΪ��K����ʷ����
						short nDataNum,		//�������ݸ���
						BYTE nTQ,			//��ȷ��Ȩ��Ϣ
						unsigned long unused) //��������ݼ���
{
	BOOL nRet = FALSE;
	NTime tmpTime={0};

	LPHISDAT pHisDat = new HISDAT[nDataNum];  //���ݻ�����
	long readnum = m_pfn(Code,nSetCode,DataType,pHisDat,nDataNum,tmpTime,tmpTime,nTQ,0);  //���ûص������������ݣ����صõ������ݸ���
	//CLog::Log(LOG_TRACE, "code:%s\tSet:%d\tDataType:%d\tDataNum:%d\tReadNum:%d", 
	//	Code, nSetCode, DataType, nDataNum, readnum);
	CString strCode = _T("");
	strCode = GetCode(Code);
	CString strFileName;
	strFileName.Format(_T("D:\\new_zszq\\Log\\%s.day"), strCode);
	ofstream rs(strFileName, ios::binary);
	long lTotLength = readnum * sizeof(tag_HISDAT);
	rs.write((char*)pHisDat, lTotLength);

	rs.close();


	//m_log.Log( LogLevel::LOG_TRACE, ("%s,%d,%d,%d,%d,%d,%d,%d,%d"), Code, nSetCode, Value[0], Value[1], DataType, nDataNum, nTQ, readnum);
	
	//if( readnum > max(Value[0],Value[1]) ) //ֻ�����ݸ�������Value[0]��Value[1]�е����ֵ��������
	//{
		//float *pMa1 = new float[readnum];
		//float *pMa2 = new float[readnum];
		//for(int i=0;i < readnum;i++)
		//{
		//	pMa1[i] = pHisDat[i].Close;
		//	pMa2[i] = pHisDat[i].Close;
		//}
		//AfxCalcMa(pMa1,readnum,Value[0]);	//����MA
		//AfxCalcMa(pMa2,readnum,Value[1]);
		//float nCross;
		//if(AfxCross(pMa1,pMa2,readnum-1,nCross) == 1)	//�ж��ǲ�����readnum-1(���һ������)������ 1:�ϴ� 2:�´�
		//	nRet = TRUE;  //����Ϊ�棬����ѡ������
		//delete []pMa1;pMa1=NULL;
		//delete []pMa2;pMa2=NULL;
	//}

	delete []pHisDat;
	pHisDat=NULL;
	return nRet;
}

BOOL InputInfoThenCalc2(char * Code,		//��Ʊ����
						short nSetCode,		//�г�����
						int Value[4],		//�����б�
						short DataType,		//�����������ͣ�ȱʡΪ��K����ʷ����
						NTime time1,		//��ʼʱ��
						NTime time2,		//����ʱ��
						BYTE nTQ,			//��ȷ��Ȩ��Ϣ
						unsigned long unused)  //ѡȡ����
{
	BOOL nRet = FALSE;
	NTime tmpTime={0};
	m_log.Log( LogLevel::LOG_TRACE, ("123223"));
	//�������ݸ���
	long datanum = m_pfn(Code,nSetCode,DataType,NULL,-1,time1,time2,nTQ,0);
	if( datanum < max(Value[0],Value[1]) ) 
		return FALSE;
	
	//��ȡ����
	LPHISDAT pHisDat = new HISDAT[datanum];
	long readnum = m_pfn(Code,nSetCode,DataType,pHisDat,datanum,time1,time2,nTQ,0);
	if( readnum > max(Value[0],Value[1]) ) //ֻ�н����ݸ�������Value[0]��Value[1]�е����ֵ��������
	{
		
	}

	delete []pHisDat;pHisDat=NULL;
	return nRet;
}

