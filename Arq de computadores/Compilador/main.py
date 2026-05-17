INSTRUCOES = {
    "ADD": "000000", "SUB": "000000", "MUL": "000000", "DIV": "000000", "LW": "100011",
    "SW": "101011", "J": "000010", "BEQ": "000100",  "BNE": "000101", "BLE": "000110",
    "BGE": "000111", "SLT": "000001",  "SGT": "000010"
}

REGISTRADORES = {
    "$zero": "00000", "$v0": "00010", "$v1": "00011", "$t0": "01000", "$t1": "01001", "$t2": "01010",
    "$t3": "01011", "$t4": "01100", "$t5": "01101", "$t6": "01110", "$t7": "01111", "$s0": "10000",
    "$s1": "10001", "$s2": "10010", "$s3": "10011", "$s4": "10100", "$s5": "10101", "$s6": "10110",
    "$s7": "10111", "$t8": "11000", "$t9": "11001"
}


class Simulador:
    def __init__(self):
        self.registradores = {reg: 0 for reg in REGISTRADORES.keys()}
        self.memoria = {}
        self.pc = 0
        self.LO = 0

    def converte_instrucao_para_binario(self, instrucao):
        partes = [p.replace(",", "").strip() for p in instrucao.split()]
        if not partes or partes[0] not in INSTRUCOES:
            raise ValueError(
                f"Instrução inválida ou não reconhecida: {instrucao}")
        opcode = partes[0]
        if opcode in ("ADD", "SUB", "MUL", "DIV"):
            return self.formato_tipo_r(partes)
        elif opcode in ("LW", "SW"):
            return self.formato_tipo_i(partes)
        elif opcode == "J":
            return self.formato_tipo_j(partes)
        elif opcode in ("BEQ", "BNE", "BLE", "BGE"):
            return self.formato_tipo_e(partes)
        elif opcode in ("SLT", "SGT"):
            return self.formato_tipo_compara(partes)
        else:
            raise ValueError(f"Instrucao {opcode} nao suportada!")

    def formato_tipo_r(self, partes):
        if len(partes) != 4:
            raise ValueError(f"Instrução R-type invalida: {' '.join(partes)}")
        opcode = INSTRUCOES[partes[0]]
        def obter_valor(operando):
            if operando in REGISTRADORES:
                return REGISTRADORES.get(operando)
            return format(int(operando), '05b')
        rs = obter_valor(partes[2])
        rt = obter_valor(partes[3])
        rd = obter_valor(partes[1])
        shamt = "00000"
        if partes[0] == "ADD":
            funct = "100000"
        elif partes[0] == "SUB":
            funct = "100010"
        elif partes[0] == "MUL":
            funct = "011000"
        elif partes[0] == "DIV":
            funct = "011010"
        return f"{opcode}-{rs}-{rt}-{rd}-{shamt}-{funct}"


    def formato_tipo_j(self, partes):
        if len(partes) != 2:
            raise ValueError(f"Instrução J-type inválida: {' '.join(partes)}")
        opcode = INSTRUCOES[partes[0]]
        endereco = format(int(partes[1]), '026b')
        return f"{opcode}-{endereco}"


    def formato_tipo_e(self, partes):
        if len(partes) != 4:
            raise ValueError(f"Instrução E-type inválida: {' '.join(partes)}")
        opcode = INSTRUCOES[partes[0]]
        def obter_valor(operando):
            if operando in REGISTRADORES:
                return REGISTRADORES.get(operando)
            return int(operando)
        endereco = format(obter_valor(partes[3]), '016b')
        rs = obter_valor(partes[1])
        rt = obter_valor(partes[2])
        return f"{opcode}-{rs}-{rt}-{endereco}"


    def formato_tipo_compara(self, partes):
        if len(partes) != 4:
            raise ValueError(f"Instrução E-type inválida: {' '.join(partes)}")
        opcode = INSTRUCOES[partes[0]]
        def obter_valor(operando):
            if operando in REGISTRADORES:
                return REGISTRADORES.get(operando)
            return int(operando)
        rs = obter_valor(partes[2])
        rt = obter_valor(partes[3])
        rd = obter_valor(partes[1])
        return f"{opcode}-{rd}-{rs}-{rt}"


    def executar_e_simular(self, instrucoes):
        self.mapear_instrucoes_by_code(instrucoes)
        pc = min(self.memoria.keys())

        def obter_valor(operando):
            if operando in self.registradores:
                return self.registradores[operando]
            return int(operando)

        while pc in self.memoria:
            instrucao = self.memoria[pc]
            opcode = instrucao[0]
            print(f"PC: {pc}, Executando: {instrucao}")
            if opcode in ("ADD", "SUB", "MUL", "DIV", "SLT", "SGT"):
                self.processar_operacao_aritmetica(instrucao, obter_valor)
            elif opcode == "J":
                pc = obter_valor(instrucao[1])
                print(f"")
                continue
            elif opcode in ("BEQ", "BNE", "BLE", "BGE"):
                pc = self.processar_branch(instrucao, obter_valor, pc)
                print(f"")
                continue
            pc *= 2
            print(f"Registradores: {self.registradores}\n")

    def processar_operacao_aritmetica(self, instrucao, obter_valor):
        if instrucao[0] == "ADD":
            self.registradores[instrucao[1]] = obter_valor(instrucao[2]) + obter_valor(instrucao[3])
        elif instrucao[0] == "SUB":
            self.registradores[instrucao[1]] = obter_valor(instrucao[2]) - obter_valor(instrucao[3])
        elif instrucao[0] == "MUL":
            self.registradores[instrucao[1]] = obter_valor(instrucao[2]) * obter_valor(instrucao[3])
        elif instrucao[0] == "DIV":
            self.LO = obter_valor(instrucao[2]) // obter_valor(instrucao[3])
            self.registradores[instrucao[1]] = self.LO
        elif instrucao[0] == "SLT":
            self.registradores[instrucao[1]] = 1 if obter_valor(instrucao[2]) < obter_valor(instrucao[3]) else 0
        elif instrucao[0] == "SGT":
            self.registradores[instrucao[1]] = 1 if obter_valor(instrucao[2]) > obter_valor(instrucao[3]) else 0

    def processar_branch(self, instrucao, obter_valor, pc):
        condicoes = {
            "BEQ": obter_valor(instrucao[1]) == obter_valor(instrucao[2]),
            "BNE": obter_valor(instrucao[1]) != obter_valor(instrucao[2]),
            "BLE": obter_valor(instrucao[1]) <= obter_valor(instrucao[2]),
            "BGE": obter_valor(instrucao[1]) >= obter_valor(instrucao[2]),
        }
        return obter_valor(instrucao[3]) if condicoes[instrucao[0]] else pc * 2


            
    def mapear_instrucoes_by_code(self, instrucoes):
        i = 1
        for instrucao in instrucoes:
            self.memoria[i] = [p.replace(",", "").strip()
                               for p in instrucao.split()]
            i *= 2


def ler_arquivo_assembly(nome_arquivo):
    with open(nome_arquivo, 'r') as f:
        return [linha.strip() for linha in f.readlines()]


def main():
    instrucoes = ler_arquivo_assembly("C:/Users/willi/OneDrive/Documentos/Faculdade/Arq de computadores/Compilador/program.asm")
    simulador = Simulador()
    for instrucao in instrucoes:
        instrucao_binaria = simulador.converte_instrucao_para_binario(
            instrucao)
        print(f"Instrucao: {instrucao} => Binario: {instrucao_binaria}")
    print("\n--- Iniciando Simulacao ---\n")
    simulador.executar_e_simular(instrucoes)


main()
