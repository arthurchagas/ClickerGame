#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class Botao {
public:
	Botao(float x, float y, std::string nome_spr);
	Botao(float x, float y, std::string nome_spr, sf::Font &fonte, unsigned tamanho_caracter, sf::Color cor);

	bool clicado(int x, int y) const;

	void set_texto(const std::string& txt, unsigned posicao);
	void set_char_size(unsigned tamanho, unsigned posicao);
	void set_fill_color(sf::Color cor, unsigned posicao);
	void set_fonte(sf::Font& fonte, unsigned posicao);


	sf::Text& get_text(unsigned posicao);
	sf::Sprite& get_spr();

private:
	float x;
	float y;
	sf::Texture txt;
	sf::Sprite spr;

	sf::Text texto[5];
};
