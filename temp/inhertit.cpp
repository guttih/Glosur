#include <iostream>

using namespace std;
class CPin {
    private: 
    public:
        virtual const char *talk(){ return " CPin";};
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
   CPinEsp32 pin32;
   CPinEsp8266 pin8266;
   CPins pins;
   pins.add(&pin);
   pins.add(&pin32);
   pins.add(&pin8266);
   pins.talk();
   /*cout << "Hello World" << endl; 
   cout << "talk " << pin.talk() << endl; 
   cout << "talk " << pin32.talk() << endl; */
   
   return 0;
}
