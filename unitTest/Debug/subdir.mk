################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main.cpp \
../test.cpp 

C_SRCS += \
/home/gerardo/eclipse-workspace/russian_draughts_c_api.c 

OBJS += \
./main.o \
./russian_draughts_c_api.o \
./test.o 

CPP_DEPS += \
./main.d \
./test.d 

C_DEPS += \
./russian_draughts_c_api.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/gerardo/eclipse-workspace/unitTest/googleTestLib" -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

russian_draughts_c_api.o: /home/gerardo/eclipse-workspace/russian_draughts_c_api.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


