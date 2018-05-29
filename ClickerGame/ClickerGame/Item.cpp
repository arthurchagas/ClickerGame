#include "Item.h"

Item::Item(int chave, const float x, const float y, std::string nome_spr): chave(chave) {
	this->botao = new Botao(x, y, nome_spr);
}

Item::Item(int chave, float x, float y, std::string nome_spr, sf::Font& fonte, unsigned tamanho_caracter,
	sf::Color cor) : chave(chave) {
	this->botao = new Botao(x, y, nome_spr, fonte, tamanho_caracter, cor);
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
