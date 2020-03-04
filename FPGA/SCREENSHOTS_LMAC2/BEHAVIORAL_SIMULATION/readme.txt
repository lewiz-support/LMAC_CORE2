1_behavioral_simulation_force_packet_at_rx
	- Shows the point at which the xgmii_rxd/rxc are forced.

2_loopback_module
	- Shows the output of LMAC2 going as an input to the LOOPBACK_MODULE, and output of the LOOPBACK_MODULE going to TX_FIFO of LMAC2.

3_LMAC_SYNTH_TXD
	- Shows the data going out of the LMAC2 on the xgmii_txd/txc lines (after being looped back).

4_phy_emulator
	- Shows the data going to the PCS/PMA IP which is then looped back again and sent on the xgmii_rxd/rxc lines.

5_lmac_synth_received_From_phy
	- Data coming back on the xgmii_rxd/rxc which will go as an input to the LMAC2 module.

6_multiple_packet_rx_tx
	- Same packet will be looped back on both sides (LMAC and PCS/PMA IP).