#pragma once
#include <string>
#include "Item.h"
#include "NoConstrucao.h"

class Upgrade : public Item {
public:

	Upgrade(int id, float x, float y, std::string nome_spr, int construcaoAlvo, double bonus, unsigned long long preco,
	        const std::string& descricao, const std::string& nome);

	bool comprar(long double& total, long double& rateGlobal, Botao* principal, NoConstrucao* alvo);

	unsigned long long get_preco() const;

	int get_construcaoAlvo() const;

private:
	int construcaoAlvo;
	double bonus;
	unsigned long long preco;
	std::string descricao;
	std::string nome;
};
