#ifdef USE_PRAGMA_IDENT_SRC
#pragma ident "@(#)c1_CFGPrinter.hpp    1.7 07/05/05 17:05:05 JVM"
#endif
/*
 * Copyright 2005 Sun Microsystems, Inc.  All Rights Reserved.
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

#ifndef PRODUCT

// This is a utility class used for recording the results of a
// compilation for later analysis.

class CFGPrinterOutput;
class IntervalList;

class CFGPrinter : public AllStatic {
private:
  static CFGPrinterOutput* _output;
public:
  static CFGPrinterOutput* output() { assert(_output != NULL, ""); return _output; }


  static void print_compilation(Compilation* compilation);
  static void print_cfg(BlockList* blocks, const char* name, bool do_print_HIR, bool do_print_LIR);
  static void print_cfg(IR* blocks, const char* name, bool do_print_HIR, bool do_print_LIR);
  static void print_intervals(IntervalList* intervals, const char* name);
};

#endif
