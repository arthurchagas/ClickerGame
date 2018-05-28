#pragma once
#include <string>
#include "Item.h"
#include "NoConstrucao.h"

class Upgrade : public Item {
public:

	Upgrade(int id, const float x, const float y, sf::Sprite& spr, int construcaoAlvo, double bonus, double preco,
	        const std::string& descricao, const std::string& nome, bool visivel);

	bool comprar(long double& total, long double& rateGlobal, Botao* principal, NoConstrucao* alvo);

	double get_preco() const;

	int get_construcaoAlvo() const;

private:
	int construcaoAlvo;
	double bonus;
	double preco;
	std::string descricao;
	std::string nome;
	bool visivel;
};
