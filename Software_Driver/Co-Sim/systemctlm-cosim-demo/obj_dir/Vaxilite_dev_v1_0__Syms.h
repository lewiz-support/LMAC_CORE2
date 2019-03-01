// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vaxilite_dev_v1_0__Syms_H_
#define _Vaxilite_dev_v1_0__Syms_H_

#include "verilated.h"

// INCLUDE MODULE CLASSES
#include "Vaxilite_dev_v1_0.h"

// SYMS CLASS
class Vaxilite_dev_v1_0__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vaxilite_dev_v1_0*             TOPp;
    
    // CREATORS
    Vaxilite_dev_v1_0__Syms(Vaxilite_dev_v1_0* topp, const char* namep);
    ~Vaxilite_dev_v1_0__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(64);

#endif // guard
