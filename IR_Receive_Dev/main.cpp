#include "hwlib.hpp"
#include "IR_receive.hpp"

int main(){
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 1000 );
    namespace target = hwlib::target;
    
    auto IN = target::pin_in(target::pins::d33);
    
    IR_Receive Rec(IN);
    for(;;){
        auto A = Rec.receive();
        hwlib::cout << hwlib::hex << A[0] << "\t" << A[1] << hwlib::endl;
    }
}