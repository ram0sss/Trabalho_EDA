/**
* Autor:                Tiago Da Cunha Silva Ramos (23512)
* Email:                a23512@alunos.ipca.pt
* Data:                 18/04/2022
*
* Descri��o:            Ficheiro com fun��es relacionadas com opera��es de "Opera��es"
*/

#include "DataManagement.h"

/**
* @brief	Criar nova opera��o
* @param	position	Posi��o da opera��o relativamente ao trabalho
* @return	Nova opera��o
*/
Operacao* newOperacao(int position) {
	Operacao* new = (Operacao*)malloc(sizeof(Operacao));

	new->position = position;
	new->next = NULL;

	return new;
}

/**
* @brief	Inserir nova opera��o no in�cio da lista de opera��es
* @param	head	Lista de opera��es
* @param	new		Nova opera��o
* @return	Lista de opera��es atualizada
*/
Operacao* InsertOperacaoInList(Operacao* head, Operacao* new) {
	
	if (head == NULL) head = new; // se a lista estiver vazia
	else // se existir algum elemento na lista
	{
		new->next = head;
		head = new;
	}

	return head;
}

/**
* @brief	Armazenar lista de opera��es em ficheiro bin�rio
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de opera��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeOperacoes(char fileName[], Operacao* head) {
	if (head == NULL) return false; // se lista est� vazia

	FILE* file = NULL;
	if ((file = fopen(fileName, "wb")) == NULL) return false; // se n�o foi poss�vel abrir o ficheiro

	Operacao* current = head;
	FileOperacao currentOperacao;	//para gravar em ficheiro
	while (current) //escrever todos os elementos da lista no ficheiro
	{
		currentOperacao.position = current->position;

		fwrite(&currentOperacao, sizeof(FileOperacao), 1, file);
		current = current->next;
	}

	fclose(file);
	return true;
}

/**
* @brief	Ler lista de opera��es de ficheiro bin�rio
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de opera��es
*/
Operacao* readOperacoes(char fileName[]){
	FILE* file;

	if ((file = fopen(fileName, "rb")) == NULL) return NULL; // se n�o foi poss�vel abrir o ficheiro

	Operacao* head = NULL;
	Operacao* current = NULL;
	FileOperacao currentOperacao; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

	while (fread(&currentOperacao, sizeof(FileOperacao), 1, file)) // l� todos os registos do ficheiro e guarda na lista
	{
		current = newOperacao(currentOperacao.position);
		head = InsertOperacaoInList(head, current);
	}

	fclose(file);
	return head;
}

/**
* @brief	Libertar a lista de opera��es da mem�ria
* @param	head	Lista de opera��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool freeOperacoes(Operacao* head){
	if (head == NULL) return false; // se lista est� vazia
	
	Operacao* current = NULL;

	while (head != NULL)
	{
		current = head;
		head = head->next;
		free(current);
	}

	return true;
}

/**
* @brief	Remover uma opera��o da lista de opera��es
* @param	head		Apontador para a lista de opera��es
* @param	position	Identificador da opera��o
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool deleteOperacao(Operacao** head, int position)
{
	if (*head == NULL) return false;

	Operacao* current = *head;
	Operacao* previous = NULL;

	if (current && current->position == position) { // se o elemento que ser� apagado � o primeiro da lista
		*head = current->next;
		free(current);
		return true;
	}

	while (current && current->position != position) // procurar o elemento a ser apagado
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
* @brief	Trocar a posi��o de uma opera��o para outra e vice-versa, num determinado trabalho
* @param	operacoes		Apontador para a lista de opera��es
* @param	oldPosition		Posi��o antiga da opera��o
* @param	newPosition		Nova posi��o da opera��o
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool updatePosition(Operacao** operacoes, int oldPosition, int newPosition)
{
	if (*operacoes == NULL) return false;// se as listas estiverem vazias

	if (oldPosition == newPosition) return false;// se as posi��es forem as mesmas


	Operacao* currentOperacao1 = *operacoes;
	Operacao* previousOperacao1 = NULL; // para a antiga
	Operacao* currentOperacao2 = *operacoes;
	Operacao* previousOperacao2 = NULL; // para a nova

	// procurar pela antiga posi��o
	while (currentOperacao1 && currentOperacao1->position != oldPosition)
	{
		previousOperacao1 = currentOperacao1;
		currentOperacao1 = currentOperacao1->next;
	}

	// procurar pela nova posi��o
	while (currentOperacao2 && currentOperacao2->position != newPosition)
	{
		previousOperacao2 = currentOperacao2;
		currentOperacao2 = currentOperacao2->next;
	}

	// se as opera��es relativas � antiga ou nova posi��o n�o foram encontradas
	if (currentOperacao1 == NULL || currentOperacao2 == NULL) return false;

	if (previousOperacao1) previousOperacao1->next = currentOperacao2; // se a opera��o anterior n�o for o head da lista
	else *operacoes = currentOperacao2; // sen�o fazer que opera��o anterior seja o head

	if (previousOperacao2) previousOperacao2->next = currentOperacao1; // se a opera��o nova n�o for o head da lista
	else *operacoes = currentOperacao1;// sen�o fazer com que opera��o anterior seja o head

	// trocar elementos
	Operacao* tempOperacao = currentOperacao2->next;
	currentOperacao2->next = currentOperacao1->next;
	currentOperacao1->next = tempOperacao;

	return true;
}

/**
* @brief	Ordenar lista de execu��es por ordem crescente do identificador da opera��o
* @param	head		Lista de execu��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
execution* SortexecutionsByOperacao(execution* head){
	//if (head == NULL) return head;// se a lista estiver vazia

	execution* current = head;
	execution* sorted = NULL;
	execution* new = NULL;

	while (current != NULL)
	{
		new = newexecution(current->operacaoPosition, current->maquinaID, current->runtime);
		sorted = InsertexecutionByOperacao(&sorted, new);
		current = current->next;
	}

	return sorted;
}

/**
* @brief	Obter a m�dia de tempo necess�rio para completar uma opera��o, considerando todas as alternativas poss�veis
* @param	head					Lista de execu��es
* @param	operacaoPosition		Identificador da opera��o
* @return	Valor da m�dia de tempo
*/
float getAverageTimeToCompleteOperacao(execution* head, int operacaoPosition)
{
	if (head == NULL) return -1.0f;// se a lista estiver vazia

	int sum = 0;
	float average = 0;
	float numberOfexecutions = 0;

	execution* current = head;

	while (current)
	{
		if (current->operacaoPosition == operacaoPosition) // se encontrar a execuca��o de opera��o relativa � opera��o
		{
			sum += current->runtime;
			numberOfexecutions++;
		}
		current = current->next;
	}

	if (numberOfexecutions > 0) average = sum / numberOfexecutions; // para n�o permitir divis�o por 0

	return average;
}

/**
* @brief	Mostrar a lista de opera��es na consola
* @param	head	Lista de opera��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool displayOperacoes(Operacao* head) {
	if (head == NULL) return false;// se a lista estiver vazia

	Operacao* current = head;

	while (current != NULL)
	{
		printf("ID/Placement: %d\n", current->position);
		current = current->next;
	}

	printf("\n");
	return true;
}