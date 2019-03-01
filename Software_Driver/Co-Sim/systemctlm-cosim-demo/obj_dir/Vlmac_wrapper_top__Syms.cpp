// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vlmac_wrapper_top__Syms.h"
#include "Vlmac_wrapper_top.h"

// FUNCTIONS
Vlmac_wrapper_top__Syms::Vlmac_wrapper_top__Syms(Vlmac_wrapper_top* topp, const char* namep)
	// Setup locals
	: __Vm_namep(namep)
	, __Vm_didInit(false)
	// Setup submodule names
{
    // Pointer to top level
    TOPp = topp;
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOPp->__Vconfigure(this, true);
}
