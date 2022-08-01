#ifndef subject_h 
#define subject_h

#include "IObserver.hpp"

#include <memory>        
#include <list>

class ISubject {

    public:
        
        virtual ~ISubject();

        void attach(std::shared_ptr<IObserver> observer);
        void detach(std::shared_ptr<IObserver> observer);
        virtual void notify() = 0;

    private:

        std::list<std::shared_ptr<IObserver>> observerList;

};



#endif

