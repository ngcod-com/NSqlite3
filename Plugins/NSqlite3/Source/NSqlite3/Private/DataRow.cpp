// Fill out your copyright notice in the Description page of Project Settings.


#include "DataRow.h"

FString UDataRow::GetString(int ColIndex)
{
    if (ColIndex >= Datas.Num())
    {
        return FString();
    }
    return Datas[ColIndex];
}

FString UDataRow::GetStringByName(const FString& ColName)
{
    const int32 index = ColNames.IndexOfByKey(ColName);
    if (index == -1 || index >= Datas.Num())
    {
        return FString();
    }
    return Datas[index];
}

float UDataRow::GetNumber(int ColIndex)
{
    if (ColIndex >= Datas.Num())
    {
        return 0.0f;
    }
    return FCString::Atof(*Datas[ColIndex]);
}

float UDataRow::GetNumberByName(const FString& ColName)
{
    const int32 index = ColNames.IndexOfByKey(ColName);
    if (index == -1 || index >= Datas.Num())
    {
        return 0.0f;
    }
    return FCString::Atof(*Datas[index]);
}

int64 UDataRow::GetInt(int ColIndex)
{
    if (ColIndex >= Datas.Num())
    {
        return -1;
    }
    return FCString::Atoi(*Datas[ColIndex]);
}

int64 UDataRow::GetIntByName(const FString& ColName)
{
    const  int32 index = ColNames.IndexOfByKey(ColName);
    if (index == -1 || index >= Datas.Num())
    {
        return -1;
    }
    return FCString::Atoi(*Datas[index]);
}

void UDataRow::Put(const FString& ColName, const FString& Value)
{
    ColNames.Emplace(ColName);
    Datas.Emplace(Value);
}
