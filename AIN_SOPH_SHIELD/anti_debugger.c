/**
 * SEFER_HA_RAZIM | MODULE: AIN_SOPH_SHIELD
 * TACTIC: ANTI-DEBUGGING & ANTI-ANALYSIS
 * * "אין סוף - Ocultando a face do Golem dos olhos do Demiurgo."
 */

#include <stdio.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void check_tracer() {
    // 1. Tática PTRACE: Tenta 'rastrear' a si mesmo. 
    // Se falhar, significa que um Depurador (GDB, Radare2) já está conectado.
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0) {
        printf("\033[1;31m[!] מת - OLHO DO DEMIURGO DETECTADO (DEBUGGER ANEXADO).\033[0m\n");
        printf("\033[38;5;196m[*] INICIANDO AUTODESTRUIÇÃO LÓGICA...\033[0m\n");
        exit(1);
    }

    // 2. Tática PROCFS: Verifica se o processo pai é um rastreador conhecido
    FILE *fp = fopen("/proc/self/status", "r");
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "TracerPid:", 10) == 0) {
                int tracer_pid = atoi(&line[10]);
                if (tracer_pid != 0) {
                    printf("\033[1;31m[!] מת - TRACER PID DETECTADO: %d. ABORTANDO.\033[0m\n", tracer_pid);
                    exit(1);
                }
            }
        }
        fclose(fp);
    }

    printf("\033[38;5;118m[+] אמת - O VÉU ESTÁ INTACTO. NENHUM ANALISTA ENCONTRADO.\033[0m\n");
}

int main() {
    printf("\033[38;5;250m[*] LEVANTANDO A ARMADURA DE AIN-SOPH...\033[0m\n");
    check_tracer();
    
    printf("\033[38;5;129m[*] EXECUTANDO CARGA ÚTIL DE NÍVEL KETER...\033[0m\n");
    // O código principal entraria aqui
    
    return 0;
}
