// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vlmac_wrapper_top__Syms_H_
#define _Vlmac_wrapper_top__Syms_H_

#include "verilated.h"

// INCLUDE MODULE CLASSES
#include "Vlmac_wrapper_top.h"

// SYMS CLASS
class Vlmac_wrapper_top__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vlmac_wrapper_top*             TOPp;
    
    // CREATORS
    Vlmac_wrapper_top__Syms(Vlmac_wrapper_top* topp, const char* namep);
    ~Vlmac_wrapper_top__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(64);

#endif // guard
