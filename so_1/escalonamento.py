import random

class Processo:
    def __init__(self, pid, tb, time_admitted, cpu):
        self.pid = pid
        self.tb = tb
        self.time_admitted = time_admitted
        self.cpu = cpu
        self.tl = cpu  

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

class FilaAptos:
    def __init__(self):
        self.processos = []

    def adicionar_processo(self, processo):
        self.processos.append(processo)

    def proximo_processo(self):
        if self.processos:
            return self.processos.pop(0)
        else:
            return None

    def esta_vazia(self):
        return len(self.processos) == 0

    def __str__(self):
        header = "Fila de Aptos:"
        processos_str = "\n".join([f"PID: {processo.pid}, TB: {processo.tb}, TIME_ADMITTED: {processo.time_admitted}, CPU: {processo.cpu}" for processo in self.processos])
        return f"{header}\n{processos_str}"


class FilaCPU:
    def __init__(self):
        self.processo_atual = None

    def adicionar_processo(self, processo):
        self.processo_atual = processo

    def remover_processo(self):
        processo = self.processo_atual
        self.processo_atual = None
        return processo

    def esta_ocupada(self):
        return self.processo_atual is not None

    def __str__(self):
        if self.processo_atual:
            return f"Fila da CPU: PID: {self.processo_atual.pid}, TIME_ADMITTED: {self.processo_atual.time_admitted}, CPU: {self.processo_atual.cpu}"
        else:
            return "Fila da CPU vazia"


def main():
    num_processos = int(input("Quantidade de Processos a Disparar: "))
    quantum = int(input("Valor para Fatia de Tempo (Quantum): "))
    first_time_zero = int(input("1o Tempo de Disparo em Zero (0 - Sim, 1 - Nao): "))
    base_time = int(input("Tempo Base de Disparo: "))
    max_cpu = int(input("Tempo Maximo de CPU: "))

    processos = gera_processos(num_processos, first_time_zero == 0, base_time, max_cpu)
    fila_aptos = FilaAptos()
    fila_cpu = FilaCPU()
    tabelaCPU = []

    for processo in processos:
        fila_aptos.adicionar_processo(processo)

    while not fila_aptos.esta_vazia() or fila_cpu.esta_ocupada():
        print(f"{fila_aptos}\n")
        
        if fila_cpu.esta_ocupada():
            processo_atual = fila_cpu.remover_processo()
            if processo_atual.cpu > quantum:
                processo_atual.cpu -= quantum

                fila_aptos.adicionar_processo(processo_atual)
            else:
                print(f"Processo {processo_atual.pid} foi concluído.")

        if not fila_aptos.esta_vazia() and not fila_cpu.esta_ocupada():
            processo_proximo = fila_aptos.proximo_processo()
            fila_cpu.adicionar_processo(processo_proximo)
            print(f"Processo {processo_proximo.pid} está na CPU.")

        tabelaCPU.append(str(fila_cpu))

    print("\nTabela de Resultados da Fila de CPU:")
    print("Estado da CPU")
    for idx, estado_cpu in enumerate(tabelaCPU):
        print(f"{estado_cpu}")

if __name__ == "__main__":
    main()