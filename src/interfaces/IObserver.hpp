#ifndef observer_h 
#define observer_h

#include <string>

class IObserver {

    public: 

        virtual ~IObserver() {};

        virtual void update(std::string) = 0;

};

#endif
