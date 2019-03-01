// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vapb_timer.h for the primary calling header

#include "Vapb_timer.h"        // For This
#include "Vapb_timer__Syms.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_SC_CTOR_IMP(Vapb_timer)
#if (SYSTEMC_VERSION>20011000)
    : clk("clk"), rst("rst"), psel("psel"), penable("penable"), 
      pwrite("pwrite"), pready("pready"), irq("irq"), 
      paddr("paddr"), pwdata("pwdata"), prdata("prdata")
#endif
 {
    Vapb_timer__Syms* __restrict vlSymsp = __VlSymsp = new Vapb_timer__Syms(this, name());
    Vapb_timer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Sensitivities on all clocks and combo inputs
    SC_METHOD(eval);
    sensitive << clk;
    sensitive << rst;
    sensitive << psel;
    sensitive << penable;
    sensitive << pwrite;
    sensitive << paddr;
    sensitive << pwdata;
    
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vapb_timer::__Vconfigure(Vapb_timer__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vapb_timer::~Vapb_timer() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void Vapb_timer::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vapb_timer::eval\n"); );
    Vapb_timer__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vapb_timer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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

void Vapb_timer::_eval_initial_loop(Vapb_timer__Syms* __restrict vlSymsp) {
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

VL_INLINE_OPT void Vapb_timer::_combo__TOP__1(Vapb_timer__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapb_timer::_combo__TOP__1\n"); );
    Vapb_timer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__apb_slave_timer__clk, vlTOPp->clk);
}

void Vapb_timer::_settle__TOP__2(Vapb_timer__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapb_timer::_settle__TOP__2\n"); );
    Vapb_timer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__apb_slave_timer__clk, vlTOPp->clk);
    VL_ASSIGN_ISW(32,vlTOPp->__Vcellinp__apb_slave_timer__pwdata, vlTOPp->pwdata);
    VL_ASSIGN_ISW(16,vlTOPp->__Vcellinp__apb_slave_timer__paddr, vlTOPp->paddr);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__apb_slave_timer__pwrite, vlTOPp->pwrite);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__apb_slave_timer__penable, vlTOPp->penable);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__apb_slave_timer__psel, vlTOPp->psel);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__apb_slave_timer__rst, vlTOPp->rst);
    VL_ASSIGN_SII(1,vlTOPp->irq, (1U & ((IData)(vlTOPp->apb_slave_timer__DOT__tmr_cfg) 
					>> 1U)));
    VL_ASSIGN_SII(1,vlTOPp->pready, vlTOPp->__Vcellout__apb_slave_timer__pready);
    VL_ASSIGN_SWI(32,vlTOPp->prdata, vlTOPp->__Vcellout__apb_slave_timer__prdata);
}

VL_INLINE_OPT void Vapb_timer::_sequent__TOP__3(Vapb_timer__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapb_timer::_sequent__TOP__3\n"); );
    Vapb_timer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__apb_slave_timer__DOT__tmr_cfg,1,0);
    VL_SIG(__Vdly__apb_slave_timer__DOT__tmr_free_cnt,31,0);
    VL_SIG(__Vdly__apb_slave_timer__DOT__tmr_cnt,31,0);
    VL_SIG(__Vdly__apb_slave_timer__DOT__tmr_div,31,0);
    // Body
    __Vdly__apb_slave_timer__DOT__tmr_free_cnt = vlTOPp->apb_slave_timer__DOT__tmr_free_cnt;
    __Vdly__apb_slave_timer__DOT__tmr_cnt = vlTOPp->apb_slave_timer__DOT__tmr_cnt;
    __Vdly__apb_slave_timer__DOT__tmr_div = vlTOPp->apb_slave_timer__DOT__tmr_div;
    __Vdly__apb_slave_timer__DOT__tmr_cfg = vlTOPp->apb_slave_timer__DOT__tmr_cfg;
    // ALWAYS at apb_timer.v:47
    __Vdly__apb_slave_timer__DOT__tmr_free_cnt = ((IData)(1U) 
						  + vlTOPp->apb_slave_timer__DOT__tmr_free_cnt);
    if ((1U & (IData)(vlTOPp->apb_slave_timer__DOT__tmr_cfg))) {
	__Vdly__apb_slave_timer__DOT__tmr_cnt = (vlTOPp->apb_slave_timer__DOT__tmr_cnt 
						 - (IData)(1U));
	if ((0U == vlTOPp->apb_slave_timer__DOT__tmr_cnt)) {
	    __Vdly__apb_slave_timer__DOT__tmr_cnt = vlTOPp->apb_slave_timer__DOT__tmr_div;
	    __Vdly__apb_slave_timer__DOT__tmr_cfg = 
		(2U | (IData)(__Vdly__apb_slave_timer__DOT__tmr_cfg));
	}
    }
    vlTOPp->__Vcellout__apb_slave_timer__prdata = 0U;
    vlTOPp->__Vcellout__apb_slave_timer__pready = 0U;
    if (vlTOPp->__Vcellinp__apb_slave_timer__psel) {
	vlTOPp->__Vcellout__apb_slave_timer__pready 
	    = vlTOPp->__Vcellinp__apb_slave_timer__penable;
	if (((IData)(vlTOPp->__Vcellinp__apb_slave_timer__penable) 
	     & (IData)(vlTOPp->__Vcellinp__apb_slave_timer__pwrite))) {
	    if ((0U == (0x3fffU & ((IData)(vlTOPp->__Vcellinp__apb_slave_timer__paddr) 
				   >> 2U)))) {
		if ((1U & ((IData)(vlTOPp->apb_slave_timer__DOT__tmr_cfg) 
			   ^ vlTOPp->__Vcellinp__apb_slave_timer__pwdata))) {
		    if ((1U & vlTOPp->__Vcellinp__apb_slave_timer__pwdata)) {
			__Vdly__apb_slave_timer__DOT__tmr_cnt 
			    = vlTOPp->apb_slave_timer__DOT__tmr_div;
		    }
		}
		__Vdly__apb_slave_timer__DOT__tmr_cfg 
		    = (3U & vlTOPp->__Vcellinp__apb_slave_timer__pwdata);
	    } else {
		if ((1U == (0x3fffU & ((IData)(vlTOPp->__Vcellinp__apb_slave_timer__paddr) 
				       >> 2U)))) {
		    __Vdly__apb_slave_timer__DOT__tmr_cnt 
			= vlTOPp->__Vcellinp__apb_slave_timer__pwdata;
		} else {
		    if ((2U == (0x3fffU & ((IData)(vlTOPp->__Vcellinp__apb_slave_timer__paddr) 
					   >> 2U)))) {
			__Vdly__apb_slave_timer__DOT__tmr_div 
			    = vlTOPp->__Vcellinp__apb_slave_timer__pwdata;
		    } else {
			if ((3U == (0x3fffU & ((IData)(vlTOPp->__Vcellinp__apb_slave_timer__paddr) 
					       >> 2U)))) {
			    __Vdly__apb_slave_timer__DOT__tmr_free_cnt 
				= vlTOPp->__Vcellinp__apb_slave_timer__pwdata;
			}
		    }
		}
	    }
	}
	if ((0U == (0x3fffU & ((IData)(vlTOPp->__Vcellinp__apb_slave_timer__paddr) 
			       >> 2U)))) {
	    vlTOPp->__Vcellout__apb_slave_timer__prdata 
		= ((0xfffffffcU & vlTOPp->__Vcellout__apb_slave_timer__prdata) 
		   | (IData)(vlTOPp->apb_slave_timer__DOT__tmr_cfg));
	} else {
	    if ((1U == (0x3fffU & ((IData)(vlTOPp->__Vcellinp__apb_slave_timer__paddr) 
				   >> 2U)))) {
		vlTOPp->__Vcellout__apb_slave_timer__prdata 
		    = vlTOPp->apb_slave_timer__DOT__tmr_cnt;
	    } else {
		if ((2U == (0x3fffU & ((IData)(vlTOPp->__Vcellinp__apb_slave_timer__paddr) 
				       >> 2U)))) {
		    vlTOPp->__Vcellout__apb_slave_timer__prdata 
			= vlTOPp->apb_slave_timer__DOT__tmr_div;
		} else {
		    if ((3U == (0x3fffU & ((IData)(vlTOPp->__Vcellinp__apb_slave_timer__paddr) 
					   >> 2U)))) {
			vlTOPp->__Vcellout__apb_slave_timer__prdata 
			    = vlTOPp->apb_slave_timer__DOT__tmr_free_cnt;
		    }
		}
	    }
	}
    }
    if (vlTOPp->__Vcellinp__apb_slave_timer__rst) {
	__Vdly__apb_slave_timer__DOT__tmr_free_cnt = 0U;
	__Vdly__apb_slave_timer__DOT__tmr_cnt = 0U;
	__Vdly__apb_slave_timer__DOT__tmr_div = 0U;
	__Vdly__apb_slave_timer__DOT__tmr_cfg = 0U;
    }
    vlTOPp->apb_slave_timer__DOT__tmr_free_cnt = __Vdly__apb_slave_timer__DOT__tmr_free_cnt;
    vlTOPp->apb_slave_timer__DOT__tmr_cnt = __Vdly__apb_slave_timer__DOT__tmr_cnt;
    vlTOPp->apb_slave_timer__DOT__tmr_div = __Vdly__apb_slave_timer__DOT__tmr_div;
    vlTOPp->apb_slave_timer__DOT__tmr_cfg = __Vdly__apb_slave_timer__DOT__tmr_cfg;
    VL_ASSIGN_SII(1,vlTOPp->irq, (1U & ((IData)(vlTOPp->apb_slave_timer__DOT__tmr_cfg) 
					>> 1U)));
    VL_ASSIGN_SWI(32,vlTOPp->prdata, vlTOPp->__Vcellout__apb_slave_timer__prdata);
    VL_ASSIGN_SII(1,vlTOPp->pready, vlTOPp->__Vcellout__apb_slave_timer__pready);
}

VL_INLINE_OPT void Vapb_timer::_combo__TOP__4(Vapb_timer__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapb_timer::_combo__TOP__4\n"); );
    Vapb_timer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__apb_slave_timer__psel, vlTOPp->psel);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__apb_slave_timer__penable, vlTOPp->penable);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__apb_slave_timer__pwrite, vlTOPp->pwrite);
    VL_ASSIGN_ISW(16,vlTOPp->__Vcellinp__apb_slave_timer__paddr, vlTOPp->paddr);
    VL_ASSIGN_ISW(32,vlTOPp->__Vcellinp__apb_slave_timer__pwdata, vlTOPp->pwdata);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__apb_slave_timer__rst, vlTOPp->rst);
}

void Vapb_timer::_eval(Vapb_timer__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapb_timer::_eval\n"); );
    Vapb_timer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
    if (((IData)(vlTOPp->__Vcellinp__apb_slave_timer__clk) 
	 & (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__apb_slave_timer__clk)))) {
	vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    vlTOPp->_combo__TOP__4(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP____Vcellinp__apb_slave_timer__clk 
	= vlTOPp->__Vcellinp__apb_slave_timer__clk;
}

void Vapb_timer::_eval_initial(Vapb_timer__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapb_timer::_eval_initial\n"); );
    Vapb_timer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vapb_timer::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapb_timer::final\n"); );
    // Variables
    Vapb_timer__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vapb_timer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vapb_timer::_eval_settle(Vapb_timer__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapb_timer::_eval_settle\n"); );
    Vapb_timer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

VL_INLINE_OPT QData Vapb_timer::_change_request(Vapb_timer__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapb_timer::_change_request\n"); );
    Vapb_timer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vapb_timer::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapb_timer::_eval_debug_assertions\n"); );
}
#endif // VL_DEBUG

void Vapb_timer::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapb_timer::_ctor_var_reset\n"); );
    // Body
    __Vcellout__apb_slave_timer__pready = VL_RAND_RESET_I(1);
    __Vcellout__apb_slave_timer__prdata = VL_RAND_RESET_I(32);
    __Vcellinp__apb_slave_timer__pwdata = VL_RAND_RESET_I(32);
    __Vcellinp__apb_slave_timer__paddr = VL_RAND_RESET_I(16);
    __Vcellinp__apb_slave_timer__pwrite = VL_RAND_RESET_I(1);
    __Vcellinp__apb_slave_timer__penable = VL_RAND_RESET_I(1);
    __Vcellinp__apb_slave_timer__psel = VL_RAND_RESET_I(1);
    __Vcellinp__apb_slave_timer__rst = VL_RAND_RESET_I(1);
    __Vcellinp__apb_slave_timer__clk = VL_RAND_RESET_I(1);
    apb_slave_timer__DOT__tmr_cfg = VL_RAND_RESET_I(2);
    apb_slave_timer__DOT__tmr_cnt = VL_RAND_RESET_I(32);
    apb_slave_timer__DOT__tmr_div = VL_RAND_RESET_I(32);
    apb_slave_timer__DOT__tmr_free_cnt = VL_RAND_RESET_I(32);
    __Vclklast__TOP____Vcellinp__apb_slave_timer__clk = VL_RAND_RESET_I(1);
}
