// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef _OE_SYS_TIME_H
#define _OE_SYS_TIME_H

#include <openenclave/bits/defs.h>
#include <openenclave/bits/types.h>

OE_EXTERNC_BEGIN

struct oe_timeval
{
    time_t tv_sec;       /* seconds */
    suseconds_t tv_usec; /* microseconds */
};

struct oe_timespec
{
    time_t tv_sec; /* seconds */
    long tv_nsec;  /* nanoseconds */
};

#if defined(OE_NEED_STDC_NAMES)

struct timeval
{
    time_t tv_sec;       /* seconds */
    suseconds_t tv_usec; /* microseconds */
};

struct timespec
{
    time_t tv_sec; /* seconds */
    long tv_nsec;  /* nanoseconds */
};

#endif /* defined(OE_NEED_STDC_NAMES) */

OE_EXTERNC_END

#endif /* _OE_SYS_TIME_H */
