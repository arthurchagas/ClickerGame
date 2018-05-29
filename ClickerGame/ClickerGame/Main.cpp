#include <iostream>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "ListaConstrucao.h"
#include "Util.h"
#include "Construcao.h"
#include "NoConstrucao.h"
#include "ListaUpgrade.h"

#define largura 1366
#define altura 768

int main() {
	double rates[] = {0.1, 1.0, 15.0, 100.0, 500.0};
	double rates_upgrades[] = {2.5, 10.0, 15.0};
	unsigned long long precos[] = {10, 100, 500, 1000, 5000};
	bool menu = true;
	sf::Event evento;
	sf::RenderWindow janelaPrincipal(sf::VideoMode(largura, altura), "RU Clicker", sf::Style::Fullscreen);
	sf::Font fontePrincipal;
	fontePrincipal.loadFromFile("arial.ttf");
	sf::Clock timer;
	sf::Texture texturaBackground;
	texturaBackground.loadFromFile("background.png");
	sf::Sprite spriteBackground(texturaBackground);
	spriteBackground.setScale(static_cast<float>(largura) / texturaBackground.getSize().x,
	                          static_cast<float>(altura) / texturaBackground.getSize().y);
	sf::Text textoUpgrade, textoConstrucoes;
	textoUpgrade.setFont(fontePrincipal);
	textoConstrucoes.setFont(fontePrincipal);
	textoUpgrade.setCharacterSize(48);
	textoConstrucoes.setCharacterSize(48);
	textoUpgrade.setFillColor(sf::Color::Blue);
	textoConstrucoes.setFillColor(sf::Color::Blue);
	textoUpgrade.setString("Upgrades");
	textoConstrucoes.setString("Construcoes");
	textoUpgrade.setPosition(225 - textoUpgrade.getGlobalBounds().width / 2.0f, 25);
	textoConstrucoes.setPosition(janelaPrincipal.getSize().x - 225 - textoUpgrade.getGlobalBounds().width / 2.0f, 25);

	sf::Texture texturaTitulo;
	texturaTitulo.loadFromFile("titulo.png");
	sf::Sprite spriteTitulo(texturaTitulo);
	spriteTitulo.setPosition((largura - texturaTitulo.getSize().x) / 2.0f, 100);

	auto botaoStart = new Botao((janelaPrincipal.getSize().x - 605) / 2.0f,
	                            (janelaPrincipal.getSize().y - 100) / 2.0f, "jogar.png");

	std::stringstream auxStream;

	long double total = 0;
	long double rateGlobal = 0;

	auto botaoPrincipal = new Botao((janelaPrincipal.getSize().x - 280) / 2.0f,
	                                (janelaPrincipal.getSize().y - 280) / 2.0f,
	                                "principal.png", fontePrincipal, 24, sf::Color::Black);
	auxStream << "Creditos RU:" << std::setprecision(0) << std::fixed << floor(total);
	botaoPrincipal->set_texto(auxStream.str(), ACIMA);
	auxStream.str(std::string());
	auxStream << std::setprecision(2) << std::fixed << rateGlobal << "CRU/s";
	botaoPrincipal->set_texto(auxStream.str(), ABAIXO);

	auto construcoes = new ListaConstrucao();

	for (auto i = 0; i < 5; ++i) {
		construcoes->inserir_final(new Construcao(
			i, static_cast<float>(janelaPrincipal.getSize().x - 300),
			static_cast<float>(100 + i * 125), "construcao_" + std::to_string(i) + ".png", fontePrincipal, 18,
			sf::Color::Black, rates[i], precos[i]));

		auto auxItem = construcoes->get_ultimo()->get_item();
		auto auxBotao = auxItem->get_botao();

		auxStream.str(std::string());
		auxStream << std::setprecision(2) << std::fixed << auxItem->get_quantidade() << '*' << auxItem->get_rate() * auxItem
			->get_bonus() << "CRU/s";
		auxBotao->set_texto(auxStream.str(), ABAIXO);

		auxStream.str(std::string());
		auxStream << auxItem->get_preco() << "CRU";
		auxBotao->set_texto(auxStream.str(), ACIMA);
	}

	auto upgrades = new ListaUpgrade();
	for (auto i = 0; i < 5; ++i) {
		for (auto j = 0; j < 3; ++j) {
			upgrades->inserir_final(new Upgrade(i * 3 + j, static_cast<float>(100 + j * 90), static_cast<float>(100 + i * 130),
			                                    "upgrade_" + std::to_string(i) + ".png", fontePrincipal, 18, sf::Color::Black, i,
			                                    rates_upgrades[j], precos[i] * 7.14005494464 / (1.61803398875 + 3 - j)));

			auto auxItem = upgrades->get_ultimo()->get_item();
			auto auxBotao = auxItem->get_botao();

			auxStream.str(std::string());
			auxStream << auxItem->get_preco() << "CRU";
			auxBotao->set_texto(auxStream.str(), ACIMA);

			auxStream.str(std::string());
			auxStream << '+' << std::setprecision(1) << std::fixed << auxItem->get_bonus() << 'x';
			auxBotao->set_texto(auxStream.str(), ABAIXO);
		}
	}

	while (janelaPrincipal.isOpen()) {
		janelaPrincipal.clear();
		janelaPrincipal.draw(spriteBackground);

		if (!menu) {
			if (rateGlobal > 0.0) {
				total += timer.getElapsedTime().asSeconds() * rateGlobal;
				timer.restart();
				auxStream.str(std::string());
				auxStream << std::setprecision(0) << std::fixed << floor(total);
				botaoPrincipal->set_texto(auxStream.str(), ACIMA);
			}
			else
				timer.restart();

			while (janelaPrincipal.pollEvent(evento)) {
				switch (evento.type) {
				case sf::Event::Closed:
					janelaPrincipal.close();
					break;
				case sf::Event::MouseButtonPressed:
					switch (evento.mouseButton.button) {
					case sf::Mouse::Left:
						if (botaoPrincipal->clicado(evento.mouseButton.x, evento.mouseButton.y)) {
							++total;
							auxStream.str(std::string());
							auxStream << "Creditos RU:" << std::setprecision(0) << std::fixed << floor(total);
							botaoPrincipal->set_texto(auxStream.str(), ACIMA);
							break;
						}

						for (unsigned i = 0; i < 5; ++i) {
							auto auxNo = construcoes->encontrar_por_chave(i);

							if (auxNo->get_item()->get_botao()->clicado(evento.mouseButton.x, evento.mouseButton.y)) {
								auxNo->get_item()->comprar(total, rateGlobal, botaoPrincipal);
								break;
							}
						}

						for (unsigned i = 0; i < 15; ++i) {
							auto auxNo = upgrades->encontrar_por_chave(i);

							if (auxNo == nullptr)
								continue;

							if (auxNo->get_item()->get_botao()->clicado(evento.mouseButton.x, evento.mouseButton.y)) {
								const auto auxNoConstrucao = construcoes->encontrar_por_chave(auxNo->get_item()->get_construcaoAlvo());

								if (auxNo->get_item()->comprar(total, rateGlobal, botaoPrincipal, auxNoConstrucao)) {
									upgrades->remover_por_chave(i);
									rateGlobal = construcoes->recalcular_rate_global();
									auxStream.str(std::string());
									auxStream << std::setprecision(2) << std::fixed << rateGlobal << "CRU/s";
									botaoPrincipal->set_texto(auxStream.str(), ABAIXO);
								}

								break;
							}
						}

						break;
					case sf::Mouse::Right:
						for (int i = 0; i < 5; ++i) {
							auto auxNo = construcoes->encontrar_por_chave(i);

							if (auxNo->get_item()->get_botao()->clicado(evento.mouseButton.x, evento.mouseButton.y))
								auxNo->get_item()->vender(total, rateGlobal, botaoPrincipal);
						}
						break;
					default: break;
					}
					break;

				default: break;
				}
			}

			janelaPrincipal.draw(botaoPrincipal->get_spr());
			janelaPrincipal.draw(botaoPrincipal->get_text(ACIMA));
			janelaPrincipal.draw(botaoPrincipal->get_text(ABAIXO));

			for (unsigned i = 0; i < 15; ++i) {
				const auto auxNo = upgrades->encontrar_por_chave(i);

				if (auxNo == nullptr)
					continue;

				janelaPrincipal.draw(auxNo->get_item()->get_botao()->get_spr());
				janelaPrincipal.draw(auxNo->get_item()->get_botao()->get_text(ACIMA));
				janelaPrincipal.draw(auxNo->get_item()->get_botao()->get_text(ABAIXO));
			}

			for (unsigned i = 0; i < 5; ++i) {
				const auto aux_no = construcoes->encontrar_por_chave(i);

				if (aux_no == nullptr)
					continue;

				janelaPrincipal.draw(aux_no->get_item()->get_botao()->get_spr());
				for (auto j = 0; j < 5; ++j)
					janelaPrincipal.draw(aux_no->get_item()->get_botao()->get_text(j));
			}

			janelaPrincipal.draw(textoUpgrade);
			janelaPrincipal.draw(textoConstrucoes);
		}
		else {
			while (janelaPrincipal.pollEvent(evento)) {
				switch (evento.type) {
				case sf::Event::Closed:
					janelaPrincipal.close();
					break;
				case sf::Event::MouseButtonPressed:
					switch (evento.mouseButton.button) {
					case sf::Mouse::Left:
						if (botaoStart->clicado(evento.mouseButton.x, evento.mouseButton.y))
							menu = false;
						break;
					default: break;
					}
					break;

				default: break;
				}
			}

			janelaPrincipal.draw(spriteTitulo);
			janelaPrincipal.draw(botaoStart->get_spr());
		}

		janelaPrincipal.display();
	}

	delete botaoPrincipal;
	delete construcoes;
	delete upgrades;
	delete botaoStart;

	return 0;
}
