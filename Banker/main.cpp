#include "Header.h"

using namespace std;



int main() {

	ofstream file ("C://Users//hgstr//Desktop//banker.txt");
	// Insert output file pathway here... ^ ^ ^ 

	//==========================================
	simulation s(500);
	s.sim_arrival(0);
	int client_avg = s.calc_avg_client_time();
	float t1_perc_time = s.calc_perc_t1();
	float t2_perc_time = s.calc_perc_t2();
	float t3_perc_time = s.calc_perc_t3();
	float t4_perc_time = s.calc_perc_t4();
	//===========================================

	file << "Average Time Spent by Clients: " << client_avg << "\n";
	file << "Percent Time by Teller1: " << t1_perc_time << "%\n";
	file << "Percent Time by Teller2: " << t2_perc_time << "%\n";
	file << "Percent Time by Teller3: " << t3_perc_time << "%\n";
	file << "Percent Time by Teller4: " << t4_perc_time << "%\n";

}