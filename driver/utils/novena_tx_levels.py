########################################################################
## Test utility to drive a constant level through Novena RF
########################################################################

import SoapySDR
from SoapySDR import * #SOAPY_SDR_ constants
import numpy as np
from optparse import OptionParser
import time
import signal

def transmit_level(
    args,
    rate,
    freq=None,
    offset=None,
    chan=0,
    ant=None,
    vga1=None,
    vga2=None,
    clockRate=None,
    ampl=0.3,
):
    sdr = SoapySDR.Device(args)

    #set clock rate first
    if clockRate is not None: sdr.setMasterClockRate(clockRate)

    #set sample rate
    sdr.setSampleRate(SOAPY_SDR_TX, chan, rate)
    print("Actual Tx Rate %f Msps"%(sdr.getSampleRate(SOAPY_SDR_TX, chan)/1e6))

    #set antenna
    if ant is not None: sdr.setAntenna(SOAPY_SDR_TX, chan, ant)

    #set gains
    if vga1 is not None:
        sdr.setGain(SOAPY_SDR_TX, chan, "VGA1", vga1)
        print("Actual VGA1 = %f"%sdr.getGain(SOAPY_SDR_TX, chan, "VGA1"))
    if vga2 is not None:
        sdr.setGain(SOAPY_SDR_TX, chan, "VGA2", vga2)
        print("Actual VGA2 = %f"%sdr.getGain(SOAPY_SDR_TX, chan, "VGA2"))

    #tune frontends
    if freq is not None:
        args = {}
        if offset is not None: args["OFFSET"] = str(offset)
        sdr.setFrequency(SOAPY_SDR_TX, chan, freq, args)
        for compName in sdr.listFrequencies(SOAPY_SDR_TX, chan):
            print("Actual Frequency(%s) = %f MHz"%(compName, sdr.getFrequency(SOAPY_SDR_TX, chan, compName)/1e6))
        print("Actual Frequency(overall) = %f MHz"%(sdr.getFrequency(SOAPY_SDR_TX, chan)/1e6))

    #create the tx stream
    print("Create Tx stream")
    txStream = sdr.setupStream(SOAPY_SDR_TX, "CF32", [chan])

    #install signal handler for continuous loop
    print('Transmit loop begin: Press Ctrl+C to exit...')
    user_exit = list()
    def signal_handler(signal, frame):
        print('User exit requested!')
        user_exit.append("EXIT")
    signal.signal(signal.SIGINT, signal_handler)

    #transmit a continuous level
    sdr.activateStream(txStream)
    """
    samples = np.array([ampl]*sdr.getStreamMTU(txStream)).astype(np.complex64)
    while not user_exit:
        sr = sdr.writeStream(txStream, [samples], len(samples))
        if sr.ret != len(samples): raise Exception('transmit failed %s'%str(sr))
    """
    sdr.writeRegister(72, int(ampl*(1 << 15))) #write(addr, fixed point ampl)
    while not user_exit: time.sleep(0.1)

    #cleanup tx stream
    print("Cleanup streams")
    sdr.deactivateStream(txStream)
    sdr.closeStream(txStream)
    print("Done!")

def main():
    parser = OptionParser()
    parser.add_option("--args", type="string", dest="args", help="device factor arguments", default="")
    parser.add_option("--rate", type="float", dest="rate", help="Tx and Rx sample rate", default=0.96e6/2)
    parser.add_option("--ant", type="string", dest="ant", help="Optional Tx antenna", default=None)
    parser.add_option("--vga1", type="float", dest="vga1", help="Optional Tx VGA1 gain (dB)", default=None)
    parser.add_option("--vga2", type="float", dest="vga2", help="Optional Tx VGA2 gain (dB)", default=None)
    parser.add_option("--chan", type="int", dest="chan", help="Transmitter channel (def=0)", default=0)
    parser.add_option("--freq", type="float", dest="freq", help="Optional Tx freq (Hz)", default=None)
    parser.add_option("--offset", type="float", dest="offset", help="Optional Tx tune offset (Hz)", default=None)
    parser.add_option("--ampl", type="float", dest="ampl", help="Digital amplitude [0.0 - 1.0] ", default=0.3)
    parser.add_option("--clockRate", type="float", dest="clockRate", help="Optional clock rate (Hz)", default=None)
    (options, args) = parser.parse_args()
    transmit_level(
        args=options.args,
        rate=options.rate,
        freq=options.freq,
        offset=options.offset,
        ant=options.ant,
        vga1=options.vga1,
        vga2=options.vga2,
        chan=options.chan,
        ampl=options.ampl,
        clockRate=options.clockRate,
    )

if __name__ == '__main__': main()
