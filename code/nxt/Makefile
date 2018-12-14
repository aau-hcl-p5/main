# Target specific macros
TARGET = nxt_OSEK
TARGET_SOURCES = \
	./src/nxt.c \
	./src/usb.c \
	./src/movement.c \
	./src/display_manager.c \
	./src/calibration.c \
	./src/laser.c \
	./src/model_up.c \
	./src/model_down.c \
	./src/model_adapter.c \

TOPPERS_OSEK_OIL_SOURCE = ./nxt.oil
USER_INC_PATH = ./inc

# Don't modify below part
O_PATH ?= build
include ../../ecrobot/ecrobot.mak
