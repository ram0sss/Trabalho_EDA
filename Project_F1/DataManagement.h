/**
* @author	Tiago Da Cunha Silva Ramos (23512)
* @email	a23512@alunos.ipca.pt
* @date		18/04/2022
* @file		DataManagement.h
*
* @brief	Ficheiro com todas as declaracoes necessarias para a execution do projeto
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#pragma once

#pragma region structs
/**
* @brief	Estrutura de dados para a lista de Trabalhos
*/
typedef struct Job{
	int id;
	struct Job* next;
	struct Job* jobs;
} Job;

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de trabalhos
 */
typedef struct FileJob{
	int id;
} FileJob;

/**
* @brief	Estrutura de dados para a lista de Maquinas
*/
typedef struct maquina{
	int id;
	bool isBusy;
	struct maquina* next;
	struct maquina* maquinas;
} maquina;

/**
* @brief	Estrutura de dados para armazenar em ficheiro a lista de maquinas
*/
typedef struct Filemaquina{
	int id;
	bool isBusy; // se a maquina esta ou nao a ser utilizada
} Filemaquina;

/**
* @brief	Estrutura de dados para a lista de executions das Operacoes das Maquinas
*/
typedef struct execution{ 
	int operacaoPosition;
	int maquinaID;
	int runtime; // tempo necessario para a execution da operacao
	struct execution* next;
	struct execution* executions;
} execution;

/**
* @brief	Estrutura de dados para armazenar em ficheiro a lista de executions das operacoes em maquinas
*/
typedef struct Fileexecution{
	int operacaoPosition;
	int maquinaID;
	int runtime;
} Fileexecution;

/**
* @brief	Estrutura de dados para a lista  de operacoes
*/
typedef struct Operacao{
	int position; // posicao da operacao 
	struct Operacao* next;
	struct Operacao* operacoes;
} Operacao;

/**
* @brief	Estrutura de dados para armazenar em ficheiro a lista de operacoes
*/
typedef struct FileOperacao{
	int position;
} FileOperacao;
#pragma endregion

#pragma region Assinaturas de Funcoes

/**
* @brief	Sobre trabalhos
*/
Job* newJob(int id);
Job* insertJobAtStart(Job* head, Job* new);
bool writeJobs(char fileName[], Job* head);
Job* readJobs(char fileName[]);
bool freeJobs(Job* head);
int getMinTimeToCompleteJob(Operacao* operacoes, execution* executions, execution** minexecutions);
int getMaxTimeToCompleteJob(Operacao* operacoes, execution* executions, execution** maxexecutions);

/**
* @brief	Sobre maquinas
*/
maquina* newMaquina(int id);
maquina* InsertMaquinaInList(maquina* head, maquina* new);
bool writeMaquinas(char fileName[], maquina* head);
maquina* readMaquinas(char fileName[]);
bool freeMaquinas(maquina* head);
bool displayMaquinas(maquina* head);

/**
* @brief	Sobre operacoes
*/
Operacao* newOperacao(int position);
Operacao* InsertOperacaoInList(Operacao* head, Operacao* new);
bool updatePosition(Operacao** operacoes, int oldPosition, int newPosition);
bool deleteOperacao(Operacao** head, int id);
bool writeOperacoes(char fileName[], Operacao* head);
Operacao* readOperacoes(char fileName[]);
bool freeOperacoes(Operacao* head);
bool displayOperacoes(Operacao* head);
float getAverageTimeToCompleteOperacao(execution* head, int operacaoID);
bool updatePosition(Operacao** operacoes, int oldPosition, int newPosition);
execution* SortexecutionsByOperacao(execution* head);

/**
* @brief	Sobre executions
*/
execution* newexecution(int operacaoPosition, int maquinaID, int runtime);
execution* InsertexecutionInList(execution* head, execution* new);
execution* InsertexecutionByOperacao(execution* head, execution* new);
bool updateRuntime(execution** head, int operacaoID, int maquinaID, int runtime);
bool deleteexecutionByOperacao(execution** head, int opercaoID);
bool writeexecutions(char fileName[], execution* head);
execution* readexecutions(char fileName[]);
bool freeexecutions(execution* head);
bool displayexecutions(execution* head);
bool searchexecution(execution* head, int operacaoID, int maquinaID);
bool searchexecutionByOperacao(execution* head, int operacaoID);

/**
 * @brief	Carregar dados para listas
 */
void loadData(Job** jobs, maquina** maquinas, Operacao** operacoes, execution** executions);

/**
 * @brief	Carregar dados para a consola
 */
void ShowData(execution* executions);

#pragma endregion
