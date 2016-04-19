KDK_PATH=$(subst $(prefix),,$(shell pwd))
.PHONY:ALL
ALL:
	cd $(KDK_PATH)/src && make

clean:
	cd $(KDK_PATH)/src && make clean




