#include <sstream>
#include <cmath>
#include "Construcao.h"
#include "Util.h"

Construcao::Construcao(int chave, const float x, const float y, std::string nome_spr, double rate,
                       unsigned long long preco)
	: Item(chave, x, y, nome_spr), quantidade(0),
	  rate(rate),
	  bonus(1),
	  preco(preco) {
}

Construcao::Construcao(int chave, float x, float y, std::string nome_spr, sf::Font& fonte, unsigned tamanho_caracter,
                       sf::Color cor, double rate, unsigned long long preco) : Item(chave, x, y, nome_spr, fonte,
                                                                                    tamanho_caracter, cor),
                                                                               quantidade(0),
                                                                               rate(rate),
                                                                               bonus(1),
                                                                               preco(preco) {
}

unsigned long long Construcao::get_quantidade() const {
	return quantidade;
}

double Construcao::get_rate() const {
	return rate;
}

double Construcao::get_bonus() const {
	return bonus;
}

unsigned long long Construcao::get_preco() const {
	return preco;
}

void Construcao::set_preco(unsigned long long preco) {
	this->preco = preco;
}

void Construcao::set_quantidade(const unsigned long long qnt) {
	this->quantidade = qnt;
}

void Construcao::set_bonus(double bonus) {
	this->bonus = bonus;
}

void Construcao::comprar(long double& total, long double& rateGlobal, Botao* principal) {
	std::stringstream auxStream;
	if (total >= this->preco) {
		rateGlobal += this->rate * this->bonus;
		auxStream << std::setprecision(2) << std::fixed << rateGlobal << "CRU/s";
		principal->set_texto(auxStream.str(), ABAIXO);

		total -= this->preco;
		auxStream.str(std::string());
		auxStream <<  "Creditos RU:" << std::setprecision(0) << std::fixed << floor(total);
		principal->set_texto(auxStream.str(), ACIMA);

		++this->quantidade;

		this->preco += static_cast<unsigned long long>(ceil(this->quantidade * (1 + exp(1) / 5.0)));
		auxStream.str(std::string());
		auxStream << this->preco << "CRU";
		this->get_botao()->set_texto(auxStream.str(), ACIMA);

		auxStream.str(std::string());
		auxStream << std::setprecision(2) << std::fixed << this->quantidade << '*' << this->rate * this->bonus << "CRU/s";
		this->get_botao()->set_texto(auxStream.str(), ABAIXO);
	}
}

void Construcao::vender(long double& total, long double& rateGlobal, Botao* principal) {
	std::stringstream auxStream;
	if (this->quantidade > 0) {
		this->preco -= static_cast<unsigned long long>(ceil(this->quantidade * (1 + exp(1) / 5.0)));
		auxStream << this->preco << "CRU";
		this->get_botao()->set_texto(auxStream.str(), ACIMA);

		total += this->preco / 2.0;
		auxStream <<  "Creditos RU:" << std::setprecision(0) << std::fixed << floor(total);
		principal->set_texto(auxStream.str(), ACIMA);

		--this->quantidade;

		auxStream.str(std::string());
		auxStream << std::setprecision(2) << std::fixed << this->quantidade << '*' << this->rate * this->bonus << "CRU/s";
		this->get_botao()->set_texto(auxStream.str(), ABAIXO);

		rateGlobal -= this->rate * this->bonus;
		auxStream.str(std::string());
		auxStream << std::setprecision(2) << std::fixed << rateGlobal << "CRU/s";
		principal->set_texto(auxStream.str(), ABAIXO);
	}
}
