// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vapb_timer_H_
#define _Vapb_timer_H_

#include "systemc.h"
#include "verilated_sc.h"
#include "verilated.h"

class Vapb_timer__Syms;

//----------

SC_MODULE(Vapb_timer) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_in<bool> psel;
    sc_in<bool> penable;
    sc_in<bool> pwrite;
    sc_out<bool> pready;
    sc_out<bool> irq;
    sc_in<sc_bv<16> > paddr;
    sc_in<sc_bv<32> > pwdata;
    sc_out<sc_bv<32> > prdata;
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    VL_SIG8(apb_slave_timer__DOT__tmr_cfg,1,0);
    VL_SIG(apb_slave_timer__DOT__tmr_cnt,31,0);
    VL_SIG(apb_slave_timer__DOT__tmr_div,31,0);
    VL_SIG(apb_slave_timer__DOT__tmr_free_cnt,31,0);
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    VL_SIG8(__Vcellinp__apb_slave_timer__clk,0,0);
    VL_SIG8(__Vcellout__apb_slave_timer__pready,0,0);
    VL_SIG8(__Vcellinp__apb_slave_timer__pwrite,0,0);
    VL_SIG8(__Vcellinp__apb_slave_timer__penable,0,0);
    VL_SIG8(__Vcellinp__apb_slave_timer__psel,0,0);
    VL_SIG8(__Vcellinp__apb_slave_timer__rst,0,0);
    VL_SIG8(__Vclklast__TOP____Vcellinp__apb_slave_timer__clk,0,0);
    VL_SIG16(__Vcellinp__apb_slave_timer__paddr,15,0);
    VL_SIG(__Vcellout__apb_slave_timer__prdata,31,0);
    VL_SIG(__Vcellinp__apb_slave_timer__pwdata,31,0);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vapb_timer__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    
    // CONSTRUCTORS
  private:
    Vapb_timer& operator= (const Vapb_timer&);  ///< Copying not allowed
    Vapb_timer(const Vapb_timer&);  ///< Copying not allowed
  public:
    SC_CTOR(Vapb_timer);
    virtual ~Vapb_timer();
    
    // API METHODS
  private:
    void eval();
  public:
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vapb_timer__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vapb_timer__Syms* symsp, bool first);
  private:
    static QData _change_request(Vapb_timer__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vapb_timer__Syms* __restrict vlSymsp);
    static void _combo__TOP__4(Vapb_timer__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset();
  public:
    static void _eval(Vapb_timer__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(Vapb_timer__Syms* __restrict vlSymsp);
    static void _eval_settle(Vapb_timer__Syms* __restrict vlSymsp);
    static void _sequent__TOP__3(Vapb_timer__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vapb_timer__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif // guard
