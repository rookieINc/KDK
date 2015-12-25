KDK_PATH=$(subst $(prefix),,$(shell cd ..; pwd))
FEE_PATH=$(subst $(prefix),,$(shell cd ../../FEE; pwd))
INC_PATH=-I$(KDK_PATH)/inc
LIB_PATH=-L$(KDK_PATH)/lib

SO_FILE=libkdk.so
H_FILE=kdk.h kdk_base.h kdk_define.h kdk_malloc.h kdk_mem_pool.h kdk_hash.h kdk_string.h kdk_config.h
C_FILE=kdk_malloc.c kdk_mem_pool.c kdk_hash.c kdk_string.c kdk_config.c

.PHONY:ALL
ALL:inc_install $(SO_FILE) lib_install


inc_install:
	cp $(H_FILE) $(KDK_PATH)/inc/

lib_install:
	cp $(SO_FILE) $(KDK_PATH)/lib/
	cp $(SO_FILE) $(FEE_PATH)/src/

libkdk.so:$(C_FILE)
	gcc -o libkdk.so -fpic -shared $(C_FILE) $(INC_PATH)

clean:
	rm -rf $(SO_FILE)
