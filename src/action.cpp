#include "action.h"

MAction::MAction(CDefsTable* defs)
    : anim(defs->GetString("anim"))
    , castingTime(defs->GetInt("castingTime",0))
    , duration(defs->GetInt("duration", 0))
    , multitarget(defs->GetBool("multitarget", false))
    , name(defs->GetString("id", "undefined_action_name"))
    , dist(defs->GetInt("dist", 0))
    , icon(new MIcon(defs->GetString("icon")))
    , id(RandomString(6))
{
    icon->setVisible(false);
    effects = defs->GetIntMap("effects");
}


void MAction::cast()
{
}
