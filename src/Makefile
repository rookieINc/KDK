PROJECT_PATH=..
INC_PATH=-I$(PROJECT_PATH)/inc
LIB_PATH=-L$(PROJECT_PATH)/lib

SO_FILE=libkdk.so
H_FILE=kdk.h kdk_define.h kdk_malloc.h kdk_mem_pool.h kdk_hash.h
C_FILE=kdk_malloc.c kdk_mem_pool.c kdk_hash.c

.PHONY:ALL
ALL:inc_install $(SO_FILE) lib_install


inc_install:
	cp $(H_FILE) $(PROJECT_PATH)/inc/

lib_install:
	cp $(SO_FILE) $(PROJECT_PATH)/lib/

libkdk.so:$(C_FILE)
	gcc -o libkdk.so -fpic -shared $(C_FILE) $(INC_PATH)

