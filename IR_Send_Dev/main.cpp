#include "hwlib.hpp"
#include "IR_Send.hpp"

int main(){
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 1000 );
    namespace target = hwlib::target;
    
    auto OUT = target::d2_36kHz();
    auto end = target::pin_out(target::pins::d31);
    uint8_t ID = 0B11011;
    uint8_t D  = 0B00000;
    IR_Send IR(OUT, ID);
    uint16_t data;
    int n = 0;
    uint8_t z;
    auto POT = hwlib::target::pin_adc(hwlib::target::ad_pins::a11);
    
    for(;;){
        z = D+n;
        data = IR.getPacket(z);
        end.set(1);
        IR.send(data);
        end.set(0);
        hwlib::wait_us(21'000);
        if(n==31) n=0;
        else n++;
    }
}