/**
 * SEFER_HA_RAZIM | MODULE: METATRON_CIPHER
 * TACTIC: COMPILE-TIME STRING OBFUSCATION (XOR)
 * * "A palavra verdadeira nunca é dita em voz alta."
 */

#include <iostream>
#include <string>

// A Chave Criptográfica Mestra
const char XOR_KEY = 0x5A; // 90 em decimal

// Estrutura que encripta a string e descriptografa apenas em tempo de execução
class XorString {
private:
    std::string data;
public:
    // O construtor recebe os bytes já criptografados manualmente ou via macro
    XorString(const char* encrypted_bytes, size_t len) {
        data.resize(len);
        for (size_t i = 0; i < len; ++i) {
            data[i] = encrypted_bytes[i] ^ XOR_KEY; // Descriptografa na RAM
        }
    }
    
    const char* c_str() { return data.c_str(); }
};

int main() {
    // TEXTO ORIGINAL: "[*] INVOCANDO O VAZIO."
    // TEXTO CRIPTOGRAFADO COM A CHAVE 0x5A:
    const char enc_msg1[] = { 0x01, 0x70, 0x07, 0x7A, 0x13, 0x14, 0x0C, 0x15, 0x19, 0x1B, 0x14, 0x1E, 0x15, 0x7A, 0x15, 0x7A, 0x0C, 0x1B, 0x00, 0x13, 0x15, 0x74 };
    XorString msg1(enc_msg1, sizeof(enc_msg1));

    // TEXTO ORIGINAL: "[+] אמת - ACESSO CONCEDIDO."
    // TEXTO CRIPTOGRAFADO COM A CHAVE 0x5A:
    const char enc_msg2[] = { 0x01, 0x71, 0x07, 0x7A, 0xA5, 0x98, 0xA4, 0x7A, 0x77, 0x7A, 0x1B, 0x19, 0x1F, 0x09, 0x09, 0x15, 0x7A, 0x19, 0x15, 0x14, 0x19, 0x1F, 0x1E, 0x13, 0x1E, 0x15, 0x74 };
    XorString msg2(enc_msg2, sizeof(enc_msg2));

    // A mágica: O texto aparece limpo no terminal, mas não existe no binário no HD
    std::cout << "\033[38;5;240m" << msg1.c_str() << "\033[0m" << std::endl;
    std::cout << "\033[38;5;118m" << msg2.c_str() << "\033[0m" << std::endl;

    return 0;
}
