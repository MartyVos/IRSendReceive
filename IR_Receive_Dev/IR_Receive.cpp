#include "IR_receive.hpp"

void IR_Receive::decodeData(){
    ID = ((dataIn >> 1) & 0x1F);
    data = ((dataIn >> 6) & 0x1F);
	invalidXor = !checkXor();
}

bool IR_Receive::checkXor(){
    if(((dataIn >> 11) & 0x1F) == (ID ^ data)){
        return true;
    }
    return false;
}

void IR_Receive::getDecodedData(){
    decData[0] = ID;
    decData[1] = data;
}

std::array<uint8_t, 2> IR_Receive::receive(){
    //hwlib::wait_ms(4);
    dataIn = 0;
    int i=15;
    while(i>=0){
		hwlib::wait_us(100);
        t = pin.get();
        TNOW = hwlib::now_us();
        while(t == 0){
			hwlib::wait_us(50);
            if(pin.get() == 1){
                break;
            }
        }
        auto tmp = hwlib::now_us()-TNOW;
        if(tmp >= 700 && tmp < 1100){
            dataIn += 0;
            i--;
        }else if(tmp >= 1500 && tmp < 1900){
            dataIn += (!t << i);
            i--;
        }else{
			i = 15;
			dataIn = 0;
		}
    }
//        hwlib::wait_us(POT.get());
//        hwlib::cout << hwlib::bin << dataIn << hwlib::endl;
    decodeData();
    if(!invalidXor){
        getDecodedData();
        return decData;
    }
    return {uint8_t(0xFF), uint8_t(0xFF)};
}