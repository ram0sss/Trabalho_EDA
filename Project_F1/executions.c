/**
* Autor:                Tiago Da Cunha Silva Ramos (23512)
* Email:                a23512@alunos.ipca.pt
* Data:                 18/04/2022
*
* Descri��o:            Ficheiro com fun��es relacionadas com opera��es de "Execu��es"
*/

#include "DataManagement.h"

/**
* @brief	Criar nova execu��o
* @param	operacaoPosition	Identificador da opera��o
* @param	maquinaID			Identificador da m�quina
* @param	runtime				Unidades de tempo necess�rias para a execu��o da opera��o
* @return	Nova execu��o
*/
execution* newexecution(int operacaoPosition, int maquinaID, int runtime) {

	execution* new = (execution*)malloc(sizeof(execution));
	if (new == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

	new->operacaoPosition = operacaoPosition;
	new->maquinaID = maquinaID;
	new->runtime = runtime;
	new->next = NULL;

	return new;
}

/**
* @brief	Inserir nova execu��o no in�cio da lista de execu��es
* @param	head	Lista de execu��es
* @param	new		Nova execu��o
* @return	Lista de execu��es atualizada
*/
execution* InsertexecutionInList(execution* head, execution* new) {
	
	if (head == NULL) head = new; // se a lista estiver vazia
	else // se existir algum elemento na lista
	{
		new->next = head;
		head = new;
	}

	return head;
}

/**
* @brief	Armazenar lista de execu��es em ficheiro bin�rio
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de execu��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeexecutions(char fileName[], execution* head){
	if (head == NULL) return false; // se lista est� vazia

	FILE* file = NULL;
	if ((file = fopen(fileName, "wb")) == NULL) return false; // se n�o foi poss�vel abrir o ficheiro

	execution* current = head;
	Fileexecution currentexecution;	//para gravar em ficheiro
	while (current) //escrever todos os elementos da lista no ficheiro
	{
		currentexecution.operacaoPosition = current->operacaoPosition;
		currentexecution.maquinaID = current->maquinaID;
		currentexecution.runtime = current->runtime;

		fwrite(&currentexecution, sizeof(Fileexecution), 1, file);
		current = current->next;
	}

	fclose(file);

	return true;
}

/**
* @brief	Ler lista de execu��es de ficheiro bin�rio
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de execu��ess
*/
execution* readexecutions(char fileName[]) {
	FILE* file;

	if ((file = fopen(fileName, "rb")) == NULL) return NULL; // se n�o foi poss�vel abrir o ficheiro

	execution* head = NULL;
	execution* current = NULL;
	Fileexecution currentexecution; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

	while (fread(&currentexecution, sizeof(Fileexecution), 1, file)) // l� todos os registos do ficheiro e guarda na lista
	{
		current = newexecution(currentexecution.operacaoPosition, currentexecution.maquinaID, currentexecution.runtime);
		head = InsertexecutionInList(head, current);
	}

	fclose(file);
	return head;
}

/**
* @brief	Libertar a lista de opera��es da mem�ria
* @param	head	Lista de opera��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool freeexecutions(execution* head){
	if (head == NULL) return false; // se a lista estiver vazia
	
	execution* current = NULL;

	while (head)
	{
		current = head;
		head = head->next;
		free(current);
	}

	return true;
}

/**
* @brief	Procurar por uma execu��o atrav�s do identificador da opera��o, na lista de execu��es
* @param	head			Lista de execu��es
* @param	operacaoID		Identificador da opera��o
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool searchexecutionByOperacao(execution* head, int operacaoPosition) {
	if (head == NULL) return false; // se a lista estiver vazia

	execution* current = head;

	while (current != NULL)
	{
		if (current->operacaoPosition == operacaoPosition) return true;

		current = current->next;
	}

	return false;
}

/**
* @brief	Remover execu��o pelo identificador da opera��o
* @param	head				Apontador para a lista de execu��es
* @param	operacaoPosition	Identificador da opera��o
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool deleteexecutionByOperacao(execution** head, int operacaoPosition){
	if (*head == NULL) return false; // se a lista estiver vazia

	execution* current = *head;
	execution* previous = NULL;

	if (current && current->operacaoPosition == operacaoPosition) { // se o elemento que ser� apagado � o primeiro da lista
		*head = current->next;
		free(current);
		return true;
	}

	while (current&& current->operacaoPosition != operacaoPosition) // procurar o elemento a ser apagado
	{
		previous = current;
		current = current->next;
	}

	if (current == NULL) return false; // se o elemento n�o foi encontrado

	previous->next = current->next; // desassociar o elemento da lista
	free(current);

	return true;
}

/**
* @brief	Atualizar as unidades de tempo necess�rias para a execu��o de uma opera��o
* @param	head			Apontador para a lista de execu��es
* @param	operacaoPOsition		Identificador da opera��o
* @param	maquinaID		Identificador da m�quina
* @param	runtime			Unidades de tempo
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool updateRuntime(execution** head, int operacaoPosition, int maquinaID, int runtime){
	if (*head == NULL) return false; // se lista est� vazia

	execution* current = *head;

	while (current != NULL)
	{
		if (current->operacaoPosition == operacaoPosition && current->maquinaID == maquinaID)
		{
			current->runtime = runtime;
			return true;
		}
		current = current->next;
	}

	return false;
}

/**
* @brief	Inserir execu��o ordenada pelo ID da opera��o na lista de execu��es
* @param	head	Lista de execu��es
* @param	new		Nova execu��o
* @return	Lista de execu��es atualizada
*/
execution* InsertexecutionByOperacao(execution* head, execution* new){

	if (head == NULL) head = new;// se a lista estiver vazia

	else
	{
		execution* current = head;
		execution* previous = NULL;

		// enquanto que atual tem o ID menor que a nova
		while (current&& current->operacaoPosition < new->operacaoPosition)
		{
			previous = current;
			current = current->next;
		}

		if (previous == NULL)
		{
			new->next = head;
			head = new; // inserir no meio
		}
		else
		{
			previous->next = new;
			new->next = current; // inserir no fim
		}
	}

	return head;
}

/**
* @brief	Procurar por uma execu��o na lista de execu��es
* @param	head			Lista de execu��es
* @param	operacaoID		Identificador da opera��o
* @param	maquinaID		Identificador da m�quina
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool searchexecution(execution* head, int operacaoPosition, int maquinaID){
	if (head == NULL) return false;// se a lista estiver vazia

	execution* current = head;

	while (current != NULL)
	{
		if (current->operacaoPosition == operacaoPosition && current->maquinaID == maquinaID)
		{
			return true;
		}
		current = current->next;
	}

	return false;
}

/**
* @brief	Mostrar a lista de execu��es na consola
* @param	head	Lista de execu��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool displayexecutions(execution* head) {
	if (head == NULL) return false; // se a lista estiver vazia

	execution* current = head;

	while (current)
	{
		printf("Operacao ID: %d, maquina ID: %d, execution Time: %d;\n", current->operacaoPosition, current->maquinaID, current->runtime);
		current = current->next;
	}

	printf("\n");
	return true;
}