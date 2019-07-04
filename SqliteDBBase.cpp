#include "stdafx.h"
#include "SqliteDBBase.h"

CSqliteDataBase::CSqliteDataBase(const CString& strSqliteDBPath):m_pDb(NULL)
{
	Open(strSqliteDBPath);
}

CSqliteDataBase::~CSqliteDataBase(void)
{
	if (NULL != m_pDb)
	{
		Close();
	}
}

int CSqliteDataBase::Open(const CString& strSqliteDBPath)
{
	// �����ַ���������ݿ�
	int rc = -1;
#ifdef UNICODE
	rc = sqlite3_open16(strSqliteDBPath,&m_pDb);
#else
	USES_CONVERSION;
	rc = sqlite3_open16(A2W(strSqliteDBPath),&m_pDb);
#endif
	// ��ʧ��
	if (SQLITE_OK != rc)
	{
		Close();
		m_pDb = NULL;
	}
	return rc;
}

int CSqliteDataBase::Open(const CString& strSqliteDBPath,sqlite3*& pDb)
{
	// �����ַ���������ݿ�
	int rc = -1;
#ifdef UNICODE
	rc = sqlite3_open16(strSqliteDBPath,&pDb);
#else
	USES_CONVERSION;
	rc = sqlite3_open16(A2W(strSqliteDBPath),&pDb);
#endif

	// ��ʧ��
	if (SQLITE_OK != rc)
	{
		Close(pDb);
		pDb = NULL;
	}
	return rc;
}

int CSqliteDataBase::Close()
{
	// �ر����ݿ�
	return sqlite3_close(m_pDb);
}

int CSqliteDataBase::Close(sqlite3* pDb)
{
	// �ر����ݿ�
	return sqlite3_close(pDb);
}
int CSqliteDataBase::Create_function(const CString& strFunctionName,const int nArg,void (*pFunc)(void* ctx,int nArg,void** values),void *pApp /*= NULL*/)
{
	// ����ص���������
	typedef void (*XFUNC) (sqlite3_context *,int,sqlite3_value **);
	XFUNC xFunc = reinterpret_cast<XFUNC>(pFunc);

	// ����ע��
#ifdef UNICODE
	return sqlite3_create_function16(m_pDb,strFunctionName,nArg,SQLITE_UTF16,pApp,xFunc,NULL,NULL);
#else
	USES_CONVERSION;
	return sqlite3_create_function16(m_pDb,A2W(strFunctionName),nArg,SQLITE_UTF16,pApp,xFunc,NULL,NULL);
#endif
}

int CSqliteDataBase::Create_Aggregation_function(const CString& strFunctionName,const int nArg,void (*pStep)(void* ctx,int nArg,void** values),
												 void (*pFinal)(void* ctx),void *pApp /*= NULL*/)
{
	// ���岽��ص���������
	typedef void (*XSTEP) (sqlite3_context *,int,sqlite3_value **);
	XSTEP xStep = reinterpret_cast<XSTEP>(pStep);

	// ������ֹ�ص���������
	typedef void (*XFINAL) (sqlite3_context *);
	XFINAL xFinal = reinterpret_cast<XFINAL>(pFinal);

	// ����ע��
#ifdef UNICODE
	return sqlite3_create_function16(m_pDb,strFunctionName,nArg,SQLITE_UTF16,pApp,NULL,xStep,xFinal);
#else
	USES_CONVERSION;
	return sqlite3_create_function16(m_pDb,A2W(strFunctionName),nArg,SQLITE_UTF16,pApp,NULL,xStep,xFinal);
#endif
}

void* CSqliteDataBase::Aggregate_Context(void* ctx, int nBytes)
{
	// ���ؾۺ�������
	return sqlite3_aggregate_context(static_cast<sqlite3_context*>(ctx),nBytes);
}

void* CSqliteDataBase::Malloc(int nBytes)
{
	// �����ڴ�
	return sqlite3_malloc(nBytes);
}

void* CSqliteDataBase::Malloc64(__int64 nBytes)
{
	// �����ڴ�
	return sqlite3_malloc64(nBytes);
}

void* CSqliteDataBase::Realloc(void* pPriorMem,int nBytes)
{
	// �����ڴ��С
	return sqlite3_realloc(pPriorMem,nBytes);
}

void* CSqliteDataBase::Realloc64(void* pPriorMem,__int64 nBytes)
{
	// �����ڴ��С
	return sqlite3_realloc64(pPriorMem,nBytes);
}

void CSqliteDataBase::Free(void* pMem)
{
	// �ͷ��ڴ�
	return sqlite3_free(pMem);
}

__int64 CSqliteDataBase::Msize(void* pMem)
{
	// ��ȡ�ڴ��С
	return sqlite3_msize(pMem);
}

int CSqliteDataBase::Create_Collation(const CString& strFunctionName,int(*xCompare)(void*,int,const void*,int,const void*),void *pArg /*= NULL*/)
{
	// ����ע��
#ifdef UNICODE
	return sqlite3_create_collation16(m_pDb,strFunctionName,SQLITE_UTF16,pArg,xCompare);
#else
	USES_CONVERSION;
	return sqlite3_create_collation16(m_pDb,A2W(strFunctionName),SQLITE_UTF16,pArg,xCompare);
#endif
}

int CSqliteDataBase::Value_Int(void* pValue)
{
	// ��ȡ�ص��������ݵ�ֵ
	return sqlite3_value_int(static_cast<sqlite3_value*>(pValue));
}

__int64 CSqliteDataBase::Value_Int64(void* pValue)
{
	// ��ȡ�ص��������ݵ�ֵ
	return sqlite3_value_int64(static_cast<sqlite3_value*>(pValue));
}

double CSqliteDataBase::Value_Double(void* pValue)
{
	// ��ȡ�ص��������ݵ�ֵ
	return sqlite3_value_double(static_cast<sqlite3_value*>(pValue));
}

CString CSqliteDataBase::Value_Text(void* pValue)
{
	// ���ûص������ķ���ֵ
	const void* pChar = sqlite3_value_text16(static_cast<sqlite3_value*>(pValue));
	const WCHAR* pWCChar = reinterpret_cast<const WCHAR*>(pChar);
	CString strValue;
#ifdef UNICODE
	strValue = pWCChar;
#else
	USES_CONVERSION;
	strValue = W2A(pWCChar);
#endif
	return strValue;
}

int CSqliteDataBase::Value_Bytes(void* pValue)
{
	// ��ȡ�ص��������ݵ�ֵ
	return sqlite3_value_bytes(static_cast<sqlite3_value*>(pValue));
}

const void* CSqliteDataBase::Value_Blob(void* pValue)
{
	// ��ȡ�ص��������ݵ�ֵ
	return sqlite3_value_blob(static_cast<sqlite3_value*>(pValue));
}

void CSqliteDataBase::Result_Int(void* ctx,int nValue)
{
	// ���ûص������ķ���ֵ
	return sqlite3_result_int(static_cast<sqlite3_context*>(ctx),nValue);
}

void CSqliteDataBase::Result_Int64(void* ctx,__int64 nValue)
{
	// ���ûص������ķ���ֵ
	return sqlite3_result_int64(static_cast<sqlite3_context*>(ctx),nValue);
}

void CSqliteDataBase::Result_Double(void* ctx,double dblValue)
{
	// ���ûص������ķ���ֵ
	return sqlite3_result_double(static_cast<sqlite3_context*>(ctx),dblValue);
}

void CSqliteDataBase::Result_Text(void* ctx,const CString& strValue)
{
	// ���ûص������ķ���ֵ
#ifdef UNICODE
	return sqlite3_result_text16(static_cast<sqlite3_context*>(ctx),strValue,-1,SQLITE_TRANSIENT);
#else
	USES_CONVERSION;
	return sqlite3_result_text16(static_cast<sqlite3_context*>(ctx),A2W(strValue),-1,SQLITE_TRANSIENT);
#endif
}

void CSqliteDataBase::Result_Blob(void* ctx,const void* pBuffer,const int nByte)
{
	// ���ûص������ķ���ֵ
	return sqlite3_result_blob(static_cast<sqlite3_context*>(ctx),pBuffer,nByte,SQLITE_TRANSIENT);
}
sqlite3* CSqliteDataBase::GetSqliteDb()
{
	// ��ȡ���ݿ����ָ��
	return m_pDb;
}

int CSqliteDataBase::LoadOrSaveDb(const CString& strFilePath,const CString& strDesDbName,const CString& strSrcDbName,BOOL bIsSave)
{
	// ���ļ�
	sqlite3 *pFile = NULL;
	int rc = Open(strFilePath,pFile);
	if(SQLITE_OK == rc)
	{
		sqlite3_backup *pBackup = NULL;
		sqlite3 *pTo = NULL;
		sqlite3 *pFrom = NULL;
		const char* pDestName = NULL;
		const char* pSourceName = NULL;
		// �ж��Ǵ��ļ��м������ݿ�, ���Ǵ����ݿⱣ�浽�ļ�
		pFrom = (bIsSave ? m_pDb : pFile);
		pTo   = (bIsSave ? pFile : m_pDb);

#ifdef UNICODE
		USES_CONVERSION;
		pDestName = W2A(strDesDbName);
		pSourceName = W2A(strSrcDbName);
#else
		pDestName = strDesDbName;
		pSourceName = strSrcDbName;
#endif
		// ���б���
		pBackup = sqlite3_backup_init(pTo,pDestName,pFrom,pSourceName);
		if( pBackup )
		{
			sqlite3_backup_step(pBackup, -1);
			sqlite3_backup_finish(pBackup);
		}
		rc = sqlite3_errcode(pTo);
	}
	sqlite3_close(pFile);
	return rc;
}

int CSqliteDataBase::LoadOrSaveDb(const CString& strFilePath,BOOL bIsSave)
{
	// Ĭ��main���ݿ�
	return LoadOrSaveDb(strFilePath,_T("main"),_T("main"),bIsSave);
}

CSqliteDBStmt::CSqliteDBStmt(CSqliteDataBase* pSqliteDB) :m_pSqliteDataBase(pSqliteDB),m_pStmt(NULL)
{

}

CSqliteDBStmt::~CSqliteDBStmt(void)
{
	// �ͷ�������
	if (NULL != m_pStmt)
	{
		m_mapstrName2iCol.clear();
		Finalize();
	}
}
void CSqliteDBStmt::Begin()
{
	Exec(_T("BEGIN"));
}

void CSqliteDBStmt::RollBack()
{

	Exec(_T("ROLLBACK"));
}

void CSqliteDBStmt::Commit()
{
	Exec(_T("COMMIT"));
}

int CSqliteDBStmt::Prepare(const CString& strSQL)
{
	if (NULL != m_pStmt)
	{
		m_mapstrName2iCol.clear();
		Finalize();
	}

	int rc = -1;
	sqlite3* pDb = m_pSqliteDataBase->GetSqliteDb();
	// ׼������SQL���
#ifdef UNICODE
	rc = sqlite3_prepare16_v2(pDb,strSQL,-1,&m_pStmt,NULL);
#else
	USES_CONVERSION;
	rc = sqlite3_prepare16_v2(pDb,A2W(strSQL),-1,&m_pStmt,NULL);
#endif
	// ��ʧ��
	if (SQLITE_OK != rc)
	{
		m_pStmt = NULL;
	}
	return rc;
}

int CSqliteDBStmt::Step()
{
	// ִ�����
	return sqlite3_step(m_pStmt);
}
int CSqliteDBStmt::Finalize()
{
	// ���
	int rc = sqlite3_finalize(m_pStmt);
	m_pStmt = NULL;
	return rc;
}

int CSqliteDBStmt::Reset()
{
	// ����
	return sqlite3_reset(m_pStmt);
}

int CSqliteDBStmt::Clear_Bindings()
{
	// ���
	return sqlite3_clear_bindings(m_pStmt);
}

int CSqliteDBStmt::Column_Count()
{
	// ��ȡ�ֶ���
	return sqlite3_column_count(m_pStmt);
}

int CSqliteDBStmt::Data_Count()
{
	// ��ȡ�ֶ���
	return sqlite3_data_count(m_pStmt);
}

CString CSqliteDBStmt::Column_Name(int iCol)
{
	// ��ȡ����
	CString strColName;
	const void* pColumnName = sqlite3_column_name16(m_pStmt,iCol);
	LPCWSTR lpColumnName = static_cast<LPCWSTR>(pColumnName);
#ifdef UNICODE
	strColName =  lpColumnName;
#else
	USES_CONVERSION;
	strColName =  W2A(lpColumnName);
#endif
	return strColName;
}
int CSqliteDBStmt::Column_Type(const CString& strColName)
{
	InitColName2ColIndex();
	MapStrName2IColIter it = m_mapstrName2iCol.find(strColName);
	// ��ȡ�е�ֵ
	if (m_mapstrName2iCol.end() == it)
	{
		return 0;	
	}
	return sqlite3_column_type(m_pStmt,it->second);
}
BOOL CSqliteDBStmt::Column_Text(const CString& strColName,CString& strColValue)
{
	InitColName2ColIndex();
	MapStrName2IColIter it = m_mapstrName2iCol.find(strColName);
	// ��ȡ�е�ֵ
	if (m_mapstrName2iCol.end() == it)
	{
		strColValue = _T("");
		return FALSE;
	}
	strColValue = Column_Text(it->second);
	return TRUE;
}

CString CSqliteDBStmt::Column_Text(int iCol)
{
	// ��ȡ�е�ֵ
	CString strColName;
	const void* pColumnName = sqlite3_column_text16(m_pStmt,iCol);
	LPCWSTR lpColumnName = static_cast<LPCWSTR>(pColumnName);
#ifdef UNICODE
	strColName = lpColumnName;
#else
	USES_CONVERSION;
	strColName = W2A(lpColumnName);
#endif
	return strColName;
}

BOOL CSqliteDBStmt::Column_Int(const CString& strColName,int& iColValue)
{
	InitColName2ColIndex();
	MapStrName2IColIter it = m_mapstrName2iCol.find(strColName);
	// ��ȡ�е�ֵ
	if (m_mapstrName2iCol.end() == it)
	{
		iColValue = 0;
		return FALSE;
	}
	iColValue = Column_Int(it->second);
	return TRUE;
}

int CSqliteDBStmt::Column_Int(int iCol)
{
	// ��ȡ�е�ֵ
	return sqlite3_column_int(m_pStmt,iCol);
}

BOOL CSqliteDBStmt::Column_Double(const CString& strColName,double& dblColValue)
{
	InitColName2ColIndex();
	MapStrName2IColIter it = m_mapstrName2iCol.find(strColName);
	// ��ȡ�е�ֵ
	if (m_mapstrName2iCol.end() == it)
	{
		dblColValue = 0.0;
		return FALSE;
	}
	dblColValue = Column_Double(it->second);
	return TRUE;
}

double CSqliteDBStmt::Column_Double(int iCol)
{
	// ��ȡ�е�ֵ
	return sqlite3_column_double(m_pStmt,iCol);
}


const void* CSqliteDBStmt::Column_Blob(int iCol)
{
	// ��ȡ�е�ֵ
	return sqlite3_column_blob(m_pStmt,iCol);
}

long CSqliteDBStmt::Column_Blob_Size(const int iCol)
{
	return sqlite3_column_bytes( m_pStmt , iCol ) ;
}

BOOL CSqliteDBStmt::Column_Blob(const CString& strColName,const void*& pBuffer)
{
	InitColName2ColIndex();
	MapStrName2IColIter it = m_mapstrName2iCol.find(strColName);
	// ��ȡ�е�ֵ
	if (m_mapstrName2iCol.end() == it)
	{
		pBuffer = NULL;
		return FALSE;
	}
	pBuffer = Column_Blob(it->second);
	return TRUE;
}

BOOL CSqliteDBStmt::Column_Blob(const CString& strColName,const void*& pBuffer,long& lBufferSize)
{
	InitColName2ColIndex();
	MapStrName2IColIter it = m_mapstrName2iCol.find(strColName);
	// ��ȡ�е�ֵ
	if (m_mapstrName2iCol.end() == it)
	{
		pBuffer = NULL;
		lBufferSize = 0;
		return FALSE;
	}
	pBuffer = Column_Blob(it->second);
	lBufferSize = Column_Blob_Size( it->second ) ;

	return TRUE ; 
}

int CSqliteDBStmt::Bind_Parameter_Index(const CString& strColName)
{
	// ��ȡ�󶨲�����Ӧ��������
	const char* pstrColName = NULL;
#ifdef UNICODE
	USES_CONVERSION;
	pstrColName = W2A(strColName);
#else
	pstrColName = strColName;
#endif
	return sqlite3_bind_parameter_index(m_pStmt,pstrColName);
}

int CSqliteDBStmt::Bind_Int(int iIndex,int iValue)
{
	// ��ֵ
	return	sqlite3_bind_int(m_pStmt,iIndex,iValue);
}

int CSqliteDBStmt::Bind_Int(const CString& strColName,int iValue)
{
	// ͨ���󶨵Ĳ������ư󶨲���
	int iIndex = Bind_Parameter_Index(strColName);
	return Bind_Int(iIndex,iValue);
}

int CSqliteDBStmt::Bind_Int64(int iIndex, __int64 llValue)
{
	// ��ֵ
	return	sqlite3_bind_int64(m_pStmt, iIndex, llValue);
}

int CSqliteDBStmt::Bind_Int64(const CString& strColName, __int64 llValue)
{
	// ͨ���󶨵Ĳ������ư󶨲���
	int iIndex = Bind_Parameter_Index(strColName);
	return Bind_Int64(iIndex, llValue);
}

int CSqliteDBStmt::Bind_Double(int iIndex,double dblValue)
{
	// ��ֵ
	return	sqlite3_bind_double(m_pStmt,iIndex,dblValue);
}

int CSqliteDBStmt::Bind_Double(const CString& strColName,double dblValue)
{
	// ͨ���󶨵Ĳ������ư󶨲���
	int iIndex = Bind_Parameter_Index(strColName);
	return Bind_Double(iIndex,dblValue);
}

int CSqliteDBStmt::Bind_Text(int iIndex,const CString& strValue)
{
	// ��ֵ
#ifdef UNICODE
	return sqlite3_bind_text16(m_pStmt,iIndex,strValue,-1,SQLITE_TRANSIENT);
#else
	USES_CONVERSION;
	return sqlite3_bind_text16(m_pStmt,iIndex,A2W(strValue),-1,SQLITE_TRANSIENT);
#endif
}

int CSqliteDBStmt::Bind_Text(const CString& strColName,const CString& strValue)
{
	// ͨ���󶨵Ĳ������ư󶨲���
	int iIndex = Bind_Parameter_Index(strColName);
	return Bind_Text(iIndex,strValue);
}

int CSqliteDBStmt::Bind_Blob(int iIndex,const void* pBuffer,const int nByte)
{
	// ��ֵ
	return sqlite3_bind_blob(m_pStmt,iIndex,pBuffer,nByte,SQLITE_TRANSIENT);
}

int CSqliteDBStmt::Bind_Blob(const CString& strColName,const void* pBuffer,const int nByte)
{
	// ͨ���󶨵Ĳ������ư󶨲���
	int iIndex = Bind_Parameter_Index(strColName);
	return Bind_Blob(iIndex,pBuffer,nByte);
}


CString CSqliteDBStmt::ErrMsg()
{
	// ��ȡ���һ�δ�����Ϣ
	CString strErrMsg;
	sqlite3* pDb = m_pSqliteDataBase->GetSqliteDb();
	const void* pErrMsg = sqlite3_errmsg16(pDb);
	LPCWSTR lpErrMsg = static_cast<LPCWSTR>(pErrMsg);
#ifdef UNICODE
	strErrMsg = lpErrMsg;
#else
	USES_CONVERSION;
	strErrMsg = W2A(lpErrMsg);
#endif
	return strErrMsg;
}

int CSqliteDBStmt::Exec(const CString& strSQL)
{
	// ����SQL���
	int rc = Prepare(strSQL);
	if (SQLITE_OK != rc)
	{
		// ׼�����ʧ��	
		return rc;
	}

	// ִ��SQL���
	rc = Step();

	// ���SQL���
	m_mapstrName2iCol.clear();
	Finalize();

	return rc;
}
int CSqliteDBStmt::Attach(const CString& strDBPath,const CString& strDBName)
{
	CString strSQL;
	// �������ݿ�
	strSQL.Format(_T("ATTACH :DBPath AS \"%s\""),strDBName);

	int rc = Prepare(strSQL);
	if (SQLITE_OK != rc)
	{
		// ׼�����ʧ��
		return rc;
	}
	Bind_Text(_T(":DBPath"),strDBPath);

	// ִ��SQL���
	rc = Step();

	// ���SQL���
	m_mapstrName2iCol.clear();
	Finalize();

	return rc;
}
int CSqliteDBStmt::Detach(const CString& strDBName)
{
	CString strSQL;
	// ���븽�ӵ����ݿ�
	strSQL.Format(_T("DETACH \"%s\""),strDBName);
	return Exec(strSQL);
}
int CSqliteDBStmt::DropTable(const CString& strTableName,const CString& strDbName /*= _T("main")*/)
{
	CString strSQL;

	// ɾ�������
	strSQL.Format(_T("DROP TABLE IF EXISTS \"%s\".\"%s\""),strDbName,strTableName);
	return Exec(strSQL);
}

int CSqliteDBStmt::DropView(const CString& strTableName,const CString& strDbName /*= _T("main")*/)
{
	CString strSQL;

	// ɾ����ͼ���
	strSQL.Format(_T("DROP VIEW IF EXISTS \"%s\".\"%s\""),strDbName,strTableName);
	return Exec(strSQL);
}

BOOL CSqliteDBStmt::IsTableExist(const CString& strTableName,const CString& strDbName /*= _T("main")*/)
{
	// ��ѯsqlite_master��
	CString strSQL;
	if (0 == strDbName.CompareNoCase(_T("temp")))
	{
		strSQL.Format(_T("SELECT * FROM sqlite_temp_master WHERE type = 'table' AND name = '%s'"),strTableName);
	}
	else
	{
		strSQL.Format(_T("SELECT * FROM \"%s\".sqlite_master WHERE type = 'table' AND name = '%s'"),strDbName,strTableName);
	}

	// �������,ִ��
	int rc = Prepare(strSQL);
	if (SQLITE_OK != rc)
	{
		// ׼�����ʧ��	
		return FALSE;
	}

	Step();

	// ���û�м�¼,������
	rc = Data_Count();

	// �ͷ�
	m_mapstrName2iCol.clear();
	Finalize();
	if (0 == rc)
	{
		return FALSE;
	}
	return TRUE;
}
BOOL CSqliteDBStmt::IsViewExist(const CString& strTableName,const CString& strDbName /*= _T("main")*/)
{
	// ��ѯsqlite_master��
	CString strSQL;
	if (0 == strDbName.CompareNoCase(_T("temp")))
	{
		strSQL.Format(_T("SELECT * FROM sqlite_temp_master WHERE type = 'view' AND name = '%s'"),strTableName);
	}
	else
	{
		strSQL.Format(_T("SELECT * FROM \"%s\".sqlite_master WHERE type = 'view' AND name = '%s'"),strDbName,strTableName);
	}

	// �������,ִ��
	int rc = Prepare(strSQL);
	if (SQLITE_OK != rc)
	{
		return FALSE;
	}

	Step();
	
	// ���û�м�¼,������
	rc = Data_Count();

	// �ͷ�
	m_mapstrName2iCol.clear();
	Finalize();
	if (0 == rc)
	{
		return FALSE;
	}
	return TRUE;
}
BOOL CSqliteDBStmt::IsFieldExist(const CString& strTableName,const CString& strFieldName,const CString& strDbName /*= _T("main")*/)
{
	// ��ȡ����Ϣ
	CString strSQL;
	
	strSQL.Format(_T("PRAGMA \"%s\".table_info(\"%s\")"),strDbName,strTableName);
	int rc = Prepare(strSQL);
	if (SQLITE_OK != rc)
	{
		return FALSE;
	}

	// �����ֶ�
	rc = Step();
	BOOL bExist = FALSE;
	while (SQLITE_ROW == rc)
	{
		CString strColName;
		Column_Text(_T("name"),strColName);
		if (strColName == strFieldName)
		{
			bExist = TRUE;
			break;
		}
		rc = Step();
	}
	m_mapstrName2iCol.clear();
	Finalize();
	return bExist;
}

sqlite3_stmt* CSqliteDBStmt::GetSqliteStmt()
{
	// ��ȡ���ݿ�������
	return m_pStmt;
}

void CSqliteDBStmt::InitColName2ColIndex()
{
	// �Ѿ���ʼ��,�����г�ʼ��
	if( false == m_mapstrName2iCol.empty())
	{
		return;
	}

	// �������������Ӧ������
	CString strColName;
	int iCount = sqlite3_column_count(m_pStmt);
	for (int i = 0;i < iCount;i++)
	{
		strColName = Column_Name(i);
		m_mapstrName2iCol[strColName] = i;
	}
}