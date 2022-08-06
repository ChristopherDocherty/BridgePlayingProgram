#ifndef observer_h 
#define observer_h

class IObserver {

    public: 

        virtual ~IObserver();

        //some JSON type as the argument here
        virtual void update(std::string) = 0;

};

#endif
