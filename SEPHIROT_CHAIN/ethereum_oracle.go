/**
 * SEFER_HA_RAZIM | MODULE: SEPHIROT_CHAIN (WEB3 C2 ORACLE v2.0)
 * ARCHITECTURE: DECOMPILED FROM 'GO-ETHEREUM' RPC STANDARDS
 * * "ספירות - Mapeando as emanações de dados dentro dos blocos."
 */

package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
	"time"
)

const ETH_RPC_NODE = "https://cloudflare-eth.com"

// Estruturas fortemente tipadas (Padrão de Arquitetura Sênior)
type EthRequest struct {
	Jsonrpc string        `json:"jsonrpc"`
	Method  string        `json:"method"`
	Params  []interface{} `json:"params"`
	Id      int           `json:"id"`
}

type Transaction struct {
	Hash  string `json:"hash"`
	Input string `json:"input"` // É aqui que os comandos C2 são escondidos
}

type BlockData struct {
	Transactions []Transaction `json:"transactions"`
}

type EthResponse struct {
	Result BlockData `json:"result"`
}

func queryBlockByTag(tag string) {
	fmt.Printf("\033[38;5;240m[*] VARRENDO A MALHA CÓSMICA. ALVO: BLOCO '%s'...\033[0m\n", tag)

	reqBody := EthRequest{
		Jsonrpc: "2.0",
		Method:  "eth_getBlockByNumber",
		Params:  []interface{}{tag, true}, // 'true' força a rede a nos dar os dados completos das transações
		Id:      1,
	}

	jsonData, _ := json.Marshal(reqBody)
	
	client := &http.Client{Timeout: 10 * time.Second}
	resp, err := client.Post(ETH_RPC_NODE, "application/json", bytes.NewBuffer(jsonData))
	
	if err != nil {
		fmt.Println("\033[1;31m[!] מת - A MALHA ESTÁ INACESSÍVEL.\033[0m")
		return
	}
	defer resp.Body.Close()

	body, _ := ioutil.ReadAll(resp.Body)
	
	var ethResp EthResponse
	json.Unmarshal(body, &ethResp)

	txCount := len(ethResp.Result.Transactions)
	fmt.Printf("\033[38;5;118m[+] אמת - BLOCO PROCESSADO. %d TRANSAÇÕES ENCONTRADAS.\033[0m\n", txCount)

	if txCount > 0 {
		fmt.Println("\033[38;5;129m[*] ANALISANDO DADOS HEXADECIMAIS DA PRIMEIRA TRANSAÇÃO (BUSCA POR COMANDOS C2):\033[0m")
		fmt.Printf("\033[1;37m    HASH: %s\033[0m\n", ethResp.Result.Transactions[0].Hash)
		
		inputData := ethResp.Result.Transactions[0].Input
		if len(inputData) > 64 {
            // Trunca a saída para não inundar o terminal
			fmt.Printf("\033[38;5;250m    DADOS (PAYLOAD): %s...\033[0m\n", inputData[:64]) 
		} else {
			fmt.Printf("\033[38;5;250m    DADOS (PAYLOAD): %s\033[0m\n", inputData)
		}
	}
}

func main() {
	fmt.Println("\033[38;5;196m[!] INICIANDO PROTOCOLO DE ORÁCULO AVANÇADO\033[0m")
	// Ao invés de pegar apenas o último bloco, pedimos o bloco 'latest' com todas as transações
	queryBlockByTag("latest")
	fmt.Println("\033[38;5;240m[*] VARREDURA CONCLUÍDA. NENHUMA INSTRUÇÃO DE DESTRUIÇÃO RECEBIDA AINDA.\033[0m")
}
