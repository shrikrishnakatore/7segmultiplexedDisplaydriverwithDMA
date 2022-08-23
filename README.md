# 7segmultiplexedDisplaydriverwithDMA<br /> 
7 segment display driver using pin multiplexing and DMA, only 8 pins multiplex with all the segments and one pin for each position.<br /> 



## This driver assumes that the display pins are multiplexed in following fasion and the 7 segment display is in COMMON CATHODE configuration <br /> 
 Display_port pin0: Seg_1(a) (of position 1..8)<br />
        "     pin1: seg_2(b)   "<br /> 
       "      pin2: seg_3(c)   "<br /> 
       "      pin3: seg_2(d)   "<br /> 
       "      pin4: seg_2(e)   "<br /> 
       "      pin5: seg_2(f)   "<br /> 
       "      pin6: seg_2(g)   "<br /> 
       "      pin7: seg_2(dp)   "<br /> 
       "      pin8: com_1   (common cathode of position 1)<br /> 
       "      pin9: com_2   (common cathode of position 2)<br /> 
       "      pin10: com_3   (common cathode of position 3)<br /> 
       "      pin11: com_4   (common cathode of position 4)<br /> 
       "      pin12: com_5   (common cathode of position 5)<br /> 
       "      pin13: com_6   (common cathode of position 6)<br /> 
       "      pin14: com_7   (common cathode of position 7)<br /> 
       "      pin15: com_8   (common cathode of position 8)<br /> 
       <br /> 
## If connections are diffrent than this then you must chnages the function display_write() implementation based on your display connections.<br /> 



Steps to import this driver:<br /> 
Step 1: Find the port address to which the display is interfaced.<br /> 
Step 2: Find the timer which can trigger the DMA transfer (you can run DMA in free run also, in this case you will not have control over refresh rate of display ).<br /> 
Step 3: Implement timer and DMA initiallisation in display_init() funtion.<br /> 
Step 4: Start the DNA first and then timer(calculate freq: desired_display_frequnecy / numberof_transfers) in display_start() function.<br /> 
Step 5: Use provided functions to write on display.<br /> 
