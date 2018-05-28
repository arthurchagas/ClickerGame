#include "Item.h"

Item::Item(int chave, const float x, const float y, sf::Sprite& spr): chave(chave) {
	this->botao = new Botao(x, y, spr);
}

Item::~Item() {
	delete this->botao;
}

int& Item::get_chave() {
	return chave;
}

Botao*& Item::get_botao() {
	return botao;
}
