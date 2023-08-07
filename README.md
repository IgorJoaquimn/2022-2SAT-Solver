# 2022-2SAT-Solver

# Trabalho Prático 1

```
DCC215 - Algoritmos 1
Igor Joaquim da Silva Costa
```
## 1. Introdução

Oproblema propostofoiverificarseé possível satisfazertodosseguidores de um
político,apartirdeumasériedepropostasquepodemseraceitasounão.Maisprecisamente,
sãoapresentadosumnúmerodeseguidoresdealgumpolítico,equantaspropostasopolítico
possui,cadaseguidorescolhenomáximoduaspropostasparaaceitar,eduaspropostaspara
recusar,oproblemaéresolvidoseexisteumacombinaçãodeaceitação/rejeiçãode propostas
que satisfaça todos seguidores.
Pararesolveroproblemacitado,cadapropostadopolíticofoitratadocomoumliteral
booleanoetodarequisiçãodeusuáriocomoumacláusuladeumaCNF,ondeosliteraissãoas
propostas que o usuário querpromover, ourejeitar, nocasoda rejeição,são tomadosos
valores negativos do literais. Nesse sentido, o problema apresentado é reduzido à uma
instânciadoproblema 2SAT.Diantedisso,éconhecidoumalgoritmopolinomialcapazde
resolver uma instância de SAT, a partir de uma modelagem em grafo.
Diantedoexposto,adocumentaçãopresentepossuicomoobjetivodetalharcomoo
sistemafoimodelado(Seção2),oquãoeficienteelepodeser(Seção3).Porfim,oprojetoé
sumarizado junto com os aprendizados gerados durante a produção do trabalho(Seção 4).

## 2. Modelagem

Estaseçãotemcomoobjetivodiscutirasdecisõesquelevaramàatualmodelagemdo
programa.

# 2.1 2SAT

Comoelucidadonaseção1,oproblemaapresentadopodeserreduzidoaoproblema
2SAT,ondecadapar(x,y)depropostaquealgumusuárioquerquesejapromovido,setornaa
cláusula(XouY),ecadapar(x,y)depropostaspararejeitarsetornaacláusula(~Xou~Y).
Dessa forma,o problema pode ser todo escritoemumaúnicafórmulana formanormal
conjuntiva de 2 literais, ou seja, uma instância de 2SAT.


# 2.2 Resolver 2SAT

Afimderesolveroproblema2SAT,foiutilizadoumaoutraredução,onde2SATpode
serresolvidoporumproblemadeconectividadeemgrafos.Qualquercláusula(XouY)pode
serreescritapelaforma(Se~XentãoY ou Se~YentãoX),nessesentido,podemosmodelar
oproblemausandografosdaseguinteforma:paracadacláusula(XouY)de2SAT,crieuma
arestade (~X,Y)e(~Y,X) emum grafoG.Para representarumvértice~X,sabendoque
existem N literais, o indexque representa~X éX+N,logo ,todo indexmaiorqueN
representa um literal negativo.
Nessegrafo,qualquercaminhoentre 2 vérticesUeVrepresentaque,seUforfalso,
entãoVdeveserverdadeiro.Logo,seexistecaminhoentreXe~Xecaminhoentre~XeX,
para algum literal X, X deveserverdadeiro efalso aomesmotempo, logoexisteuma
contradição e a fórmula não é satisfatível.

# 2.3 Encontrar Componente conexo

Comooproblemafoireduzidoaverificarse,paratodoX,nãoexistecaminhodeX
para ~X e vice-versa, basta utilizar um algoritmo que encontra todos os componentes
fortementeconexos deumgrafo,existeXe~Xnomesmocomponenteseesomentesea
fórmula for satisfatível. Dessa forma, foi implementado o algoritmo de Kosaraju para
encontrarcomponentesfortementeconexos,queconsisteemrodarumaDFSparacadanódo
grafoG,marcarqualaordemqueosvérticesforamvisitadoseexecutarumaoutraDFSno
graforeversodeG,naordemdecrescenteemqueoselementosforamvisitadosemG.Todos
pares mutuamente alcançáveis estarão em um mesmo componente,a partir disso,basta
verificar se existem X e ~X no mesmo componente, para algum literal X.

# 2.4 Estrutura de Dados

Pararepresentarografo,foitomadaumalistadeadjacênciaparacadavérticepresente,
onde existearestaentre(X,Y) seYpertencea listadeadjacênciadeX.Essadecisãofoi
tomadapois,emgrandepartedoscasos,ografoépoucodenso,fazendoarepresentaçãoem
matrizdeadjacênciamaiscaraemespaçoetempodeexecução.Nessemesmosentido,existe
uma lista de adjacência para o grafo reverso.
Alémdisso,paraexecutaroKosaraju,foiusadoumtipovetorparasimularumapilha
e armazenar a ordem que os elementos são descobertos na primeira DFS.


## 3. Análise de complexidade

# 3.1 Espaço

SejaNonúmerodeusuárioseMonúmerodepropostas.Inicialmente,écriado2*M
vetoresvaziospararepresentarografosemnenhumaaresta,nopiordoscasos,cadavetor

possuirá2*M-1elementos.Assim,acomplexidadedeespaçosetorna𝑂(𝑀^2 )naquantidade
de propostas.

# 3.2 Tempo

```
Para análise de tempo, considere N o número de usuários e M o número de propostas.
```
## 3.2.1 Kosaraju

```
Para se realizar a busca por componente conexos, são feitas 2 DFS, onde a
```
complexidade de cada DFS é de 𝑂( 2 𝑀 + ( 2 𝑀)^2 ). Logo, verificar se a fórmula é
satisfatível cresce quadraticamente em função do número de propostas.

## 4. Conclusões

Com o intuito de saber se existe um conjunto de propostasque agradetodosos
seguidoresdealgumpolíticosimultaneamente,foiimplementadoumprograma queutiliza
algoritmos de componente conexos para resolver o problema.
Duranteoprojetodosistemaforamlevadasemconsideraçãonãosóaspectospráticos
da implementaçãode umamodelagemcomputacional,mastambémcomoalinguagemde
programaçãoescolhidapoderia serumaferramentaútilparachegarno objetivoesperado.
Todaaquestãodemapearummini-mundodeinteresseemummodelocomputacionalrobusto
semostroubastanteprodutiva,levandooalunoapensaremformascriativasde seresolver e
entenderoproblema,tendocomoresultadoumextensoaprendizadosobrecomo representar
um grafo pode facilitar,ouatrapalhar,na implementaçãoe naexecuçãode determinados
algoritmos.Porfim,otempoextrausadoparaprojetarosistematrouxeváriasrecompensas
no sentido da implementação, sendo um aspecto a ser levado para trabalhos futuros.


Nessesentido,todoofluxodetrabalhofoiessencialparaaconsolidaçãodeconteúdos
aprendidos emsala, além de apresentar,de formaprática,comosoftwaresmaiores, mais
consistentes e robustos são projetados e implementados.

## 5. Instruções para compilação e execução:

## 5.1 Compilação

Existempartesdoprogramaquesãocompatíveisapenasàsversõesmaisrecentesda
linguagem c++, dito isso, deve-se seguir as seguintes configurações para a compilação:

```
Linguagem: C++
Compilador: Gnu g++
Flags de compilação:-std=c++11 -g
Versão da linguagem: standard C++1 1
Sistema operacional (preferência): distribuições baseadas no kernel Linux 5.15.
```
Ocomandoparacompilaroprogramaautomaticamenteestápresentenoarquivo **“Makefile”**
esuaexecuçãoéchamadapelocomando **“makeall”** .Destemodo,oexecutável“tp01”estará
compilado e pronto para ser utilizado.

### 5.2 Execução

```
Seguem as instruções para a execução manual:
```
1. Certifique-se que o compilável foigeradode maneiracorreta,sealgum problema
    ocorrer, execute o comando “make all” presente no “Makefile”.
2. Uma vez que os passos anteriores foram cumpridos, executeo programa com o
    comando: ./tp01 < caso Teste01.txt )
3. A saída será impressa no terminal.


