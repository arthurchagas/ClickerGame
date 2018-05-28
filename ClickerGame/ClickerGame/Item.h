#pragma once
#include "Botao.h"

class Item {
public:

	Item(int chave, float x, float y, std::string nome_spr);
	~Item();


	int& get_chave();


	Botao*& get_botao();

private:
	int chave;
	Botao* botao;
};
