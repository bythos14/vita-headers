#ifndef _PSP2_IO_ASYNC_EVENT_H_
#define _PSP2_IO_ASYNC_EVENT_H_

#include <psp2/types.h>
#include <psp2common/kernel/iofilemgr.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Release the event associated with the asynchronous operation.
 *
 * @param evId - The event ID associated with the operation.
 *
 * @return < 0 on error.
 */
int sceIoComplete(SceUID evId);

/**
 * Release multiple events associated with asynchronous operations.
 *
 * @param evIds       - The event IDs associated with the operations.
 * @param eventCount  - Number of event IDs in evIds.
 * @param numComplete - The number of events complete and released.
 *
 * @return < 0 on error.
 */
int sceIoCompleteMultiple(SceUID *evIds, SceUInt eventNum, SceUInt *numComplete);

/**
 * Cancel an asynchronous operation.
 *
 * @param evId - The event ID associated with the async op.
 *
 * @return < 0 on error.
 */
int sceIoCancel(SceUID evId);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_IO_ASYNC_EVENT_H_ */

