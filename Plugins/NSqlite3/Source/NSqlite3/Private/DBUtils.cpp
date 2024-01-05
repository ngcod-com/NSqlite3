// Copyright 2024 ngcod, Inc. All Rights Reserved.

#include "DBUtils.h"
#include "DataRow.h"
#include "NDataBase.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"

sqlite3* UDBUtils::Database = nullptr;

UDBUtils::UDBUtils(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

UNDataBase* UDBUtils::Open(const FString& RelativeDataBasePath, FString& errorMsg, bool bAutoCreate)
{
	errorMsg = TEXT("");
	sqlite3* tDatabase;
	FString path;
#if PLATFORM_IOS
	NSString *documentPath=[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES)lastObject];
	path=UTF8_TO_TCHAR(documentPath.UTF8String);
#else
	path = FPaths::ProjectPersistentDownloadDir();
#endif
	const FString DataBasePath = path + "/" + RelativeDataBasePath;

	const int index = DataBasePath.Find(TEXT("/"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	const FString folder = DataBasePath.Left(index);
	if (bAutoCreate && !FPaths::DirectoryExists(folder))
	{
		IFileManager::Get().MakeDirectory(*folder, true);
	}	
	
	const int nRes = sqlite3_open_v2(TCHAR_TO_UTF8(*DataBasePath), &tDatabase, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, nullptr);
	if (nRes != SQLITE_OK)
	{
		errorMsg = FString::Printf(TEXT("Open Database Failed! %s"), *DataBasePath);
		const char* error = sqlite3_errmsg(tDatabase);
		if (error != nullptr)
		{
			errorMsg += UTF8_TO_TCHAR(error);
		}
		sqlite3_close_v2(tDatabase);
		tDatabase = nullptr;
		FString fileExist = TEXT("True");
		if (!IFileManager::Get().FileExists(*DataBasePath))
		{
			fileExist = TEXT("False");
		}
		UE_LOG(LogTemp, Warning, TEXT("Open Database Failed! %s %s. Error Message: %s."), *DataBasePath, *fileExist, *errorMsg);
		return nullptr;
	}
	UE_LOG(LogTemp, Warning, TEXT("Open Database Success! %s"), *DataBasePath);

	UNDataBase* database = NewObject<UNDataBase>();
	database->SetDataBase(tDatabase);
	return database;
}

bool UDBUtils::Close(sqlite3* pDatabase)
{
	if (nullptr == pDatabase)
	{
		return false;
	}
	const int result = sqlite3_close_v2(pDatabase);
	if (result == SQLITE_OK)
	{
		Database = nullptr;
		return true;
	}
	return false;
}

bool UDBUtils::Execute(const FString& SQL, FString& errorMsg)
{
	if (nullptr == Database)
	{
		return false;
	}
	const FString tSQL = SQL.TrimStartAndEnd();
	if (tSQL.StartsWith(TEXT("select")))
	{
		errorMsg = TEXT("Please use query function.");
		return false;
	}
	errorMsg = TEXT("");
	TArray<UDataRow*> results;
	if (sqlite3_exec(Database, TCHAR_TO_UTF8(*tSQL), nullptr, nullptr, nullptr) == SQLITE_OK)
	{
		return true;
	}
	errorMsg = sqlite3_errmsg(Database);
	return false;
}

TArray<UDataRow*> UDBUtils::Query(const FString& TableName, const FString& ColName, FString& errorMsg)
{
	errorMsg = TEXT("");
	const FString SQL = "select " + ColName + "from " + TableName;
	return QueryBySql(SQL, errorMsg);
}

TArray<UDataRow*> UDBUtils::QueryBySql(const FString& SQL, FString& errorMsg)
{
	const FString tSQL = SQL.TrimStartAndEnd();
	errorMsg = TEXT("");
	TArray<UDataRow*> results;
	if (!tSQL.StartsWith(TEXT("select")))
	{
		errorMsg = TEXT("Please use Execute.");
		return results;
	}
	
	if (nullptr == Database)
	{
		errorMsg = TEXT("Database is null. Did you open it");
		return results;
	}
	
	sqlite3_stmt* stmt = NULL;
	const char* zTail;
	
	if (sqlite3_prepare_v2(Database, TCHAR_TO_UTF8(*tSQL), -1, &stmt, &zTail) == SQLITE_OK)
	{
		int iCount = sqlite3_column_count(stmt);
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			UDataRow* rowData = NewObject<UDataRow>();
			for (int i = 0; i < iCount; i++)
			{
				FString data;
				
				const int columnType = sqlite3_column_type(stmt, i);
				const char* columnName = sqlite3_column_name(stmt, i);
				switch (columnType)
				{
				case SQLITE_INTEGER:
					/*{
						DataField.iValue = sqlite3_column_int64(stmt, i);
						break;
					}*/
				case SQLITE_FLOAT:
					/*{
						DataField.dValue = sqlite3_column_double(stmt, i);
						break;
					}*/
				case SQLITE_TEXT:
				default:
					{
						const unsigned char* columnValue = sqlite3_column_text(stmt, i);
						data = UTF8_TO_TCHAR(columnValue);
						break;
					}
					
				}
				
				rowData->Put(UTF8_TO_TCHAR(columnName), data);
			}
			results.Emplace(rowData);
		}
	}
	else
	{
		errorMsg = sqlite3_errmsg(Database);
	}
	sqlite3_finalize(stmt);
	return results;
}

void UDBUtils::UseDB(sqlite3* pDB)
{
	Database = pDB;
}

