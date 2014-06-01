#ifndef COMPONENTINTERFACE_H
#define COMPONENTINTERFACE_H

#include <QtPlugin>

namespace Hako {
class Component;
}

class ComponentInterface {
public:
    virtual ~ComponentInterface() {}
    virtual Hako::Component *getComponent() =0;
};

Q_DECLARE_INTERFACE(ComponentInterface,
                    "com.kristou.HakoComposer.ComponentInterface/1.0")
#endif // COMPONENTINTERFACE_H
