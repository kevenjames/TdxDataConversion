// choice1.cpp : Defines the entry point for the DLL application.
// ���ʵ��

#define PLUGIN_EXPORTS

#include "stdafx.h"
#include "plugin.h"

PDATAIOFUNC	 m_pfn;

void RegisterDataInterface(PDATAIOFUNC pfn)
{
	m_pfn = pfn;
}

////////////////////////////////////////////////////////////////////////////////
//ע������Ϣ
void GetCopyRightInfo(LPPLUGIN info)
{
	//��д������Ϣ
	strcpy_s(info->Name,"��ȡ����");
	strcpy_s(info->Dy,"����");
	strcpy_s(info->Author,"����");
	strcpy_s(info->Period,"");
	strcpy_s(info->Descript,"");
	strcpy_s(info->OtherInfo,"");
	//��д������Ϣ
	info->ParamNum = 1;
	strcpy_s(info->ParamInfo[0].acParaName,"��������");
	info->ParamInfo[0].nMin=1;
	info->ParamInfo[0].nMax=100;
	info->ParamInfo[0].nDefault=1;
	strcpy_s(info->ParamInfo[1].acParaName,"��������");
	info->ParamInfo[1].nMin=1;
	info->ParamInfo[1].nMax=1000;
	info->ParamInfo[1].nDefault=60;
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

void   AfxCalcMa(float*pData,long nData,WORD nParam)
{	
	if(pData==NULL||nData==0||nParam==1) return;
	long i=nData-nParam+1,nMinEx=AfxRightData(pData,nData);
	if(nParam==0||nParam+nMinEx>nData) nMinEx=nData;
	else
	{	
		float	nDataEx=0,nDataSave=0;
		float	*MaPtr=pData+nData-1,*DataPtr=pData+nData-nParam;
		for(nMinEx+=nParam-1;i<nData;nDataEx+=pData[i++]);
		for(i=nData-1;i>=nMinEx;i--,MaPtr--,DataPtr--)
		{
			nDataEx+=(*DataPtr);
			nDataSave=(*MaPtr);
			*MaPtr=nDataEx/nParam;
			nDataEx-=nDataSave;
		}
	}
}

WORD   AfxCross(float*psData,float*plData,WORD nIndex,float&nCross)
{	
	if(psData==NULL||plData==NULL||nIndex==0) return(0);
	float  nDif=psData[nIndex-1]-plData[nIndex-1];
	float  nDifEx=plData[nIndex]-psData[nIndex];
	float  nRatio=(nDif+nDifEx)?nDif/(nDif+nDifEx):0;
	nCross=psData[nIndex-1]+(psData[nIndex]-psData[nIndex-1])*nRatio;
	if(nDif<0&&nDifEx<0)	return(1);
	if(nDif>0&&nDifEx>0)	return(2);
	return(0);
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
	if( readnum > max(Value[0],Value[1]) ) //ֻ�����ݸ�������Value[0]��Value[1]�е����ֵ��������
	{
		float *pMa1 = new float[readnum];
		float *pMa2 = new float[readnum];
		for(int i=0;i < readnum;i++)
		{
			pMa1[i] = pHisDat[i].Close;
			pMa2[i] = pHisDat[i].Close;
		}
		AfxCalcMa(pMa1,readnum,Value[0]);	//����MA
		AfxCalcMa(pMa2,readnum,Value[1]);
		float nCross;
		if(AfxCross(pMa1,pMa2,readnum-1,nCross) == 1)	//�ж��ǲ�����readnum-1(���һ������)������ 1:�ϴ� 2:�´�
			nRet = TRUE;  //����Ϊ�棬����ѡ������
		delete []pMa1;pMa1=NULL;
		delete []pMa2;pMa2=NULL;
	}

	delete []pHisDat;pHisDat=NULL;
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

	//�������ݸ���
	long datanum = m_pfn(Code,nSetCode,DataType,NULL,-1,time1,time2,nTQ,0);
	if( datanum < max(Value[0],Value[1]) ) 
		return FALSE;
	
	//��ȡ����
	LPHISDAT pHisDat = new HISDAT[datanum];
	long readnum = m_pfn(Code,nSetCode,DataType,pHisDat,datanum,time1,time2,nTQ,0);
	if( readnum > max(Value[0],Value[1]) ) //ֻ�н����ݸ�������Value[0]��Value[1]�е����ֵ��������
	{
		float *pMa1 = new float[readnum];
		float *pMa2 = new float[readnum];
		for(int i=0;i < readnum;i++)
		{
			pMa1[i] = pHisDat[i].Close;
			pMa2[i] = pHisDat[i].Close;
		}
		AfxCalcMa(pMa1,readnum,Value[0]);	//����MA
		AfxCalcMa(pMa2,readnum,Value[1]);
		float nCross;
		if(AfxCross(pMa1,pMa2,readnum-1,nCross) == 1)	//�ж��ǲ�����readnum-1(���һ������)������ 1:�ϴ� 2:�´�
			nRet = TRUE;
		delete []pMa1;pMa1=NULL;
		delete []pMa2;pMa2=NULL;
	}

	delete []pHisDat;pHisDat=NULL;
	return nRet;
}
