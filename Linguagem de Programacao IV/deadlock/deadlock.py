import os

recursos = {}
processos = {}
fila_de_processamento = []

def limpar_tela():
    os.system('cls' if os.name == 'nt' else 'clear')

def inicializar_sistema():
    limpar_tela()
    print("--- Configuração Inicial do Sistema ---")
    
    while True:
        try:
            num_recursos = int(input("Informe a quantidade de RECURSOS: "))
            if num_recursos > 0:
                break
            else:
                print("Por favor, insira um número positivo.")
        except ValueError:
            print("Entrada inválida. Por favor, insira um número inteiro.")

    while True:
        try:
            num_processos = int(input("Informe a quantidade de PROCESSOS: "))
            if num_processos > 0:
                break
            else:
                print("Por favor, insira um número positivo.")
        except ValueError:
            print("Entrada inválida. Por favor, insira um número inteiro.")

    for i in range(1, num_recursos + 1):
        recursos[f'R{i}'] = {'alocado': None, 'fila_de_espera': []}
        
    for i in range(1, num_processos + 1):
        processos[f'P{i}'] = {'estado': 'PRONTO'}
        fila_de_processamento.append(f'P{i}')

    print("\nSistema inicializado com sucesso!")
    input("Pressione Enter para continuar...")

def requisicao_recurso():
    limpar_tela()
    print("--- Requisição de Recurso ---")
    print("Processos disponíveis:", ", ".join(p for p, s in processos.items() if s['estado'] != 'FINALIZADO'))
    id_processo = input("Qual processo está solicitando? (ex: P1): ").upper()
    
    if id_processo not in processos:
        print(f"Erro: Processo {id_processo} não existe.")
        input("Pressione Enter para continuar...")
        return

    if processos[id_processo]['estado'] == 'FINALIZADO':
        print(f"\nErro: O processo {id_processo} já foi finalizado e não pode solicitar recursos.")
        input("Pressione Enter para continuar...")
        return

    print("\nRecursos disponíveis:", ", ".join(recursos.keys()))
    id_recurso = input(f"Qual recurso o processo {id_processo} solicita? (ex: R1): ").upper()

    if id_recurso not in recursos:
        print(f"Erro: Recurso {id_recurso} não existe.")
        input("Pressione Enter para continuar...")
        return

    recurso = recursos[id_recurso]
    
    if recurso['alocado'] is None:
        recurso['alocado'] = id_processo
        processos[id_processo]['estado'] = 'APTO'
        print(f"\nSucesso: Recurso {id_recurso} alocado ao processo {id_processo}.")
    else:
        if id_processo not in recurso['fila_de_espera']:
            recurso['fila_de_espera'].append(id_processo)
            processos[id_processo]['estado'] = 'ESPERANDO'
            print(f"\nRecurso {id_recurso} está ocupado. Processo {id_processo} adicionado à fila de espera.")
        else:
            print(f"\nO processo {id_processo} já está na fila de espera do recurso {id_recurso}.")

    input("Pressione Enter para continuar...")

def liberacao_recurso():
    limpar_tela()
    print("--- Liberação de Recurso ---")
    print("Recursos disponíveis:", ", ".join(recursos.keys()))
    id_recurso = input("Qual recurso será liberado? (ex: R1): ").upper()

    if id_recurso not in recursos:
        print(f"Erro: Recurso {id_recurso} não existe.")
        input("Pressione Enter para continuar...")
        return
        
    recurso = recursos[id_recurso]
    processo_alocado = recurso['alocado']

    if processo_alocado is None:
        print(f"Erro: O recurso {id_recurso} já está livre.")
    else:
        recurso['alocado'] = None
        print(f"Sucesso: Processo {processo_alocado} liberou o recurso {id_recurso}.")
        
        if processos[processo_alocado]['estado'] != 'FINALIZADO':
             processos[processo_alocado]['estado'] = 'PRONTO'
        
        if recurso['fila_de_espera']:
            proximo_processo = recurso['fila_de_espera'].pop(0)
            recurso['alocado'] = proximo_processo
            processos[proximo_processo]['estado'] = 'APTO'
            print(f"Recurso {id_recurso} foi alocado para o próximo da fila: {proximo_processo}.")

    input("Pressione Enter para continuar...")

def mostrar_situacao():
    limpar_tela()
    print("--- Situação Atual do Sistema ---")

    print("\n--- Recursos ---")
    print(f"{'Recurso':<10} | {'Alocado para':<15} | {'Fila de Espera (Solicitações)'}")
    print("-" * 55)
    for id_recurso, info in recursos.items():
        alocado = info['alocado'] if info['alocado'] else '---'
        fila = ", ".join(info['fila_de_espera']) if info['fila_de_espera'] else '---'
        print(f"{id_recurso:<10} | {alocado:<15} | {fila}")
    
    print("\n--- Processos ---")
    print(f"{'Processo':<10} | {'Estado'}")
    print("-" * 25)
    for id_processo, info in processos.items():
        print(f"{id_processo:<10} | {info['estado']}")
        
    print(f"\nFila de Processamento: {fila_de_processamento}")
    print("\n")
    input("Pressione Enter para voltar ao menu...")

def processar():
    limpar_tela()
    print("--- Simulação de Processamento ---")
    
    if not fila_de_processamento:
        print("Não há mais processos na fila de processamento para executar.")
        input("Pressione Enter para continuar...")
        return

    processo_a_executar = None
    
    for id_processo in fila_de_processamento:
        if processos[id_processo]['estado'] != 'ESPERANDO':
            possui_recurso = False
            for recurso in recursos.values():
                if recurso['alocado'] == id_processo:
                    possui_recurso = True
                    break
            
            if possui_recurso:
                processo_a_executar = id_processo
                break 

    if processo_a_executar is None:
        print("Nenhum processo está apto para execução no momento.")
        print("(Causas: ou estão em 'ESPERA' ou não possuem recursos alocados).")
        input("Pressione Enter para continuar...")
        return
    
    print(f"Processo {processo_a_executar} selecionado para execução (o primeiro apto na fila).")
    print(f"Finalizando e liberando seus recursos...")
    
    processos[processo_a_executar]['estado'] = 'FINALIZADO'
    fila_de_processamento.remove(processo_a_executar)

    for id_recurso, info in recursos.items():
        if info['alocado'] == processo_a_executar:
            info['alocado'] = None
            print(f"-> Processo {processo_a_executar} liberou o Recurso {id_recurso}.")
            
            if info['fila_de_espera']:
                proximo_processo = info['fila_de_espera'].pop(0)
                info['alocado'] = proximo_processo
                processos[proximo_processo]['estado'] = 'APTO'
                print(f"--> Recurso {id_recurso} alocado para o próximo da fila: {proximo_processo}.")

    print(f"\nProcesso {processo_a_executar} concluído e removido permanentemente da fila de execução.")
    input("Pressione Enter para continuar...")


def menu():
    while True:
        limpar_tela()
        print("--- Simulador de Deadlock ---")
        print("\nSelecione uma opção:")
        print("1. Requisição de Recurso")
        print("2. Liberação de Recurso")
        print("3. Mostrar Situação Atual")
        print("4. Processar")
        print("5. Sair")
        
        escolha = input("\nOpção: ")
        
        if escolha == '1':
            requisicao_recurso()
        elif escolha == '2':
            liberacao_recurso()
        elif escolha == '3':
            mostrar_situacao()
        elif escolha == '4':
            processar()
        elif escolha == '5':
            print("Saindo do programa...")
            break
        else:
            print("Opção inválida. Tente novamente.")
            input("Pressione Enter para continuar...")

inicializar_sistema()
menu()