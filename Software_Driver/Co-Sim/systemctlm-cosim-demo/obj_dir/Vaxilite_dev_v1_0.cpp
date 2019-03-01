// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxilite_dev_v1_0.h for the primary calling header

#include "Vaxilite_dev_v1_0.h" // For This
#include "Vaxilite_dev_v1_0__Syms.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_SC_CTOR_IMP(Vaxilite_dev_v1_0)
#if (SYSTEMC_VERSION>20011000)
    : s00_axi_aclk("s00_axi_aclk"), s00_axi_aresetn("s00_axi_aresetn"), 
      s00_axi_awvalid("s00_axi_awvalid"), s00_axi_awready("s00_axi_awready"), 
      s00_axi_wvalid("s00_axi_wvalid"), s00_axi_wready("s00_axi_wready"), 
      s00_axi_bvalid("s00_axi_bvalid"), s00_axi_bready("s00_axi_bready"), 
      s00_axi_arvalid("s00_axi_arvalid"), s00_axi_arready("s00_axi_arready"), 
      s00_axi_rvalid("s00_axi_rvalid"), s00_axi_rready("s00_axi_rready"), 
      s00_axi_awaddr("s00_axi_awaddr"), s00_axi_awprot("s00_axi_awprot"), 
      s00_axi_wdata("s00_axi_wdata"), s00_axi_wstrb("s00_axi_wstrb"), 
      s00_axi_bresp("s00_axi_bresp"), s00_axi_araddr("s00_axi_araddr"), 
      s00_axi_arprot("s00_axi_arprot"), s00_axi_rdata("s00_axi_rdata"), 
      s00_axi_rresp("s00_axi_rresp")
#endif
 {
    Vaxilite_dev_v1_0__Syms* __restrict vlSymsp = __VlSymsp = new Vaxilite_dev_v1_0__Syms(this, name());
    Vaxilite_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Sensitivities on all clocks and combo inputs
    SC_METHOD(eval);
    sensitive << s00_axi_aclk;
    sensitive << s00_axi_aresetn;
    sensitive << s00_axi_awaddr;
    sensitive << s00_axi_awvalid;
    sensitive << s00_axi_wdata;
    sensitive << s00_axi_wstrb;
    sensitive << s00_axi_wvalid;
    sensitive << s00_axi_bready;
    sensitive << s00_axi_araddr;
    sensitive << s00_axi_arvalid;
    sensitive << s00_axi_rready;
    
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vaxilite_dev_v1_0::__Vconfigure(Vaxilite_dev_v1_0__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vaxilite_dev_v1_0::~Vaxilite_dev_v1_0() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void Vaxilite_dev_v1_0::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vaxilite_dev_v1_0::eval\n"); );
    Vaxilite_dev_v1_0__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vaxilite_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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

void Vaxilite_dev_v1_0::_eval_initial_loop(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp) {
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

VL_INLINE_OPT void Vaxilite_dev_v1_0::_combo__TOP__1(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxilite_dev_v1_0::_combo__TOP__1\n"); );
    Vaxilite_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_aclk, vlTOPp->s00_axi_aclk);
}

void Vaxilite_dev_v1_0::_settle__TOP__2(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxilite_dev_v1_0::_settle__TOP__2\n"); );
    Vaxilite_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_aclk, vlTOPp->s00_axi_aclk);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_rready, vlTOPp->s00_axi_rready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_bready, vlTOPp->s00_axi_bready);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_rvalid, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid);
    VL_ASSIGN_SWI(2,vlTOPp->s00_axi_rresp, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rresp);
    VL_ASSIGN_SWI(32,vlTOPp->s00_axi_rdata, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rdata);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_bvalid, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid);
    VL_ASSIGN_SWI(2,vlTOPp->s00_axi_bresp, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bresp);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_arvalid, vlTOPp->s00_axi_arvalid);
    VL_ASSIGN_ISW(4,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_araddr, vlTOPp->s00_axi_araddr);
    VL_ASSIGN_ISW(4,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb, vlTOPp->s00_axi_wstrb);
    VL_ASSIGN_ISW(32,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata, vlTOPp->s00_axi_wdata);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_arready, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_wready, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_wready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wvalid, vlTOPp->s00_axi_wvalid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_awvalid, vlTOPp->s00_axi_awvalid);
    VL_ASSIGN_ISW(4,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_awaddr, vlTOPp->s00_axi_awaddr);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_aresetn, vlTOPp->s00_axi_aresetn);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_awready, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready);
}

VL_INLINE_OPT void Vaxilite_dev_v1_0::_sequent__TOP__3(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxilite_dev_v1_0::_sequent__TOP__3\n"); );
    Vaxilite_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready,0,0);
    VL_SIG8(__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__aw_en,0,0);
    VL_SIG8(__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_wready,0,0);
    VL_SIG8(__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid,0,0);
    VL_SIG8(__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready,0,0);
    VL_SIG8(__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid,0,0);
    // Body
    __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready 
	= vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready;
    __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_wready 
	= vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_wready;
    __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid 
	= vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid;
    __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__aw_en 
	= vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__aw_en;
    __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready 
	= vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready;
    __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid 
	= vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid;
    // ALWAYS at axilite_dev_v1_0_S00_AXI.v:191
    __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_wready 
	= ((IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_aresetn) 
	   & ((((~ (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_wready)) 
		& (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wvalid)) 
	       & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_awvalid)) 
	      & (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__aw_en)));
    // ALWAYS at axilite_dev_v1_0_S00_AXI.v:346
    if (vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_aresetn) {
	if ((((IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready) 
	      & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_arvalid)) 
	     & (~ (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid)))) {
	    __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid = 1U;
	    vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rresp = 0U;
	} else {
	    if (((IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid) 
		 & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_rready))) {
		__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid = 0U;
	    }
	}
    } else {
	__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid = 0U;
	vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rresp = 0U;
    }
    // ALWAYS at axilite_dev_v1_0_S00_AXI.v:136
    if (vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_aresetn) {
	if (((((~ (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready)) 
	       & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_awvalid)) 
	      & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wvalid)) 
	     & (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__aw_en))) {
	    __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready = 1U;
	    __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__aw_en = 0U;
	} else {
	    if (((IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_bready) 
		 & (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid))) {
		__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__aw_en = 1U;
		__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready = 0U;
	    } else {
		__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready = 0U;
	    }
	}
    } else {
	__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready = 0U;
	__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__aw_en = 1U;
    }
    // ALWAYS at axilite_dev_v1_0_S00_AXI.v:281
    if (vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_aresetn) {
	if ((((((IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready) 
		& (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_awvalid)) 
	       & (~ (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid))) 
	      & (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_wready)) 
	     & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wvalid))) {
	    __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid = 1U;
	    vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bresp = 0U;
	} else {
	    if (((IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_bready) 
		 & (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid))) {
		__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid = 0U;
	    }
	}
    } else {
	__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid = 0U;
	vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bresp = 0U;
    }
    // ALWAYS at axilite_dev_v1_0_S00_AXI.v:386
    if (vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_aresetn) {
	if ((((IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready) 
	      & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_arvalid)) 
	     & (~ (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid)))) {
	    vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rdata 
		= ((8U & (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_araddr))
		    ? ((4U & (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_araddr))
		        ? vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg3
		        : vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg2)
		    : ((4U & (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_araddr))
		        ? vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg1
		        : vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg0));
	}
    } else {
	vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rdata = 0U;
    }
    vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid 
	= __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid;
    vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid 
	= __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid;
    VL_ASSIGN_SWI(2,vlTOPp->s00_axi_rresp, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rresp);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_bvalid, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid);
    VL_ASSIGN_SWI(2,vlTOPp->s00_axi_bresp, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bresp);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_rvalid, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid);
    VL_ASSIGN_SWI(32,vlTOPp->s00_axi_rdata, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rdata);
    // ALWAYS at axilite_dev_v1_0_S00_AXI.v:315
    if (vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_aresetn) {
	if (((~ (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready)) 
	     & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_arvalid))) {
	    __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready = 1U;
	    vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_araddr 
		= vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_araddr;
	} else {
	    __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready = 0U;
	}
    } else {
	__Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready = 0U;
	vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_araddr = 0U;
    }
    // ALWAYS at axilite_dev_v1_0_S00_AXI.v:223
    if (vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_aresetn) {
	if (((((IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_wready) 
	       & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wvalid)) 
	      & (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready)) 
	     & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_awvalid))) {
	    if ((8U & (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr))) {
		if ((4U & (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr))) {
		    if ((1U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg3 
			    = ((0xffffff00U & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg3) 
			       | (0xffU & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		    if ((2U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg3 
			    = ((0xffff00ffU & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg3) 
			       | (0xff00U & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		    if ((4U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg3 
			    = ((0xff00ffffU & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg3) 
			       | (0xff0000U & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		    if ((8U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg3 
			    = ((0xffffffU & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg3) 
			       | (0xff000000U & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		} else {
		    if ((1U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg2 
			    = ((0xffffff00U & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg2) 
			       | (0xffU & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		    if ((2U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg2 
			    = ((0xffff00ffU & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg2) 
			       | (0xff00U & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		    if ((4U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg2 
			    = ((0xff00ffffU & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg2) 
			       | (0xff0000U & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		    if ((8U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg2 
			    = ((0xffffffU & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg2) 
			       | (0xff000000U & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		}
	    } else {
		if ((4U & (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr))) {
		    if ((1U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg1 
			    = ((0xffffff00U & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg1) 
			       | (0xffU & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		    if ((2U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg1 
			    = ((0xffff00ffU & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg1) 
			       | (0xff00U & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		    if ((4U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg1 
			    = ((0xff00ffffU & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg1) 
			       | (0xff0000U & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		    if ((8U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg1 
			    = ((0xffffffU & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg1) 
			       | (0xff000000U & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		} else {
		    if ((1U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg0 
			    = ((0xffffff00U & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg0) 
			       | (0xffU & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		    if ((2U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg0 
			    = ((0xffff00ffU & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg0) 
			       | (0xff00U & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		    if ((4U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg0 
			    = ((0xff00ffffU & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg0) 
			       | (0xff0000U & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		    if ((8U & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb))) {
			vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg0 
			    = ((0xffffffU & vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg0) 
			       | (0xff000000U & vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata));
		    }
		}
	    }
	}
    } else {
	vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg0 = 0U;
	vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg1 = 0U;
	vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg2 = 0U;
	vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg3 = 0U;
    }
    vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready 
	= __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready;
    vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_wready 
	= __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_wready;
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_arready, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready);
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_wready, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_wready);
    // ALWAYS at axilite_dev_v1_0_S00_AXI.v:170
    if (vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_aresetn) {
	if (((((~ (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready)) 
	       & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_awvalid)) 
	      & (IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wvalid)) 
	     & (IData)(vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__aw_en))) {
	    vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr 
		= vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_awaddr;
	}
    } else {
	vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr = 0U;
    }
    vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__aw_en 
	= __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__aw_en;
    vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready 
	= __Vdly__axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready;
    VL_ASSIGN_SII(1,vlTOPp->s00_axi_awready, vlTOPp->axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready);
}

VL_INLINE_OPT void Vaxilite_dev_v1_0::_combo__TOP__4(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxilite_dev_v1_0::_combo__TOP__4\n"); );
    Vaxilite_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_rready, vlTOPp->s00_axi_rready);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_bready, vlTOPp->s00_axi_bready);
    VL_ASSIGN_ISW(4,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_araddr, vlTOPp->s00_axi_araddr);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_arvalid, vlTOPp->s00_axi_arvalid);
    VL_ASSIGN_ISW(4,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wstrb, vlTOPp->s00_axi_wstrb);
    VL_ASSIGN_ISW(32,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wdata, vlTOPp->s00_axi_wdata);
    VL_ASSIGN_ISW(4,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_awaddr, vlTOPp->s00_axi_awaddr);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_awvalid, vlTOPp->s00_axi_awvalid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_wvalid, vlTOPp->s00_axi_wvalid);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_aresetn, vlTOPp->s00_axi_aresetn);
}

void Vaxilite_dev_v1_0::_eval(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxilite_dev_v1_0::_eval\n"); );
    Vaxilite_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
    if (((IData)(vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_aclk) 
	 & (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__axilite_dev_v1_0__s00_axi_aclk)))) {
	vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    vlTOPp->_combo__TOP__4(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP____Vcellinp__axilite_dev_v1_0__s00_axi_aclk 
	= vlTOPp->__Vcellinp__axilite_dev_v1_0__s00_axi_aclk;
}

void Vaxilite_dev_v1_0::_eval_initial(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxilite_dev_v1_0::_eval_initial\n"); );
    Vaxilite_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vaxilite_dev_v1_0::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxilite_dev_v1_0::final\n"); );
    // Variables
    Vaxilite_dev_v1_0__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vaxilite_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vaxilite_dev_v1_0::_eval_settle(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxilite_dev_v1_0::_eval_settle\n"); );
    Vaxilite_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

VL_INLINE_OPT QData Vaxilite_dev_v1_0::_change_request(Vaxilite_dev_v1_0__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxilite_dev_v1_0::_change_request\n"); );
    Vaxilite_dev_v1_0* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vaxilite_dev_v1_0::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxilite_dev_v1_0::_eval_debug_assertions\n"); );
}
#endif // VL_DEBUG

void Vaxilite_dev_v1_0::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxilite_dev_v1_0::_ctor_var_reset\n"); );
    // Body
    __Vcellinp__axilite_dev_v1_0__s00_axi_rready = VL_RAND_RESET_I(1);
    __Vcellinp__axilite_dev_v1_0__s00_axi_arvalid = VL_RAND_RESET_I(1);
    __Vcellinp__axilite_dev_v1_0__s00_axi_araddr = VL_RAND_RESET_I(4);
    __Vcellinp__axilite_dev_v1_0__s00_axi_bready = VL_RAND_RESET_I(1);
    __Vcellinp__axilite_dev_v1_0__s00_axi_wvalid = VL_RAND_RESET_I(1);
    __Vcellinp__axilite_dev_v1_0__s00_axi_wstrb = VL_RAND_RESET_I(4);
    __Vcellinp__axilite_dev_v1_0__s00_axi_wdata = VL_RAND_RESET_I(32);
    __Vcellinp__axilite_dev_v1_0__s00_axi_awvalid = VL_RAND_RESET_I(1);
    __Vcellinp__axilite_dev_v1_0__s00_axi_awaddr = VL_RAND_RESET_I(4);
    __Vcellinp__axilite_dev_v1_0__s00_axi_aresetn = VL_RAND_RESET_I(1);
    __Vcellinp__axilite_dev_v1_0__s00_axi_aclk = VL_RAND_RESET_I(1);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awaddr = VL_RAND_RESET_I(4);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_awready = VL_RAND_RESET_I(1);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_wready = VL_RAND_RESET_I(1);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bresp = VL_RAND_RESET_I(2);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_bvalid = VL_RAND_RESET_I(1);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_araddr = VL_RAND_RESET_I(4);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_arready = VL_RAND_RESET_I(1);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rdata = VL_RAND_RESET_I(32);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rresp = VL_RAND_RESET_I(2);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__axi_rvalid = VL_RAND_RESET_I(1);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg0 = VL_RAND_RESET_I(32);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg1 = VL_RAND_RESET_I(32);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg2 = VL_RAND_RESET_I(32);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__slv_reg3 = VL_RAND_RESET_I(32);
    axilite_dev_v1_0__DOT__axilite_dev_v1_0_S00_AXI_inst__DOT__aw_en = VL_RAND_RESET_I(1);
    __Vclklast__TOP____Vcellinp__axilite_dev_v1_0__s00_axi_aclk = VL_RAND_RESET_I(1);
}
