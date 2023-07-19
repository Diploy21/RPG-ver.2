#include "Items.h"


Item::Item(string Ttl, enum CharacterID id, int Charact)
	: Title(Ttl), ItemID(static_cast<char>(id)), Characteristic(Charact)
{

}

Item::~Item()
{
}
