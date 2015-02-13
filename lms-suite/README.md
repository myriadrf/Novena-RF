# LMS Suite

Utilities for use with Myriad-RF hardware based upon FPRF transceivers from Lime Microsystems.

The utilities:

* can be used to calibrate the transceiver;
* allow configuration of the transceiver plus support devices such as clock generators;
* provide an FFT display.

Please note that the strategic solution is a single binary called *lms-suite*. However, at the time of writing this software only supports the Novena-RF module.

Owners of Reference Development Kit (Myriad-RF 1 + DE0-Nano interface/Zipper) and RASDR (Myriad-RF 1 + DigiRED) hardware should use the board-specific legacy software for the present time.

## Legacy

### ctr_6002dr2_myriad

This is for use with the original DE0-Nano interface board and is a Windows-only application.

### control_LMS6002

This is for use with the Zipper interface board (FMC and HSMC) and can be built for Windows or Linux.

### FFTviewer

This is for use with the DE0-Nano and RASDR DigiRED interfaces, and can be built for Windows or Linux.

Licence
-------

This software is published under the Apache License Version 2.0.

For further details please see the [COPYING](https://raw.github.com/myriadrf/myriadrf-utils/master/COPYING) file.
