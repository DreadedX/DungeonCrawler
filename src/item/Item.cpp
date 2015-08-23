# include "Standard.h"

ItemComponent::ItemComponent(int id) {

    // TODO: Move this into a seperate function
    static int itemsID = Reader::getId("config/items");
    static byte json[1000] = {0x00};
    static rapidjson::Document d;

    if (json[0] == 0x00) {
	Reader::read(itemsID, json);

	d.Parse(reinterpret_cast<char const*>(json));
    }

    static rapidjson::Value &i = d["items"];
    rapidjson::Value &item = i[id];

    name = item[0].GetString();
    value = item[1].GetDouble();
    weight = item[2].GetDouble();
}

ModifierItemComponent::ModifierItemComponent(int id) {

    // TODO: Move this into a seperate function
    static int itemsID = Reader::getId("config/items");
    static byte json[1000] = {0x00};
    static rapidjson::Document d;

    if (json[0] == 0x00) {
	Reader::read(itemsID, json);
    
	d.Parse(reinterpret_cast<char const*>(json));
    }

    static rapidjson::Value &m = d["modifiers"];
    rapidjson::Value &modifier = m[id];

    name = modifier[0].GetString();
    value = modifier[1].GetDouble();
    weight = modifier[2].GetDouble();
}

void ModifierItemComponent::init() {

    item = &entity->getComponent<ItemComponent>();

    item->name = String::format("%s %s", name.c_str(), item->name.c_str());
    item->value *= value;
    item->weight *= weight;
}


void EnchantmentItemComponent::init() {

    item = &entity->getComponent<ItemComponent>();

    item->name = String::format("%s %s", name.c_str(), item->name.c_str());
    item->value *= value;
    item->weight *= weight;
}
