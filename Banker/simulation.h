#pragma once
#include "fel.h"
#include <vector>

using namespace std;

int gen_random_int(int l_bnd, int u_bnd);


class simulation {

	int clock, teller1, teller2, teller3, teller4, sno, client_cnt;
	//tellers 3,4 are business, 1,2 are general

	int qu1, qu2, qu3, qu4;

	//int t1_rt, t2_rt, t3_rt, t4_rt;

	int no_iter;

	int time;

	//Statistics to Calculate the active time of tellers
	//Each vector holds the time 't' when teller is busy
	vector<int> t1_rt;
	vector<int> t2_rt;
	vector<int> t3_rt;
	vector<int> t4_rt;

	vector<int> client_duration;

	fel *evnt_lst;
	fel *servc_lst;
public:
	simulation(int no_iteration);
	void sim_arrival(int t);
	void sim_departure(int t, char* ev);
	int calc_avg_client_time();
	float calc_perc_t1();
	float calc_perc_t2();
	float calc_perc_t3();
	float calc_perc_t4();
};
