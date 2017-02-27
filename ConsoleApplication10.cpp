// ConsoleApplication10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <assert.h>
#include <string.h>
#include <random>
#include <time.h>
#include <fstream>

#define LYRAND (double)rand()/RAND_MAX

using namespace std;
int xmin = 0;
int xmax = 9;
int ymin = 0;
int ymax = 9;

class agent {
public:
	int agentx;
	int agenty;
	int lastx;
	int lasty;
};

class domain {
public:
	int xmin;
	int xmax;
	int ymin;
	int ymax;
	int goalx;
	int goaly;
	int agstartx;
	int agstarty;
};

void move(agent* pbond,int d) {
	switch (d) {
	case 0:pbond->lasty = pbond->agenty;
		pbond->agenty = pbond->agenty + 1;
		break;
	case 1:pbond->lastx = pbond->agentx;
		pbond->agentx = pbond->agentx + 1;
		break;
	case 2: pbond->lasty = pbond->agenty;
		pbond->agenty = pbond->agenty - 1;
		break;
	case 3:pbond->lastx = pbond->agentx;
		pbond->agentx = pbond->agentx -1;
		break;
	}

}

void bounce(domain* pgw, agent* pbond) {
	if (pbond->agentx > pgw->xmax || pbond->agentx < pgw->xmin || pbond->agenty > pgw->ymax || pbond->agenty < pgw->ymin) {
		pbond->agentx = pbond->lastx;
		pbond->agenty = pbond->lasty;
		cout << "The agent was put outside the play area and was bounced back to its original position." << endl;
	}
	else
		pbond->agentx = pbond->agentx;
	    pbond->agenty = pbond->agenty;
}

int main()
{
	srand(time(NULL));
	domain gw;
	domain* pgw = &gw;
	pgw->xmin = 0;
	pgw->xmax = xmax;
	pgw->ymin = 0;
	pgw->ymax = ymax;
	pgw->goalx = rand()%xmax;
	pgw->goaly = rand()%ymax;
	pgw->agstartx = rand()%xmax;
	pgw->agstarty = rand()%ymax;

	agent bond;
	agent* pbond = &bond;
	pbond->agentx = pgw->agstartx;
	pbond->agenty = pgw->agstarty;
	pbond->lastx = pgw->agstartx;
	pbond->lasty = pgw->agstarty;

	int d = 0;
	int player = 0;
	if (player == 1) {
		while (pbond->agentx != pgw->goalx || pbond->agenty != pgw->goaly) {
			cout << "The agent is at " << pbond->agentx << "," << pbond->agenty << endl;
			cout << "The goal is at " << pgw->goalx << "," << pgw->goaly << endl;
			cout << "Which way should the agent move? Type 0 to go up, 1 to go left, 2 to go down, and 3 to go right." << endl;
			cin >> d;
			if (d == 0 || d == 1 || d == 2 || d == 3) {
				move(pbond, d);
			}
			else {
				cout << "The command you entered is not recognized, please try again." << endl;
			}
			bounce(pgw, pbond);
		}
	}
	else {
		cout << "Initial agent location: " << pbond->agentx << "," << pbond->agenty << endl;
		cout << "The goal is at " << pgw->goalx << "," << pgw->goaly << endl;
		int movex = pgw->goalx - pbond->agentx;
		int movey = pgw->goaly - pbond->agenty;
		if (movex > 0) {
			for (int i = 0; i < abs(movex); i++) {
				move(pbond, 1);
				bounce(pgw, pbond);
			}
		}
		else if (movex < 0) {
			for (int i = 0; i < abs(movex); i++) {
				move(pbond, 3);
				bounce(pgw, pbond);
			}
		}
		else {

		}
		if (movey > 0) {
			for (int i = 0; i < abs(movey); i++) {
				move(pbond, 0);
				bounce(pgw, pbond);
			}
		}
		else if (movey < 0) {
			for (int i = 0; i < abs(movey); i++) {
				move(pbond, 2);
				bounce(pgw, pbond);
			}
		}
		else {

		}
		cout << "Final agent location: " << pbond->agentx << "," << pbond->agenty << endl;
	}
	cout << "The agent is at the goal!" << endl;
    return 0;
}

