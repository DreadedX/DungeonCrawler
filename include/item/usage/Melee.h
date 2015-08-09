#ifndef MELEE_H
#define MELEE_H

class Melee: public ItemUsageClass {

    public:
	
	void use() const {

	    std::cout << "This item is melee" << std::endl;
	}
};

#endif

