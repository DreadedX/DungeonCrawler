#ifndef NONE_H
#define NONE_H

class None: public ItemUsageClass {

    public:
	
	void use() const {

	    std::cout << "This item has no use" << std::endl;
	}
};

#endif

