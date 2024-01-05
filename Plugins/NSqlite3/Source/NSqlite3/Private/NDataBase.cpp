// Copyright 2024 ngcod, Inc. All Rights Reserved.


#include "NDataBase.h"
#include "DBUtils.h"

bool UNDataBase::Execute(const FString& SQL, FString& errorMsg)
{
	UDBUtils::UseDB(this->Database);
	return UDBUtils::Execute(SQL, errorMsg);
}

TArray<UDataRow*> UNDataBase::Query(const FString& TableName, const FString& ColName, FString& errorMsg)
{
	UDBUtils::UseDB(this->Database);
	return UDBUtils::Query(TableName, ColName, errorMsg);
}

TArray<UDataRow*> UNDataBase::QueryBySql(const FString& SQL, FString& errorMsg)
{
	UDBUtils::UseDB(this->Database);
	return UDBUtils::QueryBySql(SQL, errorMsg);
}

bool UNDataBase::Close()
{
	const bool result = UDBUtils::Close(this->Database);
	if (result)
	{
		this->Database = nullptr;
	}
	return result;
}

void UNDataBase::SetDataBase(sqlite3* pDataBase)
{
	this->Database = pDataBase;
}
