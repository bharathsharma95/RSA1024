# RSA1024
This implementation of RSA is on an FPGA platform to test the performance of the algorithm in terms of latency as a comparison to AES

The C++ implementation works real fine for simulation in Vivado HLS but the code still has to be modified to make it work on hardware as Vivado HLS doesn't support Recursive functions and lot many others.

I am working on modifying the code for synthesis on a Zynq7000 FPGA Zedboard and will update the code soon
