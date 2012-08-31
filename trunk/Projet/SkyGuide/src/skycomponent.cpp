/**
  * Class implementation file of SkyComponent.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#include "skycomponent.h"

SkyComponent::SkyComponent(SkyConfiguration* const config, QObject* parent) :
    QObject(parent),
    p_config(config)
{
}
