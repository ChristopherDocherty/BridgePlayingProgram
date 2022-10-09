#ifndef observer_h 
#define observer_h

#include <string>

class IObserver {

    public: 

        virtual ~IObserver() {};

        virtual void update(const std::string& gamestate) const = 0;

};

#endif
