import random

class Aptos:
    def __init__(self, pid, tcf, tef, tsf, cpu):
        self.pid = pid
        self.tcf = tcf
        self.tef = tef
        self.tsf = tsf
        self.cpu = cpu
    
    def __str__(self):
        return f"{self.pid}\t{self.tcf}\t{self.tef}\t{self.tsf}"

class Cpu:
    def __init__(self, pid, ti, tt, ttc, tl):
        self.pid = pid
        self.ti = ti
        self.tt = tt
        self.ttc = ttc
        self.tl = tl
    
    def __str__(self):
        return f"{self.pid}\t{self.ti}\t{self.tt}\t{self.ttc}\t{self.tl}"

class Processo:
    def __init__(self, pid, tb, time_admitted, cpu):
        self.pid = pid
        self.tb = tb
        self.time_admitted = time_admitted
        self.cpu = cpu
        self.flag = 0
        self.concluido = 0

def gera_processos(num_processos, first_time_zero, base_time, max_cpu):
    random.seed()
    tb_acumulado = 0
    processos = []

    for i in range(num_processos):
        pid = i + 1
        tb = 0 if (first_time_zero and i == 0) else random.randint(1, base_time)
        tb_acumulado += tb
        time_admitted = tb_acumulado
        cpu = random.randint(1, max_cpu)
        processos.append(Processo(pid, tb, time_admitted, cpu))

    return processos

def mostra_processos(processos):
    print("\nTabela de Referencia para os Processos")
    print("PID\tTB\tTIME_ADMITTED\tCPU")

    for processo in processos:
        print(f"{processo.pid}\t{processo.tb}\t{processo.time_admitted}\t\t{processo.cpu}")

def alocar_primeiro_processo(tabelaAptos, tabelaCpu, processo, quantum):
    voltaParaApto = 0
    processo.flag = 1
    if processo.cpu > quantum:
        tt = processo.time_admitted + quantum
        processo.cpu = processo.cpu - quantum
        ttc = random.randint(1,2)
        voltaParaApto = 1
    else:
        tt = processo.time_admitted + processo.cpu
        processo.cpu = 0   
        ttc = 0
        processo.concluido = 1     

    tl = tt + ttc

    apto = Aptos(processo.pid, processo.time_admitted, 0, processo.time_admitted, processo.cpu)
    cpu = Cpu(processo.pid, processo.time_admitted, tt, ttc, tl)
    tabelaAptos.append(apto)
    tabelaCpu.append(cpu)

    return {"voltaParaApto":voltaParaApto,"tempoSaida": tl}

def coloca_aptos_se_chegou(tempo_saida, processos, tabelaAptos):
    for p in processos:
        if p.time_admitted <= tempo_saida and p.flag != 1:
            tabelaAptos.append(Aptos(p.pid, p.time_admitted, 0, 0, p.cpu))
            p.flag = 1

def buscar_proximo_apto(tabela):
    for i in range(0, len(tabela)):
        if tabela[i].tsf == 0:
            return tabela[i]
    return False

def alocar_processo(processo, tabelaCpu, tempoInicio, quantum):
    voltaParaApto = 0
    processo.flag = 1
    if processo.cpu > quantum:
        tt = tempoInicio + quantum
        processo.cpu = processo.cpu - quantum
        ttc = random.randint(1,2)
        voltaParaApto = 1
    else:
        tt = tempoInicio + processo.cpu
        processo.cpu = 0   
        ttc = 0 
        processo.concluido = 1 

    tl = tt + ttc
    tabelaCpu.append(Cpu(processo.pid, tempoInicio, tt, ttc, tl))

    return {"voltaParaApto":voltaParaApto,"tempoSaida": tl, "id": processo.pid, "cpu": processo.cpu}
    
def buscar_ultimo_tempo_cpu(tabela):
    tam = len(tabela)
    return tabela[tam - 1].tl

def verifica_se_finalizou_todos_processos(processos, num_processos):
    cont_processos = 0
    for i in range(0, num_processos):
        if processos[i].concluido == 1:
            cont_processos += 1
    
    if cont_processos == num_processos: 
        return True
    return False

def buscar_novo_processo(processos):
    for i in range(0, len(processos)):
        if processos[i].flag == 0:
            return processos[i]

def mostrar_aptos_cpu(aptos, cpu):
    print("\nTabela de Aptos")
    print("PID\tTCF\tTEF\tTSF")
    for i in range(0, len(aptos)): print(aptos[i])    
    print("\nTabela de Cpu")
    print("PID\tTI\tTT\tTTC\tTL")
    for i in range(0, len(cpu)): print(cpu[i])    

def main():
    num_processos = int(input("Quantidade de Processos a Disparar: "))
    quantum = int(input("Valor para Fatia de Tempo (Quantum): "))
    first_time_zero = int(input("1o Tempo de Disparo em Zero (0 - Sim, 1 - Nao): "))
    base_time = int(input("Tempo Base de Disparo: "))
    max_cpu = int(input("Tempo Maximo de CPU: "))

    processos = gera_processos(num_processos, first_time_zero == 0, base_time, max_cpu)
    mostra_processos(processos)

    tabelaAptos = []
    tabelaCpu = []

    for i in range(0, 1000):
        if i == 0:
           primeiro_processo = alocar_primeiro_processo(tabelaAptos, tabelaCpu, processos[0], quantum)
           coloca_aptos_se_chegou(primeiro_processo["tempoSaida"], processos, tabelaAptos)
           if primeiro_processo["voltaParaApto"] == 1:
            tabelaAptos.append(Aptos(processos[0].pid, primeiro_processo["tempoSaida"], 0, 0, processos[0].cpu))

        proximo_apto = buscar_proximo_apto(tabelaAptos)
        if proximo_apto != False:
            tempo_inicio = buscar_ultimo_tempo_cpu(tabelaCpu)
            proximo_apto.tsf = tempo_inicio
            processo_alocado = alocar_processo(proximo_apto, tabelaCpu, tempo_inicio, quantum)
            coloca_aptos_se_chegou(processo_alocado["tempoSaida"], processos, tabelaAptos)
            if processo_alocado["voltaParaApto"] == 1:
                tabelaAptos.append(Aptos(processo_alocado["id"], processo_alocado["tempoSaida"], 0, 0, processo_alocado["cpu"]))
        else:
            novo_processo = buscar_novo_processo(processos)
            if novo_processo is None: break;
            processo_alocado = alocar_processo(novo_processo, tabelaCpu, tempo_inicio, quantum)
            coloca_aptos_se_chegou(processo_alocado["tempoSaida"], processos, tabelaAptos)
            if processo_alocado["voltaParaApto"] == 1:
                tabelaAptos.append(Aptos(processo_alocado["id"], processo_alocado["tempoSaida"], 0, 0, processo_alocado["cpu"]))

    mostrar_aptos_cpu(tabelaAptos, tabelaCpu)
    
if __name__ == "__main__":
    main()
