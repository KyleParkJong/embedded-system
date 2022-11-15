obj-m += seg_driver.o
KDIR = ~/working/kernel
RESULT = seg_example
SRC = $(RESULT).c
RESULT2 = seg_example2
SRC2 = $(RESULT2).c
CCC = gcc

all:
        make -C $(KDIR) M=$(PWD) modules
        $(CCC) -o $(RESULT) $(SRC)
        $(CCC) -o $(RESULT2) $(SRC2)

clean:
        maek -C $(KDIR) M=$(PWD) clean
        re -f $(RESULT)
        re -f $(RESULT2)
