#include <iostream>
#include <bitset>
#include <stdio.h>
#include<stdlib.h>
#include <string>
#include <vector>
using namespace std;


// class instruction { // optional
// public:
// 	bitset<32> instr;//instruction
// 	instruction(bitset<32> fetch); // constructor

// };
enum instructType {notype, rtype, itype, stype, btype, utype, jtype};
enum operation{NONE, ADD, XOR, ORI, SRAI, LB, LW, SB, SW, BEQ, LUI, JAL};
//declaration for immediate gen helper functions 
unsigned long getItypeImmediate(unsigned long binary);
unsigned long getItypeShiftAmt(unsigned long binary);
unsigned long getStypeImmHigh(unsigned long binary);
unsigned long getStypeImmLow(unsigned long binary);
unsigned long getStypeImmediate(unsigned long immhigh, unsigned long immlow);
unsigned long getBtypeImmediate(unsigned long binary);
unsigned long getUtypeImmediate(unsigned long binary);
unsigned long getJtypeImmediate(unsigned long binary);
//declaration for register set helper functions
unsigned long getRs1(unsigned long binary);
unsigned long getRs2(unsigned long binary);
unsigned long getRd(unsigned long binary);
// function declarations that are used in main to bring in the hex bytes in the right order and into binary
string hexChartoBinary(char hex);
string hextoBinary(const string &hex);
vector<string> createBinaryFromHex(vector<string> &instructions, int numofInstructions);
vector<string> turnPairsToFullInstruction(vector<string> pairs, vector<string>instructions, int i);
//CPU class declaration
class CPU {
private:
	unsigned long PC; //pc 
public:
	CPU();
	unsigned long getPC();
	unsigned long readPC();
	void incPC();
	// used to bring instructions from main and load them into the CPU
	void setInstructions(vector<unsigned long> instr);

	// recognize the operation and type; info is used for set register/set immediate
	void setOperationAndType(unsigned long opcode, unsigned long funct3);

	// load the appropriate registers with the values to be used in the alu
	// beware the values in registers are just indexes to which register to acces
	void setRegister(unsigned long binary);
	void setImmediate(unsigned long binary);
	void jumpPC();

	void setControlSignals();
	unsigned long ALUMUX();
	unsigned long ALU();

	// data variables to store register/immediate/general info
	int32_t registers[33]; 
	uint8_t memory[4096] = {0};
	int32_t displayReg(int x);
	unsigned long rs1; 
	unsigned long rs2;
	unsigned long rd; 
	unsigned long immediate;
	unsigned long shamt; 
	instructType instructionType; 
	operation operationType; 

	// total number of instructions to let the main function know when to stop executing
	int numofInstructions;

	// all instructions in unsigned long binary
	vector<unsigned long> instructions;
	
	// control signals
	bool aluMux; // 0 is rs2, 1 is imm gen
	bool memWrite; 
	bool regWrite;
	bool memRead;

};

