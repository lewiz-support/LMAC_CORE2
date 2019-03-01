// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vaxifull_dev_v1_0__Syms_H_
#define _Vaxifull_dev_v1_0__Syms_H_

#include "verilated.h"

// INCLUDE MODULE CLASSES
#include "Vaxifull_dev_v1_0.h"

// SYMS CLASS
class Vaxifull_dev_v1_0__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vaxifull_dev_v1_0*             TOPp;
    
    // CREATORS
    Vaxifull_dev_v1_0__Syms(Vaxifull_dev_v1_0* topp, const char* namep);
    ~Vaxifull_dev_v1_0__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(64);

#endif // guard
