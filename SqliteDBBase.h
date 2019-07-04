#pragma once
#include "sqlite3.h"
#include <map>
#include <atlstr.h>

// �򵥷�װ��Sqlite���ݿ����
class CSqliteDataBase
{
public:
	explicit CSqliteDataBase(const CString& strSqliteDBPath);
	~CSqliteDataBase(void);
public:
	/**
	*  @brief : ��ȡ���ݿ����ָ��
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/31 9:07
	*/
	sqlite3* GetSqliteDb();

	/**
	*  @brief : �������ݿ���߱������ݿ�(������main���ݿ��н��в���)
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/8/4 13:55
	*/
	int LoadOrSaveDb(const CString& strFilePath,BOOL bIsSave);

	/**
	*  @brief :  �������ݿ���߱������ݿ�(��ָ���������ݿ�)
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/8/4 13:56
	*/
	int LoadOrSaveDb(const CString& strFilePath,const CString& strDesDbName,const CString& strSrcDbName,BOOL bIsSave);
	
private:
	/**
	*  @brief : �����ݿ�,���������,�򴴽�
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:47
	*/
	int Open(const CString& strSqliteDBPath);
	int Open(const CString& strSqliteDBPath,sqlite3*& pDb);
	/**
	*  @brief : �ر����ݿ�
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:47
	*/
	int Close(sqlite3* pDb);
private:
	CSqliteDataBase(const CSqliteDataBase&);
	CSqliteDataBase& operator = (const CSqliteDataBase&);
public:
	int Close();
public:
	/**
	*  @brief : ע���Զ��庯��
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2016/5/16 16:52
	*/
	int Create_function(const CString& strFunctionName,const int nArg,void (*pFunc)(void* ctx,int nArg,void** values),void *pApp = NULL);
	/**
	*  @brief : ��ȡ�Զ��庯�����ݵ�ֵ
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2016/5/17 9:57
	*/
	static int Value_Int(void* pValue);
	static __int64 Value_Int64(void* pValue);
	static double Value_Double(void* pValue);
	static CString Value_Text(void* pValue);
	static int Value_Bytes(void* pValue);
	static const void* Value_Blob(void* pValue);
	/**
	*  @brief : �����Զ��庯���ķ���ֵ
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2016/5/17 10:16
	*/
	static void Result_Int(void* ctx,int nValue);
	static void Result_Int64(void* ctx,__int64 nValue);
	static void Result_Double(void* ctx,double dblValue);
	static void Result_Text(void* ctx,const CString& strValue);
	static void Result_Blob(void* ctx,const void* pBuffer,const int nByte);

	/**
	*  @brief : �����Զ���ۺϺ���
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2016/5/18 9:21
	*/
	int Create_Aggregation_function(const CString& strFunctionName,const int nArg,void (*pStep)(void* ctx,int nArg,void** values),
									void (*pFinal)(void* ctx),void *pApp = NULL);

	/**
	*  @brief : �ۺ�������,�����洢�ۺ�SQL����״̬
	*
	*
	*  @note	�״ε���Ϊ�ۺϷ����ڴ�,֮��ÿ�ε��÷����״η�����ڴ��ַ
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2016/5/18 9:37
	*/
	static void* Aggregate_Context(void* ctx,int nBytes);
	/**
	*  @brief : �ڴ������
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2016/5/18 10:41
	*/
	static void* Malloc(int nBytes);						// �����ڴ�
	static void* Malloc64(__int64 nBytes);					// �����ڴ�
	static void* Realloc(void* pPriorMem,int nBytes);		// �����ڴ��С
	static void* Realloc64(void* pPriorMem,__int64 nBytes);	// �����ڴ��С
	static void Free(void* pMem);							// �ͷ��ڴ�
	static __int64 Msize(void* pMem);						// ��ȡ�ڴ��С
	/**
	*  @brief : �����Զ�������
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2016/5/18 13:56
	*/
	int Create_Collation(const CString& strFunctionName,int(*xCompare)(void*,int,const void*,int,const void*),void *pArg = NULL);
private:
	sqlite3* m_pDb;					// ���ݿ�ָ�����
};

// �򵥷�װ��Sqlite������
class CSqliteDBStmt
{
public:
	explicit CSqliteDBStmt(CSqliteDataBase* sqliteDB);
	~CSqliteDBStmt(void);

	/**
	*  @brief : ��������
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/8/4 15:43
	*/
	void Begin();
	/**
	*  @brief : �ع�����
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/8/25 16:00
	*/
	void RollBack();
	/**
	*  @brief : �ύ����
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/8/4 15:43
	*/
	void Commit();
	/**
	*  @brief : ׼���������
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:48
	*/
	int Prepare(const CString& strSQL);

	/**
	*  @brief : ִ�����
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:48
	*/
	int Step();

	/**
	*  @brief : ������
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:50
	*/
	int Finalize();

	/**
	*  @brief : �������
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:50
	*/
	int Reset();
	/**
	*  @brief : ��հ�ֵΪnull
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:50
	*/
	int Clear_Bindings();
	/**
	*  @brief : ��ȡSELECT�����ֶθ���
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:50
	*/
	int Column_Count();
	/**
	*  @brief : ��ȡ��¼���ֶθ���,ֻ����������л�α�ſ��Թ���
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:50
	*/
	int Data_Count();

	/**
	*  @brief : ��ȡ�ֶ�����
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:52
	*/
	CString Column_Name(int iCol);
	/**
	*  @brief : ��ȡ�е�ֵ����
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2016/8/19 17:31
	*/
	int Column_Type(const CString& strColName);
	/**
	*  @brief : ��ȡ�ֶ�ֵΪ�ַ�
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:52
	*/
	CString Column_Text(int iCol);
	BOOL Column_Text(const CString& strColName,CString& strColValue);
	/**
	*  @brief : ��ȡ�ֶ�ֵΪ����
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:53
	*/
	int Column_Int(int iCol);
	BOOL Column_Int(const CString& strColName,int& iColValue);
	/**
	*  @brief : ��ȡ�ֶ�ֵΪ������
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:54
	*/
	double Column_Double(int iCol);
	BOOL Column_Double(const CString& strColName,double& dblColValue);

	/**
	*  @brief : �󶨴��ֶ�
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:54
	*/
	const void* Column_Blob(int iCol);
	BOOL Column_Blob(const CString& strColName,const void*& pBuffer);
	BOOL Column_Blob( const CString& strColName,const void*& pBuffer,long & lBufferSize);

	/**
	*  @brief : ��ȡ���ֶεĴ�С
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/9/10 16:19
	*/
	long Column_Blob_Size( const int iCol ); 

	/**
	*  @brief : ��ȡ�����ƶ�Ӧ��������
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/8/4 9:14
	*/
	int Bind_Parameter_Index(const CString& strColName);
	/**
	*  @brief : ������ֵ
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:54
	*/
	int Bind_Int(int iIndex,int iValue);
	int Bind_Int(const CString& strColName,int iValue);
	int Bind_Int64(int iIndex, __int64 llValue);
	int Bind_Int64(const CString& strColName, __int64 llValue);
	/**
	*  @brief : �󶨸�����ֵ
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:55
	*/
	int Bind_Double(int iIndex,double dblValue);
	int Bind_Double(const CString& strColName,double dblValue);
	/**
	*  @brief : ���ַ���ֵ
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:55
	*/
	int Bind_Text(int iIndex,const CString& strValue);
	int Bind_Text(const CString& strColName,const CString& strValue);
	/**
	*  @brief : �󶨶�����
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 16:55
	*/
	int Bind_Blob(int iIndex,const void* pBuffer,const int nByte);
	int Bind_Blob(const CString& strColName,const void* pBuffer,const int nByte);
	/**
	*  @brief : ��ȡ����Ĵ�����Ϣ
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/22 17:21
	*/
	CString ErrMsg();
	/**
	*  @brief : ִ��SQL���
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/23 10:06
	*/
	int Exec(const CString& strSQL);
	/**
	*  @brief : �������ݿ⵽��ǰ���ݿ�
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2016/8/4 9:15
	*/
	int Attach(const CString& strtDBPath,const CString& strDBName);
	/**
	*  @brief : ���븽�����ݿ�
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/8/5 11:10
	*/
	int Detach(const CString& strDBName);
	/**
	*  @brief : ɾ��ָ�����ݿ��ָ����
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/8/7 15:56
	*/
	int DropTable(const CString& strTableName,const CString& strDbName = _T("main"));
	/**
	*  @brief : ɾ����ͼ
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2016/5/19 19:15
	*/
	int DropView(const CString& strTableName,const CString& strDbName = _T("main"));
	/**
	*  @brief : �жϱ��Ƿ����
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/8/7 15:01
	*/
	BOOL IsTableExist(const CString& strTableName,const CString& strDbName = _T("main"));
	/**
	*  @brief : �ж��Ƿ����ָ����ͼ
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2016/5/19 19:13
	*/
	BOOL IsViewExist(const CString& strTableName,const CString& strDbName = _T("main"));
	/**
	*  @brief : �жϱ��Ƿ����
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/8/7 15:01
	*/
	BOOL IsFieldExist(const CString& strTableName,const CString& strFieldName,const CString& strDbName = _T("main"));

	/**
	*  @brief : ��ȡ���ݿ�������ָ��
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/7/31 9:30
	*/
	sqlite3_stmt* GetSqliteStmt();

	/**
	*  @brief : ��ʼ������������ŵĶ�Ӧ��ϵ
	*
	*
	*  @note
	*  @param : 
	*  @defenc: 
	*  @return: 
	*  @author: yjc
	*  @date  : 2015/8/3 14:50
	*/
	void InitColName2ColIndex();
private:
	typedef std::map<CString,int> MapStrName2ICol;
	typedef MapStrName2ICol::iterator MapStrName2IColIter;		
	MapStrName2ICol m_mapstrName2iCol;							// �����������Map
	sqlite3_stmt* m_pStmt;										// ������ָ��
	CSqliteDataBase* m_pSqliteDataBase;							// Sqlite�������ָ��
};
