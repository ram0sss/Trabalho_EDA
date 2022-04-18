/**
* @author	Tiago Da Cunha Silva Ramos (23512)
* @email	a23512@alunos.ipca.pt
* @data     18/04/2022
* @file		StandardData.c
*
* @brief	Ficheiro com funcao para carregar dados iniciais em listas
*/

#include "DataManagement.h"

/**
* @brief	Carregar dados para as listas
* @param	jobs		Apontador para a lista de jobs
* @param	maquinas	Apontador para a lista de maquinas
* @param	operacoes	Apontador para a lista de operacoes
* @param	executions	Apontador para a lista de executions de operacoes
*/

void loadData(Job** jobs, maquina** maquinas, Operacao** operacoes, execution** executions)
{
	Job* job = NULL;
	maquina* maquina = NULL;
	Operacao* operacao = NULL;
	execution* execution = NULL;

	// jobs (id)
	job = newJob(1);
	*jobs = InsertJobInList(*jobs, job);

	// maquinas (id)
	maquina = newMaquina(1);
	*maquinas = InsertMaquinaInList(*maquinas, maquina);
	maquina = newMaquina(2);
	*maquinas = InsertMaquinaInList(*maquinas, maquina);
	maquina = newMaquina(3);
	*maquinas = InsertMaquinaInList(*maquinas, maquina);
	maquina = newMaquina(4);
	*maquinas = InsertMaquinaInList(*maquinas, maquina);
	maquina = newMaquina(5);
	*maquinas = InsertMaquinaInList(*maquinas, maquina);
	maquina = newMaquina(6);
	*maquinas = InsertMaquinaInList(*maquinas, maquina);
	maquina = newMaquina(7);
	*maquinas = InsertMaquinaInList(*maquinas, maquina);
	maquina = newMaquina(8);
	*maquinas = InsertMaquinaInList(*maquinas, maquina);
	
	// operacoes (id/order)
	operacao = newOperacao(1);
	*operacoes = InsertOperacaoInList(*operacoes, operacao);
	operacao = newOperacao(2);
	*operacoes = InsertOperacaoInList(*operacoes, operacao);
	operacao = newOperacao(3);
	*operacoes = InsertOperacaoInList(*operacoes, operacao);
	operacao = newOperacao(4);
	*operacoes = InsertOperacaoInList(*operacoes, operacao);

	// execution (operation_id, maquina_id, time)
	// operacao 1
	execution = newexecution(1, 1, 4);
	*executions = InsertexecutionInList(*executions, execution);
	execution = newexecution(1, 3, 5);
	*executions = InsertexecutionInList(*executions, execution);

	// operacao 2
	execution = newexecution(2, 2, 4);
	*executions = InsertexecutionInList(*executions, execution);
	execution = newexecution(2, 4, 5);
	*executions = InsertexecutionInList(*executions, execution);

	// operacao 3
	execution = newexecution(3, 3, 5);
	*executions = InsertexecutionInList(*executions, execution);
	execution = newexecution(3, 5, 6);
	*executions = InsertexecutionInList(*executions, execution);

	// operacao 4
	execution = newexecution(4, 4, 5);
	*executions = InsertexecutionInList(*executions, execution);
	execution = newexecution(4, 5, 5);
	*executions = InsertexecutionInList(*executions, execution);
	execution = newexecution(4, 6, 4);
	*executions = InsertexecutionInList(*executions, execution);
	execution = newexecution(4, 7, 5);
	*executions = InsertexecutionInList(*executions, execution);
	execution = newexecution(4, 8, 9);
	*executions = InsertexecutionInList(*executions, execution);
}

/**
* @brief	Extra para mostrar dados na consola
*/
void ShowData(execution* executions) {
	printf("executions:\n");
	displayexecutions(executions);
}
