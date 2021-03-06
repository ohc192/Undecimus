//
//  utils.h
//  Undecimus
//
//  Created by Sam Bingner on 11/23/18.
//  Copyright © 2018 - 2019 Pwn20wnd. All rights reserved.
//

#ifndef utils_h
#define utils_h
#import <sys/types.h>
#import <sys/stat.h>

#define system(x) _system(x)

#define DEFAULT_VERSION_STRING "Hacked"

#define empty_list 0
#define multi_path 1
#define async_wake 2
#define deja_xnu 3
#define necp 4

int proc_pidpath(pid_t pid, void *buffer, uint32_t buffersize);

static inline bool create_file_data(const char *file, int owner, mode_t mode, NSData *data) {
    return [[NSFileManager defaultManager] createFileAtPath:@(file) contents:data attributes:@{
               NSFileOwnerAccountID: @(owner),
               NSFileGroupOwnerAccountID: @(owner),
               NSFilePosixPermissions: @(mode)
            }
        ];
}

static inline bool create_file(const char *file, int owner, mode_t mode) {
    return create_file_data(file, owner, mode, nil);
}

static inline bool clean_file(const char *file) {
    NSString *path = @(file);
    if ([[NSFileManager defaultManager] attributesOfItemAtPath:path error:nil]) {
        return [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
    }
    return YES;
}

static inline bool init_file(const char *file, int owner, mode_t mode) {
    NSString *path = @(file);
    return ([[NSFileManager defaultManager] fileExistsAtPath:path] &&
            [[NSFileManager defaultManager] setAttributes:@{
                    NSFileOwnerAccountID: @(owner),
                    NSFileGroupOwnerAccountID: @(owner),
                    NSFilePosixPermissions: @(mode)
                } ofItemAtPath:path error:nil]);
}

int sha1_to_str(const unsigned char *hash, size_t hashlen, char *buf, size_t buflen);
NSString *sha1sum(NSString *file);
bool verifySha1Sums(NSString *sumFile);
int _system(const char *cmd);
int systemf(const char *cmd, ...);
bool debIsInstalled(char *packageID);
bool debIsConfigured(char *packageID);
bool compareInstalledVersion(const char *packageID, const char *op, const char *version);
bool installDeb(char *debName, bool forceDeps);
bool installDebs(NSArray <NSString*> *debs, bool forceDeps);
bool pidFileIsValid(NSString *pidfile);
bool pspawnHookLoaded(void);
bool is_symlink(const char *filename);
bool is_directory(const char *filename);
bool ensure_directory(const char *directory, int owner, mode_t mode);
bool ensure_symlink(const char *to, const char *from);
bool mode_is(const char *filename, mode_t mode);
int runCommandv(const char *cmd, int argc, const char * const*argv);
int runCommand(const char *cmd, ...);
NSString *pathForResource(NSString *resource);
pid_t pidOfProcess(const char *name);
bool kernelVersionContains(const char *string);
bool multi_path_tcp_enabled(void);
bool jailbreakEnabled(void);
bool supportsExploit(NSInteger exploit);
bool jailbreakSupported(void);
bool respringSupported(void);
bool restartSupported(void);
NSInteger recommendedJailbreakSupport(void);
NSInteger recommendedRestartSupport(void);
NSInteger recommendedRespringSupport(void);
bool daemonIsLoaded(char *daemonID);
NSString *getBundledResources(void);

extern NSData *lastSystemOutput;

#endif /* utils_h */
