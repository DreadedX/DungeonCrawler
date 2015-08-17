# include "Standard.h"

ItemComponent::ItemComponent(int id) {

    // TODO: Move this into a seperate function
    static int itemsID = IO::Reader::getId("items");
    static byte json[1000] = {0x00};
    static rapidjson::Document d;
#if DEBUG_MODE
    static rapidjson::StringBuffer buffer;
#endif
    if (json[0] == 0x00) {
	IO::Reader::read(itemsID, json);
    
	d.Parse(reinterpret_cast<char const*>(json));

#if DEBUG_MODE
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);
#endif
    }

    Log::print(buffer.GetString(), DEBUG);

    static rapidjson::Value &i = d["items"];
    rapidjson::Value &item = i[id];

    Log::print(String::format("%s %.1f %.1f", item[0].GetString(), item[1].GetDouble(), item[2].GetDouble()), DEBUG);

    name = item[0].GetString();
    value = item[1].GetDouble();
    weight = item[2].GetDouble();
}

ModifierItemComponent::ModifierItemComponent(int id) {

    // TODO: Move this into a seperate function
    static int itemsID = IO::Reader::getId("items");
    static byte json[1000] = {0x00};
    static rapidjson::Document d;
#if DEBUG_MODE
    static rapidjson::StringBuffer buffer;
#endif
    if (json[0] == 0x00) {
	IO::Reader::read(itemsID, json);
    
	d.Parse(reinterpret_cast<char const*>(json));

#if DEBUG_MODE
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	d.Accept(writer);
#endif
    }

    Log::print(buffer.GetString(), DEBUG);

    static rapidjson::Value &m = d["modifiers"];
    rapidjson::Value &modifier = m[id];

    Log::print(String::format("%s %.1f %.1f", modifier[0].GetString(), modifier[1].GetDouble(), modifier[2].GetDouble()), DEBUG);

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
