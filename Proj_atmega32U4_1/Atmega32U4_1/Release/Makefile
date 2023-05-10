################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Library


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../Library/atmega32u4mapping.c \
../Library/explode.c \
../main.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
Library/atmega32u4mapping.o \
Library/explode.o \
main.o

OBJS_AS_ARGS +=  \
Library/atmega32u4mapping.o \
Library/explode.o \
main.o

C_DEPS +=  \
Library/atmega32u4mapping.d \
Library/explode.d \
main.d

C_DEPS_AS_ARGS +=  \
Library/atmega32u4mapping.d \
Library/explode.d \
main.d

OUTPUT_FILE_PATH +=Atmega32U4_1.elf

OUTPUT_FILE_PATH_AS_ARGS +=Atmega32U4_1.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
Library/atmega32u4mapping.o: ../Library/atmega32u4mapping.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.41
	$(QUOTE)C:\Program Files\Microchip\xc8\v2.41\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega32U4  -mdfp="C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega32U4__ -DNDEBUG  -I"../Library"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

Library/explode.o: ../Library/explode.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.41
	$(QUOTE)C:\Program Files\Microchip\xc8\v2.41\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega32U4  -mdfp="C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega32U4__ -DNDEBUG  -I"../Library"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./main.o: .././main.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.41
	$(QUOTE)C:\Program Files\Microchip\xc8\v2.41\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega32U4  -mdfp="C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega32U4__ -DNDEBUG  -I"../Library"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking:  XC8 C Linker : 2.41
	$(QUOTE)C:\Program Files\Microchip\xc8\v2.41\bin\xc8-cc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -mcpu=ATmega32U4  -mdfp="C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -Wl,-Map="Atmega32U4_1.map" -funsigned-char -funsigned-bitfields -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,-L"../Library"  -Wl,--gc-sections -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax --memorysummary,memoryfile.xml  
	@echo Finished building target: $@
	"C:\Program Files\Microchip\xc8\v2.41\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Atmega32U4_1.elf" "Atmega32U4_1.hex"
	"C:\Program Files\Microchip\xc8\v2.41\bin\avr-objcopy.exe" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "Atmega32U4_1.elf" "Atmega32U4_1.eep" || exit 0
	"C:\Program Files\Microchip\xc8\v2.41\bin\avr-objdump.exe" -h -S "Atmega32U4_1.elf" > "Atmega32U4_1.lss"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Atmega32U4_1.elf" "Atmega32U4_1.hex" "Atmega32U4_1.eep" "Atmega32U4_1.map" "Atmega32U4_1.usersignatures" "Atmega32U4_1.a"  "Atmega32U4_1.lss"
	