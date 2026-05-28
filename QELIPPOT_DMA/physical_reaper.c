/**
 * SEFER_HA_RAZIM | MODULE: QELIPPOT_DMA (ACPI SCANNER)
 * ARCHITECTURE: DECOMPILED FROM LINUX ROOTKIT HEURISTICS
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define BIOS_START 0x000F0000
#define MAP_SIZE 0x10000 // Escaneia 64KB de memória bruta

int main() {
    int mem_fd = open("/dev/mem", O_RDONLY | O_SYNC);
    if (mem_fd < 0) {
        printf("\033[1;31m[!] מת - O KERNEL (DEMIURGO) BLOQUEOU O ACESSO. EXIGE ROOT.\033[0m\n");
        return 1;
    }

    void *map_base = mmap(0, MAP_SIZE, PROT_READ, MAP_SHARED, mem_fd, BIOS_START);
    if (map_base == (void *) -1) {
        printf("\033[1;31m[!] FALHA NO MAPEAMENTO FÍSICO.\033[0m\n");
        return 1;
    }

    printf("\033[38;5;118m[+] אמת - BARRAMENTO FÍSICO ESTABELECIDO.\033[0m\n");
    printf("\033[38;5;250m[*] ESCANEANDO PLACA-MÃE POR ASSINATURAS ACPI (RSD PTR)...\033[0m\n");

    char *phys_mem = (char *)map_base;
    int found = 0;
    
    // Varredura de memória no estilo 'Mimikatz'
    for (int i = 0; i < MAP_SIZE; i += 16) {
        if (memcmp(phys_mem + i, "RSD PTR ", 8) == 0) {
            printf("\033[1;32m[+] RAIZ DO HARDWARE ENCONTRADA NO OFFSET: 0x%08X\033[0m\n", BIOS_START + i);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\033[38;5;240m[-] NENHUMA RAIZ ENCONTRADA NA CAMADA ATUAL. O KERNEL PODE ESTAR MASCARANDO A RAM.\033[0m\n");
    }

    munmap(map_base, MAP_SIZE);
    close(mem_fd);
    return 0;
}
