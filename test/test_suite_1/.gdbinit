#
# J-LINK GDB SERVER initialization
#
########################################
# This connects to a GDB Server listening
# for commands on localhost at tcp port 2331
target remote localhost:2331
########################################


########################################
# Enable Flash Device
monitor flash device = NRF52
# Enable Flash Download
monitor flash download = 1
# Enable flash breakpoints
monitor flash breakpoints = 1
########################################





########################################
# Reset the chip to get to a known state.
monitor reset 0
#monitor sleep 10


########################################


# Load the program executable
file ../../_build/test/test_suite_1/blue42_test1





set breakpoint pending on

load
mon reset
break main
