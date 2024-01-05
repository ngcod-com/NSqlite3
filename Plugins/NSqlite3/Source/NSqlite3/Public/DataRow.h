// Copyright 2024 ngcod, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataRow.generated.h"

union NDataField
{
	char* text;
	double dValue;
	int64 iValue;
};
/**
 * 
 */
UCLASS(BlueprintType)
class NSQLITE3_API UDataRow : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NSqlite3|Row")
	FString GetString(int ColIndex);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NSqlite3|Row")
	FString GetStringByName(const FString& ColName);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NSqlite3|Row")
	float GetNumber(int ColIndex);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NSqlite3|Row")
	float GetNumberByName(const FString& ColName);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NSqlite3|Row")
	int64 GetInt(int ColIndex);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NSqlite3|Row")
	int64 GetIntByName(const FString& ColName);

	void Put(const FString& ColName, const FString& Value);
private:
	TArray<FString> Datas;
	TArray<FString> ColNames;
};
