// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "sqlite3.h"
#include "DBUtils.generated.h"

class UDataRow;
/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
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
