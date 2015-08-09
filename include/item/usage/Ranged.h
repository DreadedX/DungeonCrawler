#ifndef RANGED_H
#define RANGED_H

class Ranged: public ItemUsageClass {

    public:
	
	void use() const {

	    std::cout << "This item is ranged" << std::endl;
	}
};

#endif

