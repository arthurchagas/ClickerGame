#pragma once
#include "Lista.h"
#include "Upgrade.h"
#include "NoUpgrade.h"

class ListaUpgrade : public Lista {
public:

	ListaUpgrade();
	~ListaUpgrade();

	void inserir_final(Upgrade* I);
	void remover_final();
	void inserir_comeco(Upgrade* I);
	void remover_comeco();
	void remover_por_chave(int chave);
	NoUpgrade* encontrar_por_chave(int chave);
	NoUpgrade* get_ultimo();
	NoUpgrade* get_primeiro();

	void esvazia();
private:
	NoUpgrade* primeiro;
	NoUpgrade* ultimo;
};
