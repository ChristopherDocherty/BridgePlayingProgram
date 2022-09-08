#include "ISubject.hpp"
#include "IObserver.hpp"

#include <algorithm>        
#include <memory>        


void ISubject::detach(std::shared_ptr<IObserver> pObserver) {

    auto observerIterToErase = std::find(observerList.begin(), observerList.end(), pObserver);

    if (observerIterToErase != observerList.end()) {
        observerList.erase(observerIterToErase);
    }

}
