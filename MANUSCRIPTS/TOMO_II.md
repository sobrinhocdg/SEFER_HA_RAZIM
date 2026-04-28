
📖 TOMO II: EVASÃO FANTASMA
[ A Anatomia do memfd_create e a Morte do Disco Rígido ]

O disco rígido (SSD/HDD) é um cemitério de evidências. Analistas de SOC, Antivírus e sistemas de EDR baseiam 90% de suas heurísticas em "File Signatures" (Assinaturas de Arquivos). Se o seu código toca o disco, ele deixa um cadáver digital que pode ser periciado.

A verdadeira elite não escreve no disco. Ela forja na mente efêmera da máquina: a Memória Volátil.

A Syscall do Vazio (memfd_create)
Introduzida no Kernel Linux 3.17, a syscall memfd_create permite a criação de um arquivo anônimo. Este arquivo se comporta como um arquivo regular, mas vive exclusivamente na RAM (normalmente suportado pelo tmpfs). Ele não possui um caminho de diretório (/usr/bin/...). Ele existe apenas como um número de Descritor de Arquivo (File Descriptor).

C
// Invocação do Fantasma
int fd = memfd_create("nome_disfarce", MFD_CLOEXEC);
write(fd, payload_malicioso, tamanho);
O Golpe de Mestre (Execução via procfs)
Como você executa um arquivo que não tem caminho no disco? Você usa a reflexão do próprio sistema contra ele. O diretório virtual /proc/self/fd/ lista os arquivos que o processo atual está segurando.

Nós ordenamos que o Kernel execute o artefato apontando para a própria mente do programa:
execl("/bin/bash", "bash", "/proc/self/fd/[FD_NUM]", NULL);

O arquivo surge na RAM, executa seu propósito e, assim que o processo morre, a RAM é limpa.
