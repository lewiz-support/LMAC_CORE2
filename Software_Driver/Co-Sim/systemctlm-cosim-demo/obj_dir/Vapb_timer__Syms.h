// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vapb_timer__Syms_H_
#define _Vapb_timer__Syms_H_

#include "verilated.h"

// INCLUDE MODULE CLASSES
#include "Vapb_timer.h"

// SYMS CLASS
class Vapb_timer__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vapb_timer*                    TOPp;
    
    // CREATORS
    Vapb_timer__Syms(Vapb_timer* topp, const char* namep);
    ~Vapb_timer__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(64);

#endif // guard
