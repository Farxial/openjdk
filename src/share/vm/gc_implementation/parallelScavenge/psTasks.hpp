#ifdef USE_PRAGMA_IDENT_HDR
#pragma ident "@(#)psTasks.hpp  1.21 07/05/05 17:05:29 JVM"
#endif
/*
 * Copyright 2002-2005 Sun Microsystems, Inc.  All Rights Reserved.
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

//
// psTasks.hpp is a collection of GCTasks used by the
// parallelScavenge collector.
//

class GCTask;
class OopClosure;
class OopStack;
class ObjectStartArray;
class ParallelTaskTerminator;
class MutableSpace;
class PSOldGen;
class Thread;
class VMThread;

//
// ScavengeRootsTask
//
// This task scans all the roots of a given type.
//
//

class ScavengeRootsTask : public GCTask {
 public:
  enum RootType {
    universe              = 1,
    jni_handles           = 2,
    threads               = 3,
    object_synchronizer   = 4,
    flat_profiler         = 5,
    system_dictionary     = 6,
    management            = 7,
    jvmti                 = 8
  };
 private:
  RootType _root_type;
 public:
  ScavengeRootsTask(RootType value) : _root_type(value) {}

  char* name() { return (char *)"scavenge-roots-task"; }

  virtual void do_it(GCTaskManager* manager, uint which);
};

//
// ThreadRootsTask
//
// This task scans the roots of a single thread. This task
// enables scanning of thread roots in parallel.
//

class ThreadRootsTask : public GCTask {
 private:
  JavaThread* _java_thread;
  VMThread* _vm_thread;
 public:
  ThreadRootsTask(JavaThread* root) : _java_thread(root), _vm_thread(NULL) {}
  ThreadRootsTask(VMThread* root) : _java_thread(NULL), _vm_thread(root) {}

  char* name() { return (char *)"thread-roots-task"; }

  virtual void do_it(GCTaskManager* manager, uint which);
};

//
// StealTask
//
// This task is used to distribute work to idle threads.
//

class StealTask : public GCTask {
 private:
   ParallelTaskTerminator* const _terminator;
 public:
  char* name() { return (char *)"steal-task"; }

  StealTask(ParallelTaskTerminator* t);

  ParallelTaskTerminator* terminator() { return _terminator; }

  virtual void do_it(GCTaskManager* manager, uint which);
};

//
// SerialOldToYoungRootsTask
//
// This task is used to scan for roots in the perm gen

class SerialOldToYoungRootsTask : public GCTask {
 private:
  PSOldGen* _gen;
  HeapWord* _gen_top;

 public:
  SerialOldToYoungRootsTask(PSOldGen *gen, HeapWord* gen_top) :
    _gen(gen), _gen_top(gen_top) { }

  char* name() { return (char *)"serial-old-to-young-roots-task"; }

  virtual void do_it(GCTaskManager* manager, uint which);
};

//
// OldToYoungRootsTask
//
// This task is used to scan old to young roots in parallel

class OldToYoungRootsTask : public GCTask {
 private:
  PSOldGen* _gen;
  HeapWord* _gen_top;
  uint _stripe_number;

 public:
  OldToYoungRootsTask(PSOldGen *gen, HeapWord* gen_top, uint stripe_number) :
    _gen(gen), _gen_top(gen_top), _stripe_number(stripe_number) { }

  char* name() { return (char *)"old-to-young-roots-task"; }

  virtual void do_it(GCTaskManager* manager, uint which);
};
