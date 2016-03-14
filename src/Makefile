KDK_PATH=$(subst $(prefix),,$(shell cd ..; pwd))
FEE_PATH=$(subst $(prefix),,$(shell cd ../../FEE; pwd))
INC_PATH=-I$(KDK_PATH)/inc
LIB_PATH=-L$(KDK_PATH)/lib
C_FLAG=-g -Wall

SO_FILE=libkdk.so
H_FILE=kdk.h kdk_base.h kdk_define.h \
	   kdk_malloc.h kdk_mem_pool.h kdk_hash_table.h kdk_string.h \
	   kdk_config.h kdk_dl.h kdk_daemon.h kdk_log.h kdk_time.h
C_FILE=kdk_malloc.c kdk_mem_pool.c kdk_hash_table.c kdk_string.c \
	   kdk_config.c kdk_dl.c kdk_daemon.c kdk_log.c kdk_time.c

.PHONY:ALL
ALL:inc_install $(SO_FILE) lib_install


inc_install:
	cp $(H_FILE) $(KDK_PATH)/inc/

lib_install:
	cp $(SO_FILE) $(KDK_PATH)/lib/
	cp $(SO_FILE) $(FEE_PATH)/src/

libkdk.so:$(C_FILE)
	gcc $(C_FLAG) -o libkdk.so -fpic -shared $(C_FILE) $(INC_PATH)

clean:
	rm -rf $(SO_FILE)
