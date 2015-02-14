////////////////////////////////////////////////////////////////////////
// SoapySDR module for Novena-RF SDR
//
// Copyright (c) 2015-2015 Lime Microsystems
// Copyright (c) 2015-2015 Andrew "bunnie" Huang
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
////////////////////////////////////////////////////////////////////////

#include "NovenaRF.hpp"
#include "LMS6002_MainControl.h"
#include "CompoundOperations.h"
#include "CompoundOperations.h"

/***********************************************************************
 * Log handler from the lms suite
 **********************************************************************/
class SignalHandlerLogger : public SignalHandler
{
public:
    SignalHandlerLogger(void)
    {
        return;
    }

    void HandleMessage(const LMS_Message &msg)
    {
        switch (msg.type)
        {
        case MSG_ERROR: SoapySDR::log(SOAPY_SDR_ERROR, msg.text); break;
        case MSG_WARNING: SoapySDR::log(SOAPY_SDR_WARNING, msg.text); break;
        default: SoapySDR::log(SOAPY_SDR_INFO, msg.text); break;
        }
    }
};

static SignalHandlerLogger myLogger;

/***********************************************************************
 * Setup and tear-down hooks
 **********************************************************************/
void NovenaRF::initRFIC(void)
{
    auto ser = new ConnectionManager();
    ser->RegisterForNotifications(&myLogger);
    ser->Open();

    //main control owns the connection manager
    _lms6ctrl = new lms6::LMS6002_MainControl(ser);
    _lms6ctrl->ResetChip(LMS_RST_PULSE);
    _lms6ctrl->NewProject();

    _lms6ctrl->SetReferenceFrequency(this->getMasterClockRate(), true/*Rx*/);
    _lms6ctrl->SetReferenceFrequency(this->getMasterClockRate(), false/*Tx*/);

    _lms6ctrl->SetParam(lms6::STXEN, 1); //enable transmitter
    _lms6ctrl->SetParam(lms6::SRXEN, 1); //enable receiver

    //enable all the things
    _lms6ctrl->SetParam(lms6::EN_TOP, 1);
    _lms6ctrl->SetParam(lms6::EN_RXPLL, 1);
    _lms6ctrl->SetParam(lms6::EN_TXPLL, 1);
    _lms6ctrl->SetParam(lms6::EN_ADC_DAC, 1);
    _lms6ctrl->SetParam(lms6::EN_TXRF, 1);
    _lms6ctrl->SetParam(lms6::EN_RXFE, 1);
    _lms6ctrl->SetParam(lms6::EN_RXLPF, 1);
    _lms6ctrl->SetParam(lms6::EN_TXLPF, 1);
    _lms6ctrl->SetParam(lms6::EN_RXVGA2, 1);
    lms6::CompoundOperations(_lms6ctrl).CustSet_RxVGA2PowerON();
    lms6::CompoundOperations(_lms6ctrl).CustSet_LNAPowerON();
    lms6::CompoundOperations(_lms6ctrl).CustSet_RxLpfPowerON();
    lms6::CompoundOperations(_lms6ctrl).CustSet_RxFePowerON();

    //bypass LPF by default with large BW
    this->setBandwidth(SOAPY_SDR_TX, 0, 30.0e6);
    this->setBandwidth(SOAPY_SDR_RX, 0, 30.0e6);

    //initialize to minimal gain settings
    this->setGain(SOAPY_SDR_TX, 0, 0.0);
    this->setGain(SOAPY_SDR_RX, 0, 0.0);
}

void NovenaRF::exitRFIC(void)
{
    _lms6ctrl->SetParam(lms6::STXEN, 0); //disable transmitter
    _lms6ctrl->SetParam(lms6::SRXEN, 0); //disable receiver
    lms6::CompoundOperations(_lms6ctrl).CustSet_RxVGA2PowerOFF();
    lms6::CompoundOperations(_lms6ctrl).CustSet_LNAPowerOFF();
    lms6::CompoundOperations(_lms6ctrl).CustSet_RxLpfPowerOFF();
    lms6::CompoundOperations(_lms6ctrl).CustSet_RxFePowerOFF();

    delete _lms6ctrl;
    _lms6ctrl = nullptr;
}

/*******************************************************************
 * Gain API
 ******************************************************************/
std::vector<std::string> NovenaRF::listGains(const int direction, const size_t channel) const
{
    std::vector<std::string> gains;
    if (direction == SOAPY_SDR_TX)
    {
        gains.push_back("VGA1");
        gains.push_back("VGA2");
    }
    if (direction == SOAPY_SDR_RX)
    {
        gains.push_back("VGA2");
        gains.push_back("LNA");
    }
    return gains;
}

#define MinMaxClip(minimum, maximum, value) \
    std::max(minimum, std::min(maximum, value))

void NovenaRF::setGain(const int direction, const size_t channel, const double value)
{
    //distribute gain automatically
    //for tx distribute to VGA1 first
    if (direction == SOAPY_SDR_TX)
    {
        if (value > 31.0)
        {
            this->setGain(direction, channel, "VGA1", -4.0);
            this->setGain(direction, channel, "VGA2", value-31.0);
        }
        else
        {
            this->setGain(direction, channel, "VGA1", value-35.0);
            this->setGain(direction, channel, "VGA2", 0.0);
        }
    }
    //for rx distribute to LNA first
    if (direction == SOAPY_SDR_RX)
    {
        if (value > 6.0)
        {
            this->setGain(direction, channel, "LNA", 6.0);
            this->setGain(direction, channel, "VGA2", value-6.0);
        }
        else
        {
            this->setGain(direction, channel, "LNA", 0.0);
            this->setGain(direction, channel, "VGA2", value);
        }
    }
}

void NovenaRF::setGain(const int direction, const size_t channel, const std::string &name, const double value)
{
    if (direction == SOAPY_SDR_TX and name == "VGA1")
    {
        const double regVal(MinMaxClip(-35.0, -4.0, value));
        _lms6ctrl->SetParam(lms6::VGA1GAIN, lrint(regVal+35.0));
    }
    if (direction == SOAPY_SDR_TX and name == "VGA2")
    {
        const double regVal(MinMaxClip(0.0, 25.0, value));
        _lms6ctrl->SetParam(lms6::VGA2GAIN_TXVGA2, lrint(regVal));
    }
    if (direction == SOAPY_SDR_RX and name == "VGA2")
    {
        const double regVal(MinMaxClip(0.0, 30.0, value));
        _lms6ctrl->SetParam(lms6::VGA2GAIN_RXVGA2, lrint(regVal/3.0));
    }
    if (direction == SOAPY_SDR_RX and name == "LNA")
    {
        const double regVal(MinMaxClip(0.0, 6.0, value));
        _lms6ctrl->SetParam(lms6::G_LNA_RXFE, 2 | lrint(regVal/6.0));
    }
}

double NovenaRF::getGain(const int direction, const size_t channel, const std::string &name) const
{
    if (direction == SOAPY_SDR_TX and name == "VGA1")
    {
        return _lms6ctrl->GetParam(lms6::VGA1GAIN) - 35.0;
    }
    if (direction == SOAPY_SDR_TX and name == "VGA2")
    {
        return _lms6ctrl->GetParam(lms6::VGA2GAIN_TXVGA2);
    }
    if (direction == SOAPY_SDR_RX and name == "VGA2")
    {
        return _lms6ctrl->GetParam(lms6::VGA2GAIN_RXVGA2)*3.0;
    }
    if (direction == SOAPY_SDR_RX and name == "LNA")
    {
        return (_lms6ctrl->GetParam(lms6::G_LNA_RXFE) & 0x1)*6.0;
    }
    return SoapySDR::Device::getGain(direction, channel, name);
}

double NovenaRF::getGain(const int direction, const size_t channel) const
{
    if (direction == SOAPY_SDR_TX) return this->getGain(direction, channel, "VGA1") + 35 + this->getGain(direction, channel, "VGA2");
    if (direction == SOAPY_SDR_RX) return this->getGain(direction, channel, "VGA2") + this->getGain(direction, channel, "LNA");
    return SoapySDR::Device::getGain(direction, channel);
}

SoapySDR::Range NovenaRF::getGainRange(const int direction, const size_t channel) const
{
    //overall range presented to the user
    if (direction == SOAPY_SDR_TX) return SoapySDR::Range(0.0, 56.0);
    if (direction == SOAPY_SDR_RX) return SoapySDR::Range(0.0, 36.0);
    return SoapySDR::Device::getGainRange(direction, channel);
}

SoapySDR::Range NovenaRF::getGainRange(const int direction, const size_t channel, const std::string &name) const
{
    if (direction == SOAPY_SDR_TX and name == "VGA1") return SoapySDR::Range(-35.0, -4.0);
    if (direction == SOAPY_SDR_TX and name == "VGA2") return SoapySDR::Range(0.0, 25.0);
    if (direction == SOAPY_SDR_RX and name == "VGA2") return SoapySDR::Range(0.0, 30.0);
    if (direction == SOAPY_SDR_RX and name == "LNA") return SoapySDR::Range(0.0, 6.0);
    return SoapySDR::Device::getGainRange(direction, channel, name);
}

/*******************************************************************
 * Frequency API
 ******************************************************************/
void NovenaRF::setFrequency(const int direction, const size_t channel, const double frequency, const SoapySDR::Kwargs &args)
{
    double realFreq, fVco;
    unsigned Nint, Nfrac, iVco;
    int divider;

    _lms6ctrl->SetFrequency(direction == SOAPY_SDR_RX, frequency/1e6, realFreq, Nint, Nfrac, iVco, fVco, divider);
    _lms6ctrl->Tune(direction == SOAPY_SDR_RX);

    //select the TX PAs or RX LNAs based on frequency
    //these calls also modify external RF switch GPIOs
    if (direction == SOAPY_SDR_TX)
    {
        //1: High band output (1500 - 3800 MHz)
        //2: Broadband output
        if (realFreq >= 1500) _lms6ctrl->SetParam(lms6::PA_EN, 1);
        else                    _lms6ctrl->SetParam(lms6::PA_EN, 2);
        SoapySDR::logf(SOAPY_SDR_TRACE, "NovenaRF: TxTune(%f MHz), actual = %f MHz, PA_EN=%d", frequency/1e6, realFreq, _lms6ctrl->GetParam(lms6::PA_EN));
    }
    else
    {
        //1: Low band input (300 - 2200 MHz)
        //2: High band input (1500-3800MHz)
        //3: Broadband input
        if (realFreq >= 1850) lms6::CompoundOperations(_lms6ctrl).SetLnaChain(1);
        else                    lms6::CompoundOperations(_lms6ctrl).SetLnaChain(2);
        SoapySDR::logf(SOAPY_SDR_TRACE, "NovenaRF: RxTune(%f MHz), actual = %f MHz, LNASEL=%d", frequency/1e6, realFreq, _lms6ctrl->GetParam(lms6::LNASEL_RXFE));
    }
}

double NovenaRF::getFrequency(const int direction, const size_t) const
{
    return _lms6ctrl->GetFrequency(direction == SOAPY_SDR_RX)*1e6;
}

SoapySDR::RangeList NovenaRF::getFrequencyRange(const int direction, const size_t channel) const
{
    return SoapySDR::RangeList(1, SoapySDR::Range(0.3e9, 3.8e9));
}

/*******************************************************************
 * Bandwidth filters API
 ******************************************************************/
void NovenaRF::setBandwidth(const int direction, const size_t channel, const double bw)
{
    //map the requested frequency to the next greatest bandwidth setting
    const auto bws = this->listBandwidths(direction, channel);
    long val = 0;
    while (val < 0xf)
    {
        if (bw >= bws.at(val)) break;
        val++;
    }

    //bypass when BW is larger than max filter
    const bool bypass = (bw/2.0 > 14e6);
    if (direction == SOAPY_SDR_TX and bypass)     lms6::CompoundOperations(_lms6ctrl).CustSet_BypassTxLpfON();
    if (direction == SOAPY_SDR_TX and not bypass) lms6::CompoundOperations(_lms6ctrl).CustSet_BypassTxLpfOFF();
    if (direction == SOAPY_SDR_RX and bypass)     lms6::CompoundOperations(_lms6ctrl).CustSet_BypassRxLpfON();
    if (direction == SOAPY_SDR_RX and not bypass) lms6::CompoundOperations(_lms6ctrl).CustSet_BypassRxLpfOFF();

    //write the setting
    const auto reg = (direction == SOAPY_SDR_RX)?lms6::BWC_LPF_RXLPF:lms6::BWC_LPF_TXLPF;
    _lms6ctrl->SetParam(reg, val);
}

double NovenaRF::getBandwidth(const int direction, const size_t channel) const
{
    const auto reg = (direction == SOAPY_SDR_RX)?lms6::BWC_LPF_RXLPF:lms6::BWC_LPF_TXLPF;
    long val = _lms6ctrl->GetParam(reg);
    return this->listBandwidths(direction, channel).at(val & 0xf);
}

std::vector<double> NovenaRF::listBandwidths(const int direction, const size_t channel) const
{
    std::vector<double> bws;
    bws.push_back(14e6);
    bws.push_back(10e6);
    bws.push_back(7e6);
    bws.push_back(6e6);
    bws.push_back(5e6);
    bws.push_back(4.375e6);
    bws.push_back(3.5e6);
    bws.push_back(3e6);
    bws.push_back(2.75e6);
    bws.push_back(2.5e6);
    bws.push_back(1.92e6);
    bws.push_back(1.5e6);
    bws.push_back(1.375e6);
    bws.push_back(1.25e6);
    bws.push_back(0.875e6);
    bws.push_back(0.75e6);
    for (auto &bw : bws) bw *= 2; //convert to complex width in Hz
    return bws;
}
