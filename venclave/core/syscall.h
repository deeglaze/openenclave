// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef _VE_ENCLAVE_SYSCALL_H
#define _VE_ENCLAVE_SYSCALL_H

#include "common.h"

/* Supported syscalls. */
#if defined(__x86_64__)
#define VE_SYS_read 0
#define VE_SYS_write 1
#define VE_SYS_close 3
#define VE_SYS_brk 12
#define VE_SYS_rt_sigaction 13
#define VE_SYS_ioctl 16
#define VE_SYS_pipe 22
#define VE_SYS_shmat 30
#define VE_SYS_dup 32
#define VE_SYS_getpid 39
#define VE_SYS_recvmsg 47
#define VE_SYS_socketpair 53
#define VE_SYS_fork 57
#define VE_SYS_execve 59
#define VE_SYS_exit 60
#define VE_SYS_wait4 61
#define VE_SYS_kill 62
#define VE_SYS_nanosleep 35
#define VE_SYS_getrlimit 97
#define VE_SYS_arch_prctl 158
#define VE_SYS_gettid 186
#define VE_SYS_tkill 200
#define VE_SYS_futex 202
#define VE_SYS_clock_gettime 228
#define VE_SYS_tgkill 234
#endif

long ve_syscall0(long n);

long ve_syscall1(long n, long x1);

long ve_syscall2(long n, long x1, long x2);

long ve_syscall3(long n, long x1, long x2, long x3);

long ve_syscall4(long n, long x1, long x2, long x3, long x4);

long ve_syscall5(long n, long x1, long x2, long x3, long x4, long x5);

long ve_syscall6(long n, long x1, long x2, long x3, long x4, long x5, long x6);

#endif /* _VE_ENCLAVE_SYSCALL_H */
