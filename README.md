# 7segmultiplexedDisplaydriverwithDMA
7 seg ment display driver with using pin multiplexing and DMA , only 8 pins multiplex with all the semets and one pin for each digit.

Steps to import this driver:
Step 1: Find the port address to whioch the display is interfaced.
Step 2: Find the timer which can trigger the DMA transfer (you can run DMA in free run also, in this case you will not have control over refresh rate iof display ).
Step 3: Implement timer and DMA initiallisation in display_init() funtion.
Step 4: Start the DNA first and then timer(calculate freq: desired_display_frequnecy / numberof_transfers) in display_start() function.
Step 5: Use provided functions to write on display.
