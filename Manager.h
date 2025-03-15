#ifndef MANAGER_H
#define MANAGER_H

class Manager{
    public:
        static Manager* getInstance() {
            if (instance == nullptr) {
                instance = new Manager();
            }
            return instance;
        }
        
        void matchBids();
        void notifyActiveUser();

    private:
        static Manager* instance;
        Manager();
};


#endif