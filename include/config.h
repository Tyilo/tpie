// Copyright (c) 1994 Darren Erik Vengroff
//
// File: config.h.in
// Author: Darren Erik Vengroff <darrenv@eecs.umich.edu>
// Created: 10/13/94
//
// $Id: config.h,v 1.1 2004-02-05 17:30:37 jan Exp $
//
#ifndef _CONFIG_H
#define _CONFIG_H

// Define if you have getrusage()
#define HAVE_GETRUSAGE 0

// Define if you have mmap()
#define HAVE_MMAP 0

// Define if asyncronous I/O is avaialable.
#define HAVE_LIBAIO 0

// Define if you have a prototype for mmap()
#define HAVE_PROTOTYPE_MMAP 0

// Define if you have a prototype for munmap()
#define HAVE_PROTOTYPE_MUNMAP 0

// Define if you have a prototype for ftruncate()
#define HAVE_PROTOTYPE_FTRUNCATE 0

// Do we have string.h or strings.h?
#define HAVE_STRING_H 0
#define HAVE_STRINGS_H 0

// Where is unistd.h?
#ifdef _WIN32
#define HAVE_UNISTD_H 0
#define HAVE_SYS_UNISTD_H 0
#else
#define HAVE_UNISTD_H 1
#define HAVE_SYS_UNISTD_H 1
#endif

// Are we on a hacked kernel that supports zero()?
#define HAVE_ZERO 0

#if HAVE_UNISTD_H
#include <unistd.h>
#elif HAVE_SYS_UNISTD_H
#include <sys/unistd.h>
#endif

// On Solaris, _SC_PAGE_SIZE is called _SC_PAGE_SIZE.  Here's a quick
// fix.
#if !defined(_SC_PAGE_SIZE) && defined(_SC_PAGESIZE)
#define _SC_PAGE_SIZE _SC_PAGESIZE
#endif

// Flags to enable or disable various features of the system.

#define TP_ASSERT_APPS 1
#define TP_ASSERT_LIB 1

#define TP_LOG_APPS 1
#define TP_LOG_LIB 1

#endif // _CONFIG_H 