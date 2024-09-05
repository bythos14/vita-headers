#ifndef _PSP2_IO_FCNTL_H_
#define _PSP2_IO_FCNTL_H_

#include <psp2/types.h>
#include <psp2common/kernel/iofilemgr.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Open or create a file for reading or writing (async)
 *
 * @param file - Pointer to a string holding the name of the file to open.
 * @param flags - Libc styled flags that are or'ed together (One or more ::SceIoMode).
 * @param mode - One or more ::SceIoAccessMode flags or'ed together. Can also use Unix absolute permissions.
 * @param asyncParam - Asynchronous op parameters
 * 
 * @return an async event ID, < 0 on error.
 */
SceUID sceIoOpenAsync(const char *file, int flags, SceMode mode, SceIoAsyncParam *asyncParam);

/**
 * Delete a descriptor (async)
 *
 * @param fd - File descriptor to close
 * @param asyncParam - Asynchronous op parameters
 * 
 * @return an async event ID, < 0 on error
 */
SceUID sceIoCloseAsync(SceUID fd, SceIoAsyncParam *asyncParam);

/**
 * Read input (async)
 *
 * @param fd    - Opened file descriptor to read from
 * @param buf   - Pointer to the buffer where the read data will be placed
 * @param nbyte - Size of the read in bytes
 * @param asyncParam - Asynchronous op parameters
 *
 * @return an async event ID, < 0 on error
 */
SceUID sceIoReadAsync(SceUID fd, void *buf, SceSize nbyte, SceIoAsyncParam *asyncParam);

/**
 * Read input at offset (async)
 *
 * @param fd - Opened file descriptor to read from
 * @param data - Pointer to the buffer where the read data will be placed
 * @param size - Size of the read in bytes
 * @param offset - Offset to read
 * @param asyncParam - Asynchronous op parameters
 *
 * @return an async event ID, < 0 on error
 */
SceUID sceIoPreadAsync(SceUID fd, void *data, SceSize size, SceOff offset, SceIoAsyncParam *asyncParam);

/**
 * Write output (async)
 *
 * @param fd    - Opened file descriptor to write to
 * @param buf   - Pointer to the data to write
 * @param nbyte - Size of data to write
 * @param asyncParam - Asynchronous op parameters
 *
 * @return an async event ID, < 0 on error
 */
SceUID sceIoWriteAsync(SceUID fd, const void *buf, SceSize nbyte, SceIoAsyncParam *asyncParam);

/**
 * Write output at offset (async)
 *
 * @param fd - Opened file descriptor to write to
 * @param data - Pointer to the data to write
 * @param size - Size of data to write
 * @param offset - Offset to write
 * @param asyncParam - Asynchronous op parameters
 *
 * @return an async event ID, < 0 on error
 */
SceUID sceIoPwriteAsync(SceUID fd, const void *data, SceSize size, SceOff offset, SceIoAsyncParam *asyncParam);

/**
 * Reposition read/write file descriptor offset (async)
 *
 * @param fd - Opened file descriptor with which to seek
 * @param offset - Relative offset from the start position given by whence
 * @param whence - One of ::SceIoSeekMode.
 * @param asyncParam - Asynchronous op parameters
 *
 * @return an async event ID, < 0 on error
 */
SceUID sceIoLseekAsync(SceUID fd, SceOff offset, int whence, SceIoAsyncParam *asyncParam);

/**
 * Remove directory entry (async)
 *
 * @param file - Path to the file to remove
 * @param asyncParam - Asynchronous op parameters
 * 
 * @return an async event ID, < 0 on error
 */
SceUID sceIoRemoveAsync(const char *file, SceIoAsyncParam *asyncParam);

/**
 * Change the name of a file (async)
 *
 * @param oldname - The old filename
 * @param newname - The new filename
 * @param asyncParam - Asynchronous op parameters
 * 
 * @return an async event ID, < 0 on error.
 */
SceUID sceIoRenameAsync(const char *oldname, const char *newname, SceIoAsyncParam *asyncParam);

/**
 * Synchronize the file data on the device.
 *
 * @param device - The device to synchronize (e.g. msfat0:)
 * @param unk - Unknown
 * @param asyncParam - Asynchronous op parameters
 * 
 * @return an async event ID, < 0 on error.
 */
SceUID sceIoSyncAsync(const char *device, unsigned int unk, SceIoAsyncParam *param);

/**
 * Synchronize the file data for one file (async)
 *
 * @param fd   - Opened file descriptor to sync
 * @param flag - unknown
 *
 * @return an async event ID, < 0 on error.
 */
SceUID sceIoSyncByFdAsync(SceUID fd, int flag, SceIoAsyncParam *param);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_FCNTL_H_ */

