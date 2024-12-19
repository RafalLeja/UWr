#include <memory>

#include "Updater.hpp"
#include "GreeterUpdater.hpp"

class LazyUpdater: public Updater {
public:
    LazyUpdater()
    {}

    void checkForUpdates(){
        longUpdater = std::make_unique<GreeterUpdater>();

        longUpdater->checkForUpdates();
    }

private:
    std::unique_ptr<Updater> longUpdater;
};