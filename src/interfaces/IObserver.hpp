#ifndef observer_h 
#define observer_h

class IObserver {

    public: 

        virtual ~IObserver();

        //some JSON type as the argument here
        virtual void update() = 0;

};

#endif
