
#include "EVEServerPCH.h"

using namespace Destiny;

Asteroid::Asteroid(
	SystemManager *system,
	InventoryItemRef self
)
: ItemSystemEntity(self),
  m_system(system)
{
}

Asteroid::~Asteroid() {
}
	
void Asteroid::Grow() {
}

bool Asteroid::ApplyDamage(Damage &d) {
	//ignore it.
	_log(MINING__DEBUG, "Asteroid %u: Ignoring %f damage from %s", m_self->itemID(), d.GetTotal(), d.source->GetName());
	return(false);
}

void Asteroid::EncodeDestiny(std::vector<uint8> &into) const {
	const GPoint &position = GetPosition();

	#pragma pack(1)
	struct AddBall_Asteroid {
		BallHeader head;
		DSTBALL_RIGID_Struct main;
		NameStruct name;
	};
	#pragma pack()

	size_t start = into.size();
	into.resize(start 
		+ sizeof(AddBall_Asteroid)
		);
	AddBall_Asteroid *item = (AddBall_Asteroid *) &into[start];

	item->head.entityID = GetID();
	item->head.mode = Destiny::DSTBALL_RIGID;
	item->head.radius = GetRadius();
	item->head.x = position.x;
	item->head.y = position.y;
	item->head.z = position.z;
	item->head.sub_type = AddBallSubType_cargoContainer_asteroid;

	item->main.formationID = 0xFF;
	
	item->name.name_len = 0;
	//strcpy_fake_unicode(item->name.name, data.itemName.c_str());
}

/*PyDict *Asteroid::MakeSlimItem() const {
	PyDict *slim = new PyDict();
	slim->add("typeID", new PyInt(m_typeID));
	slim->add("ownerID", new PyInt(500021));	//no idea.
	slim->add("itemID", new PyInt(m_itemID));
	return(slim);
}*/











