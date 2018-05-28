#include "ListaConstrucao.h"

ListaConstrucao::ListaConstrucao() {
	this->primeiro = new NoConstrucao();
	this->ultimo = new NoConstrucao();

	this->primeiro->set_proximo(this->ultimo);
	this->primeiro->set_anterior(nullptr);

	this->ultimo->set_proximo(nullptr);
	this->ultimo->set_anterior(this->primeiro);
}

ListaConstrucao::~ListaConstrucao() {
	this->esvazia();

	delete this->primeiro;
	delete this->ultimo;
}

void ListaConstrucao::inserir_final(Construcao* I) {
	if (Lista::cheia())
		return;

	auto aux = new NoConstrucao(I);

	this->ultimo->get_anterior()->set_proximo(aux);
	aux->set_proximo(this->ultimo);
	aux->set_anterior(this->ultimo->get_anterior());
	this->ultimo->set_anterior(aux);

	++this->tamanho;
}

void ListaConstrucao::remover_final() {
	if (this->vazia())
		return;

	const auto aux = this->ultimo->get_anterior();

	aux->get_anterior()->set_proximo(this->ultimo);
	this->ultimo->set_anterior(aux->get_anterior());

	delete aux;

	--this->tamanho;
}

void ListaConstrucao::inserir_comeco(Construcao* I) {
	if (Lista::cheia())
		return;

	auto aux = new NoConstrucao(I);

	this->primeiro->get_proximo()->set_anterior(aux);
	aux->set_anterior(this->primeiro);
	aux->set_proximo(this->primeiro->get_proximo());
	this->primeiro->set_proximo(aux);

	++this->tamanho;
}

void ListaConstrucao::remover_comeco() {
	if (this->vazia())
		return;

	const auto aux = this->primeiro->get_proximo();

	aux->get_proximo()->set_anterior(this->primeiro);
	this->primeiro->set_proximo(aux->get_proximo());

	delete aux;

	--this->tamanho;
}

void ListaConstrucao::remover_por_chave(int chave) {
	if (this->vazia())
		return;

	const auto aux = this->encontrar_por_chave(chave);

	aux->get_proximo()->set_anterior(aux->get_anterior());
	aux->get_anterior()->set_proximo(aux->get_proximo());

	delete aux;

	--this->tamanho;
}

long double ListaConstrucao::recalcular_rate_global() {
	auto aux = this->primeiro->get_proximo();
	long double rateGlobal = 0;

	while (aux != this->ultimo) {
		rateGlobal += aux->get_item()->get_quantidade() * aux->get_item()->get_rate() * aux->get_item()->get_bonus();
		aux = aux->get_proximo();
	}

	return rateGlobal;
}

NoConstrucao* ListaConstrucao::encontrar_por_chave(int chave) {
	if (this->vazia())
		return nullptr;

	auto aux = this->primeiro->get_proximo();

	while (aux != this->ultimo) {
		if (aux->get_item()->get_chave() == chave)
			return aux;
		aux = aux->get_proximo();
	}

	return nullptr;
}

NoConstrucao* ListaConstrucao::get_ultimo() {
	if (this->vazia())
		return nullptr;

	return this->ultimo->get_anterior();
}

NoConstrucao* ListaConstrucao::get_primeiro() {
	if (this->vazia())
		return nullptr;

	return this->primeiro->get_proximo();
}

void ListaConstrucao::esvazia() {
	while (!this->vazia())
		this->remover_final();
}
