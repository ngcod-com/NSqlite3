// Copyright 2024 ngcod, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "sqlite3.h"
#include "NDataBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class NSQLITE3_API UNDataBase : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "NSqlite3")
	bool Execute(const FString& SQL, FString& errorMsg);
	
	UFUNCTION(BlueprintCallable, Category = "NSqlite3")
	TArray<UDataRow*> Query(const FString& TableName, const FString& ColName, FString& errorMsg);
	
	UFUNCTION(BlueprintCallable, Category = "NSqlite3")
	TArray<class UDataRow*> QueryBySql(const FString& SQL, FString& errorMsg);

	UFUNCTION(BlueprintCallable, Category = "NSqlite3")
	bool Close();

	void SetDataBase(sqlite3* pDataBase);
private:
	sqlite3* Database;
};
