# 2021 Senior Project for Landon Page: Triple Modular Redundancy #

Project Presentation and Demo: https://www.youtube.com/watch?v=yBMrABR2kcc

Most of the code for this project can also be found at the GitHub repositories listed in my report, however I have made considerable
changes to the code, so I have posted the code I used for the project here.

To build and run the code, for anyone wanting to recreate this project, you will need the following software:

Xilinx Vivado (I used 2019.2) for the HDL Code
Xilinx Vitis IDE (also 2019.2) for the Drivers and Application Code

To build the HDL Code: Create a new project in Vivado, and from the IP catalog, import a MicroBlaze MCS object (label it cpu), and then
import the HDL code in the Actuator_Code folder. Generate the bitstream and then Export Hardware (include the bitstream). Also check the
constraint file (Nexys4_DDR_chu.xdc) to make sure your wires for the tx and rx from the Raspberry Pis are in the right pins on the PMOD ports
JC and JD.

To build the Application and Drivers: Create a new application project in Vitis, and use the .xsa file created from exporting your hardware
in Vivado as the platform for the Vitis project. Then in the src folder, import all the files from the Drivers and Application folders in the
Actuator_Code folder. Then build the project and use it to program the FPGA.

After the application is running on the FPGA and the Raspberry Pis are hooked up to the FPGA board, run the sdp_tmr.py file from the 
RaspberryPi_Code folder on the Pis.
