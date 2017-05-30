#include <iostream>
#include <string.h>
using namespace std;

enum PINTYPE {
    PINTYPE_INPUT_ANALOG,   /*Read method analogRead shall be used*/
    PINTYPE_INPUT_DIGITAL,  /*Read method digitalRead shall be used*/
    PINTYPE_OUTPUT_ANALOG,  /*Write method analogWrite shall be used*/
    PINTYPE_OUTPUT_DIGITAL /*Write method digitalWrite shall be used*/
};

class CPin {
    private:
        int mNumber;
        int mValue;
       PINTYPE mType;
        char *mName;
        void GPin();
    public:
        
        void init(const char*strPinName, PINTYPE pinType, int pinNumber, int pinValue) {
            mName = NULL;
            setName(strPinName);
            mType = pinType;
           /* if (mType == PINTYPE_INPUT_ANALOG || mType == PINTYPE_INPUT_DIGITAL){
                pinMode(pinNumber, INPUT);
                mNumber = pinNumber;
                getValue();//to set the member mValue
            } 
            else { //TYPE IS PINTYPE_OUTPUT_DIGITAL or it is (ESP8266 && PINTYPE_OUTPUT_ANALOG)
                pinMode(pinNumber, OUTPUT);
                set(pinNumber, pinValue);
            }*/
        
        }
        void GPin(const char *strPinName, PINTYPE pinType, int pinNumber, int pinValue){init(strPinName, pinType, pinNumber, pinValue);}
        virtual const char *talk(){ return " CPin";};
        void setName(const char *newPinName) {
            if (newPinName == NULL) 
                return;
            if (mName != NULL) 
                delete[] mName;
            mName = new char[strlen(newPinName) + 1];
            strcpy(mName, newPinName);
        }
};

class CPinEsp32: public CPin{
    public:
        virtual const char *talk(){ return " CPinEsp32";}
        
};
class CPinEsp8266: public CPin{
    public:
        const char *talk(){ return " CPinEsp8266";}
};

class CPins {
    private:
        CPin **pins;
        int count;
    public:
        CPins(){count = 0;}
        void talk(){
            cout << "pins: " << count << endl; 
             cout << count << " : " << pins[0]->talk() << endl; 
            for(int i = 0; i<count;i++)
            {
             cout << cout << " : " << pins[i]->talk() << endl; 
            }
        }
        void add(CPin *addMe){
         pins[count] = addMe;
         count++;
        }
};

int main()
{
   CPin pin;
   cout << "talk " << pin.talk() << endl; 
   CPinEsp32 pin32;
   cout << "talk " << pin32.talk() << endl; 
   CPinEsp8266 pin8266;
   cout << "talk " << pin8266.talk() << endl; 
   /*CPins pins;
   pins.add(&pin);
   pins.add(&pin32);
   pins.add(&pin8266);
   pins.talk();*/
   /*cout << "Hello World" << endl; 
   cout << "talk " << pin.talk() << endl; 
   cout << "talk " << pin32.talk() << endl; */
   
   return 0;
}
