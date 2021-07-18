#include "Arduino.h"
#include <RadioLib.h>
#ifndef RADIOHAL_HPP
#define RADIOHAL_HPP


class IRadioHal {
public:
    virtual int16_t begin(float freq, float bw, uint8_t sf, uint8_t cr, uint8_t syncWord, int8_t power, uint16_t preambleLength, uint8_t gain, float tcxoVoltage) = 0;
    virtual int16_t beginFSK(float freq = 434.0, float br = 48.0, float freqDev = 50.0, float rxBw = 125.0, int8_t power = 10, uint16_t preambleLength = 16, bool enableOOK = false, float tcxoVoltage = 1.6, bool useRegulatorLDO = false) = 0;
    virtual int16_t autoLDRO() = 0;
    virtual int16_t forceLDRO(bool enable) = 0;
    virtual int16_t setCRC(bool enable) = 0;
    virtual int16_t setDataShaping(uint8_t sh) = 0;
    virtual void setDio0Action(void (*func)(void)) = 0;
    virtual int16_t startReceive(uint8_t len = 0, uint8_t mode = SX127X_RXCONTINUOUS) = 0;
    virtual int16_t transmit(uint8_t* data, size_t len, uint8_t addr = 0) = 0;
    virtual int16_t sleep() = 0;
    virtual size_t getPacketLength(bool update = true) = 0;
    virtual int16_t readData(uint8_t* data, size_t len) = 0;
    virtual float getRSSI(bool skipReceive = false) = 0;
    virtual float getSNR() = 0;
    virtual float getFrequencyError(bool autoCorrect = false) = 0;
    virtual int16_t fixedPacketLengthMode(uint8_t len) = 0;
    virtual int16_t setSyncWord(uint8_t* syncWord, uint8_t len) = 0;
};


template <typename T>
class RadioHal : public IRadioHal {
public:
    RadioHal(Module* mod)
    {
        radio = new T(mod);
    }

    int16_t begin(float freq, float bw, uint8_t sf, uint8_t cr, uint8_t syncWord, int8_t power, uint16_t preambleLength, uint8_t gain, float tcxoVoltage);
    int16_t beginFSK(float freq = 434.0, float br = 48.0, float freqDev = 50.0, float rxBw = 125.0, int8_t power = 10, uint16_t preambleLength = 16, bool enableOOK = false, float tcxoVoltage = 1.6, bool useRegulatorLDO = false);

    int16_t autoLDRO()
    {
        return radio->autoLDRO();
    }

    int16_t forceLDRO(bool enable)
    {
        return radio->forceLDRO(enable);
    }

    int16_t setCRC(bool enable)
    {
        return radio->setCRC(enable);
    }

    int16_t setDataShaping(uint8_t sh)
    {
        return radio->setDataShaping(sh);
    }

    void setDio0Action(void (*func)(void));

    int16_t startReceive(uint8_t len = 0, uint8_t mode = SX127X_RXCONTINUOUS);

    int16_t transmit(uint8_t* data, size_t len, uint8_t addr = 0)
    {
        return radio->transmit(data, len, addr);
    }

    int16_t sleep()
    {
        return radio->sleep();
    }

    size_t getPacketLength(bool update = true)
    {
        return radio->getPacketLength(update);
    }

    int16_t readData(uint8_t* data, size_t len)
    {
        return radio->readData(data, len);
    }

    float getRSSI(bool skipReceive = false);

    float getSNR()
    {
        return radio->getSNR();
    }

    float getFrequencyError(bool autoCorrect = false);

    int16_t fixedPacketLengthMode(uint8_t len)
    {
        return fixedPacketLengthMode(len);
    }

    int16_t setSyncWord(uint8_t* syncWord, uint8_t len)
    {
        return setSyncWord(syncWord, len);
    }
    

private:
    T* radio;
};


#endif