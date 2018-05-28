#include <sstream>
#include "Construcao.h"
#include "Util.h"

Construcao::Construcao(int chave, const float x, const float y, sf::Sprite& spr, double rate, unsigned long long preco,
                       std::string nome)
	: Item(chave, x, y, spr), quantidade(0),
	  rate(rate),
	  bonus(1),
	  preco(preco),
	  nome(nome) {
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
		total -= this->preco;
		auxStream << std::setprecision(0) << std::fixed << floor(total);
		principal->set_texto(auxStream.str(), ACIMA);

		++this->quantidade;

		this->preco += static_cast<unsigned long long>(ceil(this->quantidade * (1 + exp(1) / 5.0)));
		this->get_botao()->set_texto(std::to_string(this->preco), ACIMA);

		auxStream.str(std::string());
		auxStream << std::setprecision(2) << std::fixed << this->quantidade << '*' << this->rate * this->bonus << " /s";
		this->get_botao()->set_texto(auxStream.str(), ABAIXO);

		rateGlobal += this->rate * this->bonus;
		auxStream.str(std::string());
		auxStream << std::setprecision(2) << std::fixed << rateGlobal << " /s";
		principal->set_texto(auxStream.str(), ABAIXO);
	}
}

void Construcao::vender(long double& total, long double& rateGlobal, Botao* principal) {
	std::stringstream aux_stream;
	if (this->quantidade > 0) {
		this->preco -= static_cast<unsigned long long>(ceil(this->quantidade * (1 + exp(1) / 5.0)));
		this->get_botao()->set_texto(std::to_string(this->preco), ACIMA);

		total += this->preco / 2.0;
		aux_stream << std::setprecision(0) << std::fixed << floor(total);
		principal->set_texto(aux_stream.str(), ACIMA);

		--this->quantidade;

		aux_stream.str(std::string());
		aux_stream << std::setprecision(2) << std::fixed << this->quantidade << '*' << this->rate * this->bonus << " /s";
		this->get_botao()->set_texto(aux_stream.str(), ABAIXO);

		rateGlobal -= this->rate * this->bonus;
		aux_stream.str(std::string());
		aux_stream << std::setprecision(2) << std::fixed << rateGlobal << " /s";
		principal->set_texto(aux_stream.str(), ABAIXO);
	}
}

std::string& Construcao::get_nome() {
	return this->nome;
}
