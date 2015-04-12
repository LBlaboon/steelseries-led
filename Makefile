# Build rules
steelseries-led: steelseries-led.c
	gcc -std=gnu99 -lhidapi-libusb -o steelseries-led steelseries-led.c

.PHONY: clean

clean:
	rm -f steelseries-led
