#include "IR_Send.hpp"

void IR_Send::generatePacket(uint8_t &data){
    packet = 0x0001;
//    if(player_ID > 31){
//        hwlib::cout << "INVALID PLAYER_ID. USING DEFAULT VALUE 0x1F" << hwlib::endl;
//        player_ID = 31;
//    }
//    if(data > 31){
//        hwlib::cout << "INVALID DATA. USING DEFAULT VALUE 0x1F" << hwlib::endl;
//        data = 31;
//    }
    data_xor = (player_ID ^ data);
    packet += uint16_t(player_ID << 1) + uint16_t(data << 6) + uint16_t(data_xor << 11);
}

void IR_Send::pulse(bool i){
    auto buf = hwlib::buffering::unbuffered;
    int l = 1600; int s = 800;
    if(i){
        pin.set(1,buf);
        hwlib::wait_us(l);
        pin.set(0,buf);
        hwlib::wait_us(s);
    }else{
        pin.set(1,buf);
        hwlib::wait_us(s);
        pin.set(0,buf);
        hwlib::wait_us(l);
    }
}

uint16_t IR_Send::getPacket(uint8_t &data){
    IR_Send::generatePacket(data);
    return packet;
}

void IR_Send::send(uint16_t D){
    for(int i=15; i>=0; i--){
        IR_Send::pulse((D >> i) & 1);
    }
}