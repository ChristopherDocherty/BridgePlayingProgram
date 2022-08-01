#include "ISubject.hpp"
#include "IObserver.hpp"

#include <memory>        

void ISubject::attach(std::shared_ptr<IObserver> observer) {

    observerList.push_back(observer);

}

void ISubject::detach(std::shared_ptr<IObserver> observer) {

}
