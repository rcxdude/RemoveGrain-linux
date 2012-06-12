#ifndef __WINNT_LINUX_H__
#define __WINNT_LINUX_H__

#include "basicDataTypeConversions.h"

namespace avxsynth {

/////////////////////////////////
// Copied from Windows WinNT.h
/////////////////////////////////

#define NTSTATUS LONG
#define STATUS_NO_MEMORY                 ((NTSTATUS)0xC0000017L)    // winnt
#define STATUS_NONCONTINUABLE_EXCEPTION  ((NTSTATUS)0xC0000025L)    // winnt
#define STATUS_INVALID_DISPOSITION       ((NTSTATUS)0xC0000026L)    // winnt
#define STATUS_ACCESS_VIOLATION         0xC0000005
#define STATUS_ARRAY_BOUNDS_EXCEEDED    0xC000008C
#define STATUS_BAD_COMPRESSION_BUFFER   0xC0000242
#define STATUS_BREAKPOINT               0x80000003
#define STATUS_CALLBACK_POP_STACK       0xC0000423
#define STATUS_DATATYPE_MISALIGNMENT    0x80000002
#define STATUS_FLOAT_DENORMAL_OPERAND   0xC000008D
#define STATUS_FLOAT_DIVIDE_BY_ZERO     0xC000008E
#define STATUS_FLOAT_INEXACT_RESULT     0xC000008F
#define STATUS_FLOAT_INVALID_OPERATION  0xC0000090
#define STATUS_FLOAT_OVERFLOW           0xC0000091
#define STATUS_FLOAT_STACK_CHECK        0xC0000092
#define STATUS_FLOAT_UNDERFLOW          0xC0000093
#define STATUS_FLOAT_MULTIPLE_FAULTS    0xC00002B4
#define STATUS_FLOAT_MULTIPLE_TRAPS     0xC00002B5
#define STATUS_GUARD_PAGE_VIOLATION     0x80000001
#define STATUS_ILLEGAL_FLOAT_CONTEXT    0xC000014A
#define STATUS_ILLEGAL_INSTRUCTION      0xC000001D
#define STATUS_INSTRUCTION_MISALIGNMENT 0xC00000AA
#define STATUS_INVALID_HANDLE           0xC0000008
#define STATUS_INVALID_LOCK_SEQUENCE    0xC000001E
#define STATUS_INVALID_OWNER            0xC000005A
#define STATUS_INVALID_PARAMETER        0xC000000D
#define STATUS_INVALID_PARAMETER_1      0xC00000EF
#define STATUS_INVALID_SYSTEM_SERVICE   0xC000001C
#define STATUS_INVALID_THREAD           0xC000071C
#define STATUS_INTEGER_DIVIDE_BY_ZERO   0xC0000094
#define STATUS_INTEGER_OVERFLOW         0xC0000095
#define STATUS_IN_PAGE_ERROR            0xC0000006
#define STATUS_KERNEL_APC               0x0100
#define STATUS_LONGJUMP                 0x80000026
#define STATUS_NO_CALLBACK_ACTIVE       0xC0000258
#define STATUS_NO_EVENT_PAIR            0xC000014E
#define STATUS_PRIVILEGED_INSTRUCTION   0xC0000096
#define STATUS_SINGLE_STEP              0x80000004
#define STATUS_STACK_BUFFER_OVERRUN     0xC0000409
#define STATUS_STACK_OVERFLOW           0xC00000FD
#define STATUS_SUCCESS                  0x0000
#define STATUS_THREAD_IS_TERMINATING    0xC000004B
#define STATUS_TIMEOUT                  0x0102
#define STATUS_UNWIND                   0xC0000027
#define STATUS_UNWIND_CONSOLIDATE       0x80000029
#define STATUS_USER_APC                 0x00C0H
#define STATUS_WAKE_SYSTEM_DEBUGGER     0x80000007

#define EXCEPTION_MAXIMUM_PARAMETERS 15 // maximum number of exception parameters
typedef struct _EXCEPTION_RECORD {
    DWORD    ExceptionCode;
    DWORD ExceptionFlags;
    struct _EXCEPTION_RECORD *ExceptionRecord;
    PVOID ExceptionAddress;
    DWORD NumberParameters;
    ULONG_PTR ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
} EXCEPTION_RECORD;


}; // namespace avxsynth

#endif //  __WINNT_LINUX_H__
