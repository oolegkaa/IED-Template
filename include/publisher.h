#include <string>

struct sGoosePublisher;
struct sLinkedList;

class GP {
public:

    void Tick();

    void SetValue(bool newValue, int index);
    
    GP(std::string& interface);

    ~GP();

private:
    sGoosePublisher* publisher {nullptr};
    sLinkedList* dataSetValues {nullptr};

};