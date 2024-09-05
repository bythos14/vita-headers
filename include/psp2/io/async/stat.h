#ifndef _PSP2_IO_ASYNC_STAT_H_
#define _PSP2_IO_ASYNC_STAT_H_

#include <psp2/types.h>
#include <psp2common/kernel/iofilemgr.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Make a directory file (async)
 *
 * @param dir - The path to the directory
 * @param mode - Access mode (One or more ::SceIoAccessMode).
 * @param asyncParam - Asynchronous op parameters
 * 
 * @return an async event ID, < 0 on error
 */
SceUID sceIoMkdirAsync(const char *dir, SceMode mode, SceIoAsyncParam *asyncParam);

/**
 * Remove a directory file (async)
 *
 * @param path - Removes a directory file pointed by the string path
 * @param asyncParam - Asynchronous op parameters
 * 
 * @return an async event ID, < 0 on error
 */
SceUID sceIoRmdirAsync(const char *path, SceIoAsyncParam *asyncParam);

/**
 * Get the status of a file. (async)
 *
 * @param file - The path to the file.
 * @param stat - A pointer to a ::SceIoStat structure.
 * @param asyncParam - Asynchronous op parameters
 *
 * @return an async event ID, < 0 on error
 */
SceUID sceIoGetstatAsync(const char *file, SceIoStat *stat, SceIoAsyncParam *asyncParam);

/**
 * Get the status of a file descriptor. (async)
 *
 * @param fd - The file descriptor.
 * @param stat - A pointer to a ::SceIoStat structure.
 * @param asyncParam - Asynchronous op parameters
 *
 * @return an async event ID, < 0 on error
 */
SceUID sceIoGetstatByFdAsync(SceUID fd, SceIoStat *stat, SceIoAsyncParam *asyncParam);

/**
 * Change the status of a file. (async)
 *
 * @param file - The path to the file.
 * @param stat - A pointer to a ::SceIoStat structure.
 * @param bits - Bitmask defining which bits to change.
 * @param asyncParam - Asynchronous op parameters
 *
 * @return an async event ID, < 0 on error
 */
SceUID sceIoChstatAsync(const char *file, SceIoStat *stat, int bits, SceIoAsyncParam *asyncParam);

/**
 * Change the status of a file descriptor. (async)
 *
 * @param fd - The file descriptor.
 * @param stat - A pointer to an io_stat_t structure.
 * @param bits - Bitmask defining which bits to change.
 * @param asyncParam - Asynchronous op parameters
 *
 * @return an async event ID, < 0 on error
 */
SceUID sceIoChstatByFdAsync(SceUID fd, const SceIoStat *buf, unsigned int cbit, SceIoAsyncParam *asyncParam);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_ASYNC_STAT_H_ */

