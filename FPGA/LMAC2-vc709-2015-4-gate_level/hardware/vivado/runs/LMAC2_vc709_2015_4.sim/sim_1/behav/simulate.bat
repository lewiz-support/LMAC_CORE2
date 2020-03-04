@echo off
set xv_path=C:\\Xilinx\\Vivado\\2015.4\\bin
call %xv_path%/xsim board_behav -key {Behavioral:sim_1:Functional:board} -tclbatch board.tcl -log simulate.log -testplusarg TESTNAME=basic_test
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
