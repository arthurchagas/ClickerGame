#pragma once
#include "Upgrade.h"

class NoUpgrade {
public:
	NoUpgrade(Upgrade* item);
	NoUpgrade();
	~NoUpgrade();

	Upgrade*& get_item();

	void set_item(Upgrade* item);

	NoUpgrade* get_proximo() const;

	void set_proximo(NoUpgrade* proximo);

	NoUpgrade* get_anterior() const;

	void set_anterior(NoUpgrade* anterior);
private:
	Upgrade* item;
	NoUpgrade* proximo;
	NoUpgrade* anterior;
};
