//
//  SqliteMgr.h
//  OCStudy2
//

#import <Foundation/Foundation.h>
#import "sqlite3.h"

@interface SqliteMgr : NSObject {
    sqlite3* _db;
}

+ (instancetype) GetInstance;
- (BOOL) OpenDB : (NSString*) dbPath;
- (BOOL) CloseDB;
- (BOOL) Execute : (NSString*) sql;
- (NSArray*) Query : (NSString*) sql;
- (NSDictionary*) QueryFirst : (NSString*)sql;
- (double) Count : (NSString*)sql;

- (NSDictionary*) stmt2Dict : (sqlite3_stmt*) stmt;

@end
