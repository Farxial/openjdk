#ifdef USE_PRAGMA_IDENT_HDR
#pragma ident "@(#)jvm_windows.h        1.24 07/05/05 17:04:43 JVM"
#endif
/*
 * Copyright 1998-2005 Sun Microsystems, Inc.  All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
 * CA 95054 USA or visit www.sun.com if you need additional information or
 * have any questions.
 *
 */

#ifndef _JAVASOFT_JVM_MD_H_
#define _JAVASOFT_JVM_MD_H_

/*
 * This file is currently collecting system-specific dregs for the
 * JNI conversion, which should be sorted out later.
 */

#include <windows.h>
// #include <windef.h>
// #include <winbase.h>


// #include "jni.h"

#define JNI_ONLOAD_SYMBOLS      {"_JNI_OnLoad@8", "JNI_OnLoad"}
#define JNI_ONUNLOAD_SYMBOLS    {"_JNI_OnUnload@8", "JNI_OnUnload"}
#define JVM_ONLOAD_SYMBOLS      {"_JVM_OnLoad@12", "JVM_OnLoad"}
#define AGENT_ONLOAD_SYMBOLS    {"_Agent_OnLoad@12", "Agent_OnLoad"}
#define AGENT_ONUNLOAD_SYMBOLS  {"_Agent_OnUnload@4", "Agent_OnUnload"}
#define AGENT_ONATTACH_SYMBOLS  {"_Agent_OnAttach@12", "Agent_OnAttach"}

#define JNI_LIB_PREFIX ""
#define JNI_LIB_SUFFIX ".dll"

struct dirent {
    char d_name[MAX_PATH];
};

typedef struct {
    struct dirent dirent;
    char *path;
    HANDLE handle;
    WIN32_FIND_DATA find_data;
} DIR;

#include <stdlib.h>

#define JVM_MAXPATHLEN _MAX_PATH

#define JVM_R_OK    4
#define JVM_W_OK    2
#define JVM_X_OK    1
#define JVM_F_OK    0

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void * JNICALL
JVM_GetThreadInterruptEvent();

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

/*
 * File I/O
 */

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <errno.h>

/* O Flags */

#define JVM_O_RDONLY     O_RDONLY
#define JVM_O_WRONLY     O_WRONLY
#define JVM_O_RDWR       O_RDWR
#define JVM_O_O_APPEND   O_APPEND
#define JVM_O_EXCL       O_EXCL
#define JVM_O_CREAT      O_CREAT
#define JVM_O_DELETE     O_TEMPORARY

/* Signals */

#define JVM_SIGINT     SIGINT
#define JVM_SIGTERM    SIGTERM

#define SHUTDOWN1_SIGNAL SIGINT            /* Shutdown Hooks support.    */
#define SHUTDOWN2_SIGNAL SIGTERM

#endif /* !_JAVASOFT_JVM_MD_H_ */
