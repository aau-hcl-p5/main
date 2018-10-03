# Common Makefile for C/C++(*.cc) with TOPPERS ATK(OSEK) and JSP(��ITRON)

#
## ROOT path configurations
#
ifndef ROOT
ROOT := $(dir $(lastword $(MAKEFILE_LIST)))..
endif

ECROBOT_ROOT = $(ROOT)/ecrobot
CXX_ROOT=$(ROOT)/c++
LEJOSNXJSRC_ROOT = $(ROOT)/lejos_nxj/src/

ifeq ($(TOPPERS_KERNEL), NXT_JSP)
TOPPERS_ROOT = $(ROOT)/toppers_jsp
else
TOPPERS_ROOT = $(ROOT)/toppers_osek
endif

# 03/11/2009 added by takashic
ECROBOT_C_ROOT = $(ECROBOT_ROOT)/c

vpath %.c $(LEJOSNXJSRC_ROOT) $(TOPPERS_ROOT) $(ECROBOT_ROOT) $(ECROBOT_C_ROOT)
vpath %.S $(LEJOSNXJSRC_ROOT) $(TOPPERS_ROOT)
vpath %.s $(LEJOSNXJSRC_ROOT) $(TOPPERS_ROOT) $(ECROBOT_ROOT) $(ECROBOT_C_ROOT)

################################################################################
# TOPPERS ATK/JSP specific settings. By default, TOPPERS ATK is configured as 
# RTOS for the NXT, however, JSP also can be used by defining TOPPERS_KERNEL = NXT_JSP 
# macro in user Makefile

ifeq ($(TOPPERS_KERNEL), NXT_JSP)
	TOPPERS_INC_PATH = \
		$(TOPPERS_ROOT)/kernel \
		$(TOPPERS_ROOT)/include \
		$(TOPPERS_ROOT)/config/armv4 \
		$(TOPPERS_ROOT)/config/armv4/at91sam7s

	TOPPERS_KERNEL_SOURCES = $(addprefix kernel/, \
		banner.c \
		cyclic.c \
		dataqueue.c \
		eventflag.c \
		exception.c \
		interrupt.c \
		mailbox.c \
		mempfix.c \
		semaphore.c \
		startup.c \
		sys_manage.c \
		syslog.c \
		task.c \
		task_except.c \
		task_manage.c \
		task_sync.c \
		time_event.c \
		time_manage.c \
		wait.c )

	TOPPERS_CONFIG_SOURCES = $(addprefix config/armv4/, \
		cpu_config.c )

	TOPPERS_CONFIG_SYS_SOURCES = $(addprefix config/armv4/at91sam7s/, \
		sys_config.c )

	TOPPERS_SYSLIB_SOURCES = $(addprefix library/, \
		log_output.c \
		strerror.c \
		t_perror.c \
		vasyslog.c )

	TOPPERS_SRAM_SOURCES = \
		config/armv4/cpu_support.s \
		config/armv4/at91sam7s/irq.s

else
	# if you need to modify the Makefiles to set absolute path,
	# TOPPERS_OSEK_ROOT_SG should be defined like...
	# TOPPERS_OSEK_ROOT_SG = C:/cygwin/nxtOSEK/toppers_osek
	ifndef TOPPERS_OSEK_ROOT_SG
		TOPPERS_OSEK_ROOT_SG = $(TOPPERS_ROOT)
	endif

	TOPPERS_INC_PATH = \
		$(TOPPERS_ROOT)/kernel \
		$(TOPPERS_ROOT)/include \
		$(TOPPERS_ROOT)/config/at91sam7s-gnu \
		$(TOPPERS_ROOT)/config/at91sam7s-gnu/lego_nxt \
		$(TOPPERS_ROOT)/sg \
		$(TOPPERS_ROOT)/syslib/at91sam7s-gnu/lego_nxt

	TOPPERS_KERNEL_SOURCES = $(addprefix kernel/, \
		alarm.c \
		event.c	\
		interrupt.c \
		osctl.c	\
		resource.c \
		task.c \
		task_manage.c )

	TOPPERS_CONFIG_SOURCES = $(addprefix config/at91sam7s-gnu/, \
		cpu_config.c )

	TOPPERS_CONFIG_SYS_SOURCES = $(addprefix config/at91sam7s-gnu/lego_nxt/, \
		sys_config.c )

	TOPPERS_SYSLIB_SOURCES = $(addprefix syslib/at91sam7s-gnu/lego_nxt/, \
		hw_sys_timer.c )

	TOPPERS_S_SOURCES = \
		config/at91sam7s-gnu/debug.s \
		config/at91sam7s-gnu/lego_nxt/sys_support.s

	TOPPERS_SRAM_SOURCES = \
		config/at91sam7s-gnu/cpu_support.s \
		config/at91sam7s-gnu/irq.s
endif

TOPPERS_CFG_SOURCE = ./kernel_cfg.c
TOPPERS_CFG_HEADER = ./kernel_id.h

################################################################################
# Embedded Coder Robot(ECRobot) NXT specific settings
#

ifndef ECROBOT_SOURCES
ECROBOT_SOURCES = \
	syscalls.c \
	ecrobot_bluetooth.c \
	ecrobot_base.c \
	ecrobot.c
endif

################################################################################
# leJOS NXJ specific settings
#

LEJOS_PLATFORM_SOURCES_PATH = nxtvm/platform/nxt
LEJOS_VM_SOURCES_PATH = nxtvm/javavm

################################################################################
# Common settings
#

C_SOURCES = \
	$(TOPPERS_KERNEL_SOURCES) \
	$(TOPPERS_CONFIG_SOURCES) \
	$(TOPPERS_CONFIG_SYS_SOURCES) \
	$(TOPPERS_CFG_SOURCE) \
	$(ECROBOT_SOURCES) \
	$(TARGET_SOURCES)

C_RAMSOURCES = \
	$(TOPPERS_SYSLIB_SOURCES)

S_SOURCES = \
	$(LEJOS_PLATFORM_SOURCES_PATH)/vectors.s \
	$(TOPPERS_S_SOURCES) \
	nxt_binary_header.s \
	nxt_entry_point.s \
	ecrobot_init.s

S_RAMSOURCES = \
	$(TOPPERS_SRAM_SOURCES)

CC_SOURCES = \
	$(TARGET_CC_SOURCES)

# using the new linker script
LDSCRIPT_SOURCE = $(ECROBOT_C_ROOT)/sam7_ecrobot.lds

LIBECROBOT = -lecrobot
LIBLEJOSOSEK = -llejososek
include $(ECROBOT_ROOT)/tool_gcc.mak

INC_PATH = \
	$(LEJOSNXJSRC_ROOT)/$(LEJOS_PLATFORM_SOURCES_PATH) \
	$(LEJOSNXJSRC_ROOT)/$(LEJOS_VM_SOURCES_PATH) \
	$(ECROBOT_ROOT)/bios \
	$(ECROBOT_ROOT) \
	$(ECROBOT_C_ROOT) \
	$(CXX_ROOT) \
	$(USER_INC_PATH)

PHONY: EnvironmentMessage
EnvironmentMessage:
	@echo " CC      $(CC)"
	@echo " CPP     $(CPP)"
	@echo " AS      $(AS)"
	@echo " AR      $(AR)"
	@echo " LD      $(LD)"
	@echo " OBJCOPY $(OBJCOPY)"

ROM_TARGET = $(TARGET)_rom.elf
RAM_TARGET = $(TARGET)_ram.elf
RXE_TARGET = $(TARGET)_rxe.elf

ROMBIN_TARGET = $(TARGET)_rom.bin
RAMBIN_TARGET = $(TARGET)_ram.bin
RXEBIN_TARGET = $(TARGET).rxe

ROM_LDSCRIPT = $(O_PATH)/$(TARGET)_rom.ld
RAM_LDSCRIPT = $(O_PATH)/$(TARGET)_ram.ld
RXE_LDSCRIPT = $(O_PATH)/$(TARGET)_rxe.ld

S_OBJECTS   = $(addprefix $(O_PATH)/,$(S_SOURCES:.s=.o) $(S_RAMSOURCES:.s=.oram))
C_OBJECTS   = $(addprefix $(O_PATH)/,$(C_SOURCES:.c=.o) $(C_RAMSOURCES:.c=.oram))
CC_OBJECTS  = $(addprefix $(O_PATH)/,$(CC_SOURCES:.cc=.o) $(CC_RAMSOURCES:.cc=.oram))
WAV_OBJECTS = $(addprefix $(O_PATH)/,$(WAV_SOURCES:.wav=.owav))
BMP_OBJECTS = $(addprefix $(O_PATH)/,$(BMP_SOURCES:.bmp=.obmp))
SPR_OBJECTS = $(addprefix $(O_PATH)/,$(SPR_SOURCES:.spr=.ospr))

dependencies = $(subst .o,.d,$(C_OBJECTS) $(CC_OBJECTS) $(S_OBJECTS))
dependencies += $(subst .owav,.d,$(WAV_OBJECTS))
dependencies += $(subst .obmp,.d,$(BMP_OBJECTS))
dependencies += $(subst .ospr,.d,$(SPR_OBJECTS))

def_target: all

ifndef BUILD_MODE
ALL_TARGETS = $(ROM_TARGET) $(ROMBIN_TARGET) $(RAM_TARGET) $(RAMBIN_TARGET) $(RXE_TARGET) $(RXEBIN_TARGET) biosflash appflash ramboot rxeflash
else
ifeq ($(BUILD_MODE), ROM_ONLY)
ALL_TARGETS = $(ROM_TARGET) $(ROMBIN_TARGET) biosflash appflash
else
ifeq ($(BUILD_MODE), RAM_ONLY)
ALL_TARGETS = $(RAM_TARGET) $(RAMBIN_TARGET) ramboot
else
ifeq ($(BUILD_MODE), RXE_ONLY)
ALL_TARGETS = $(RXE_TARGET) $(RXEBIN_TARGET) rxeflash
else
$(error BUILD_MODE is not set correctly. Change "Flash_only" to "ROM_ONLY" or "SRAM_only" to "RAM_ONLY" in the Makefile.)
endif
endif
endif
endif


.PHONY: all
all: toppers_cfg $(ALL_TARGETS) movefiles

PHONY: TargetMessage
TargetMessage:
	@echo ""
	@echo "Building: $(ALL_TARGETS)"
	@echo ""
	@echo "C sources: $(C_SOURCES) to $(C_OBJECTS)"
	@echo ""
	@echo "C++ sources: $(CC_SOURCES) to $(CC_OBJECTS)"
	@echo ""
	@echo "Assembler sources: $(S_SOURCES) to $(S_OBJECTS)"
	@echo ""
	@echo "LD source: $(LDSCRIPT_SOURCE)"
	@echo ""

.PHONY: BuildMessage
BuildMessage: TargetMessage EnvironmentMessage

$(RXE_LDSCRIPT): $(LDSCRIPT_SOURCE)
	sed -e 's/^RXE_ONLY//' -e '/^RAM_ONLY/d' -e '/^ROM_ONLY/d' $< >$@

$(RAM_LDSCRIPT): $(LDSCRIPT_SOURCE)
	sed -e 's/^RAM_ONLY//' -e '/^ROM_ONLY/d' -e '/^RXE_ONLY/d' $< >$@

$(ROM_LDSCRIPT): $(LDSCRIPT_SOURCE)
	sed -e 's/^ROM_ONLY//' -e '/^RAM_ONLY/d' -e '/^RXE_ONLY/d' $< >$@

$(RXE_TARGET): $(C_OBJECTS) $(CC_OBJECTS) $(S_OBJECTS) $(WAV_OBJECTS) $(BMP_OBJECTS) $(SPR_OBJECTS) $(RXE_LDSCRIPT)
	$(LD) -o $@ $(C_OBJECTS) $(CC_OBJECTS) $(S_OBJECTS) $(WAV_OBJECTS) $(BMP_OBJECTS) $(SPR_OBJECTS) -T $(RXE_LDSCRIPT) $(LDFLAGS) $(EXTRALIBS)

$(RAM_TARGET): $(C_OBJECTS) $(CC_OBJECTS) $(S_OBJECTS) $(WAV_OBJECTS) $(BMP_OBJECTS) $(SPR_OBJECTS) $(RAM_LDSCRIPT)
	$(LD) -o $@ $(C_OBJECTS) $(CC_OBJECTS) $(S_OBJECTS) $(WAV_OBJECTS) $(BMP_OBJECTS) $(SPR_OBJECTS) -T $(RAM_LDSCRIPT) $(LDFLAGS) $(EXTRALIBS)

$(ROM_TARGET): $(C_OBJECTS) $(CC_OBJECTS) $(S_OBJECTS) $(WAV_OBJECTS) $(BMP_OBJECTS) $(SPR_OBJECTS) $(ROM_LDSCRIPT)
	$(LD) -o $@ $(C_OBJECTS) $(CC_OBJECTS) $(S_OBJECTS) $(WAV_OBJECTS) $(BMP_OBJECTS) $(SPR_OBJECTS) -T $(ROM_LDSCRIPT) $(LDFLAGS) $(EXTRALIBS)

$(ROMBIN_TARGET): $(ROM_TARGET)
	@echo "Generating binary image file: $@"
	$(OBJCOPY) -O binary $< $@

$(RAMBIN_TARGET): $(RAM_TARGET)
	@echo "Generating binary image file: $@"
	$(OBJCOPY) -O binary $< $@

$(RXEBIN_TARGET): $(RXE_TARGET)
	@echo "Generating binary image file: $@"
	$(OBJCOPY) -O binary $< $@

# on Linux, use wine to run the windows application
ifneq "$(OS)" "Windows_NT"
WINECONSOLE := wineconsole
endif

.PHONY: toppers_cfg
toppers_cfg:
ifeq ($(TOPPERS_KERNEL), NXT_JSP)
$(TOPPERS_CFG_SOURCE) $(TOPPERS_CFG_HEADER) : $(TOPPERS_JSP_CFG_SOURCE)
	@echo "Generating JSP kernel config files from $(TOPPERS_JSP_CFG_SOURCE)"
	$(CC) -E -x c-header -fno-inline-functions $(TOPPERS_JSP_CFG_SOURCE) $(addprefix -I ,$(CXX_ROOT)) $(addprefix -iquote ,$(INC_PATH)) -I. $(addprefix -I,$(TOPPERS_INC_PATH)) > tmpfile1
	$(TOPPERS_ROOT)/cfg/cfg -s tmpfile1 -c -obj
else
$(TOPPERS_CFG_SOURCE) $(TOPPERS_CFG_HEADER) implementation.oil : $(TOPPERS_OSEK_OIL_SOURCE)
	@echo "Generating OSEK kernel config files from $(TOPPERS_OSEK_OIL_SOURCE)"
	$(error Unable to generate implementation.oil from makefile, use build script to generate it beforehand)
endif

.PHONY: biosflash
biosflash:
	@echo "echo Executing NeXTTool to upload $(ROOT)/ecrobot/bios/nxt_bios_rom.rfw..." >./biosflash.sh
	@echo "$(WINECONSOLE) $(NEXTTOOL_ROOT)/$(NEXTTOOL) /COM=usb -firmware=$(ROOT)/ecrobot/bios/nxt_bios_rom.rfw" >>./biosflash.sh

.PHONY: appflash
appflash:
	@echo "echo Executing appflash to upload $(ROMBIN_TARGET)..." >./appflash.sh
	@echo "$(WINECONSOLE) ./$(APPFLASH) ./$(ROMBIN_TARGET)" >>./appflash.sh

.PHONY: ramboot
ramboot:
	@echo "echo Executing ramboot to upload $(RAMBIN_TARGET)..." >./ramboot.sh
	@echo "$(WINECONSOLE) ./$(RAMBOOT) ./$(RAMBIN_TARGET)" >>./ramboot.sh

.PHONY: rxeflash
rxeflash:
	@echo "echo Executing NeXTTool to upload $(RXEBIN_TARGET)..." >./rxeflash.sh
	@echo "$(WINECONSOLE) $(NEXTTOOL_ROOT)/$(NEXTTOOL) /COM=usb -download=$(RXEBIN_TARGET)" >>./rxeflash.sh
	@echo "$(WINECONSOLE) $(NEXTTOOL_ROOT)/$(NEXTTOOL) /COM=usb -listfiles=$(RXEBIN_TARGET)" >>./rxeflash.sh
	@echo "echo NeXTTool is terminated."  >>./rxeflash.sh

.PHONY: clean
clean:  
	@echo "Removing kernel config files"
	-@rm -f $(TOPPERS_CFG_SOURCE)
	-@rm -f $(TOPPERS_CFG_HEADER)
	-@rm -f implementation.oil
	-@rm -f *.dat
	-@rm -f tmpfile1
ifeq ($(TOPPERS_KERNEL), NXT_JSP)
	-@rm -f kernel_chk.c
endif
	@echo "Removing objects"
	-@rm -rf $(O_PATH)
	@echo "Removing targets"
	-@rm -f $(ALL_TARGETS)
	@echo "Removing map files"
	-@rm -f *.map
	@echo "Removing upload scripts"
	-@rm -f appflash.sh
	-@rm -f biosflash.sh
	-@rm -f ramboot.sh
	-@rm -f rxeflash.sh
	-@rm -f appflash.exe
	-@rm -f ramboot.exe
	-@rm -rf output

.PHONY: movefiles
movefiles:
  
	@mkdir -p output
	@echo "Moving kernel config files"
	-@mv -f $(TOPPERS_CFG_SOURCE) output
	-@mv -f $(TOPPERS_CFG_HEADER) output
	-@mv -f implementation.oil output
ifeq ($(TOPPERS_KERNEL), NXT_JSP)
	-@mv -f kernel_chk.c output
endif
	@echo "Moving targets"
	-@mv -f $(ALL_TARGETS) output 2>/dev/null
	@echo "Moving map files"
	-@mv -f *.map output
	@echo "Moving upload scripts"
	-@mv -f appflash.sh output
	-@mv -f biosflash.sh output
	-@mv -f ramboot.sh output
	-@mv -f rxeflash.sh output
	@echo "Moving binaries"
	-@mv -f $(ROOT)/bin/$(APPFLASH) output
	-@mv -f $(ROOT)/bin/$(RAMBOOT) output

ifneq "$(MAKECMDGOALS)" "clean"
  -include $(dependencies)
endif
