# Myriad-RF Module for the Novena Open Hardware Computing Plaform

This repository contains the design and manufacturing files for an RF module that adds 300MHz-3.8GHz broadband SDR transmit/receive capability to the [Novena Open Hardware Computing Platform](http://www.kosagi.com/w/index.php?title=Novena_Main_Page), along with RTL sources for interfacing implemented in the Novena FPGA.

## Contents

The directory structure for the hardware designs is as follows:

      /hardware/<version>/
          BOM/                   - bill of materials spreadsheet
          Gerbers/               - Gerber CAM files
          KiCAD/                 - KiCAD schematic and layout files
          Manufacturing/         - Additional manufacturing information
          PDF/                   - Schematic and layout PDFs
          Reports/               - DRC, ERC and drill reports

## Licensing

### Hardware design

The hardware design is licensed under a Creative Commons Attribution 3.0 Unported licence.

### FPGA design

The FPGA RTL is licensed under the Apache License, Version 2.0. However, please note that this does not extend to any files provided with the Xilinx design tools and see the relevant files for the associated terms and conditions.
