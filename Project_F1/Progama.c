/**
* @author	Tiago Da Cunha Silva Ramos (23512)
* @email	a23512@alunos.ipca.pt
* @data		18/04/2022
* @file		MainProgram.c
* 
* @brief	Ficheiro principal da aplicacao, com menu e chamada de funcoes
*
* Software desenvolvido para a proposta de escalonamento para a producao de um produto que envolve varias operacoes
* e a utilizacao de varias maquinas, para minimizar o tempo necessario na sua producao.
* @see https://github.com/ram0sss/Trabalho_EDA.git
*/

#include"DataManagement.h"
#include "jobs.c"


/**
* @brief	Funcao principal do programa
*/
void main() {
	setlocale(LC_ALL, "Portuguese"); // permitir caracteres especiais na consola
	
	Job* jobs = NULL;
	Operacao* operacoes = NULL;
	maquina* maquinas = NULL;
	execution* executions = NULL;

#pragma region Funcionalidade 1: Definicao de uma estrutura de dados dinamica para a representacao de um job com um conjunto finito de n operacoes;
	printf("FUNCIONALIDADE 1: Definicao de uma estrutura de dados dinamica para a representacao de um job com um conjunto finito de n operacoes;\n\n");

	loadData(&jobs, &maquinas, &operacoes, &executions);
	
	ShowData(executions);
#pragma endregion


#pragma region Funcionalidade 2: Armazenamento/leitura de ficheiro de texto com representacao de um job;
	printf("\nFUNCIONALIDADE 2: Armazenamento/leitura de ficheiro de texto com representacao de um job;\n\n");

	// guardar os dados em ficheiros
	writeJobs("jobs", jobs);
	writeMaquinas("maquinas", maquinas);
	writeOperacoes("operacoes", operacoes);
	writeexecutions("executions", executions);
	printf("Dados exportados com sucesso!\n");

	// libertar memoria das listas anteriores, para serem lidas dos ficheiros
	freeJobs(jobs);
	freeMaquinas(maquinas);
	freeOperacoes(operacoes);
	freeexecutions(executions);

	// depois de libertar memoria, definir listas como NULL para evitar possiveis erros
	jobs = NULL;
	maquinas = NULL;
	operacoes = NULL;
	executions = NULL;

	// ler dados de ficheiros
	jobs = readJobs("jobs");
	maquinas = readMaquinas("maquinas");
	operacoes = readOperacoes("operacoes");
	executions = readexecutions("executions");
	
	printf("Dados importados com sucesso!\n\n");
#pragma endregion


#pragma region Funcionalidade 3: Insercao de uma nova operacao;
	printf("\nFUNCIONALIDADE 3: Insercao de uma nova operacao;\n\n");

	//inserir nova operacao
	Operacao* operacao = NULL;
	operacao = newOperacao(5);
	operacoes = InsertOperacaoInList(operacoes, operacao);

	//inserir nova execution de uma operacao
	execution* execution = NULL;
	execution = newexecution(5, 10, 10);
	executions = InsertexecutionInList(executions, execution);

	//guardar as novas insercoes em ficheiros
	writeOperacoes("operacoes", operacoes);
	writeexecutions("executions", executions);
	
	//mostrar dados na consola
	printf("Insercao de uma nova operacao com sucesso!\n\n");

	ShowData(executions);
#pragma endregion


#pragma region Funcionalidade 4: Remocao de uma determinada operacao;
	printf("\nFUNCIONALIDADE 4: Remocao de uma determinada operacao;\n\n");

	// remover operacao
	deleteOperacao(&operacoes, 5);
	printf("Operacao removida com sucesso!\n");

	bool allFound = false;
	while (allFound == false) // enquanto que encontrar operacoes, remover as executions de operacoes associadas
	{
		if (searchexecutionByOperacao(executions, 5))
		{
			// remover execution
			deleteexecutionByOperacao(&executions, 5);
			printf("execution associada a operacao removida com sucesso!\n\n\n");
		}
		else allFound = true;
	}

	ShowData(executions);
#pragma endregion


#pragma region Funcionalidade 5: Alteracao de uma determinada operacao;
	printf("\nFUNCIONALIDADE 5: Alteracao de uma determinada operacao;\n\n");
	
	// alterar a posicao da operacao num determinado job (...; posicao antiga; posicao nova
	updatePosition(&operacoes, 4, 2);
	printf("Posicao da operacao alterada com sucesso!\n");

	// alterar o tempo necessario para uma execution da operacao(...; operacao_position; maquina_id; new_runtime)
	updateRuntime(&executions, 2, 2, 10);
	printf("Tempo necessario para a execution da operacao alterada com sucesso!\n\n");

	ShowData(executions);
#pragma endregion


#pragma region Funcionalidade 6: Determinacao da quantidade minima de unidades de tempo necessarias para completar o job e listagem das respetivas operacoes;
	printf("\nFUNCIONALIDADE 6: Determinacao da quantidade minima de unidades de tempo necessarias para completar o job e listagem das respetivas operacoes;\n\n");
	
	// obter o tempo minimo para completar um job e as respetivas operacoes
	execution* minExecutions = NULL;
	int minTime = getMinTimeToCompleteJob(operacoes, executions, &minexecutions);

	// mostrar resultados
	printf("Menor tempo necessario para completar o trabalho � %d!\n", minTime);
	printf("Operacoes com menor tempo:\n");
	minexecutions = SortexecutionsByOperacao(minexecutions);
	displayexecutions(minexecutions);
#pragma endregion


#pragma region Funcionalidade 7: Determinacao da quantidade maxima de unidades de tempo necessarias para completar o job e listagem das respetivas operacoes;
	printf("\nFUNCIONALIDADE 7: Determinacao da quantidade maxima de unidades de tempo necessarias para completar o job e listagem das respetivas operacoes;\n\n");
	
	// obter o tempo maximo para completar um job
	execution* maxexecutions = NULL;
	int maxTime = getMaxTimeToCompleteJob(operacoes, executions,&maxexecutions);

	// mostrar resultados
	printf("Maior tempo necessario para completar o trabalho(ID: %d) � %d!\n",  maxTime);
	printf("Operacoes com maior tempo:\n");
	maxexecutions = SortexecutionsByOperacao(maxexecutions);
	displayexecutions(maxexecutions);
#pragma endregion


#pragma region Funcionalidade 8: Determinacao da quantidade media de unidades de tempo necessarias para completar uma operacao, considerando todas as alternativas poss�veis;
	printf("\nFUNCIONALIDADE 8: Determinacao da quantidade media de unidades de tempo necessarias para completar uma operacao, considerando todas as alternativas poss�veis;\n\n");

	// obter o tempo medio para completar uma operacao
	float average = getAverageTimeToCompleteOperacao(executions, 1);

	// mostrar resultado
	printf("Media de tempo necessario para completar a operacao(ID: %d) � %.2f!\n", 1, average);
#pragma endregion

}



