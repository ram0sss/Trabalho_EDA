/**
* Autor:                Tiago Da Cunha Silva Ramos (23512)
* Email:                a23512@alunos.ipca.pt
* Data:                 18/04/2022
*
* Descricao:            Ficheiro com funcoes relacionadas com operacoes de "Trabalhos"
*/

#include "DataManagement.h"

/**
* @brief	Criar novo trabalho
* @param	id	Identificador do trabalho
* @return	Novo trabalho
*/
Job* newJob(int id) {
	Job* new = (Job*)malloc(sizeof(Job));

	new->id = id;
	new->next = NULL;

	return new;
}

/**
* @brief	Inserir novo trabalho no inicio da lista de trabalhos
* @param	head	Lista de trabalhos
* @param	new		Novo trabalho
* @return	Lista de trabalhos atualizada
*/
Job* InsertJobInList(Job* head, Job* new) {
	
	if (head == NULL) head = new; // se a lista estiver vazia
	else // se existir algum elemento na lista
	{
		new->next = head;
		head = new;
	}

	return head;
}

/**
* @brief	Armazenar lista de trabalhos em ficheiro bin�rio
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de trabalhos
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeJobs(char fileName[], Job* head){
	if (head == NULL) return false; // se lista est� vazia
	
	FILE* file = NULL;
	if ((file = fopen(fileName, "wb")) == NULL) return false; // se n�o foi poss�vel abrir o ficheiro
	
	Job* current = head;
	FileJob currentJob;	//para gravar em ficheiro
	while (current) //escrever todos os elementos da lista no ficheiro
	{
		currentJob.id = current->id;

		fwrite(&currentJob, sizeof(FileJob), 1, file);
		current = current->next;
	}

	fclose(file);

	return true;
}

/**
* @brief	Ler lista de trabalhos de ficheiro bin�rio
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de trabalhos
*/
Job* readJobs(char fileName[]){
	FILE* file;

	if ((file = fopen(fileName, "rb")) == NULL) return NULL; // se nao foi possivel abrir o ficheiro

	Job* head = NULL;
	Job* current = NULL;
	FileJob currentJob; //  a mesma estrutura mas sem o campo *next, uma vez que esse campo nao e armazenado no ficheiro

	while (fread(&currentJob, sizeof(FileJob), 1, file)) // le todos os registos do ficheiro e guarda na lista
	{
		current = newJob(currentJob.id);
		head = InsertJobInList(head, current);
	}

	fclose(file);
	return head;
}

/**
* @brief	Libertar a lista de trabalhos da mem�ria
* @param	head	Lista de trabalhos
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool freeJobs(Job* head){
	if (head == NULL) return false; // se lista est� vazia

	Job* current = NULL;

	while (head != NULL)
	{
		current = head;
		head = head->next;
		free(current);
	}

	return true;
}

/**
* @brief	Obter o m�nimo de tempo necess�rio para completo um trabalho e as respetivas execu��es
* @param	operacoes		Lista de opera��es
* @param	executions		Lista de execu��es
* @param	minexecutions	Apontador para a lista de execu��es a ser devolvida, relativamente ao tempo m�nimo
* @return	Quantidade de tempo
*/
int getMinTimeToCompleteJob(Operacao* operacoes, execution* executions, execution** minexecutions)
{
	if (operacoes == NULL || executions == NULL) return -1;// se as listas estiverem vazias

	int time = 99999;
	int counter = 0;

	Operacao* currentOperacao = operacoes;
	execution* currentexecution = executions;
	execution* minexecution = NULL;

	while (currentOperacao) // percorrer lista de opera��es
	{
			while (currentexecution) // percorrer lista de execu��o de opera��es
			{
				if (currentexecution->operacaoPosition == currentOperacao->position) // se encontrar a execuca��o de opera��o relativa � opera��o
				{
					// guardar execu��o de opera��o com menor tempo de utiliza��o
					if (currentexecution->runtime < time)
					{
						time = currentexecution->runtime;
						minexecution = newexecution(currentexecution->operacaoPosition, currentexecution->maquinaID, currentexecution->runtime);
					}
				}
				currentexecution = currentexecution->next;
			}

		*minexecutions = InsertexecutionInList(*minexecutions, minexecution);

		// repor lista percorrida (currentexecution), para que se for necess�rio voltar a percorrer o while da execu��o de opera��es de novo
		freeexecutions(currentexecution);
		currentexecution = NULL;
		currentexecution = executions;
		counter += time; // acumular o tempo de utiliza��o de cada execu��o de opera��o
		time = 99999; // resetar tempo para a pr�xima itera��o
		
		currentOperacao = currentOperacao->next;
	}

	return counter;
}

/**
* @brief	Obter o m�ximo de tempo necess�rio para completo um trabalho e as respetivas execu��es
* @param	operacoes		Lista de opera��es
* @param	executions		Lista de execu��es
* @param	maxexecutions	Apontador para a lista de execu��es a ser devolvida, relativamente ao tempo m�ximo
* @return	Quantidade de tempo
*/
int getMaxTimeToCompleteJob(Operacao* operacoes, execution* executions, execution** maxexecutions)
{
	if (operacoes == NULL || executions == NULL) return -1;// se as listas estiverem vazias

	int time = 0;
	int counter = 0;

	Operacao* currentOperacao = operacoes;
	execution* currentexecution = executions;
	execution* maxexecution = NULL;

	while (currentOperacao != NULL) // percorrer lista de opera��es
	{
			while (currentexecution != NULL) // percorrer lista de execu��o de opera��es
			{
				if (currentexecution->operacaoPosition == currentOperacao->position) // se encontrar a execuca��o de opera��o relativa � opera��o
				{
					// guardar execu��o de opera��o com maior tempo de utiliza��o
					if (currentexecution->runtime > time)
					{
						time = currentexecution->runtime;
						maxexecution = newexecution(currentexecution->operacaoPosition, currentexecution->maquinaID, currentexecution->runtime);
					}
				}

				currentexecution = currentexecution->next;
			}

		*maxexecutions = InsertexecutionInList(*maxexecutions, maxexecution);

		// repor lista percorrida (currentexecution), para que se for necess�rio voltar a percorrer o while da execu��o de opera��es de novo
		freeexecutions(currentexecution);
		currentexecution = NULL;
		currentexecution = executions;
		counter += time; // acumular o tempo de utiliza��o de cada execu��o de opera��o
		time = 0; // resetar tempo de utiliza��o para a pr�xima itera��o

		currentOperacao = currentOperacao->next;
	}

	return counter;
}