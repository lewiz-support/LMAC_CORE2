// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vaxilite_dev_v1_0_H_
#define _Vaxilite_dev_v1_0_H_

#include "systemc.h"
#include "verilated_sc.h"
#include "verilated.h"

class Vaxilite_dev_v1_0__Syms;

//----------

SC_MODULE(Vaxilite_dev_v1_0) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    sc_in<bool> s00_axi_aclk;
    sc_in<bool> s00_axi_aresetn;
    sc_in<bool> s00_axi_awvalid;
    sc_out<bool> s00_axi_awready;
    sc_in<bool> s00_axi_wvalid;
    sc_out<bool> s00_axi_wready;
    sc_out<bool> s00_axi_bvalid;
    sc_in<bool> s00_axi_bready;
    sc_in<bool> s00_axi_arvalid;
    sc_out<bool> s00_axi_arready;
    sc_out<bool> s00_axi_rvalid;
    sc_in<bool> s00_axi_rready;
    sc_in<sc_bv<4> > s00_axi_awaddr;
    sc_in<sc_bv<3> > s00_axi_awprot;
    sc_in<sc_bv<32> > s00_axi_wdata;
    sc_in<sc_bv<4> > s00_axi_wstrb;
    sc_out<sc_bv<2> > s00_axi_bresp;
    sc_in<sc_bv<4> > s00_axi_araddr;
    sc_in<sc_bv<3> > s00_axi_arprot;
    sc_out<sc_bv<32> > s00_axi_rdata;
    sc_out<sc_bv<2> > s00_axi_rresp;
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    VL_SIG8(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr,3,0);
    VL_SIG8(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready,0,0);
    VL_SIG8(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_wready,0,0);
    VL_SIG8(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bresp,1,0);
    VL_SIG8(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid,0,0);
    VL_SIG8(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_araddr,3,0);
    VL_SIG8(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready,0,0);
    VL_SIG8(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rresp,1,0);
    VL_SIG8(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid,0,0);
    VL_SIG8(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__aw_en,0,0);
    VL_SIG(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rdata,31,0);
    VL_SIG(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg0,31,0);
    VL_SIG(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg1,31,0);
    VL_SIG(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg2,31,0);
    VL_SIG(axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg3,31,0);
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    VL_SIG8(__Vcellinp__axilite_dev_v1_0__s00_axi_aclk,0,0);
    VL_SIG8(__Vcellinp__axilite_dev_v1_0__s00_axi_rready,0,0);
    VL_SIG8(__Vcellinp__axilite_dev_v1_0__s00_axi_arvalid,0,0);
    VL_SIG8(__Vcellinp__axilite_dev_v1_0__s00_axi_araddr,3,0);
    VL_SIG8(__Vcellinp__axilite_dev_v1_0__s00_axi_bready,0,0);
    VL_SIG8(__Vcellinp__axilite_dev_v1_0__s00_axi_wvalid,0,0);
    VL_SIG8(__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb,3,0);
    VL_SIG8(__Vcellinp__axilite_dev_v1_0__s00_axi_awvalid,0,0);
    VL_SIG8(__Vcellinp__axilite_dev_v1_0__s00_axi_awaddr,3,0);
    VL_SIG8(__Vcellinp__axilite_dev_v1_0__s00_axi_aresetn,0,0);
    VL_SIG8(__Vclklast__TOP____Vcellinp__axilite_dev_v1_0__s00_axi_aclk,0,0);
    VL_SIG(__Vcellinp__axilite_dev_v1_0__s00_axi_wdata,31,0);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vaxilite_dev_v1_0__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    
    // CONSTRUCTORS
  private:
    Vaxilite_dev_v1_0& operator= (const Vaxilite_dev_v1_0&);  ///< Copying not allowed
    Vaxilite_dev_v1_0(const Vaxilite_dev_v1_0&);  ///< Copying not allowed
  public:
    SC_CTOR(Vaxilite_dev_v1_0);
    virtual ~Vaxilite_dev_v1_0();
    
    // API METHODS
  private:
    void eval();
  public:
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vaxilite_dev_v1_0__Syms* symsp, bool first);
  private:
    static QData _change_request(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp);
    static void _combo__TOP__4(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset();
  public:
    static void _eval(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp);
    static void _eval_settle(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp);
    static void _sequent__TOP__3(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif // guard
