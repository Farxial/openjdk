#ifdef USE_PRAGMA_IDENT_HDR
#pragma ident "@(#)prefetch.hpp 1.9 07/05/05 17:06:53 JVM"
#endif
/*
 * Copyright 2003 Sun Microsystems, Inc.  All Rights Reserved.
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

// If calls to prefetch methods are in a loop, the loop should be cloned
// such that if Prefetch{Scan,Copy}Interval and/or PrefetchFieldInterval
// say not to do prefetching, these methods aren't called.  At the very
// least, they take up a memory issue slot.  They should be implemented
// as inline assembly code: doing an actual call isn't worth the cost.

class Prefetch : AllStatic {
 public:
  enum style {
    do_none,  // Do no prefetching
    do_read,  // Do read prefetching
    do_write  // Do write prefetching
  };

  // Prefetch anticipating read; must not fault, semantically a no-op
  static void read(void* loc, intx interval);

  // Prefetch anticipating write; must not fault, semantically a no-op
  static void write(void* loc, intx interval);
};
