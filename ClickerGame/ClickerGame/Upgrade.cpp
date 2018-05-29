#include "Upgrade.h"
#include "Util.h"
#include <sstream>
#include <cmath>

Upgrade::Upgrade(int id, const float x, const float y, std::string nome_spr, int construcaoAlvo, double bonus,
                 unsigned long long preco) :
	Item(id, x, y, nome_spr),
	construcaoAlvo(construcaoAlvo),
	bonus(bonus),
	preco(preco) {
}

Upgrade::Upgrade(int id, float x, float y, std::string nome_spr, sf::Font& fonte, unsigned tamanho_caracter,
                 sf::Color cor, int construcaoAlvo, double bonus, unsigned long long preco) :
	Item(id, x, y, nome_spr, fonte, tamanho_caracter, cor),
	construcaoAlvo(construcaoAlvo),
	bonus(bonus),
	preco(preco) {
}

bool Upgrade::comprar(long double& total, long double& rateGlobal, Botao* principal, NoConstrucao* alvo) {
	if (total < this->preco)
		return false;

	std::stringstream auxStream;
	total -= this->preco;
	auxStream << std::setprecision(0) << std::fixed << floor(total);
	principal->set_texto(auxStream.str(), ACIMA);

	alvo->get_item()->set_bonus(alvo->get_item()->get_bonus() + this->bonus);

	auxStream.str(std::string());
	auxStream << std::setprecision(2) << std::fixed << rateGlobal << " /s";
	principal->set_texto(auxStream.str(), ABAIXO);

	auxStream.str(std::string());
	auxStream << std::setprecision(2) << std::fixed << alvo->get_item()->get_quantidade() << '*'
		<< alvo->get_item()->get_rate() * alvo->get_item()->get_bonus() << " /s";
	alvo->get_item()->get_botao()->set_texto(auxStream.str(), ABAIXO);

	return true;
}

unsigned long long Upgrade::get_preco() const {
	return preco;
}

double Upgrade::get_bonus() const {
	return bonus;
}

int Upgrade::get_construcaoAlvo() const {
	return construcaoAlvo;
}
