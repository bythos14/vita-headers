#ifndef _PSP2_IO_ASYNC_DIRENT_H_
#define _PSP2_IO_ASYNC_DIRENT_H_

#include <psp2/types.h>
#include <psp2common/kernel/iofilemgr.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Open a directory (async)
 * 
 * @param dirname - The directory to open for reading.
 * @param asyncParam - Asynchronous op parameters
 * 
 * @return an async event ID, < 0 on error
 */
SceUID sceIoDopenAsync(const char *dirname, SceIoAsyncParam *asyncParam);

/**
 * Reads an entry from an opened file descriptor. (async)
 *
 * @param fd - Already opened file descriptor (using ::sceIoDopen)
 * @param dir - Pointer to a ::SceIoDirent structure to hold the file information
 * @param asyncParam - Asynchronous op parameters
 *
 * @return an async event ID, < 0 on error
 */
SceUID sceIoDreadAsync(SceUID fd, SceIoDirent *dir, SceIoAsyncParam *asyncParam);

/**
 * Close an opened directory file descriptor (async)
 *
 * @param fd - Already opened file descriptor (using ::sceIoDopen)
 * @param asyncParam - Asynchronous op parameters
 * 
 * @return an async event ID, < 0 on error
 */
SceUID sceIoDcloseAsync(SceUID fd, SceIoAsyncParam *asyncParam);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_DIRENT_H_ */

