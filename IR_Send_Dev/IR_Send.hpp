#ifndef IR_SEND_HPP
#define IR_SEND_HPP

#include "hwlib.hpp"

class IR_Send{
private:
    uint8_t player_ID;  //%00'0001-%11'1111
    uint8_t data;       //%00'0000-%11'1111
    uint8_t data_xor;
    uint16_t packet = 0x8000;  //%1000'0000'0000'0000
    hwlib::target::d2_36kHz pin;
    
    void generatePacket(uint8_t &data);
    void pulse(bool i);
    
public:
    IR_Send(hwlib::target::d2_36kHz &pin, uint8_t &player_ID):
        player_ID(player_ID), pin(pin){}
    
    uint16_t getPacket(uint8_t &data);
    void send(uint16_t D);

};

#endif // IR_SEND_HPP