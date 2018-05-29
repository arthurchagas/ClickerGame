#include "Botao.h"
#include "Util.h"


Botao::Botao(const float x, const float y, std::string nome_spr): x(x), y(y) {
	this->txt.loadFromFile(nome_spr);
	this->spr.setTexture(this->txt);
	this->spr.setPosition(this->x, this->y);
}

Botao::Botao(float x, float y, std::string nome_spr, sf::Font& fonte, unsigned tamanho_caracter,
             sf::Color cor) : x(x), y(y) {
	this->txt.loadFromFile(nome_spr);
	this->spr.setTexture(this->txt);
	this->spr.setPosition(this->x, this->y);

	for (auto i = 0; i < 5; ++i) {
		this->set_fonte(fonte, i);
		this->set_char_size(tamanho_caracter, i);
		this->set_fill_color(cor, i);
	}
}

bool Botao::clicado(const int x, const int y) const {
	return x > this->spr.getPosition().x &&
		x < this->spr.getPosition().x + this->spr.getGlobalBounds().width &&
		y > this->spr.getPosition().y &&
		y < this->spr.getPosition().y + this->spr.getGlobalBounds().height;
}

void Botao::set_texto(const std::string& txt, unsigned posicao) {
	if (posicao > 4)
		return;

	this->texto[posicao].setString(txt);

	float x, y;

	switch (posicao) {
	default:
	case ACIMA:
		x = this->spr.getPosition().x + this->spr.getGlobalBounds().width / 2 - this->texto[posicao].getGlobalBounds().width /
			2;
		y = this->spr.getPosition().y - 1.5f * this->texto[posicao].getGlobalBounds().height;
		break;
	case ABAIXO:
		x = this->spr.getPosition().x + this->spr.getGlobalBounds().width / 2 - this->texto[posicao].getGlobalBounds().width /
			2;
		y = this->spr.getPosition().y + this->spr.getGlobalBounds().height;
		break;
	case DIREITA:
		x = this->spr.getPosition().x + this->spr.getGlobalBounds().width + this->texto[posicao].getGlobalBounds().width;
		y = this->spr.getPosition().y + this->spr.getGlobalBounds().height / 2 - 0.75f * this->texto[posicao]
		                                                                                 .getGlobalBounds().height;
		break;
	case ESQUERDA:
		x = this->spr.getPosition().x - this->texto[posicao].getGlobalBounds().width;
		y = this->spr.getPosition().y + this->spr.getGlobalBounds().height / 2 - 0.75f * this->texto[posicao]
		                                                                                 .getGlobalBounds().height;
		break;
	case CENTRO:
		x = this->spr.getPosition().x + this->spr.getGlobalBounds().width / 2 - this->texto[posicao].getGlobalBounds().width /
			2;
		y = this->spr.getPosition().y + this->spr.getGlobalBounds().height / 2 - 0.75f * this->texto[posicao]
		                                                                                 .getGlobalBounds().height;
		break;
	}

	this->texto[posicao].setPosition(x, y);
}

void Botao::set_char_size(const unsigned tamanho, unsigned posicao) {
	if (posicao > 4)
		return;

	this->texto[posicao].setCharacterSize(tamanho);
}

void Botao::set_fill_color(const sf::Color cor, unsigned posicao) {
	if (posicao > 4)
		return;

	this->texto[posicao].setFillColor(cor);
}

void Botao::set_fonte(sf::Font& fonte, unsigned posicao) {
	if (posicao > 4)
		return;

	this->texto[posicao].setFont(fonte);
}

sf::Text& Botao::get_text(unsigned posicao) {
	return this->texto[posicao];
}


sf::Sprite& Botao::get_spr() {
	return spr;
}
