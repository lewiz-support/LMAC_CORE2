// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vaxifull_dev_v1_0_H_
#define _Vaxifull_dev_v1_0_H_

#include "systemc.h"
#include "verilated_sc.h"
#include "verilated.h"

class Vaxifull_dev_v1_0__Syms;

//----------

SC_MODULE(Vaxifull_dev_v1_0) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    sc_in<bool> s00_axi_aclk;
    sc_in<bool> s00_axi_aresetn;
    sc_in<bool> s00_axi_awlock;
    sc_in<bool> s00_axi_awvalid;
    sc_out<bool> s00_axi_awready;
    sc_in<bool> s00_axi_wlast;
    sc_in<bool> s00_axi_wvalid;
    sc_out<bool> s00_axi_wready;
    sc_out<bool> s00_axi_bvalid;
    sc_in<bool> s00_axi_bready;
    sc_in<bool> s00_axi_arlock;
    sc_in<bool> s00_axi_arvalid;
    sc_out<bool> s00_axi_arready;
    sc_out<bool> s00_axi_rlast;
    sc_out<bool> s00_axi_rvalid;
    sc_in<bool> s00_axi_rready;
    sc_in<sc_bv<8> > s00_axi_awid;
    sc_in<sc_bv<10> > s00_axi_awaddr;
    sc_in<sc_bv<8> > s00_axi_awlen;
    sc_in<sc_bv<3> > s00_axi_awsize;
    sc_in<sc_bv<2> > s00_axi_awburst;
    sc_in<sc_bv<4> > s00_axi_awcache;
    sc_in<sc_bv<3> > s00_axi_awprot;
    sc_in<sc_bv<4> > s00_axi_awqos;
    sc_in<sc_bv<4> > s00_axi_awregion;
    sc_in<sc_bv<2> > s00_axi_awuser;
    sc_in<sc_bv<128> > s00_axi_wdata;
    sc_in<sc_bv<16> > s00_axi_wstrb;
    sc_in<sc_bv<2> > s00_axi_wuser;
    sc_out<sc_bv<8> > s00_axi_bid;
    sc_out<sc_bv<2> > s00_axi_bresp;
    sc_out<sc_bv<2> > s00_axi_buser;
    sc_in<sc_bv<8> > s00_axi_arid;
    sc_in<sc_bv<10> > s00_axi_araddr;
    sc_in<sc_bv<8> > s00_axi_arlen;
    sc_in<sc_bv<3> > s00_axi_arsize;
    sc_in<sc_bv<2> > s00_axi_arburst;
    sc_in<sc_bv<4> > s00_axi_arcache;
    sc_in<sc_bv<3> > s00_axi_arprot;
    sc_in<sc_bv<4> > s00_axi_arqos;
    sc_in<sc_bv<4> > s00_axi_arregion;
    sc_in<sc_bv<2> > s00_axi_aruser;
    sc_out<sc_bv<8> > s00_axi_rid;
    sc_out<sc_bv<128> > s00_axi_rdata;
    sc_out<sc_bv<2> > s00_axi_rresp;
    sc_out<sc_bv<2> > s00_axi_ruser;
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awready,0,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready,0,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bresp,1,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_buser,0,-1);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid,0,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arready,0,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rresp,1,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast,0,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_ruser,0,-1);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid,0,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__aw_wrap_en,0,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__ar_wrap_en,0,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag,0,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag,0,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen_cntr,7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen_cntr,7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arburst,1,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awburst,1,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen,7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen,7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address,7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren,0,0);
    VL_SIG16(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr,9,0);
    VL_SIG16(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr,9,0);
    VL_SIG(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__aw_wrap_size,31,0);
    VL_SIG(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__ar_wrap_size,31,0);
    VL_SIGW(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out[1],127,0,4);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__0__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__1__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__2__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__3__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__4__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__5__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__6__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__7__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__8__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__9__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__10__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__11__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__12__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__13__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__14__KET____DOT__byte_ram[513],7,0);
    VL_SIG8(axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__15__KET____DOT__byte_ram[513],7,0);
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    VL_SIG8(__Vcellinp__axifull_dev_v1_0__s00_axi_aclk,0,0);
    VL_SIG8(__Vcellinp__axifull_dev_v1_0__s00_axi_rready,0,0);
    VL_SIG8(__Vcellinp__axifull_dev_v1_0__s00_axi_arvalid,0,0);
    VL_SIG8(__Vcellinp__axifull_dev_v1_0__s00_axi_arburst,1,0);
    VL_SIG8(__Vcellinp__axifull_dev_v1_0__s00_axi_arlen,7,0);
    VL_SIG8(__Vcellinp__axifull_dev_v1_0__s00_axi_arid,7,0);
    VL_SIG8(__Vcellinp__axifull_dev_v1_0__s00_axi_bready,0,0);
    VL_SIG8(__Vcellinp__axifull_dev_v1_0__s00_axi_wvalid,0,0);
    VL_SIG8(__Vcellinp__axifull_dev_v1_0__s00_axi_wlast,0,0);
    VL_SIG8(__Vcellinp__axifull_dev_v1_0__s00_axi_awvalid,0,0);
    VL_SIG8(__Vcellinp__axifull_dev_v1_0__s00_axi_awburst,1,0);
    VL_SIG8(__Vcellinp__axifull_dev_v1_0__s00_axi_awlen,7,0);
    VL_SIG8(__Vcellinp__axifull_dev_v1_0__s00_axi_awid,7,0);
    VL_SIG8(__Vcellinp__axifull_dev_v1_0__s00_axi_aresetn,0,0);
    VL_SIG8(__Vclklast__TOP____Vcellinp__axifull_dev_v1_0__s00_axi_aclk,0,0);
    VL_SIG16(__Vcellinp__axifull_dev_v1_0__s00_axi_araddr,9,0);
    VL_SIG16(__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb,15,0);
    VL_SIG16(__Vcellinp__axifull_dev_v1_0__s00_axi_awaddr,9,0);
    VL_SIGW(__Vcellinp__axifull_dev_v1_0__s00_axi_wdata,127,0,4);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vaxifull_dev_v1_0__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    
    // CONSTRUCTORS
  private:
    Vaxifull_dev_v1_0& operator= (const Vaxifull_dev_v1_0&);  ///< Copying not allowed
    Vaxifull_dev_v1_0(const Vaxifull_dev_v1_0&);  ///< Copying not allowed
  public:
    SC_CTOR(Vaxifull_dev_v1_0);
    virtual ~Vaxifull_dev_v1_0();
    
    // API METHODS
  private:
    void eval();
  public:
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vaxifull_dev_v1_0__Syms* symsp, bool first);
  private:
    static QData _change_request(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp);
    static void _combo__TOP__4(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset();
  public:
    static void _eval(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp);
    static void _eval_settle(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp);
    static void _sequent__TOP__3(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(128);

#endif // guard
