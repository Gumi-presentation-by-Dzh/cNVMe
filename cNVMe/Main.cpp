/*
This file is part of cNVMe and is released under the MIT License
(C) - Charles Machalow - 2017
Main.cpp - An implementation file for the Main entry
*/

#include "Strings.h"
#include "Tests.h"

#include <iostream>

using namespace cnvme;
using namespace cnvme::command;

int main()
{
	// This is testing code.

	LOG_SET_LEVEL(2);

	Controller co;
	auto regs = co.getControllerRegisters()->getControllerRegisters();

	// One entry per queue
	regs->AQA.ACQS = 2;
	regs->AQA.ASQS = 2;
	Payload subQ(512);
	Payload compQ(512);
	regs->ASQ.ASQB = subQ.getMemoryAddress();
	regs->ACQ.ACQB = compQ.getMemoryAddress();

	// enable controller
	regs->CC.EN = 1;
	co.getControllerRegisters()->waitForChangeLoop(); // Wait for enable

	NVME_COMMAND* command = (NVME_COMMAND*)subQ.getBuffer();
	command->DWord0Breakdown.OPC = 0x18; // Send keep alive
	command->DWord1 = 0x1;

	auto queueDoorbells = co.getControllerRegisters()->getQueueDoorbells();
	queueDoorbells[0].SQTDBL.SQT = 1;
	//soon after this, we see the DWs come up from the logging 

	co.waitForChangeLoop();

	// That should have rung the completion doorbell.
	COMPLETION_QUEUE_ENTRY* cqe = (COMPLETION_QUEUE_ENTRY*)compQ.getBuffer();

	command++;
	command->DWord0Breakdown.CID = 1; // Don't want to hit invalid CID/SQID combo
	command->DWord0Breakdown.OPC = 0x18; // Send keep alive
	command->DWord1 = 0x1;

	queueDoorbells[0].SQTDBL.SQT = 0;

	//soon after this, we see the DWs come up from the logging 

	co.waitForChangeLoop();

	LOG_SET_LEVEL(1);

	std::cout << "Tests passing: " << strings::toString(cnvme::tests::helpers::runTests()) << std::endl;

	char c = '1';
	std::cin >> c;

	// End testing code.
}