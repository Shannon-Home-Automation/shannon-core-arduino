#include "Arduino.h"
#include "devices.h"
#include <SoftwareSerial.h>

class NetworkAdaptor{
    private:
    Device devices[20];
    int deviceListIndex = 0;
    SoftwareSerial port;

    public:
    NetworkAdaptor(SoftwareSerial port){
        this->port = port;
        this->port.begin(9600);
    }

    void addDevice(Device device){
        this->devices[deviceListIndex] = device;
        this->deviceListIndex =+ 1;
    }

    void addDevices(Device devices[], int count){
        for(int i=0; i<count; i++){
            this->addDevice(devices[i]);
        }
    }
    
    void begin(){
        for(int i=0; i<=this->deviceListIndex; i++){
            this->devices[i].begin();
        }
    }

    void receive(){
        byte serialBuff[2];
        if (this->port.available()){
            
            this->port.readBytes(serialBuff, 2);
            byte id = serialBuff[0];
            byte command = serialBuff[1];
            

            // requesting device list
            if (id == byte(0x00)){
                for(int i=0; i<=this->deviceListIndex; i++){
                    Device device = this->devices[i];
                    this->send(byte(0x00), device.id());
                }
                return;
            }

            // requesting device executation code
            for(int i=0; i<=this->deviceListIndex; i++){
                Device device = this->devices[i];
                device.executeCodeWithId(command, id);
            }
        }
    }
    
    void send(byte code, byte id){
        this->port.write(id);
        this->port.write(code);
    }
};