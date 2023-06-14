//
//  SqliteMgr.m
//  OCStudy2
//

#import <Foundation/Foundation.h>
#import "SqliteMgr.h"

@implementation SqliteMgr {
    
}

static SqliteMgr* instance;

+ (instancetype) GetInstance {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[self alloc] init];
    });
    return instance;
}

- (BOOL) OpenDB:(NSString *)dbPath {
    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
    NSString *DBPath = [documentPath stringByAppendingPathComponent:dbPath];
    NSLog(@"数据库路径%@", DBPath);
    int r = sqlite3_open_v2([DBPath UTF8String], &_db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, nil);
    if (r == SQLITE_OK)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

- (BOOL) CloseDB {
    int r = sqlite3_close(_db);
    if (r == SQLITE_OK)
    {
        _db = nil;
        return TRUE;
    }
    const char * errormsg = sqlite3_errmsg(_db);
    NSLog(@"error: %s", errormsg);
    return FALSE;
}

- (BOOL) Execute:(NSString *)sql {
    int r = sqlite3_exec(_db, [sql UTF8String], nil, nil, nil);
    return r == SQLITE_OK;
}

- (NSArray*) Query : (NSString*) sql{
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(_db, [sql UTF8String], -1, &stmt, nil) != SQLITE_OK)
    {
        NSLog(@"Query failed%@", sql);
        sqlite3_finalize(stmt);
        return NULL;
    }
    NSMutableArray* results = [[NSMutableArray alloc] init];
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        [results addObject: [self stmt2Dict:stmt]];
    }
    sqlite3_finalize(stmt);
    return results;
}

- (NSDictionary*) QueryFirst:(NSString *)sql {
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(_db, [sql UTF8String], -1, &stmt, nil) != SQLITE_OK)
    {
        NSLog(@"Query failed%@", sql);
        sqlite3_finalize(stmt);
        return NULL;
    }
    NSDictionary* result = NULL;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = [self stmt2Dict:stmt];
    }
    sqlite3_finalize(stmt);
    return result;
}

- (double) Count:(NSString *)sql {
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(_db, [sql UTF8String], -1, &stmt, nil) != SQLITE_OK)
    {
        NSLog(@"Query failed%@", sql);
        sqlite3_finalize(stmt);
        return 0;
    }
    double result = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_double(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return result;
}

- (NSDictionary*) stmt2Dict:(sqlite3_stmt *) stmt {
    int columnCount = sqlite3_column_count(stmt);
    NSMutableDictionary* row = [[NSMutableDictionary alloc] init];
    for (int i=0; i < columnCount; i++)
    {
        const char* name = sqlite3_column_name(stmt, i);
        int type = sqlite3_column_type(stmt, i);
        switch (type)
        {
            case SQLITE_INTEGER:
            {
                int Value = sqlite3_column_int(stmt, i);
                row[[NSString stringWithUTF8String:name]] = @(Value);
                break;
            }
            case SQLITE_FLOAT:
            {
                double Value = sqlite3_column_double(stmt, i);
                row[[NSString stringWithUTF8String:name]] = @(Value);
                break;
            }
            case SQLITE_TEXT:
            default:
            {
                const char* Value = (const char*)sqlite3_column_text(stmt, i);
                row[[NSString stringWithUTF8String:name]] = [NSString stringWithUTF8String:Value];
                break;
            }
        }
    }
    return row;
}
@end
