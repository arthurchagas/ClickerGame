#ifndef ITEM_H
#define ITEM_H
#include "Botao.h"

class Item {
public:

	Item(int chave, float x, float y, std::string nome_spr);
	Item(int chave, float x, float y, std::string nome_spr, sf::Font &fonte, unsigned tamanho_caracter, sf::Color cor);
	~Item();


	int& get_chave();


	Botao*& get_botao();

private:
	int chave;
	Botao* botao;
};
#endif //ITEM_H