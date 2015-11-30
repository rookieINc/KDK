include $(WORK_HOME)/make/makeobj.inc

NAN_C_FILE=nan_hash.c nan_mem_pool.c nan_malloc.c nan_stack.c nan_queue.c
NAN_H_FILE=nan_mem_pool.h nan_malloc.h nan_hash.h nan_string.h nan_butterfly.h nan_stack.h nan_queue.h
NAN_SO_FILE=libglx.so

SO_LINK=-lglx 
C_FILE=demo.c
BIN_FILE=demo

.PHONY:all
all:$(NAN_SO_FILE) 

libglx.so:$(NAN_C_FILE)
	$(CC) $(CC_FLAGS) -o libglx.so -fpic -shared $(NAN_C_FILE) $(INC_PATH)

demo:$(C_FILE)
	$(CC) $(CC_FLAGS) -g -o demo $(C_FILE) $(INC_PATH) $(LIB_PATH) $(SO_LINK)


install:
	make clean
	make $(NAN_SO_FILE) 
	cp $(NAN_H_FILE) $(H_FILE) $(WORK_HOME)/inc
	cp $(NAN_SO_FILE) $(WORK_HOME)/lib
	make demo
	cp -f $(BIN_FILE) $(WORK_HOME)/bin

clean:
	rm -f $(NAN_SO_FILE) $(BIN_FILE)
