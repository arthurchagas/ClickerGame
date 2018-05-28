#pragma once
#include "Construcao.h"

class NoConstrucao {
public:
	NoConstrucao(Construcao* item);
	NoConstrucao();
	~NoConstrucao();

	Construcao*& get_item();

	void set_item(Construcao* item);

	NoConstrucao* get_proximo() const;

	void set_proximo(NoConstrucao* proximo);

	NoConstrucao* get_anterior() const;

	void set_anterior(NoConstrucao* anterior);
private:
	Construcao* item;
	NoConstrucao* proximo;
	NoConstrucao* anterior;
};
