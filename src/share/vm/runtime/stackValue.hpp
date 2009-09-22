#ifdef USE_PRAGMA_IDENT_HDR
#pragma ident "@(#)stackValue.hpp       1.37 07/05/24 14:38:39 JVM"
#endif
/*
 * Copyright 1997-2005 Sun Microsystems, Inc.  All Rights Reserved.
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

class StackValue : public ResourceObj {
 private:
  BasicType _type;
  intptr_t  _i; // Blank java stack slot value
  Handle    _o; // Java stack slot value interpreted as a Handle
 public:

  StackValue(intptr_t value) {
    _type  = T_INT;
    _i     = value;
  }

  StackValue(Handle value) {
    _type    = T_OBJECT;
    _o       = value;
  }

  StackValue() {
    _type   = T_CONFLICT;
    _i      = 0;
  }

  // Only used during deopt- preserve object type.
  StackValue(intptr_t o, BasicType t) {
    assert(t == T_OBJECT, "should not be used");
    _type   = t;
    _i      = o;
  }

  Handle get_obj() const {
    assert(type() == T_OBJECT, "type check");
    return _o;
  }

  void set_obj(Handle value) {
    assert(type() == T_OBJECT, "type check");
    _o = value;
  }

  intptr_t get_int() const {
    assert(type() == T_INT, "type check");
    return _i;
  }

  // For special case in deopt.
  intptr_t get_int(BasicType t) const {
    assert(t == T_OBJECT && type() == T_OBJECT, "type check");
    return _i;
  }

  void set_int(intptr_t value) {
    assert(type() == T_INT, "type check");
    _i = value;
  }

  BasicType type() const { return  _type; }

  bool equal(StackValue *value) {
    if (_type != value->_type) return false;
    if (_type == T_OBJECT)
      return (_o == value->_o);
    else {
      assert(_type == T_INT, "sanity check");
      // [phh] compare only low addressed portions of intptr_t slots
      return (*(int *)&_i == *(int *)&value->_i);
    }
  }

  static StackValue* create_stack_value(const frame* fr, const RegisterMap* reg_map, ScopeValue* sv);
  static BasicLock*  resolve_monitor_lock(const frame* fr, Location location);

#ifndef PRODUCT
 public:
  // Printing
  void print_on(outputStream* st) const;
#endif
};
