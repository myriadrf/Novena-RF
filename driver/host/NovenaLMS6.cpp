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
    _lms6ctrl->LoadAdditionalSettings();

    _lms6ctrl->SetReferenceFrequency(this->getMasterClockRate(), true/*Rx*/);
    _lms6ctrl->SetReferenceFrequency(this->getMasterClockRate(), false/*Tx*/);
}

void NovenaRF::exitRFIC(void)
{
    delete _lms6ctrl;
    _lms6ctrl = nullptr;
}

/*******************************************************************
 * Gain API
 ******************************************************************/
std::vector<std::string> NovenaRF::listGains(const int direction, const size_t channel) const
{
    
}

void NovenaRF::setGain(const int direction, const size_t channel, const double value)
{
    
}

void NovenaRF::setGain(const int direction, const size_t channel, const std::string &name, const double value)
{
    
}

double NovenaRF::getGain(const int direction, const size_t channel, const std::string &name) const
{
    
}

SoapySDR::Range NovenaRF::getGainRange(const int direction, const size_t channel) const
{
    
}

SoapySDR::Range NovenaRF::getGainRange(const int direction, const size_t channel, const std::string &name) const
{
    
}

/*******************************************************************
 * Frequency API
 ******************************************************************/
void NovenaRF::setFrequency(const int direction, const size_t channel, const double frequency, const SoapySDR::Kwargs &args)
{
    double realFreq, fVco;
    unsigned Nint, Nfrac, iVco;
    int divider;

    _lms6ctrl->SetFrequency(direction == SOAPY_SDR_RX, frequency, realFreq, Nint, Nfrac, iVco, fVco, divider);
    _lms6ctrl->Tune(direction == SOAPY_SDR_RX);
    _cachedTuneResults[direction] = realFreq;
}

double NovenaRF::getFrequency(const int direction, const size_t) const
{
    return _cachedTuneResults.at(direction);
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
    return bws;
}
