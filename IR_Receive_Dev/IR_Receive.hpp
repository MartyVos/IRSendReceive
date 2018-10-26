#ifndef IR_RECEIVE_HPP
#define IR_RECEIVE_HPP

#include <array>
#include "hwlib.hpp"

class IR_Receive{
private:
    hwlib::target::pin_in pin;
    bool t;
    uint8_t ID;
    uint8_t data;
    uint16_t dataIn;
    uint_fast64_t TNOW;
    std::array<uint8_t, 2> decData;
    bool invalidXor = false;
    
    void decodeData();
    bool checkXor();
    void getDecodedData();
public:
    IR_Receive(hwlib::target::pin_in &pin):
        pin(pin)
    {}
    std::array<uint8_t, 2> receive();
};

#endif // IR_RECEIVE_HPP