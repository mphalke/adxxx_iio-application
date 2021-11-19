Now into test branch...
-----
Evaluation Boards/Products Supported
------------------------------------ 
EVAL-AD70081z_ARDZ

Overview
--------
This is a IIO based firmware application to evalute the AD70081z device.
This code was developed and tested on SDP-K1 and ADuCM410 controller boards.
Use of Mbed platform allows code to port on other Mbed supported target boards with little or no modifications.

Communication Protocol: SPI


Hardware Setup
--------------
Required: SDP-K1 (or alternative Mbed enabled controller board), ADuCM410 Controller Board, EVAL-AD70081z board and USB cable.
Plug in the EVAL-AD70081z board on SDP-K1/ADuCM410 board using Arduino interface header 
(refer software wiki page to identify suitable interface).
Connect SDP-K1/ADuCM410 board to the PC using the USB cable.


How to Get Started
------------------
Open Mbed online compiler. https://ide.mbed.com/compiler
Instructions on how to import code are here: https://os.mbed.com/docs/mbed-os/v5.12/tools/importing-code.html
Compile code. Drag and drop binary into SDP-K1 controller board. Find detailed 
instructions here: https://os.mbed.com/docs/mbed-os/v5.12/tools/getting-your-program-on-your-board.html
For ADuCM410, refer software user guide.
Open IIO Oscilloscope (or alternative GUI), select 230400 baud rate, and the applicable COM 
port to see the list of options.


Notes
-----
If using Win 7, install serial drivers for Mbed. https://os.mbed.com/docs/mbed-os/v5.12/tutorials/windows-serial-driver.html
A detailed user guide on SDP-K1 controller board is available here https://www.analog.com/en/design-center/evaluation-hardware-and-software/evaluation-boards-kits/SDP-K1.html.


Copyright (c) 2021 Analog Devices, Inc.  All rights reserved.

