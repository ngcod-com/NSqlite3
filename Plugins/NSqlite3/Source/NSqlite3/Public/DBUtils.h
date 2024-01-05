// Copyright 2024 ngcod, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "sqlite3.h"
#include "DBUtils.generated.h"

class UDataRow;

UCLASS()
class NSQLITE3_API UDBUtils : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "NSqlite3")
		static UNDataBase* Open(const FString& RelativeDataBasePath, FString& errorMsg, bool bAutoCreate=false);
		static bool Close(sqlite3* db);
	//UFUNCTION(BlueprintCallable, Category = "NSqlite3")
		static bool Execute(const FString& SQL, FString& errorMsg);

	//UFUNCTION(BlueprintCallable, Category = "NSqlite3")
		static TArray<UDataRow*> Query(const FString& TableName, const FString& ColName, FString& errorMsg);
	//UFUNCTION(BlueprintCallable, Category = "NSqlite3")
		static TArray<class UDataRow*> QueryBySql(const FString& SQL, FString& errorMsg);
	static void UseDB(sqlite3* pDB);
private:
	static sqlite3* Database;
};
