// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxifull_dev_v1_0.h for the primary calling header

#include "Vaxifull_dev_v1_0.h" // For This
#include "Vaxifull_dev_v1_0__Syms.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_SC_CTOR_IMP(Vaxifull_dev_v1_0)
#if (SYSTEMC_VERSION>20011000)
    : s00_axi_aclk("s00_axi_aclk"), s00_axi_aresetn("s00_axi_aresetn"), 
      s00_axi_awlock("s00_axi_awlock"), s00_axi_awvalid("s00_axi_awvalid"), 
      s00_axi_awready("s00_axi_awready"), s00_axi_wlast("s00_axi_wlast"), 
      s00_axi_wvalid("s00_axi_wvalid"), s00_axi_wready("s00_axi_wready"), 
      s00_axi_bvalid("s00_axi_bvalid"), s00_axi_bready("s00_axi_bready"), 
      s00_axi_arlock("s00_axi_arlock"), s00_axi_arvalid("s00_axi_arvalid"), 
      s00_axi_arready("s00_axi_arready"), s00_axi_rlast("s00_axi_rlast"), 
      s00_axi_rvalid("s00_axi_rvalid"), s00_axi_rready("s00_axi_rready"), 
      s00_axi_awid("s00_axi_awid"), s00_axi_awaddr("s00_axi_awaddr"), 
      s00_axi_awlen("s00_axi_awlen"), s00_axi_awsize("s00_axi_awsize"), 
      s00_axi_awburst("s00_axi_awburst"), s00_axi_awcache("s00_axi_awcache"), 
      s00_axi_awprot("s00_axi_awprot"), s00_axi_awqos("s00_axi_awqos"), 
      s00_axi_awregion("s00_axi_awregion"), s00_axi_awuser("s00_axi_awuser"), 
      s00_axi_wdata("s00_axi_wdata"), s00_axi_wstrb("s00_axi_wstrb"), 
      s00_axi_wuser("s00_axi_wuser"), s00_axi_bid("s00_axi_bid"), 
      s00_axi_bresp("s00_axi_bresp"), s00_axi_buser("s00_axi_buser"), 
      s00_axi_arid("s00_axi_arid"), s00_axi_araddr("s00_axi_araddr"), 
      s00_axi_arlen("s00_axi_arlen"), s00_axi_arsize("s00_axi_arsize"), 
      s00_axi_arburst("s00_axi_arburst"), s00_axi_arcache("s00_axi_arcache"), 
      s00_axi_arprot("s00_axi_arprot"), s00_axi_arqos("s00_axi_arqos"), 
      s00_axi_arregion("s00_axi_arregion"), s00_axi_aruser("s00_axi_aruser"), 
      s00_axi_rid("s00_axi_rid"), s00_axi_rdata("s00_axi_rdata"), 
      s00_axi_rresp("s00_axi_rresp"), s00_axi_ruser("s00_axi_ruser")
#endif
 {
    Vaxifull_dev_v1_0__Syms* __restrict vlSymsp = __VlSymsp = new Vaxifull_dev_v1_0__Syms(this, name());
    Vaxifull_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Sensitivities on all clocks and combo inputs
    SC_METHOD(eval);
    sensitive << s00_axi_aclk;
    sensitive << s00_axi_aresetn;
    sensitive << s00_axi_awid;
    sensitive << s00_axi_awaddr;
    sensitive << s00_axi_awlen;
    sensitive << s00_axi_awburst;
    sensitive << s00_axi_awvalid;
    sensitive << s00_axi_wdata;
    sensitive << s00_axi_wstrb;
    sensitive << s00_axi_wlast;
    sensitive << s00_axi_wvalid;
    sensitive << s00_axi_bready;
    sensitive << s00_axi_arid;
    sensitive << s00_axi_araddr;
    sensitive << s00_axi_arlen;
    sensitive << s00_axi_arburst;
    sensitive << s00_axi_arvalid;
    sensitive << s00_axi_rready;
    
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vaxifull_dev_v1_0::__Vconfigure(Vaxifull_dev_v1_0__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vaxifull_dev_v1_0::~Vaxifull_dev_v1_0() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void Vaxifull_dev_v1_0::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vaxifull_dev_v1_0::eval\n"); );
    Vaxifull_dev_v1_0__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vaxifull_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    while (VL_LIKELY(__Vchange)) {
	VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (VL_UNLIKELY(++__VclockLoop > 100)) VL_FATAL_MT(__FILE__,__LINE__,__FILE__,"Verilated model didn't converge");
    }
}

void Vaxifull_dev_v1_0::_eval_initial_loop(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    int __VclockLoop = 0;
    QData __Vchange = 1;
    while (VL_LIKELY(__Vchange)) {
	_eval_settle(vlSymsp);
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (VL_UNLIKELY(++__VclockLoop > 100)) VL_FATAL_MT(__FILE__,__LINE__,__FILE__,"Verilated model didn't DC converge");
    }
}

//--------------------
// Internal Methods

VL_INLINE_OPT void Vaxifull_dev_v1_0::_combo__TOP__1(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxifull_dev_v1_0::_combo__TOP__1\n"); );
    Vaxifull_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISW(8,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_arid, vlTOPp->s00_axi_arid);
    VL_ASSIGN_ISW(8,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awid, vlTOPp->s00_axi_awid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_aclk, vlTOPp->s00_axi_aclk);
    VL_ASSIGN_SWI(8,vlTOPp->s00_axi_rid, vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_arid);
    VL_ASSIGN_SWI(8,vlTOPp->s00_axi_bid, vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awid);
}

void Vaxifull_dev_v1_0::_settle__TOP__2(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxifull_dev_v1_0::_settle__TOP__2\n"); );
    Vaxifull_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIGW(__Vtemp3,127,0,4);
    // Body
    VL_ASSIGN_ISW(8,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_arid, vlTOPp->s00_axi_arid);
    VL_ASSIGN_ISW(8,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awid, vlTOPp->s00_axi_awid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_aclk, vlTOPp->s00_axi_aclk);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_rready, vlTOPp->s00_axi_rready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_arvalid, vlTOPp->s00_axi_arvalid);
    VL_ASSIGN_ISW(2,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_arburst, vlTOPp->s00_axi_arburst);
    VL_ASSIGN_ISW(8,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_arlen, vlTOPp->s00_axi_arlen);
    VL_ASSIGN_ISW(10,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_araddr, vlTOPp->s00_axi_araddr);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_bready, vlTOPp->s00_axi_bready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wlast, vlTOPp->s00_axi_wlast);
    VL_ASSIGN_ISW(16,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb, vlTOPp->s00_axi_wstrb);
    VL_ASSIGN_WSW(128,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata, vlTOPp->s00_axi_wdata);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awvalid, vlTOPp->s00_axi_awvalid);
    VL_ASSIGN_ISW(2,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awburst, vlTOPp->s00_axi_awburst);
    VL_ASSIGN_ISW(8,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awlen, vlTOPp->s00_axi_awlen);
    VL_ASSIGN_ISW(10,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awaddr, vlTOPp->s00_axi_awaddr);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_aresetn, vlTOPp->s00_axi_aresetn);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wvalid, vlTOPp->s00_axi_wvalid);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_rvalid, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid);
    VL_ASSIGN_SWI(2,vlTOPp->s00_axi_ruser, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_ruser);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_rlast, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast);
    VL_ASSIGN_SWI(2,vlTOPp->s00_axi_rresp, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rresp);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_arready, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arready);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_bvalid, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid);
    VL_ASSIGN_SWI(2,vlTOPp->s00_axi_buser, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_buser);
    VL_ASSIGN_SWI(2,vlTOPp->s00_axi_bresp, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bresp);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_wready, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_awready, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awready);
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__aw_wrap_size 
	= ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen) 
	   << 4U);
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__ar_wrap_size 
	= ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen) 
	   << 4U);
    __Vtemp3[0U] = ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid)
		     ? vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
		    [0U][0U] : 0U);
    __Vtemp3[1U] = ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid)
		     ? vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
		    [0U][1U] : 0U);
    __Vtemp3[2U] = ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid)
		     ? vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
		    [0U][2U] : 0U);
    __Vtemp3[3U] = ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid)
		     ? vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
		    [0U][3U] : 0U);
    VL_ASSIGN_SWW(128,vlTOPp->s00_axi_rdata, __Vtemp3);
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__aw_wrap_en 
	= (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr) 
	    & ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen) 
	       << 4U)) == ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen) 
			   << 4U));
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__ar_wrap_en 
	= (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr) 
	    & ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen) 
	       << 4U)) == ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen) 
			   << 4U));
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address 
	= (0xffU & ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag)
		     ? (0xffU & ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr) 
				 >> 4U)) : ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag)
					     ? (0xffU 
						& ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr) 
						   >> 4U))
					     : 0U)));
    VL_ASSIGN_SWI(8,vlTOPp->s00_axi_rid, vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_arid);
    VL_ASSIGN_SWI(8,vlTOPp->s00_axi_bid, vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awid);
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren 
	= ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready) 
	   & (IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wvalid));
}

VL_INLINE_OPT void Vaxifull_dev_v1_0::_sequent__TOP__3(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxifull_dev_v1_0::_sequent__TOP__3\n"); );
    Vaxifull_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awready,0,0);
    VL_SIG8(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag,0,0);
    VL_SIG8(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awburst,1,0);
    VL_SIG8(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen,7,0);
    VL_SIG8(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen_cntr,7,0);
    VL_SIG8(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready,0,0);
    VL_SIG8(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid,0,0);
    VL_SIG8(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arready,0,0);
    VL_SIG8(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag,0,0);
    VL_SIG8(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arburst,1,0);
    VL_SIG8(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen,7,0);
    VL_SIG8(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen_cntr,7,0);
    VL_SIG8(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast,0,0);
    VL_SIG8(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__0__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__0__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v0,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v0,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__1__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__1__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v1,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v1,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v1,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__2__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__2__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v2,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v2,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v2,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__3__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__3__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v3,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v3,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v3,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__4__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__4__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v4,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v4,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v4,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__5__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__5__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v5,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v5,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v5,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__6__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__6__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v6,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v6,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v6,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__7__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__7__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v7,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v7,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v7,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__8__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__8__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v8,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v8,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v8,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__9__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__9__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v9,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v9,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v9,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__10__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__10__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v10,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v10,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v10,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__11__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__11__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v11,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v11,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v11,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__12__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__12__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v12,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v12,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v12,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__13__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__13__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v13,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v13,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v13,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__14__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__14__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v14,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v14,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v14,0,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__15__KET____DOT__byte_ram__v0,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__15__KET____DOT__byte_ram__v0,0,0);
    VL_SIG8(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v15,6,0);
    VL_SIG8(__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v15,7,0);
    VL_SIG8(__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v15,0,0);
    VL_SIG16(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr,9,0);
    VL_SIG16(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__0__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__1__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__2__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__3__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__4__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__5__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__6__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__7__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__8__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__9__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__10__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__11__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__12__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__13__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__14__KET____DOT__byte_ram__v0,9,0);
    VL_SIG16(__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__15__KET____DOT__byte_ram__v0,9,0);
    VL_SIGW(__Vtemp6,127,0,4);
    // Body
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__0__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__1__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__2__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__3__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__4__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__5__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__6__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__7__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__8__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__9__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__10__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__11__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__12__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__13__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__14__KET____DOT__byte_ram__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__15__KET____DOT__byte_ram__v0 = 0U;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awready 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awready;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arready 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arready;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awburst 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awburst;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen_cntr 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen_cntr;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arburst 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arburst;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen_cntr 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen_cntr;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen;
    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr 
	= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v0 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v1 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v2 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v3 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v4 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v5 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v6 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v7 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v8 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v9 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v10 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v11 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v12 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v13 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v14 = 0U;
    __Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v15 = 0U;
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:353
    if (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_aresetn) {
	if ((((~ (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready)) 
	      & (IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wvalid)) 
	     & (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag))) {
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready = 1U;
	} else {
	    if (((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wlast) 
		 & (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready))) {
		__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready = 0U;
	    }
	}
    } else {
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready = 0U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:527
    if (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_aresetn) {
	if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) 
	     & (~ (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid)))) {
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid = 1U;
	    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rresp = 0U;
	} else {
	    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid) 
		 & (IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_rready))) {
		__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid = 0U;
	    }
	}
    } else {
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid = 0U;
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rresp = 0U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:380
    if (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_aresetn) {
	if ((((((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag) 
		& (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready)) 
	       & (IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wvalid)) 
	      & (~ (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid))) 
	     & (IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wlast))) {
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid = 1U;
	    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bresp = 0U;
	} else {
	    if (((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_bready) 
		 & (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid))) {
		__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid = 0U;
	    }
	}
    } else {
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid = 0U;
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bresp = 0U;
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_buser = 0U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & (IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__0__KET____DOT__byte_ram__v0 
	    = (0xffU & vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[0U]);
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__0__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__0__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 1U))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__1__KET____DOT__byte_ram__v0 
	    = (0xffU & ((vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[1U] 
			 << 0x18U) | (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[0U] 
				      >> 8U)));
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__1__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__1__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 2U))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__2__KET____DOT__byte_ram__v0 
	    = (0xffU & ((vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[1U] 
			 << 0x10U) | (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[0U] 
				      >> 0x10U)));
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__2__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__2__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 3U))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__3__KET____DOT__byte_ram__v0 
	    = (0xffU & ((vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[1U] 
			 << 8U) | (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[0U] 
				   >> 0x18U)));
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__3__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__3__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 4U))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__4__KET____DOT__byte_ram__v0 
	    = (0xffU & vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[1U]);
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__4__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__4__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 5U))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__5__KET____DOT__byte_ram__v0 
	    = (0xffU & ((vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[2U] 
			 << 0x18U) | (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[1U] 
				      >> 8U)));
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__5__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__5__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 6U))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__6__KET____DOT__byte_ram__v0 
	    = (0xffU & ((vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[2U] 
			 << 0x10U) | (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[1U] 
				      >> 0x10U)));
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__6__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__6__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 7U))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__7__KET____DOT__byte_ram__v0 
	    = (0xffU & ((vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[2U] 
			 << 8U) | (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[1U] 
				   >> 0x18U)));
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__7__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__7__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 8U))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__8__KET____DOT__byte_ram__v0 
	    = (0xffU & vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[2U]);
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__8__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__8__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 9U))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__9__KET____DOT__byte_ram__v0 
	    = (0xffU & ((vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[3U] 
			 << 0x18U) | (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[2U] 
				      >> 8U)));
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__9__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__9__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 0xaU))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__10__KET____DOT__byte_ram__v0 
	    = (0xffU & ((vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[3U] 
			 << 0x10U) | (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[2U] 
				      >> 0x10U)));
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__10__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__10__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 0xbU))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__11__KET____DOT__byte_ram__v0 
	    = (0xffU & ((vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[3U] 
			 << 8U) | (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[2U] 
				   >> 0x18U)));
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__11__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__11__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 0xcU))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__12__KET____DOT__byte_ram__v0 
	    = (0xffU & vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[3U]);
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__12__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__12__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 0xdU))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__13__KET____DOT__byte_ram__v0 
	    = (0xffU & (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[3U] 
			>> 8U));
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__13__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__13__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 0xeU))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__14__KET____DOT__byte_ram__v0 
	    = (0xffU & (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[3U] 
			>> 0x10U));
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__14__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__14__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:582
    if (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren) 
	 & ((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb) 
	    >> 0xfU))) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__15__KET____DOT__byte_ram__v0 
	    = (0xffU & (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata[3U] 
			>> 0x18U));
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__15__KET____DOT__byte_ram__v0 = 1U;
	__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__15__KET____DOT__byte_ram__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:254
    if (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_aresetn) {
	if (((((~ (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awready)) 
	       & (IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awvalid)) 
	      & (~ (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag))) 
	     & (~ (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag)))) {
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awready = 1U;
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag = 1U;
	} else {
	    if (((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wlast) 
		 & (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready))) {
		__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag = 0U;
	    } else {
		__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awready = 0U;
	    }
	}
    } else {
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awready = 0U;
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag = 0U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:415
    if (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_aresetn) {
	if (((((~ (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arready)) 
	       & (IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_arvalid)) 
	      & (~ (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag))) 
	     & (~ (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag)))) {
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arready = 1U;
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag = 1U;
	} else {
	    if ((((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid) 
		  & (IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_rready)) 
		 & ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen_cntr) 
		    == (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen)))) {
		__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag = 0U;
	    } else {
		__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arready = 0U;
	    }
	}
    } else {
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arready = 0U;
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag = 0U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:287
    if (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_aresetn) {
	if ((((~ (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awready)) 
	      & (IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awvalid)) 
	     & (~ (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag)))) {
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr 
		= vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awaddr;
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awburst 
		= vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awburst;
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen 
		= vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awlen;
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen_cntr = 0U;
	} else {
	    if (((((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen_cntr) 
		   <= (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen)) 
		  & (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready)) 
		 & (IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wvalid))) {
		__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen_cntr 
		    = (0xffU & ((IData)(1U) + (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen_cntr)));
		if ((0U == (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awburst))) {
		    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr 
			= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr;
		} else {
		    if ((1U == (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awburst))) {
			__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr 
			    = ((0xfU & (IData)(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr)) 
			       | (0x3f0U & (((IData)(1U) 
					     + ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr) 
						>> 4U)) 
					    << 4U)));
			__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr 
			    = (0x3f0U & (IData)(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr));
		    } else {
			if ((2U == (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awburst))) {
			    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__aw_wrap_en) {
				__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr 
				    = (0x3ffU & ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr) 
						 - vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__aw_wrap_size));
			    } else {
				__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr 
				    = ((0xfU & (IData)(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr)) 
				       | (0x3f0U & 
					  (((IData)(1U) 
					    + ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr) 
					       >> 4U)) 
					   << 4U)));
				__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr 
				    = (0x3f0U & (IData)(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr));
			    }
			} else {
			    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr 
				= (0x3ffU & ((IData)(1U) 
					     + (0x3fU 
						& ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr) 
						   >> 4U))));
			}
		    }
		}
	    }
	}
    } else {
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr = 0U;
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen_cntr = 0U;
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awburst = 0U;
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen = 0U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:444
    if (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_aresetn) {
	if ((((~ (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arready)) 
	      & (IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_arvalid)) 
	     & (~ (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag)))) {
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr 
		= vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_araddr;
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arburst 
		= vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_arburst;
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen 
		= vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_arlen;
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen_cntr = 0U;
	    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast = 0U;
	} else {
	    if (((((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen_cntr) 
		   <= (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen)) 
		  & (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid)) 
		 & (IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_rready))) {
		__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen_cntr 
		    = (0xffU & ((IData)(1U) + (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen_cntr)));
		if ((0U == (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arburst))) {
		    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr 
			= vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr;
		} else {
		    if ((1U == (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arburst))) {
			__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr 
			    = ((0xfU & (IData)(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr)) 
			       | (0x3f0U & (((IData)(1U) 
					     + ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr) 
						>> 4U)) 
					    << 4U)));
			__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr 
			    = (0x3f0U & (IData)(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr));
		    } else {
			if ((2U == (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arburst))) {
			    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__ar_wrap_en) {
				__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr 
				    = (0x3ffU & ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr) 
						 - vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__ar_wrap_size));
			    } else {
				__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr 
				    = ((0xfU & (IData)(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr)) 
				       | (0x3f0U & 
					  (((IData)(1U) 
					    + ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr) 
					       >> 4U)) 
					   << 4U)));
				__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr 
				    = (0x3f0U & (IData)(__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr));
			    }
			} else {
			    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr 
				= (0x3ffU & ((IData)(1U) 
					     + (0x3fU 
						& ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr) 
						   >> 4U))));
			}
		    }
		}
		__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast = 0U;
	    } else {
		if (((((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen_cntr) 
		       == (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen)) 
		      & (~ (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast))) 
		     & (IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag))) {
		    __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast = 1U;
		} else {
		    if (vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_rready) {
			__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast = 0U;
		    }
		}
	    }
	}
    } else {
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr = 0U;
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen_cntr = 0U;
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arburst = 0U;
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen = 0U;
	__Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast = 0U;
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_ruser = 0U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v0 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__0__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v0 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v0 = 0U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v1 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__1__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v1 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v1 = 8U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v2 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__2__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v2 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v2 = 0x10U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v3 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__3__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v3 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v3 = 0x18U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v4 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__4__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v4 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v4 = 0x20U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v5 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__5__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v5 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v5 = 0x28U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v6 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__6__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v6 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v6 = 0x30U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v7 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__7__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v7 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v7 = 0x38U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v8 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__8__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v8 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v8 = 0x40U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v9 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__9__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v9 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v9 = 0x48U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v10 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__10__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v10 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v10 = 0x50U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v11 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__11__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v11 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v11 = 0x58U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v12 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__12__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v12 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v12 = 0x60U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v13 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__13__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v13 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v13 = 0x68U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v14 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__14__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v14 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v14 = 0x70U;
    }
    // ALWAYS at axifull_dev_v1_0_S00_AXI.v:590
    if (vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag) {
	__Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v15 
	    = vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__15__KET____DOT__byte_ram
	    [vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address];
	__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v15 = 1U;
	__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v15 = 0x78U;
    }
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid;
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen_cntr 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen_cntr;
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awburst 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awburst;
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awready 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awready;
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag;
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen;
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready;
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr;
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arburst 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arburst;
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen_cntr 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen_cntr;
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast;
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arready 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arready;
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen;
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid;
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr;
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__0__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__0__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__0__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__0__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__1__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__1__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__1__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__1__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__2__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__2__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__2__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__2__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__3__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__3__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__3__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__3__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__4__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__4__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__4__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__4__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__5__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__5__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__5__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__5__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__6__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__6__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__6__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__6__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__7__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__7__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__7__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__7__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__8__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__8__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__8__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__8__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__9__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__9__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__9__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__9__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__10__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__10__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__10__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__10__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__11__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__11__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__11__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__11__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__12__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__12__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__12__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__12__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__13__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__13__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__13__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__13__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__14__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__14__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__14__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__14__KET____DOT__byte_ram__v0;
    }
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:586
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__15__KET____DOT__byte_ram__v0) {
	vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__15__KET____DOT__byte_ram[__Vdlyvdim0__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__15__KET____DOT__byte_ram__v0] 
	    = __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__15__KET____DOT__byte_ram__v0;
    }
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag 
	= __Vdly__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag;
    // ALWAYSPOST at axifull_dev_v1_0_S00_AXI.v:594
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v0) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v0), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v0);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v1) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v1), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v1);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v2) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v2), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v2);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v3) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v3), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v3);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v4) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v4), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v4);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v5) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v5), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v5);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v6) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v6), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v6);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v7) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v7), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v7);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v8) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v8), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v8);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v9) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v9), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v9);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v10) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v10), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v10);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v11) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v11), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v11);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v12) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v12), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v12);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v13) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v13), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v13);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v14) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v14), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v14);
    }
    if (__Vdlyvset__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v15) {
	VL_ASSIGNSEL_WIII(8,(IData)(__Vdlyvlsb__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v15), 
			  vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
			  [0U], __Vdlyvval__axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out__v15);
    }
    VL_ASSIGN_SWI(2,vlTOPp->s00_axi_rresp, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rresp);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_bvalid, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid);
    VL_ASSIGN_SWI(2,vlTOPp->s00_axi_bresp, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bresp);
    VL_ASSIGN_SWI(2,vlTOPp->s00_axi_buser, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_buser);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_awready, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awready);
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__aw_wrap_size 
	= ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen) 
	   << 4U);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_wready, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready);
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__aw_wrap_en 
	= (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr) 
	    & ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen) 
	       << 4U)) == ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen) 
			   << 4U));
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_rlast, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_arready, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arready);
    VL_ASSIGN_SWI(2,vlTOPp->s00_axi_ruser, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_ruser);
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__ar_wrap_size 
	= ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen) 
	   << 4U);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_rvalid, vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid);
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__ar_wrap_en 
	= (((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr) 
	    & ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen) 
	       << 4U)) == ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen) 
			   << 4U));
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address 
	= (0xffU & ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag)
		     ? (0xffU & ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr) 
				 >> 4U)) : ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag)
					     ? (0xffU 
						& ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr) 
						   >> 4U))
					     : 0U)));
    __Vtemp6[0U] = ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid)
		     ? vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
		    [0U][0U] : 0U);
    __Vtemp6[1U] = ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid)
		     ? vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
		    [0U][1U] : 0U);
    __Vtemp6[2U] = ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid)
		     ? vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
		    [0U][2U] : 0U);
    __Vtemp6[3U] = ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid)
		     ? vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out
		    [0U][3U] : 0U);
    VL_ASSIGN_SWW(128,vlTOPp->s00_axi_rdata, __Vtemp6);
}

VL_INLINE_OPT void Vaxifull_dev_v1_0::_combo__TOP__4(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxifull_dev_v1_0::_combo__TOP__4\n"); );
    Vaxifull_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_bready, vlTOPp->s00_axi_bready);
    VL_ASSIGN_ISW(16,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wstrb, vlTOPp->s00_axi_wstrb);
    VL_ASSIGN_WSW(128,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wdata, vlTOPp->s00_axi_wdata);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wlast, vlTOPp->s00_axi_wlast);
    VL_ASSIGN_ISW(10,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awaddr, vlTOPp->s00_axi_awaddr);
    VL_ASSIGN_ISW(2,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awburst, vlTOPp->s00_axi_awburst);
    VL_ASSIGN_ISW(8,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awlen, vlTOPp->s00_axi_awlen);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_awvalid, vlTOPp->s00_axi_awvalid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wvalid, vlTOPp->s00_axi_wvalid);
    VL_ASSIGN_ISW(10,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_araddr, vlTOPp->s00_axi_araddr);
    VL_ASSIGN_ISW(2,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_arburst, vlTOPp->s00_axi_arburst);
    VL_ASSIGN_ISW(8,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_arlen, vlTOPp->s00_axi_arlen);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_arvalid, vlTOPp->s00_axi_arvalid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_rready, vlTOPp->s00_axi_rready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_aresetn, vlTOPp->s00_axi_aresetn);
    vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren 
	= ((IData)(vlTOPp->axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready) 
	   & (IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_wvalid));
}

void Vaxifull_dev_v1_0::_eval(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxifull_dev_v1_0::_eval\n"); );
    Vaxifull_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
    if (((IData)(vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_aclk) 
	 & (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__axifull_dev_v1_0__s00_axi_aclk)))) {
	vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    vlTOPp->_combo__TOP__4(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP____Vcellinp__axifull_dev_v1_0__s00_axi_aclk 
	= vlTOPp->__Vcellinp__axifull_dev_v1_0__s00_axi_aclk;
}

void Vaxifull_dev_v1_0::_eval_initial(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxifull_dev_v1_0::_eval_initial\n"); );
    Vaxifull_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vaxifull_dev_v1_0::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxifull_dev_v1_0::final\n"); );
    // Variables
    Vaxifull_dev_v1_0__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vaxifull_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vaxifull_dev_v1_0::_eval_settle(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxifull_dev_v1_0::_eval_settle\n"); );
    Vaxifull_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

VL_INLINE_OPT QData Vaxifull_dev_v1_0::_change_request(Vaxifull_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxifull_dev_v1_0::_change_request\n"); );
    Vaxifull_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vaxifull_dev_v1_0::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxifull_dev_v1_0::_eval_debug_assertions\n"); );
}
#endif // VL_DEBUG

void Vaxifull_dev_v1_0::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxifull_dev_v1_0::_ctor_var_reset\n"); );
    // Body
    __Vcellinp__axifull_dev_v1_0__s00_axi_rready = VL_RAND_RESET_I(1);
    __Vcellinp__axifull_dev_v1_0__s00_axi_arvalid = VL_RAND_RESET_I(1);
    __Vcellinp__axifull_dev_v1_0__s00_axi_arburst = VL_RAND_RESET_I(2);
    __Vcellinp__axifull_dev_v1_0__s00_axi_arlen = VL_RAND_RESET_I(8);
    __Vcellinp__axifull_dev_v1_0__s00_axi_araddr = VL_RAND_RESET_I(10);
    __Vcellinp__axifull_dev_v1_0__s00_axi_arid = VL_RAND_RESET_I(8);
    __Vcellinp__axifull_dev_v1_0__s00_axi_bready = VL_RAND_RESET_I(1);
    __Vcellinp__axifull_dev_v1_0__s00_axi_wvalid = VL_RAND_RESET_I(1);
    __Vcellinp__axifull_dev_v1_0__s00_axi_wlast = VL_RAND_RESET_I(1);
    __Vcellinp__axifull_dev_v1_0__s00_axi_wstrb = VL_RAND_RESET_I(16);
    VL_RAND_RESET_W(128,__Vcellinp__axifull_dev_v1_0__s00_axi_wdata);
    __Vcellinp__axifull_dev_v1_0__s00_axi_awvalid = VL_RAND_RESET_I(1);
    __Vcellinp__axifull_dev_v1_0__s00_axi_awburst = VL_RAND_RESET_I(2);
    __Vcellinp__axifull_dev_v1_0__s00_axi_awlen = VL_RAND_RESET_I(8);
    __Vcellinp__axifull_dev_v1_0__s00_axi_awaddr = VL_RAND_RESET_I(10);
    __Vcellinp__axifull_dev_v1_0__s00_axi_awid = VL_RAND_RESET_I(8);
    __Vcellinp__axifull_dev_v1_0__s00_axi_aresetn = VL_RAND_RESET_I(1);
    __Vcellinp__axifull_dev_v1_0__s00_axi_aclk = VL_RAND_RESET_I(1);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr = VL_RAND_RESET_I(10);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awready = VL_RAND_RESET_I(1);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_wready = VL_RAND_RESET_I(1);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bresp = VL_RAND_RESET_I(2);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_buser = VL_RAND_RESET_I(2);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid = VL_RAND_RESET_I(1);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_araddr = VL_RAND_RESET_I(10);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arready = VL_RAND_RESET_I(1);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rresp = VL_RAND_RESET_I(2);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rlast = VL_RAND_RESET_I(1);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_ruser = VL_RAND_RESET_I(2);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid = VL_RAND_RESET_I(1);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__aw_wrap_en = VL_RAND_RESET_I(1);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__ar_wrap_en = VL_RAND_RESET_I(1);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__aw_wrap_size = VL_RAND_RESET_I(32);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__ar_wrap_size = VL_RAND_RESET_I(32);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awv_awr_flag = VL_RAND_RESET_I(1);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arv_arr_flag = VL_RAND_RESET_I(1);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen_cntr = VL_RAND_RESET_I(8);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen_cntr = VL_RAND_RESET_I(8);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arburst = VL_RAND_RESET_I(2);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awburst = VL_RAND_RESET_I(2);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_arlen = VL_RAND_RESET_I(8);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__axi_awlen = VL_RAND_RESET_I(8);
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_address = VL_RAND_RESET_I(8);
    { int __Vi0=0; for (; __Vi0<1; ++__Vi0) {
	    VL_RAND_RESET_W(128,axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__mem_data_out[__Vi0]);
    }}
    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__mem_wren = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__0__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__1__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__2__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__3__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__4__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__5__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__6__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__7__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__8__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__9__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__10__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__11__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__12__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__13__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__14__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<513; ++__Vi0) {
	    axifull_dev_v1_0__DOT__axifull_dev_v1_0_S00_AXI_inst__DOT__BRAM_GEN__BRA__0__KET____DOT__BYTE_BRAM_GEN__BRA__15__KET____DOT__byte_ram[__Vi0] = VL_RAND_RESET_I(8);
    }}
    __Vclklast__TOP____Vcellinp__axifull_dev_v1_0__s00_axi_aclk = VL_RAND_RESET_I(1);
}
