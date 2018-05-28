#include "Item.h"

Item::Item(int chave, const float x, const float y, std::string nome_spr): chave(chave) {
	this->botao = new Botao(x, y, nome_spr);
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
