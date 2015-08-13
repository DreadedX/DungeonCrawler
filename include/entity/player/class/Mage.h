#ifndef MAGE_H
#define MAGE_H

class Mage: public Player {

    using Player::Player;

    public:

	void init();

    protected:

	void attack();
};

#endif

