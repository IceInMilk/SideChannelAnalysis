# Default firmware (overridden by the Bash command)
TARGET = simpleserial-xxx
SRC += simpleserial-xxx.c

# Use simpleserial 2
SS_VER = SS_VER_2_1

# No crypto required
CRYPTO_TARGET = NONE

# ChipWhisperer repository paths
CW_PATH = /home/$(USER)/Documents/chipwhisperer/
FIRMWAREPATH = $(CW_PATH)/firmware/mcu/


# include other required build files
include $(FIRMWAREPATH)/simpleserial/Makefile.simpleserial
include $(FIRMWAREPATH)/Makefile.inc