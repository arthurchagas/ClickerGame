#include "Botao.h"
#include "Util.h"


Botao::Botao(const float x, const float y, sf::Sprite& spr): x(x), y(y), spr(spr)
{
	this->spr.setPosition(this->x, this->y);
}

bool Botao::clicado(const int x, const int y) const
{
	return x > this->spr.getPosition().x &&
		x < this->spr.getPosition().x + this->spr.getGlobalBounds().width &&
		y > this->spr.getPosition().y &&
		y < this->spr.getPosition().y + this->spr.getGlobalBounds().height;
}

void Botao::set_texto(const std::string& txt, const unsigned posicao)
{
	if (posicao > 4)
		return;

	this->texto[posicao].setString(txt);

	float x, y;

	switch (posicao)
	{
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

void Botao::set_char_size(const unsigned tamanho, const unsigned posicao)
{
	if (posicao > 4)
		return;

	this->texto[posicao].setCharacterSize(tamanho);
}

void Botao::set_fill_color(const sf::Color cor, const unsigned posicao)
{
	if (posicao > 4)
		return;

	this->texto[posicao].setFillColor(cor);
}

void Botao::set_fonte(sf::Font& fonte, const unsigned posicao)
{
	if (posicao > 4)
		return;

	this->texto[posicao].setFont(fonte);
}

sf::Text& Botao::get_text(const unsigned posicao)
{
	return this->texto[posicao];
}


sf::Sprite& Botao::get_spr()
{
	return spr;
}
