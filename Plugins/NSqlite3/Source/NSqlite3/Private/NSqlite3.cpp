// Copyright 2024 ngcod, Inc. All Rights Reserved.

#include "NSqlite3.h"

#define LOCTEXT_NAMESPACE "FNSqlite3Module"

void FNSqlite3Module::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FNSqlite3Module::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNSqlite3Module, NSqlite3)