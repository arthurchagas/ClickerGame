#include "ListaUpgrade.h"

ListaUpgrade::ListaUpgrade() {
	this->primeiro = new NoUpgrade();
	this->ultimo = new NoUpgrade();

	this->primeiro->set_proximo(this->ultimo);
	this->primeiro->set_anterior(nullptr);

	this->ultimo->set_proximo(nullptr);
	this->ultimo->set_anterior(this->primeiro);
}

ListaUpgrade::~ListaUpgrade() {
	this->esvazia();

	delete this->primeiro;
	delete this->ultimo;
}

void ListaUpgrade::inserir_final(Upgrade* I) {
	if (Lista::cheia())
		return;

	auto aux = new NoUpgrade(I);

	this->ultimo->get_anterior()->set_proximo(aux);
	aux->set_proximo(this->ultimo);
	aux->set_anterior(this->ultimo->get_anterior());
	this->ultimo->set_anterior(aux);

	++this->tamanho;
}

void ListaUpgrade::remover_final() {
	if (this->vazia())
		return;

	const auto aux = this->ultimo->get_anterior();

	aux->get_anterior()->set_proximo(this->ultimo);
	this->ultimo->set_anterior(aux->get_anterior());

	delete aux;

	--this->tamanho;
}

void ListaUpgrade::inserir_comeco(Upgrade* I) {
	if (Lista::cheia())
		return;

	auto aux = new NoUpgrade(I);

	this->primeiro->get_proximo()->set_anterior(aux);
	aux->set_anterior(this->primeiro);
	aux->set_proximo(this->primeiro->get_proximo());
	this->primeiro->set_proximo(aux);

	++this->tamanho;
}



void ListaUpgrade::remover_comeco() {
	if (this->vazia())
		return;

	const auto aux = this->primeiro->get_proximo();

	aux->get_proximo()->set_anterior(this->primeiro);
	this->primeiro->set_proximo(aux->get_proximo());

	delete aux;

	--this->tamanho;
}

void ListaUpgrade::remover_por_chave(int chave) {
	if (this->vazia())
		return;

	const auto aux = this->encontrar_por_chave(chave);

	aux->get_proximo()->set_anterior(aux->get_anterior());
	aux->get_anterior()->set_proximo(aux->get_proximo());

	delete aux;

	--this->tamanho;
}

NoUpgrade* ListaUpgrade::encontrar_por_chave(int chave) {
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

NoUpgrade* ListaUpgrade::get_ultimo() {
	if (this->vazia())
		return nullptr;

	return this->ultimo->get_anterior();
}

NoUpgrade* ListaUpgrade::get_primeiro() {
	if (this->vazia())
		return nullptr;

	return this->primeiro->get_proximo();
}

void ListaUpgrade::esvazia() {
	while (!this->vazia())
		this->remover_final();
}