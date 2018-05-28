#include <iostream>
#include <sstream>
#include <iomanip>
#include "ListaConstrucao.h"
#include "Util.h"
#include <SFML/Graphics.hpp>
#include "Construcao.h"
#include "NoConstrucao.h"
#include "ListaUpgrade.h"

#define largura 1366
#define altura 768

int main() {
	double rates[] = {0.1, 1.0, 15.0, 300.0, 5000.0};
	unsigned long long precos[] = {10, 100, 2000, 10000, 50000};
	std::string nomes[] = {"Upgrade A", "Upgrade B", "Upgrade C", "Upgrade D", "Upgrade E"};
	sf::Event evento{};
	sf::RenderWindow janelaPrincipal(sf::VideoMode(largura, altura), "Hello SFML", sf::Style::Fullscreen);
	sf::Font fontePrincipal;
	sf::Clock timer;

	std::stringstream auxStream;

	fontePrincipal.loadFromFile("arial.ttf");
	long double total = 0;
	long double rateGlobal = 0;

	sf::Texture texturaPrincipal;
	texturaPrincipal.loadFromFile("principal.png");
	sf::Sprite sprite_principal(texturaPrincipal);
	auto botaoPrincipal = new Botao((janelaPrincipal.getSize().x - texturaPrincipal.getSize().x) / 2.0f,
	                                (janelaPrincipal.getSize().y - texturaPrincipal.getSize().y) / 2.0f,
	                                sprite_principal);
	botaoPrincipal->set_fonte(fontePrincipal, ACIMA);
	botaoPrincipal->set_char_size(24, ACIMA);
	botaoPrincipal->set_fill_color(sf::Color::White, ACIMA);
	auxStream << std::setprecision(0) << std::fixed << floor(total);
	botaoPrincipal->set_texto(auxStream.str(), ACIMA);
	botaoPrincipal->set_fonte(fontePrincipal, ABAIXO);
	botaoPrincipal->set_char_size(24, ABAIXO);
	botaoPrincipal->set_fill_color(sf::Color::White, ABAIXO);
	auxStream.str(std::string());
	auxStream << std::setprecision(2) << std::fixed << rateGlobal << " /s";
	botaoPrincipal->set_texto(auxStream.str(), ABAIXO);


	auto construcoes = new ListaConstrucao();
	sf::Texture texturaConstrucao;
	texturaConstrucao.loadFromFile("construcao1.png");
	sf::Sprite spriteConstrucao(texturaConstrucao);

	for (auto i = 0; i < 5; ++i) {
		construcoes->inserir_final(new Construcao(
			i, static_cast<float>(janelaPrincipal.getSize().x - texturaConstrucao.getSize().x - 100),
			static_cast<float>(100 + i * 125), spriteConstrucao, rates[i], precos[i], nomes[i]));

		auto auxItem = construcoes->get_ultimo()->get_item();
		auto auxBotao = auxItem->get_botao();

		auxBotao->set_fonte(fontePrincipal, ABAIXO);
		auxBotao->set_char_size(18, ABAIXO);
		auxBotao->set_fill_color(sf::Color::White, ABAIXO);
		auxStream.str(std::string());
		auxStream << std::setprecision(2) << std::fixed << auxItem->get_quantidade() << '*' << auxItem->get_rate() * auxItem
			->get_bonus() << " /s";
		auxBotao->set_texto(auxStream.str(), ABAIXO);

		auxBotao->set_fonte(fontePrincipal, ACIMA);
		auxBotao->set_char_size(18, ACIMA);
		auxBotao->set_fill_color(sf::Color::White, ACIMA);
		auxBotao->set_texto(std::to_string(auxItem->get_preco()), ACIMA);
	}

	auto upgrades = new ListaUpgrade();
	sf::Texture texturaUpgrade;
	texturaUpgrade.loadFromFile("melhora.png");
	sf::Sprite spriteUpgrade(texturaUpgrade);

	for (auto i = 0; i < 5; ++i) {
		for (auto j = 0; j < 3; ++j) {
			upgrades->inserir_final(new Upgrade(i * 3 + j, static_cast<float>(100 + j * 90), static_cast<float>(100 + i * 90),
			                                    spriteUpgrade, i, 2, 100,
			                                    "Upgrade para a construcao 1",
			                                    "Dedo no Cu"));

			auto auxItem = upgrades->get_ultimo()->get_item();
			auto auxBotao = auxItem->get_botao();

			auxBotao->set_fonte(fontePrincipal, CENTRO);
			auxBotao->set_char_size(18, CENTRO);
			auxBotao->set_fill_color(sf::Color::White, CENTRO);
			auxBotao->set_texto(std::to_string(auxItem->get_preco()), CENTRO);
		}
	}

	while (janelaPrincipal.isOpen()) {
		if (rateGlobal > 0.0) {
			total += timer.getElapsedTime().asSeconds() * rateGlobal;
			timer.restart();
			auxStream.str(std::string());
			auxStream << std::setprecision(0) << std::fixed << floor(total);
			botaoPrincipal->set_texto(auxStream.str(), ACIMA);
		}

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
						auxStream << std::setprecision(0) << std::fixed << floor(total);
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
								auxStream << std::setprecision(2) << std::fixed << rateGlobal << " /s";
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

		janelaPrincipal.clear();
		janelaPrincipal.draw(botaoPrincipal->get_spr());
		janelaPrincipal.draw(botaoPrincipal->get_text(ACIMA));
		janelaPrincipal.draw(botaoPrincipal->get_text(ABAIXO));

		for (unsigned i = 0; i < 15; ++i) {
			const auto auxNo = upgrades->encontrar_por_chave(i);

			if (auxNo == nullptr)
				continue;

			janelaPrincipal.draw(auxNo->get_item()->get_botao()->get_spr());
			janelaPrincipal.draw(auxNo->get_item()->get_botao()->get_text(CENTRO));
		}

		for (unsigned i = 0; i < 5; ++i) {
			const auto aux_no = construcoes->encontrar_por_chave(i);

			if (aux_no == nullptr)
				continue;

			janelaPrincipal.draw(aux_no->get_item()->get_botao()->get_spr());
			for (auto j = 0; j < 5; ++j)
				janelaPrincipal.draw(aux_no->get_item()->get_botao()->get_text(j));
		}

		janelaPrincipal.display();
	}

	delete botaoPrincipal;
	delete construcoes;
	delete upgrades;

	return 0;
}
