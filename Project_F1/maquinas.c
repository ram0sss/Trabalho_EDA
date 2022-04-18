/**
* Autor:                Tiago Da Cunha Silva Ramos (23512)
* Email:                a23512@alunos.ipca.pt
* Data:                 18/04/2022
*
* Descri��o:            Ficheiro com fun��es relacionadas com opera��es de "M�quinas"
*/

#include "DataManagement.h"

/**
* @brief	Criar nova m�quina
* @param	id		Identificador da m�quina
* @return	Nova m�quina
*/
maquina* newMaquina(int id){
	maquina* new = (maquina*)malloc(sizeof(maquina));

	new->id = id;
	new->next = NULL;

	return new;
}

/**
* @brief	Inserir nova m�quina no in�cio da lista de m�quinas
* @param	head	Lista de m�quinas
* @param	new		Nova m�quina
* @return	Lista de m�quinas atualizada
*/
maquina* InsertMaquinaInList(maquina* head, maquina* new){

	if (head == NULL) head = new; // se a lista estiver vazia
	else // se existir algum elemento na lista
	{
		new->next = head;
		head = new;
	}
	return head;
}

/**
* @brief	Armazenar lista de m�quinas em ficheiro bin�rio
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de m�quinas
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeMaquinas(char fileName[], maquina* head) {
	if (head == NULL) return false; // se lista est� vazia

	FILE* file = NULL;
	if ((file = fopen(fileName, "wb")) == NULL) return false; // se n�o foi poss�vel abrir o ficheiro

	maquina* current = head;
	Filemaquina currentMaquina;	//para gravar em ficheiro
	while (current) //escrever todos os elementos da lista no ficheiro
	{
		currentMaquina.id = current->id;

		fwrite(&currentMaquina, sizeof(Filemaquina), 1, file);
		current = current->next;
	}

	fclose(file);
	return true;
}

/**
* @brief	Ler lista de m�quinas de ficheiro bin�rio
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de m�quinas
*/
maquina* readMaquinas(char fileName[]){
	FILE* file;

	if ((file = fopen(fileName, "rb")) == NULL) return NULL; // se n�o foi poss�vel abrir o ficheiro

	maquina* head = NULL;
	maquina* current = NULL;
	Filemaquina currentMaquina; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

	while (fread(&currentMaquina, sizeof(Filemaquina), 1, file)) // l� todos os registos do ficheiro e guarda na lista
	{
		current = newMaquina(currentMaquina.id);
		head = InsertMaquinaInList(head, current);
	}

	fclose(file);
	return head;
}

/**
* @brief	Libertar a lista de m�quinas da mem�ria
* @param	head	Lista de m�quinas
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool freeMaquinas(maquina* head){
	if (head == NULL) return false; // se lista est� vazia
	
	maquina* current = NULL;

	while (head != NULL)
	{
		current = head;
		head = head->next;
		free(current);
	}

	return true;
}

/**
* @brief	Mostrar a lista de m�quinas na consola
* @param	head	Lista de m�quinas
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool displayMaquinas(maquina* head) {
	if (head == NULL) return false; // se lista est� vazia

	maquina* current = head;

	while (current != NULL)
	{
		printf("ID: %d\n", current->id);
		current = current->next;
	}

	printf("\n");
	return true;
}