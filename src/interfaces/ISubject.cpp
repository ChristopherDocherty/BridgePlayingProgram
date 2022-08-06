#include "ISubject.hpp"
#include "IObserver.hpp"

#include <memory>        
#include <algorithm>        


void ISubject::detach(std::shared_ptr<IObserver> pObserver) {

    auto observerIterToErase = std::find(observerList.begin(), observerList.end(), pObserver);

    if (observerIterToErase != observerList.end()) {
        observerList.erase(observerIterToErase);
    }

}
