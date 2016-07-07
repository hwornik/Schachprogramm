#include "stdafx.h"
#include "Compute.h"


Compute::Compute()
{
	end = false;
	mymoves = new Movement();
	mynot = new Notation();
	this->printWelcome();
	searchmvs = false;
}


Compute::~Compute()
{
}

void Compute::init()
{
	myzug = 0;
	mode = NAKED;
	//mycalc = new CalculusTopTh();
	mycomp = new Communicate();
	mycomp->init();
	mycomp->setMovement(mymoves);
}

bool Compute::start()
{
	while (!end)
	{
		if (mycomp->input())
			this->readInput();
	}
	return true;
}

void Compute::readInput()
{

	std::getline(std::cin, command);
	//std::cout << command;
	//std::cin.clear();
	//gets(command);
	if (mode == NAKED)
		this->naked(command);
	else if (mode == UCI)
		this->uci(command);
	else if (mode == XBOARD)
		this->xboard(command);

}
bool Compute::uci(std::string command)
{
	if (command.compare("uci") == 0) {
		mode = 1;
		this->mycomp->setMode(1);

		this->mycomp->send("id name SchachHanse 1.1");
		this->mycomp->send("id author Hans Wornik");

		printf("option name\n");
		// send options

		this->mycomp->send("uciok");
	}
	//if (!strcmp(command, "d"))			{	this->displayBoard();return 1;}
	if (command.compare("isready") == 0)
		this->mycomp->send("readyok");
	if (command.compare(0, 2, "d ") == 0)				this->displayBoard();
	if (command.compare(0, 9, "setoption") == 0) {
		char name[256];
		char value[256];

		/*sscanf(command, "setoption name %s value %s", &name, &value);

		if (strcmp(name, "Hash")==0) {
		int val;
		sscanf(value, "%d", &val);
		//tt_setsize(val << 20);   // Transposition aufruf setzt Hashwert
		//ttpawn_setsize(val << 18);//Transposition aufruf setzt Hashwert
		}*/
		this->mycomp->send("isready");
		this->mycomp->send("readyok");

	}

	if (command.compare("ucinewgame") == 0) {
		this->mymoves->loadFromFen(STARTFEN);
	}

	if (command.compare(0, 8, "position") == 0) {
		//position [fen | startpos] [moves ...]

		if (command.compare(0, 17, "position startpos") == 0) {

			this->mymoves->loadFromFen(STARTFEN);
		}
		else if (command.compare(0, 12, "position fen") == 0) {
			// position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
			// position fen rnbqkbnr/pppppppp/8/8/8/P7/1PPPPPPP/RNBQKBNR b KQkq - 0 1
			this->mymoves->loadFromFen(command.substr(13));
		}
		std::size_t moves = command.find("moves");
		if (moves != std::string::npos) {
			this->mymoves->movePieces(command.substr(moves + 6));

		}
	}

	if (command.compare(0, 2, "go") == 0)
	{
		searchmvs = false;
		std::size_t moves = command.find("searchmoves");
		if (moves != std::string::npos) {
			this->setSearchmoves(command.substr(moves + 12));
		}
		this->starUpCalc();//this->mycalc->start(mymoves);
	}
	if (command.compare(0, 5, "debug") == 0)
		;//debug = strcmp(command, "debug off");

	if (command.compare("ponderhit") == 0)
		this->mycomp->setPonder();//this->mytiming->uci_ponderhit();

	if (command.compare(0, 4, "stop") == 0)
		//----------------------------------
		//this->mycalc->stoptreadproc();//task = TASK_NOTHING;
		//----------------------------------
	if (command.compare("register") == 0)
		this->mycomp->send("later");//task = TASK_NOTHING;

	if (command.compare("quit") == 0)
	{
		//-------------------------------------------
		//this->mycalc->stoptreadproc();
        //--------------------------------------------
		exit(0);
	}

	return false;
}

bool Compute::xboard(std::string command)
{
	/*
	if (!strcmp(command, "xboard"))
	{
	mode = XBOARD;
	this->mycomp->setMode(mode);
	}

	if (!strcmp(command, "new"))
	this->mymoves->loadFromFen(STARTFEN);

	else if (!strcmp(command, "force"))
	;//task = TASK_NOTHING;

	else if (!strcmp(command, "white"))
	myside = WHITE;

	else if (!strcmp(command, "black"))
	myside = BLACK;

	else if (!strncmp(command, "st", 2)) {
	/*sscanf(command, "st %d", this->mytiming->getMoveTime());
	this->mytiming->setMoveTime(1000);
	this->mytiming->setFlag(FMOVETIME);*/
	//		;
	//	}
	/*
	else if (!strncmp(command, "sd", 2)) {
	/*sscanf(command, "sd %d", this->mytiming->getDepth());
	this->mytiming->setFlag(FDEPTH);*/
	;
	//	}
	/*
	else if (!strncmp(command, "time", 4)) {
	/*sscanf(command, "time %d", this->mytiming->getTime(sd.myside));
	this->mytiming->setFlag(FTIME);*/
	;
	//	}
	/*
	else if (!strncmp(command, "otim", 4)) {
	/*sscanf(command, "otim %d", this->mytiming->getTime(!sd.myside));
	this->mytiming->setFlag(FTIME);*/
	;
	//	}
	/*
	else if (!strcmp(command, "go"))
	this->starUpCalc();//this->mycalc->start(mymoves);

	else if (!strcmp(command, "hint")) {
	// hint
	}

	else if (!strcmp(command, "undo")) {
	// undo
	}

	else if (!strcmp(command, "remove")) {
	// remove
	}

	else if (!strcmp(command, "post")) {
	// post
	}

	else if (!strcmp(command, "nopost")) {
	// nopost
	}

	else if (!strcmp(command, "quit")) {
	this->mycalc->stoptreadproc();
	exit(0);
	}

	else if (ismove(command)) {
	this->mymoves->movePieces(command);
	//this->mytiming->xboard_go();
	}*/
	return false;
}

bool Compute::naked(std::string command)// const_cast<char*>(tmp.c_str());
{
	if (command.compare("xboard") == 0)				this->xboard(command);
	else if (command.compare("uci") == 0)			this->uci(command);
													  //------------------------------------------------------
	//else if (command.compare(0, 5, "perft") == 0)	  	this->mycalc->perft(const_cast<char*>(command.c_str()));
														//-----------------------------
	//else if (command.compare(0, 5, "bench") == 0)	  	this->mycalc->util_bench(const_cast<char*>(command.c_str()));
													  //-----------------------------------
	//else if (command.compare("eval") == 0)			this->mycalc->printeva();
                                                        //-----------------------------
	else if (command.compare("stat") == 0)			this->printStats();
	else if (command.compare("d") == 0)				this->displayBoard();
	else if (command.compare("new") == 0)			this->loadFromFen(STARTFEN);
	else if (command.compare(0, 3, "pos") == 0)		this->loadFromFen(command.substr(4));
	else if (command.compare("go") == 0)			this->starUpCalc();
	//--------------------------------
	//else if (command.compare("quit") == 0) { this->mycalc->stoptreadproc(); exit(0); }
	//--------------------------------
	else if (command.compare("help") == 0)			this->printHelp();
	else if (ismove(const_cast<char*>(command.c_str()))) {
		if (this->mymoves->movePieces(command))
			;//this->mymoves->movePieces(this->mycalc->start(this->mymoves));
		else
			printf("Sorry, this is not a legal move\n");
	}
	else if (command.compare(0, 2, "st") == 0) {
		/*sscanf(command, "st %d", this->mytiming->getMoveTime());
		this->mytiming->setMoveTime(1000);
		this->mytiming->setFlag(FMOVETIME);*/
		;
	}
	else if (command.compare(0, 2, "sd") == 0) {
		/*sscanf(command, "sd %d", this->mytiming->getDepth());
		this->mytiming->setFlag(FDEPTH);*/
		;
	}
	//else if (command[0] == '\n') {}
	else {

		command = " - UNKNOWN COMMAND (type 'help' for a list of commands)";
		this->mycomp->send(command);
	}

	return false;
}

int Compute::ismove(char * command) {
	return (command[0] >= 'a' && command[0] <= 'h' &&
		command[1] >= '1' && command[1] <= '8' &&
		command[2] >= 'a' && command[2] <= 'h' &&
		command[3] >= '1' && command[3] <= '8' &&
		(command[4] == ' ' || command[4] == '\n' || command[4] == 0 ||
			command[4] == '-' ||
			command[4] == 'q' || command[4] == 'r' || command[4] == 'b' || command[4] == 'n'));

	/***************************************************************
	*  command[4] might be:                                        *
	*                                                              *
	*  (a) any kind of a blank space                               *
	*    (b) '-' or any other mark used in opening book processing   *
	*    (c) first letter of a name of a promoted piece              *
	***************************************************************/
}


void Compute::printWelcome() {
	printf(" Schach Mentor chess engine ");
	printf(VERSION_STRING);
	printf("\n");
	printf(COMPILE_STRING);
	printf("\n");
	printf(" created by Wornik Hans \n");
	printf(" http://www.wornik.eu/ \n");
	printf(" type 'help' for a list of commands \n\n");
}

void Compute::printHelp() {
	printf("------------------------------------------ \n");
	printf("d        =  display current board position \n");
	printf("bench n  =  test search speed to depth n \n");
	printf("perft n  =  test perft numbers up to depth n \n");
	printf("eval     =  display evaluation details \n");
	printf("stat     =  display search statistics \n");
	printf("go       =  play for the side to move \n");
	printf("new      =  start a new game \n");
	printf("sd n     =  set search depth to n plies \n");
	printf("st n     =  set search time to n seconds \n");
	printf("quit     =  exit CPW engine \n");
	printf("\n");
	printf("Please enter moves in algebraic notation (e2e4 d7d5 e4d5 d8d5 ... b7b8q) \n");
	printf("or better use a GUI compliant with the UCI protocol \n");
	printf("------------------------------------------ \n");
}

void Compute::printStats() {
	/*U64 nodes = sd.nodes + (sd.nodes == 0);

	printf("-----------------------------\n");
	printf("Nodes       : %d \n", sd.nodes);
	printf("Quiesc nodes: %d \n", sd.q_nodes);
	printf("Ratio       : %d %\n", sd.q_nodes * 100 / nodes);*/
	printf("-----------------------------\n");
}

void Compute::printSearchHeader() {
	printf("-------------------------------------------------------\n");
	printf("ply      nodes   time score pv\n");
	printf("-------------------------------------------------------\n");
}

void Compute::displayBoard()
{
	for (int i = 8; i > 0; i--)
	{
		for (int j = 1; j < 9; j++)
		{
			printf("%c", this->mymoves->getPieceonPos(j, i));
		}
		printf("\n");
	}
	if (this->mymoves->getWhitehasMove())
	{
		printf("White to Move");
	}
	else
	{
		printf("Black to Move");
	}
	printf("\n");
}

char Compute::starUpCalc()
{
	//mycalc->stoptreadproc();
	mycalc = new CalculusTopTh(true);
    mycalc->setData(mynot, searchmvs, mymoves->copyBoard(), mycomp, clock());
    mycalc->Start();
	//mycalc->MainSearch2();
	return true;
}

bool Compute::setSearchmoves(std::string command)
{
	searchmvs = true;
	delete this->mynot;
	this->mynot = new Notation();
	Zuege *aktzug;
	char *pch, *mystring;
	char delimiter[] = " ";
	int vx, vy, nx, ny, z;
	mystring = strdup(command.c_str());
	pch = strtok(mystring, delimiter);
	int zhl = 0;
	while (pch != NULL)
	{
		zhl++;
		aktzug = new Zuege();
		aktzug->setWhitePiece(pch);
		aktzug->setZugNr(zhl);
		this->mynot->addZug(aktzug);
		pch = strtok(NULL, delimiter);
	}
	return true;
}

void Compute::loadFromFen(std::string pos)
{
	mymoves->init();
	//delete mymoves;
	//free(mycalc);
	//delete mycalc;
	//mycalc = 0;
	//mycalc = new Calculus();
	//mymoves = new Movement();
	mymoves->loadFromFen(pos);
}