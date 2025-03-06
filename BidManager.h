#ifndef BIDMANAGER_H
#define BIDMANAGER_H

class BidManager{
    public:
        static BidManager* getInstance() {
            if (instance == nullptr) {
                instance = new BidManager();
            }
            return instance;
        }

    private:
        static BidManager* instance;
        BidManager();
};


#endif