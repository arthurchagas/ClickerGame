#pragma once
#include <iomanip>
#include "Item.h"
#include <string>

class Construcao : public Item {
public:

	Construcao(int chave, float x, float y, std::string nome_spr, double rate, unsigned long long preco, std::string nome);

	unsigned long long get_quantidade() const;
	double get_rate() const;
	double get_bonus() const;
	unsigned long long get_preco() const;
	void set_preco(unsigned long long preco);
	void set_quantidade(unsigned long long qnt);


	void set_bonus(double bonus);

	void comprar(long double& total, long double& rateGlobal, Botao* principal);
	void vender(long double& total, long double& rateGlobal, Botao* principal);

	std::string& get_nome();
private:
	unsigned long long quantidade;
	double rate;
	double bonus;
	unsigned long long preco;
	std::string nome;
};
