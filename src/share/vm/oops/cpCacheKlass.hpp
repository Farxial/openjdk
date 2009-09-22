#ifdef USE_PRAGMA_IDENT_HDR
#pragma ident "@(#)cpCacheKlass.hpp     1.33 07/05/29 09:44:19 JVM"
#endif
/*
 * Copyright 1998-2008 Sun Microsystems, Inc.  All Rights Reserved.
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

class constantPoolCacheKlass: public Klass {
  juint    _alloc_size;        // allocation profiling support
 public:
  // Dispatched klass operations
  bool oop_is_constantPoolCache() const          { return true; }
  int  oop_size(oop obj) const;
  int  klass_oop_size() const                    { return object_size(); }

  // Allocation
  DEFINE_ALLOCATE_PERMANENT(constantPoolCacheKlass);
  constantPoolCacheOop allocate(int length, TRAPS);
  static klassOop create_klass(TRAPS);

  // Casting from klassOop
  static constantPoolCacheKlass* cast(klassOop k) {
    assert(k->klass_part()->oop_is_constantPoolCache(), "cast to constantPoolCacheKlass");
    return (constantPoolCacheKlass*)k->klass_part();
  }

  // Sizing
  static int header_size()       { return oopDesc::header_size() + sizeof(constantPoolCacheKlass)/HeapWordSize; }
  int object_size() const        { return align_object_size(header_size()); }

  // Garbage collection
  void oop_follow_contents(oop obj);
  int oop_adjust_pointers(oop obj);

  // Parallel Scavenge and Parallel Old
  PARALLEL_GC_DECLS

  // Iterators
  int oop_oop_iterate(oop obj, OopClosure* blk);
  int oop_oop_iterate_m(oop obj, OopClosure* blk, MemRegion mr);

  // Allocation profiling support
  juint alloc_size() const              { return _alloc_size; }
  void set_alloc_size(juint n)          { _alloc_size = n; }

#ifndef PRODUCT
 public:
  // Printing
  void oop_print_on(oop obj, outputStream* st);
#endif

 public:
  // Verification
  const char* internal_name() const;
  void oop_verify_on(oop obj, outputStream* st);
};
