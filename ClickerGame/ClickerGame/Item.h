#pragma once
#include "Botao.h"

class Item {
public:

	Item(int chave, const float x, const float y, sf::Sprite& spr);
	~Item();


	int& get_chave();


	Botao*& get_botao();

private:
	int chave;
	Botao* botao;
};
