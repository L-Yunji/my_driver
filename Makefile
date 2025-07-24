# 커널 모듈 타겟
obj-m := mydriver.o

# 커널 헤더 경로
KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

# 디바이스 트리 관련
DTS := mydriver-overlay.dts
DTBO := mydriver.dtbo

all: mydriver.ko $(DTBO)

mydriver.ko:
	make -C $(KDIR) M=$(PWD) modules

$(DTBO): $(DTS)
	dtc -I dts -O dtb -o $(DTBO) $(DTS)

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -f $(DTBO)
