#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef enum {
	GUERREIRO = 1,
	ARQUEIRO,
	MAGO
} Classe;

typedef enum {
	ARMA = 1,
	POCAO,
	ARMADURA
} Tipoitem;

typedef enum {
	CASA_VAZIA = 1,
	CASA_COMBATE,
	CASA_TESOURO,
	CASA_CURA,
	CASA_ARMADILHA,
	CASA_LOJA,
	CASA_MISSAO,
	CASA_CHEFE
} Tipocasa;

typedef enum {
	ACAO_ATACAR = 1,
	ACAO_DEFENDER,
	ACAO_HABILIDADE,
	ACAO_FUGIR,
	ACAO_POCAO
} Acaocombate;

typedef enum {
	FACIL =1,
	MEDIO,
	DIFICIL
} Dificuldade;

typedef struct {
	char nome[30];
	char descricao[100];
	int vidaatual, vidamax,ataque,defesa;
	int nivel, xprecompensa;
	Dificuldade dificuldade;
	int ourorecompensa;
	int turnosQueimadura;
	int danoQueimadura;
} Monstro;


typedef struct {
	char nome[30];
	int vidaatual, vidamax, ataque,defesa, agilidade, inteligencia;
	int ouro;
	int pocaoPequena;
	int pocaoGrande;
	Classe classe;
	int xp, nivel;
	int usosMaximosHabilidade;
	int usosHabilidade;
} Personagem;

typedef struct {
	char nome[30];
	Tipoitem tipo;
	int bonusvida;
    int bonusataque;
    int bonusdefesa;
} Item;
	
Personagem jogador;

int calcularatributo(int base, int bonus) {
    return base + bonus;
}
void recompensaChefe(Personagem *p, int fase){
	if (fase == 1) {
    p->vidamax += 20;
    p->vidaatual += 20;

    printf("\n===== RECOMPENSA RECEBIDA =====\n");
    printf("Cristal de Vitalidade!\n");
    printf("+20 de vida maxima!\n");
}else if (fase == 2) {
    p->ataque += 5;
    p->inteligencia += 5;

    printf("\n===== RECOMPENSA RECEBIDA =====\n");
    printf("Nucleo Arcano!\n");
    printf("+5 de ataque!\n");
    printf("+5 de inteligencia!\n");
}else if (fase == 3) {
    p->ataque += 10;
    p->defesa += 10;
    p->inteligencia += 10;

    printf("\n===== RECOMPENSA FINAL =====\n");
    printf("Coracao Demoniaco!\n");
    printf("+10 de ataque!\n");
    printf("+10 de defesa!\n");
    printf("+10 de inteligencia!\n");
}
}
int rolardado(int lados){
	return rand() % lados + 1;
}
void moverJogador(int *posicao, int tamanhoTabuleiro, int missaoConcluida) {
    int dado;

    dado = rolardado(6);

    printf("Voce tirou %d no dado!\n", dado);
	int posicaoAnterior = *posicao;
    *posicao = *posicao + dado;

    if (*posicao >= tamanhoTabuleiro) {
        *posicao = tamanhoTabuleiro - 1;
    }
	if (!missaoConcluida && *posicao > 8) {
		*posicao = 8;
		printf("Voce precisa concluir a missao antes de enfrentar o chefe!\n");
}
	printf("Voce avancou %d casas!\n", *posicao - posicaoAnterior);
	printf("Posicao atual: Casa %d\n", *posicao + 1);
}

void curarPersonagem(Personagem *p, int cura) {
    p->vidaatual += cura;

    if (p->vidaatual > p->vidamax) {
        p->vidaatual = p->vidamax;
    }

    printf("\nVoce recuperou vida!\n");
    printf("Vida atual: %d/%d\n", p->vidaatual, p->vidamax);
}

void ativarArmadilha(Personagem *p) {
    int dano = rolardado(20);

    printf("\n========== ARMADILHA ==========\n");
    printf("Voce pisou em uma armadilha!\n");
    printf("A armadilha causou %d de dano!\n", dano);

    p->vidaatual -= dano;

    if (p->vidaatual < 0) {
        p->vidaatual = 0;
    }

    printf("Vida atual: %d/%d\n", p->vidaatual, p->vidamax);
    printf("===============================\n");
}

void encontrarTesouro(Personagem *p) {
    int recompensa = rolardado(30);

    p->ouro += recompensa;

    printf("\n=== TESOURO ENCONTRADO! ===\n");
    printf("Voce encontrou %d moedas de ouro!\n", recompensa);
    printf("Ouro total: %d\n", p->ouro);
}

void loja(Personagem *p) {
    int opcao;

    do {
        printf("\n========== LOJA ==========\n");
        printf("Ouro: %d moedas\n", p->ouro);
        printf("1 - Pocao pequena (20 moedas)\n");
        printf("2 - Pocao grande (40 moedas)\n");
        printf("3 - Sair da loja\n");
        printf("==========================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
				if (p->ouro >= 20) {
					p->ouro -= 20;
					p->pocaoPequena++;
					printf("Pocao pequena comprada!\n");
				} else {
					printf("Ouro insuficiente!\n");
				}
				break;

			case 2:
				if (p->ouro >= 40) {
					p->ouro -= 40;
					p->pocaoGrande++;
					printf("Pocao grande comprada!\n");
				} else {
					printf("Ouro insuficiente!\n");
				}
				break;

            case 3:
                printf("Voce saiu da loja!\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 3);
}

void exibirInventario(Personagem p, Item inventario[]) {
    printf("\n========== INVENTARIO ==========\n");
    printf("Ouro: %d\n", p.ouro);
    printf("Pocoes pequenas: %d\n", p.pocaoPequena);
    printf("Pocoes grandes: %d\n", p.pocaoGrande);
    printf("Vida: %d/%d\n", p.vidaatual, p.vidamax);
    printf("================================\n");
	printf("\n===== EQUIPAMENTOS =====\n");

	for (int i = 0; i < 5; i++) {
		if (inventario[i].nome[0] != '\0') {
			printf("- %s\n", inventario[i].nome);
		}
	}
}

int usarPocao(Personagem *p) {
    int opcao;

    printf("\n====== INVENTARIO DE POCOES ======\n");
    printf("1 - Pocao pequena (+30 vida) [%d]\n", p->pocaoPequena);
    printf("2 - Pocao grande (+60 vida) [%d]\n", p->pocaoGrande);
    printf("3 - Voltar\n");
    printf("Escolha: ");

    if (scanf("%d", &opcao) != 1) {
        printf("Entrada invalida!\n");
        while (getchar() != '\n');
        return 0;
    }

    switch (opcao) {
        case 1:
            if (p->pocaoPequena <= 0) {
                printf("Voce nao possui essa pocao!\n");
                return 0;
            }

            if (p->vidaatual == p->vidamax) {
                printf("Sua vida ja esta cheia!\n");
                return 0;
            }

            p->pocaoPequena--;
            curarPersonagem(p, 30);
            return 1;

        case 2:
            if (p->pocaoGrande <= 0) {
                printf("Voce nao possui essa pocao!\n");
                return 0;
            }

            if (p->vidaatual == p->vidamax) {
                printf("Sua vida ja esta cheia!\n");
                return 0;
            }

            p->pocaoGrande--;
            curarPersonagem(p, 60);
            return 1;

        case 3:
            printf("Voltando ao combate...\n");
            return 0;

        default:
            printf("Opcao invalida!\n");
            return 0;
    }
}


void combate(Personagem *p, Monstro *m,int ehChefe);
void adicionarAtributoAleatorio(Personagem *p) {
	 int sorteio = rolardado(5);

    switch (sorteio) {
        case 1:
            p->ataque += 1;
            printf("\nBonus recebido: +1 de ataque!\n");
            break;

        case 2:
            p->defesa += 1;
            printf("\nBonus recebido: +1 de defesa!\n");
            break;

        case 3:
            p->agilidade += 1;
            printf("\nBonus recebido: +1 de agilidade!\n");
            break;

        case 4:
            p->inteligencia += 1;
            printf("\nBonus recebido: +1 de inteligencia!\n");
            break;

        case 5:
            p->vidamax += 5;
            p->vidaatual += 5;
            printf("\nBonus recebido: +5 de vida maxima!\n");
            break;
    }
}

void verificarCasa(Tipocasa casa, Personagem *p, Monstro monstros[], int quantidade, int *missaoConcluida, int *chefeDerrotado, Monstro *chefe, int fase) {

    switch (casa) {

        case CASA_VAZIA:
            printf("\nVoce encontrou uma casa vazia!\n");
            break;

        case CASA_COMBATE: {
            int sorteio = rolardado(quantidade) - 1;
			monstros[sorteio].vidaatual = monstros[sorteio].vidamax;
			monstros[sorteio].turnosQueimadura = 0;
			monstros[sorteio].danoQueimadura = 0;
				
			Monstro monstroAtual = monstros[sorteio];
			
            printf("\nUm %s apareceu!\n", monstroAtual.nome);
            combate(p, &monstroAtual, 0);
			if (monstroAtual.vidaatual <= 0 && p->vidaatual > 0) {
				adicionarAtributoAleatorio(p);
			}
            break;
        }

        case CASA_TESOURO:
            encontrarTesouro(p);
            break;

        case CASA_CURA:
            curarPersonagem(p, 20);
            break;

        case CASA_ARMADILHA:
            ativarArmadilha(p);
            break;

        case CASA_LOJA:
            loja(p);
            break;

        case CASA_MISSAO:

			printf("\n");
			printf("========================================\n");
			printf("              MISSAO\n");
			printf("========================================\n");

			switch (fase) {

				case 1:
					printf("\nVoce chegou ao coracao da Floresta Sombria!\n");
					printf("Uma criatura colossal domina a floresta.\n");
					printf("O Ogro Rei esta destruindo tudo ao seu redor.\n");
					printf("Prepare-se para uma batalha epica!\n");
					break;

				case 2:
					printf("\nVoce entrou nas profundezas da Masmorra!\n");
					printf("Um Lich controla as almas dos mortos.\n");
					printf("Para libertar este lugar, destrua sua magia sombria!\n");
					break;

				case 3:
					printf("\nVoce chegou ao Reino Demoniaco!\n");
					printf("O Rei Demoniaco aguarda sua chegada.\n");
					printf("Esta sera sua batalha final!\n");
					break;

				default:
					printf("\nMissao desconhecida!\n");
					break;
			}
			*missaoConcluida = 1;
			printf("========================================\n");
			break;

        case CASA_CHEFE:
			if (*missaoConcluida == 1 && !(*chefeDerrotado)) {
				printf("\n========== CHEFE FINAL ==========\n");
				printf("O %s apareceu!\n", chefe->nome);
				chefe->vidaatual = chefe->vidamax;
				chefe->turnosQueimadura = 0;
				chefe->danoQueimadura = 0;
				combate(p, chefe, 1);
				if (chefe->vidaatual <= 0 && p->vidaatual > 0) {
					p->ouro += chefe->ourorecompensa;

					printf("\n===== CHEFE DERROTADO! =====\n");
					printf("Voce recebeu %d moedas de ouro!\n",
						   chefe->ourorecompensa);
					printf("Ouro total: %d\n", p->ouro);
					recompensaChefe(p, fase);
					*chefeDerrotado = 1;
				}
			} else {
				printf("\nVoce precisa concluir a missao primeiro!\n");
			}
			break;

        default:
            printf("\nCasa desconhecida!\n");
            break;
    }
}
void exibirHistoria() {
    printf("\n");
    printf("============================================\n");
    printf("          AS CRONICAS DE ELDORIA\n");
    printf("============================================\n");

    printf("\nHa muitos seculos, o reino de Eldoria era");
    printf("\nprotegido pelo poderoso Coracao da Luz.\n");

    printf("\nUm antigo feiticeiro, conhecido como Rei");
    printf("\nDemoniaco, corrompeu o cristal e espalhou");
    printf("\numa terrivel maldicao pelo reino.\n");

    printf("\nMonstros surgiram, cidades foram destruidas");
    printf("\ne a escuridao tomou conta das terras.\n");

    printf("\nAgora, um heroi foi escolhido para recuperar");
    printf("\nos tres fragmentos do Coracao da Luz e");
    printf("\nderrotar o responsavel pela destruicao.\n");

    printf("\n============================================\n");
    printf("                 SUA JORNADA\n");
    printf("============================================\n");

    printf("\nFASE 1 - FLORESTA SOMBRIA");
    printf("\nAtravesse a floresta e derrote o Ogro Rei.");

    printf("\n\nFASE 2 - A MASMORRA");
    printf("\nEnfrente criaturas amaldicoadas e derrote o Lich.");

    printf("\n\nFASE 3 - REINO DEMONIACO");
    printf("\nEnfrente os guardioes e derrote o Rei Demoniaco.");

    printf("\n\nSeu destino e salvar Eldoria!");
    printf("\n============================================\n");
}
void exibirTabuleiro(int posicao, int tamanho, Tipocasa tabuleiro[]) {
    printf("\n========== TABULEIRO ==========\n");

    for (int i = 0; i < tamanho; i++) {

		if (i == posicao) {
			printf("[ P ]");
		} else {
			switch (tabuleiro[i]) {
				case CASA_VAZIA:
					printf("[ V ]");
					break;

				case CASA_COMBATE:
					printf("[ C ]");
					break;

				case CASA_TESOURO:
					printf("[ T ]");
					break;

				case CASA_CURA:
					printf("[ H ]");
					break;

				case CASA_ARMADILHA:
					printf("[ A ]");
					break;

				case CASA_LOJA:
					printf("[ L ]");
					break;

				case CASA_MISSAO:
					printf("[ M ]");
					break;
				case CASA_CHEFE:
					printf("[ B ]");
					break;
			}
    }
}

    printf("\n===============================\n");
}

void danoNoMonstro(Monstro *m, int dano) {
    m->vidaatual = m->vidaatual - dano;

    if (m->vidaatual < 0) {
        m->vidaatual = 0;
    }
}

int vidabase = 120;
int ataquebase = 13;
int defesabase = 5;
int agilidadebase = 5;
int inteligenciabase = 5;
int bonusagilidade = 0;
int bonusinteligencia = 0;
int bonusvida = 0;
int bonusataque = 0;
int bonusdefesa = 0;
int bonusarma = 0;
int resp = 0;
int dado;


int calculardano(Personagem jogador) {
    return jogador.ataque;
}

void atacarMonstro(Monstro *m, Personagem jogador) {
    int dado = rolardado(20);
    int ataque = jogador.ataque + dado / 4;
    int dano;

    printf("\n--- ATAQUE ---\n");
    printf("Dado: %d\n", dado);

    if (dado == 1) {
        printf("Falha critica!\n");
        dano = 0;
    } else {
        if (dado == 20) {
            printf("Acerto critico!\n");
            ataque = ataque + ataque / 2;
        } else {
            printf("Ataque normal!\n");
        }

        dano = ataque - (m->defesa / 2);

        if (dano < 1) {
            dano = 1;
        }
    }

    danoNoMonstro(m, dano);

    printf("Ataque total: %d\n", ataque);
    printf("Dano causado: %d\n", dano);
    printf("Vida do %s: %d/%d\n",
           m->nome, m->vidaatual, m->vidamax);
}
int habilidadeEspecial(Monstro *m, Personagem jogador){
	int dano;
	if (jogador.classe == GUERREIRO) {
		printf("\nGolpe poderoso!\n");

		dano = jogador.ataque + 5 - m->defesa;

        if (dano < 1) {
            dano = 1;
        }

        danoNoMonstro(m, dano);
        printf("Dano da habilidade: %d\n", dano);
		
		return 1;
    } else if (jogador.classe == ARQUEIRO) {
    printf("\nDisparo preciso!\n");
	
	dado = rolardado(20);
    dano = jogador.ataque*2 - (m->defesa / 2);
	
    if (dano < 1) {
        dano = 1;
    }
	    printf("Resultado do dado: %d\n", dado);

    if (dado == 20) {
        dano *= 2;
        printf("CRITICO! Dano dobrado!\n");
    } else if (dado >= 17) {
        printf("Ataque certeiro! 50%% a mais de dano!!\n");
		dano = dano * 3/2;
    } else {
        printf("Ataque normal!\n");
    }

    danoNoMonstro(m, dano);

    printf("Dano da habilidade: %d\n", dano);
} else if (jogador.classe == MAGO) {
    printf("\nBola de fogo!\n");
	m->turnosQueimadura = 3;
	m->danoQueimadura = 5;
    dano = jogador.ataque + jogador.inteligencia - m->defesa;

    if (dano < 1) {
        dano = 1;
    }

    danoNoMonstro(m, dano);

    printf("Dano da habilidade: %d\n", dano);
	printf("O inimigo foi queimado!\n");
	printf("Ele recebera 5 de dano por 3 turnos.\n");
}
return 0;
}
int tentarFugir(Personagem jogador) {
    int dado = rolardado(20);
    int resultado = dado + jogador.agilidade / 4;

    printf("\nTentativa de fuga!\n");
    printf("Resultado: %d\n", resultado);

    if (resultado >= 15) {
        printf("Voce conseguiu fugir!\n");
        return 1;
    } else {
        printf("Voce nao conseguiu fugir!\n");
        return 0;
    }
}
void atacarJogador(Personagem *p, Monstro m, int defendendo) {
    int dado = rolardado(20);
    int ataque = m.ataque + dado / 4;
    int dano;

    printf("\n--- TURNO DO INIMIGO ---\n");
    printf("Dado: %d\n", dado);

    dano = ataque - p->defesa;

    if (dano < 1) {
        dano = 1;
    }
	if (defendendo){
		dano = dano/2;
	}
    p->vidaatual -= dano;
    if (p->vidaatual < 0) {
        p->vidaatual = 0;
    }

    printf("%s causou %d de dano!\n",m.nome, dano);
    printf("Vida de %s: %d/%d\n",
           p->nome, p->vidaatual, p->vidamax);
}
void exibirMenuCombate(Personagem jogador, Monstro monstro) {

    printf("\n");
    printf("============================================\n");
    printf("               COMBATE \n");
    printf("============================================\n");

    printf("\n");
    printf(" JOGADOR: %-15s\n", jogador.nome);
    printf(" Vida: %d/%d\n", jogador.vidaatual, jogador.vidamax);

    printf("--------------------------------------------\n");

    printf(" INIMIGO: %-15s\n", monstro.nome);
    printf(" Vida: %d/%d\n", monstro.vidaatual, monstro.vidamax);

    printf("============================================\n");
    printf("               SUAS ACOES\n");
    printf("============================================\n");

    printf(" [1] Atacar\n");
    printf(" [2] Defender\n");
    printf(" [3] Habilidade Especial\n");
    printf(" [4] Fugir\n");
	printf(" [5] Usar pocao\n");

    printf("============================================\n");
    printf(" Escolha sua acao: ");
}

void ganharXP(Personagem *p, int xp) {
    p->xp += xp;

    printf("\nVoce recebeu %d XP!\n", xp);
	 if (p->xp >= 100) {
        p->nivel++;
        p->xp -= 100;
		p->usosHabilidade = p->usosMaximosHabilidade;
        p->vidamax += 20;
        p->vidaatual = p->vidamax;
        p->ataque += 3;
        p->defesa += 1;

        printf("\n===== SUBIU DE NIVEL! =====\n");
        printf("Nivel: %d\n", p->nivel);
        printf("Vida maxima: %d\n", p->vidamax);
        printf("Ataque: %d\n", p->ataque);
        printf("Defesa: %d\n", p->defesa);
		printf("Habilidades especiais restauradas!\n");
    }
    printf("XP atual: %d\n", p->xp);

    }


void combate(Personagem *p, Monstro *m, int ehChefe) {
    int fugiu = 0;
	if (ehChefe) {
		printf("\n");
		printf("========================================\n");
		printf("             CHEFE FINAL\n");
		printf("========================================\n");
		printf("         %s apareceu!\n", m->nome);
		printf("%s\n", m->descricao);
		printf("----------------------------------------\n");
		printf("Vida: %d\n", m->vidamax);
		printf("Ataque: %d\n", m->ataque);
		printf("Defesa: %d\n", m->defesa);
		printf("========================================\n");
	}
    while (p->vidaatual > 0 && m->vidaatual > 0 && !fugiu) {
        int acao;
        int defendendo = 0;
        int inimigoPerdeuVez = 0;

        exibirMenuCombate(*p, *m);
        if (scanf("%d", &acao) != 1) {
			printf("\nEntrada invalida! Digite apenas numeros.\n");

			while (getchar() != '\n');

			continue;
		}

        switch (acao) {
            case ACAO_ATACAR:
                atacarMonstro(m, *p);
                break;

            case ACAO_DEFENDER:
                printf("Voce esta em posicao de defesa!\n");
                defendendo = 1;
                break;

            case ACAO_HABILIDADE:
                if (p->usosHabilidade > 0) {
                    inimigoPerdeuVez = habilidadeEspecial(m, *p);
                    p->usosHabilidade--;

                    printf("\nUsos restantes: %d/%d\n",
                           p->usosHabilidade,
                           p->usosMaximosHabilidade);
                } else {
                    printf("\nVoce nao possui usos de habilidade disponiveis!\n");
                    continue;
                }
                break;

            case ACAO_FUGIR:
				if (ehChefe == 1) {
					printf("\nVoce nao pode fugir de uma batalha contra um chefe!\n");
					continue;
				}

				fugiu = tentarFugir(*p);
				break;

            case ACAO_POCAO:
                if (usarPocao(p) == 0){
					continue;
				}
                break;

            default:
                printf("Opcao invalida!\n");
                continue;
        }

        if (m->vidaatual > 0 && !fugiu && !inimigoPerdeuVez) {

            if (m->turnosQueimadura > 0) {
                printf("\nO monstro sofre queimadura!\n");

                danoNoMonstro(m, m->danoQueimadura);
                m->turnosQueimadura--;

                printf("Dano da queimadura: %d\n", m->danoQueimadura);
                printf("Turnos restantes: %d\n", m->turnosQueimadura);
            }

            if (m->vidaatual > 0) {
                atacarJogador(p, *m, defendendo);
            }
        }
    }
    if (fugiu) {
        printf("\nVoce escapou da batalha!\n");
    } else if (p->vidaatual <= 0) {
        printf("\nVoce foi derrotado!\n");
    } else if (m->vidaatual <= 0) {
        printf("\nVoce derrotou o %s!\n", m->nome);
        ganharXP(p, m->xprecompensa);
    }
}
void exibirStatus(Personagem p, int fase) {
    printf("\n========== STATUS DO PERSONAGEM ==========\n");
    printf("Nome: %s\n", p.nome);
	printf("Classe: ");
	switch (p.classe) {
		case GUERREIRO:
			printf("Guerreiro\n");
			break;
		case ARQUEIRO:
			printf("Arqueiro\n");
			break;
		case MAGO:
			printf("Mago\n");
			break;
		default:
			printf("Desconhecida\n");
			break;
	}
    printf("Vida: %d/%d\n", p.vidaatual, p.vidamax);
    printf("Ataque: %d\n", p.ataque);
    printf("Defesa: %d\n", p.defesa);
    printf("Agilidade: %d\n", p.agilidade);
    printf("Inteligencia: %d\n", p.inteligencia);
    printf("Nivel: %d\n", p.nivel);
    printf("XP: %d\n", p.xp);
    printf("Ouro: %d\n", p.ouro);
	printf("Fase atual: ");
	switch (fase) {
		case 1:
			printf("Floresta Sombria\n");
			break;
		case 2:
			printf("Masmorra\n");
			break;
		case 3:
			printf("Reino Demoniaco\n");
			break;
		default:
			printf("Desconhecida\n");
			break;
	}
    printf("==========================================\n");
}
void exibirResumoFinal(Personagem p, int fase) {
    printf("\n");
    printf("================================\n");
    printf("       RESUMO DA AVENTURA\n");
    printf("================================\n");

    printf("Personagem: %s\n", p.nome);
    printf("Nivel: %d\n", p.nivel);
    printf("Experiencia: %d XP\n", p.xp);
    printf("Vida: %d/%d\n", p.vidaatual, p.vidamax);
    printf("Ouro: %d\n", p.ouro);
    printf("Fase alcancada: %d\n", fase);

    if (p.vidaatual > 0) {
        printf("\nResultado: VITORIA!\n");
    } else {
        printf("\nResultado: DERROTA!\n");
    }

    printf("================================\n");
}

int main(void) {
	Tipocasa tabuleiroFacil[10];
	Tipocasa tabuleiroMedio[10];
	Tipocasa tabuleiroDificil[10];
	srand(time(NULL));
	tabuleiroFacil[0] = CASA_VAZIA;
	tabuleiroFacil[1] = CASA_COMBATE;
	tabuleiroFacil[2] = CASA_TESOURO;
	tabuleiroFacil[3] = CASA_VAZIA;
	tabuleiroFacil[4] = CASA_CURA;
	tabuleiroFacil[5] = CASA_COMBATE;
	tabuleiroFacil[6] = CASA_ARMADILHA;
	tabuleiroFacil[7] = CASA_LOJA;
	tabuleiroFacil[8] = CASA_MISSAO;
	tabuleiroFacil[9] = CASA_CHEFE;

	tabuleiroMedio[0] = CASA_VAZIA;
	tabuleiroMedio[1] = CASA_COMBATE;
	tabuleiroMedio[2] = CASA_CURA;
	tabuleiroMedio[3] = CASA_TESOURO;
	tabuleiroMedio[4] = CASA_COMBATE;
	tabuleiroMedio[5] = CASA_ARMADILHA;
	tabuleiroMedio[6] = CASA_LOJA;
	tabuleiroMedio[7] = CASA_COMBATE;
	tabuleiroMedio[8] = CASA_MISSAO;
	tabuleiroMedio[9] = CASA_CHEFE;

	tabuleiroDificil[0] = CASA_VAZIA;
	tabuleiroDificil[1] = CASA_COMBATE;
	tabuleiroDificil[2] = CASA_ARMADILHA;
	tabuleiroDificil[3] = CASA_LOJA;
	tabuleiroDificil[4] = CASA_COMBATE;
	tabuleiroDificil[5] = CASA_TESOURO;
	tabuleiroDificil[6] = CASA_CURA;
	tabuleiroDificil[7] = CASA_COMBATE;
	tabuleiroDificil[8] = CASA_MISSAO;
	tabuleiroDificil[9] = CASA_CHEFE;
	
	int faseatual = 1;
	int posicao = 0;
	int missaoConcluida = 0;
	int chefeDerrotado = 0;
	int jogoCompleto = 0;
	int totalFases = 3;
	Monstro goblin;
	strcpy(goblin.nome, "Goblin");
	goblin.vidamax = 40;
	goblin.vidaatual = goblin.vidamax;
	goblin.ataque = 8;
	goblin.defesa = 5;
	goblin.dificuldade = FACIL;
	goblin.xprecompensa = 30;
	goblin.nivel = 1;
	goblin.ourorecompensa = 10;
	goblin.turnosQueimadura = 0;
	goblin.danoQueimadura = 0;
	Monstro lobo;
	strcpy(lobo.nome, "Lobo Selvagem");
	lobo.vidamax = 50;
	lobo.vidaatual = lobo.vidamax;
	lobo.ataque = 12;
	lobo.defesa = 7;
	lobo.dificuldade = FACIL;
	lobo.xprecompensa = 35;
	lobo.nivel = 1;
	lobo.ourorecompensa = 15;
	lobo.turnosQueimadura = 0;
	lobo.danoQueimadura = 0;
	Monstro esqueleto;
	strcpy(esqueleto.nome, "Guerreiro Esqueleto");
	esqueleto.vidamax = 60;
	esqueleto.vidaatual = esqueleto.vidamax;
	esqueleto.ataque = 16;
	esqueleto.defesa = 10;
	esqueleto.dificuldade = FACIL;
	esqueleto.xprecompensa = 50;
	esqueleto.nivel = 2;
	esqueleto.ourorecompensa = 20;
	esqueleto.turnosQueimadura = 0;
	esqueleto.danoQueimadura = 0;
	Monstro chefeFacil;
	strcpy(chefeFacil.nome, "Ogro Rei");
	chefeFacil.vidamax = 100;
	chefeFacil.vidaatual = chefeFacil.vidamax;
	chefeFacil.ataque = 18;
	chefeFacil.defesa = 10;
	chefeFacil.dificuldade = FACIL;
	chefeFacil.xprecompensa = 100;
	chefeFacil.nivel = 3;
	chefeFacil.ourorecompensa = 50;
	chefeFacil.turnosQueimadura = 0;
	chefeFacil.danoQueimadura = 0;
	
	Monstro zumbi;
	strcpy(zumbi.nome, "Morto Vivo");
	zumbi.vidamax = 65;
	zumbi.vidaatual = zumbi.vidamax;
	zumbi.ataque = 16;
	zumbi.defesa = 10;
	zumbi.dificuldade = MEDIO;
	zumbi.xprecompensa = 50;
	zumbi.nivel = 5;
	zumbi.ourorecompensa = 30;
	zumbi.turnosQueimadura = 0;
	zumbi.danoQueimadura = 0;
	Monstro golem;
	strcpy(golem.nome, "Golem Guardiao");
	golem.vidamax = 120;
	golem.vidaatual = golem.vidamax;
	golem.ataque = 13;
	golem.defesa = 20;
	golem.dificuldade = MEDIO;
	golem.xprecompensa = 80;
	golem.nivel = 5;
	golem.ourorecompensa = 35;
	golem.turnosQueimadura = 0;
	golem.danoQueimadura = 0;
	Monstro aranha;
	strcpy(aranha.nome, "Aranha Gigante");
	aranha.vidamax = 70;
	aranha.vidaatual = aranha.vidamax;
	aranha.ataque = 18;
	aranha.defesa = 8;
	aranha.dificuldade = MEDIO;
	aranha.xprecompensa = 55;
	aranha.nivel = 3;
	aranha.ourorecompensa = 20;
	aranha.turnosQueimadura = 0;
	aranha.danoQueimadura = 0;
	Monstro chefeMedio;
	strcpy(chefeMedio.nome, "Lich ");
	chefeMedio.vidamax = 180;
	chefeMedio.vidaatual = chefeMedio.vidamax;
	chefeMedio.ataque = 25;
	chefeMedio.defesa = 15;
	chefeMedio.dificuldade = MEDIO;
	chefeMedio.xprecompensa = 200;
	chefeMedio.nivel = 6;
	chefeMedio.ourorecompensa = 100;
	chefeMedio.turnosQueimadura = 0;
	chefeMedio.danoQueimadura = 0;
	
	Monstro demonio;
	strcpy(demonio.nome, "Demonio");
	strcpy(demonio.descricao, "Uma criatura das profundezas");
	demonio.vidamax = 130;
	demonio.vidaatual = demonio.vidamax;
	demonio.ataque = 28;
	demonio.defesa = 15;
	demonio.nivel = 8;
	demonio.xprecompensa = 100;
	demonio.dificuldade = DIFICIL;
	demonio.ourorecompensa = 40;
	demonio.turnosQueimadura = 0;
	demonio.danoQueimadura = 0;
	Monstro cavaleiro;
	strcpy(cavaleiro.nome, "Cavaleiro Amaldicoado");
	strcpy(cavaleiro.descricao, "Um guerreiro corrompido pelas trevas");
	cavaleiro.vidamax = 160;
	cavaleiro.vidaatual = cavaleiro.vidamax;
	cavaleiro.ataque = 30;
	cavaleiro.defesa = 22;
	cavaleiro.nivel = 9;
	cavaleiro.xprecompensa = 120;
	cavaleiro.dificuldade = DIFICIL;
	cavaleiro.ourorecompensa = 50;
	cavaleiro.turnosQueimadura = 0;
	cavaleiro.danoQueimadura = 0;
	Monstro caoInfernal;
	strcpy(caoInfernal.nome, "Cao Infernal");
	strcpy(caoInfernal.descricao, "Uma fera demoníaca das profundezas");
	caoInfernal.vidamax = 120;
	caoInfernal.vidaatual = caoInfernal.vidamax;
	caoInfernal.ataque = 32;
	caoInfernal.defesa = 12;
	caoInfernal.nivel = 8;
	caoInfernal.xprecompensa = 110;
	caoInfernal.dificuldade = DIFICIL;
	caoInfernal.ourorecompensa = 45;
	caoInfernal.turnosQueimadura = 0;
	caoInfernal.danoQueimadura = 0;
	Monstro chefeDificil;
	strcpy(chefeDificil.nome, "Rei Demoniaco");
	chefeDificil.vidamax = 300;
	chefeDificil.vidaatual = chefeDificil.vidamax;
	chefeDificil.ataque = 35;
	chefeDificil.defesa = 20;
	chefeDificil.dificuldade = DIFICIL;
	chefeDificil.xprecompensa = 300;
	chefeDificil.nivel = 10;
	chefeDificil.ourorecompensa = 200;
	chefeDificil.turnosQueimadura = 0;
	chefeDificil.danoQueimadura = 0;
	Monstro MontrosDifFacil[3] = {goblin, lobo, esqueleto};
	Monstro MonstrosDifMedio[3] = {zumbi, golem, aranha};
	Monstro MonstrosDifDificil[3] = {demonio, cavaleiro, caoInfernal};
	Monstro *chefeAtual = &chefeFacil;
	int sorteio = rolardado(3) - 1;
	Item inventario[5]= {0};
	exibirHistoria();
	while (getchar() != '\n');
		printf("\nPressione ENTER para continuar...");
		getchar();
	while (resp == 0) {
		printf("Escolha uma classe:  \n");
		printf("1 - GUERREIRO\n");
		printf("2 - ARQUEIRO\n");
		printf("3 - MAGO\n");		
		printf("Resposta:");
		if (scanf("%d", &resp) != 1) {
			printf("\nEntrada invalida! Digite apenas numeros.\n");

			while (getchar() != '\n');

			continue;
		}
		if (resp == 1) {
			jogador.classe = GUERREIRO;
		} else if (resp == 2) {
			jogador.classe = ARQUEIRO;
		} else if (resp == 3){
			jogador.classe = MAGO;
		} else {
			resp = 0;
		}
	}
	if (jogador.classe == GUERREIRO) {
		bonusvida = 20;
		bonusataque = 2;
		bonusdefesa = 5;
		bonusagilidade = 3;
		bonusinteligencia = 0;
		strcpy(inventario[0].nome, "Espada");
		inventario[0].tipo = ARMA;
		inventario[0].bonusataque = 5;
		strcpy(inventario[1].nome, "Escudo");
		inventario[1].tipo = ARMADURA;
		inventario[1].bonusdefesa = 5;
	} else if (jogador.classe == ARQUEIRO) {
		bonusvida = 10;
		bonusataque = 4;
		bonusdefesa = 2;
		bonusagilidade = 6;
		bonusinteligencia = 3;
		strcpy(inventario[0].nome, "Arco");
		inventario[0].tipo = ARMA;
		inventario[0].bonusataque = 4;
		strcpy(inventario[1].nome, "Armadura Leve");
		inventario[1].tipo = ARMADURA;
		inventario[1].bonusdefesa = 3;
	} else if (jogador.classe == MAGO){
		bonusvida = 0;
		bonusataque = 10;
		bonusdefesa = 0;
		bonusagilidade = 3;
		bonusinteligencia = 6;
		strcpy(inventario[0].nome, "Cajado");
		inventario[0].tipo = ARMA;
		inventario[0].bonusataque = 6;
		strcpy(inventario[1].nome, "Manto Arcano");
		inventario[1].tipo = ARMADURA;
		inventario[1].bonusdefesa = 2;
	}
	
	strcpy(inventario[2].nome, "Pocao de cura");
	inventario[2].tipo = POCAO;
	inventario[2].bonusvida = 20;
	jogador.vidamax = calcularatributo(vidabase, bonusvida);
	jogador.vidaatual = jogador.vidamax;
	jogador.ataque = calcularatributo(ataquebase, bonusataque);
	jogador.ataque = calcularatributo(jogador.ataque, inventario[0].bonusataque);
	jogador.defesa = calcularatributo(defesabase, bonusdefesa);
	jogador.agilidade = calcularatributo(agilidadebase, bonusagilidade);
	jogador.inteligencia = calcularatributo(inteligenciabase, bonusinteligencia);
	jogador.pocaoPequena = 0;
	jogador.pocaoGrande = 0;
	jogador.ouro = 50;
	jogador.xp = 0;
	jogador.nivel = 1;
	jogador.usosMaximosHabilidade = 3;
	jogador.usosHabilidade = jogador.usosMaximosHabilidade;
	jogador.defesa = calcularatributo( jogador.defesa, inventario[1].bonusdefesa);
	char nomeClasse[15];

	if (jogador.classe == GUERREIRO) {
		strcpy(nomeClasse, "Guerreiro");
	} else if (jogador.classe == ARQUEIRO) {
		strcpy(nomeClasse, "Arqueiro");
	} else {
		strcpy(nomeClasse, "Mago");
	}
	printf("Digite o nome do personagem: ");
	scanf("%29s", jogador.nome);
	printf("\n--- JOGADOR ---\n");
	printf("%-15s | %-15s | %-7s | %-7s | %-7s | %-7s| %-7s\n",
		   "Nome","Classe", "Vida", "Ataque", "Defesa", "Agilidade", "Inteligencia");
	printf("----------------|-----------------|---------|---------|---------|----------|--------\n");
	printf("%-15s |%-15s  | %d/%-3d | %-7d | %-7d | %-8d | %-7d \n",
       jogador.nome,
	   nomeClasse,
       jogador.vidaatual,
       jogador.vidamax,
       jogador.ataque,
       jogador.defesa,
	   jogador.agilidade,
	   jogador.inteligencia);
	   while (getchar() != '\n');
			printf("\nPressione ENTER para continuar...");
			getchar();
	Tipocasa *tabuleiroAtual;
	Monstro *monstrosAtuais;
	int quantidadeMonstros = 3;
	int opcao;
	while (jogador.vidaatual > 0 && jogoCompleto == 0) {
		switch (faseatual) {
			case 1:
				tabuleiroAtual = tabuleiroFacil;
				monstrosAtuais = MontrosDifFacil;
				chefeAtual = &chefeFacil;
				break;

			case 2:
				tabuleiroAtual = tabuleiroMedio;
				monstrosAtuais = MonstrosDifMedio;
				chefeAtual = &chefeMedio;
				break;

			case 3:
				tabuleiroAtual = tabuleiroDificil;
				monstrosAtuais = MonstrosDifDificil;
				chefeAtual = &chefeDificil;
				break;
		}
		exibirTabuleiro(posicao, 10, tabuleiroAtual);
		printf("\n\nLegenda:\n");
		printf("[P] Jogador | [V] Vazia | [C] Combate\n");
		printf("[T] Tesouro | [H] Cura | [A] Armadilha\n");
		printf("[L] Loja | [M] Missao\n");
		printf("\n========== AVENTURA ==========\n");
		printf("Posicao atual: Casa %d\n", posicao + 1);
		printf("1 - Rolar dado e movimentar\n");
		printf("2 - Ver inventario\n");
		printf("3 - Mostrar status\n");
		printf("Escolha: ");
		if (scanf("%d", &opcao) != 1) {
			printf("\nEntrada invalida! Digite apenas numeros.\n");

			while (getchar() != '\n');

			continue;
		}
		switch (opcao) {
			case 1:
				moverJogador(&posicao, 10, missaoConcluida);
				verificarCasa(tabuleiroAtual[posicao], &jogador, monstrosAtuais, quantidadeMonstros, &missaoConcluida, &chefeDerrotado, chefeAtual, faseatual);
				if (chefeDerrotado == 1) {
					printf("\n");
					printf("========================================\n");
					printf("          FASE CONCLUIDA!\n");
					printf("========================================\n");
					printf("Parabens, %s!\n", jogador.nome);
					printf("Voce derrotou o chefe!\n");
					printf("Preparando a proxima fase...\n");
					printf("========================================\n");
					while (getchar() != '\n');
						printf("\nPressione ENTER para continuar...");
						getchar();
					if (faseatual < totalFases) {
						faseatual++;
						posicao = 0;
						missaoConcluida = 0;
						chefeDerrotado = 0;

						printf("\n================================\n");
						printf("       PROXIMA FASE!\n");
						printf("       FASE %d\n", faseatual);
						printf("================================\n");
						while (getchar() != '\n');
							printf("\nPressione ENTER para continuar...");
							getchar();
						if (faseatual == 2) {
							chefeAtual = &chefeMedio;
						}
						else if (faseatual == 3) {
							chefeAtual = &chefeDificil;
						}
					}
					else {
						jogoCompleto = 1;
					}
				}
				break;
			case 2:
				exibirInventario(jogador, inventario);
				while (getchar() != '\n');
						printf("\nPressione ENTER para continuar...");
						getchar();
				break;
				
			case 3:
				exibirStatus(jogador, faseatual);
				while (getchar() != '\n');
						printf("\nPressione ENTER para continuar...");
						getchar();
				break;
			default:
				printf("Opcao Invalida!\n");
				while (getchar() != '\n');
						printf("\nPressione ENTER para continuar...");
						getchar();
		}
	}
	if (jogoCompleto == 1) {
		printf("\n================================\n");
		printf("       PARABENS!\n");
		printf("   VOCE COMPLETOU O RPG!\n");
		printf("================================\n");
	}
	else {
		printf("\nGAME OVER! Voce foi derrotado.\n");
	}
	exibirResumoFinal(jogador, faseatual);
	return 0;
}