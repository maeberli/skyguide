#include "skycomponent.h"

SkyComponent::SkyComponent(SkyConfiguration* config, QObject *parent) :
    QObject(parent),
    p_config(config)
{
}
