#include "publisher.h"
#include "goose_publisher.h"

void GP::Tick()
{
    if (publisher != nullptr) {
        
        GoosePublisher_publish(publisher, dataSetValues);
    }
}

void GP::SetValue(bool newValue, int index)
{
    if (index >= 4) {
        return;
    };
    if (dataSetValues != nullptr) {
        auto element = LinkedList_get(dataSetValues, index);
        MmsValue* data = (MmsValue*)LinkedList_getData(element);
        MmsValue_setBoolean(data, newValue);
    }
    
}

GP::GP(std::string& interface)
{
    dataSetValues = LinkedList_create();

    LinkedList_add(dataSetValues, MmsValue_newBoolean(false));
    LinkedList_add(dataSetValues, MmsValue_newBoolean(false));
    LinkedList_add(dataSetValues, MmsValue_newBoolean(false));
    LinkedList_add(dataSetValues, MmsValue_newBoolean(false));


    CommParameters gooseCommParameters;

    gooseCommParameters.appId = 1000;
    gooseCommParameters.dstAddress[0] = 0x01;
    gooseCommParameters.dstAddress[1] = 0x0c;
    gooseCommParameters.dstAddress[2] = 0xcd;
    gooseCommParameters.dstAddress[3] = 0x01;
    gooseCommParameters.dstAddress[4] = 0x00;
    gooseCommParameters.dstAddress[5] = 0x01;
    gooseCommParameters.vlanId = 0;
    gooseCommParameters.vlanPriority = 4;

    publisher = GoosePublisher_create(&gooseCommParameters, interface.c_str());

    if (publisher) {
        GoosePublisher_setGoCbRef(publisher, "SPbPUIO/oolegkaa");
        GoosePublisher_setConfRev(publisher, 1);
        GoosePublisher_setDataSetRef(publisher, "SPbPU/LLN0n1");
        GoosePublisher_setTimeAllowedToLive(publisher, 500);

    }

}

GP::~GP() {
    GoosePublisher_destroy(publisher);
    LinkedList_destroyDeep(dataSetValues, (LinkedListValueDeleteFunction) MmsValue_delete);
}