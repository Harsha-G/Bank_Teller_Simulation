#include "Header.h"

int gen_random_int(int l_bnd, int u_bnd) {
	return (rand() % (u_bnd - l_bnd)) + l_bnd;
}

float gen_random_float() {
	return ((rand() % (100 - 1)) + 1)*0.01;
}

simulation::simulation(int no_iteration) {
	clock = teller1 = teller2 = teller3 = teller4 = sno;
	qu1 = qu2 = qu3 = qu4 = 0;
	//t1_rt = t2_rt = t3_rt = t4_rt = 0;

	time = 0;

	client_cnt = 1;

	evnt_lst = new fel();
	servc_lst = new fel();
	no_iter = no_iteration;

}

//*Note: Whether the client is general or business is decided at the arrival of the client itself...
void simulation::sim_arrival(int t) {

	time = t;

	sno++;

	char c[10];
	sprintf_s(c, "C%d", client_cnt);

	//Removing the top most Event notice in Future event list
	if (evnt_lst->get_peek() != NULL) {
		evnt_lst->pop_peek();
	}

	int n = gen_random_int(0, 10);

	//decide of arrival is general or business client
	if (gen_random_float() < 0.33) {
		//client is business

		//Now, to see if there is a vacant teller
		if (teller3 == 0 && teller4 == 1) {
			teller3 = 1;

			//Schedule departure where ET3 = Exit Teller 3

			evnt_lst->fel_insert(spawn_event("ET3", gen_random_int(10, 15) + t, c), *evnt_lst->return_peek());

		}
		else if (teller3 == 1 && teller4 == 0) {
			teller4 = 1;

			//Schedule departure where ET4 = Exit Teller 4
			evnt_lst->fel_insert(spawn_event("ET4", gen_random_int(10, 15) + t, c), *evnt_lst->return_peek());
		}
		else if (teller3 == 1 && teller4 == 1) {
			if (gen_random_int(1, 10) < 5) {
				qu3++;
			}
			else {
				qu4++;

			}
		}
		else { //if teller 3 == teller4 ==0
			if (gen_random_int(1, 10) < 5) {
				teller3 = 1;
				evnt_lst->fel_insert(spawn_event("ET3", gen_random_int(10, 15) + t, c), *evnt_lst->return_peek());
			}
			else {
				teller4 = 1;
				evnt_lst->fel_insert(spawn_event("ET4", gen_random_int(10, 15) + t, c), *evnt_lst->return_peek());
			}
		}
		//evnt_lst->fel_insert(spawn_event('A', gen_random_int(1, 3)), *evnt_lst->return_peek());
	}
	else {
		//client is general

		if (teller1 == 0 && teller2 == 1) {
			teller1 = 1;
			//Schedule departure where ET1 = Exit Teller 1
			evnt_lst->fel_insert(spawn_event("ET1", gen_random_int(5, 6) + t, c), *evnt_lst->return_peek());
		}
		else if (teller1 == 1 && teller2 == 0) {
			teller2 = 1;
			//Schedule departure where ET2 = Exit Teller 2
			evnt_lst->fel_insert(spawn_event("ET2", gen_random_int(5, 6) + t, c), *evnt_lst->return_peek());
		}
		else if (teller1 == 1 && teller2 == 1) {
			if (gen_random_int(1, 10) < 5) qu1++;
			else qu2++;
		}
		else { //if teller 1 == teller2 ==0
			if (gen_random_int(1, 10) < 5) {
				teller1 = 1;
				evnt_lst->fel_insert(spawn_event("ET1", gen_random_int(5, 6) + t, c), *evnt_lst->return_peek());
			}
			else {
				teller2 = 1;
				evnt_lst->fel_insert(spawn_event("ET2", gen_random_int(5, 6) + t, c), *evnt_lst->return_peek());
			}
		}
		//evnt_lst->fel_insert(spawn_event('A', gen_random_int(1, 3)), *evnt_lst->return_peek());
	}

	//Inserting new arrival into service queue
	servc_lst->fel_insert(spawn_event(c, t), *servc_lst->return_peek());

	//incrementing for next arrival
	client_cnt++;
	sprintf_s(c, "C%d", client_cnt);
	evnt_lst->fel_insert(spawn_event("A", gen_random_int(1, 3) + t, c), *evnt_lst->return_peek());

	//Once no of iterations is complete, exit simullation
	if (sno == no_iter) {
		return;
	}

	if (strcmp(evnt_lst->get_peek()->evnt, "A") == 0) {
		//Schedule next arrival at the time of the next event notice
		sim_arrival(evnt_lst->get_peek()->time);
	}
	else {
		//Schedule next departure at the time of next event notice
		sim_departure(evnt_lst->get_peek()->time, evnt_lst->get_peek()->evnt);
	}
}

void simulation::sim_departure(int t, char* ev) {

	sno++;

	if (strcmp(ev, "ET1") == 0) {
		if (qu1 > 0) {
			qu1--;
			evnt_lst->fel_insert(spawn_event("ET1", gen_random_int(5, 6) + t), *evnt_lst->return_peek());
		}
		else teller1 = 0;

		//calculating time teller 1 was busy
		t1_rt.push_back(t - servc_lst->get_peek()->time);
	}

	else if (strcmp(ev, "ET2") == 0) {
		if (qu2 > 0) {
			qu2--;
			evnt_lst->fel_insert(spawn_event("ET2", gen_random_int(5, 6) + t), *evnt_lst->return_peek());
		}
		else teller2 = 0;
		
		//calculating time teller 2 was busy
		t2_rt.push_back(t - servc_lst->get_peek()->time);
	}

	else if (strcmp(ev, "ET3") == 0) {
		if (qu3 > 0) {
			qu3--;
			evnt_lst->fel_insert(spawn_event("ET3", gen_random_int(10, 15) + t), *evnt_lst->return_peek());
		}
		else teller3 = 0;			
		//calculating time teller 3 was busy
		t3_rt.push_back(t - servc_lst->get_peek()->time);
	}

	else if (strcmp(ev, "ET4") == 0) {
		if (qu4 > 0) {
			qu4--;
			evnt_lst->fel_insert(spawn_event("ET4", gen_random_int(10, 15) + t), *evnt_lst->return_peek());
		}
		else teller4 = 0;			
		//calculating time teller 4 was busy
		t4_rt.push_back(t - servc_lst->get_peek()->time);
	}

	//Here we get the difference between the time of arrival and time of departure of the client...
	client_duration.push_back(t - servc_lst->get_peek()->time);


	if (servc_lst->get_peek() != NULL) {
		servc_lst->pop_peek();
	}

	//Once no of iterations is complete, exit simullation
	if (sno == no_iter) {
		return;
	}

	if (evnt_lst->get_peek() != NULL) {
		evnt_lst->pop_peek();
	}

	if (strcmp(evnt_lst->get_peek()->evnt, "A") == 0) {
		sim_arrival(evnt_lst->get_peek()->time);
	}
	else {
		sim_departure(evnt_lst->get_peek()->time, evnt_lst->get_peek()->evnt);
	}
}

int simulation::calc_avg_client_time() {
	int avg = 0;
	for (int i = 0; i < client_duration.size();i++) {
		avg = avg + client_duration[i];
	}
	return (avg / client_duration.size());
}

float simulation::calc_perc_t1() {
	float total = 0.0;
	for (int i = 0; i < t1_rt.size();i++) {
		total = total + t1_rt[i];
	}
	return ((total / time)*100);
}

float simulation::calc_perc_t2() {
	float total = 0.0;
	for (int i = 0; i < t2_rt.size();i++) {
		total = total + t2_rt[i];
	}
	return ((total / time) * 100);
}

float simulation::calc_perc_t3() {
	float total = 0.0;
	for (int i = 0; i < t3_rt.size();i++) {
		total = total + t3_rt[i];
	}
	return ((total / time) * 100);
}

float simulation::calc_perc_t4() {
	float total = 0.0;
	for (int i = 0; i < t4_rt.size();i++) {
		total = total + t4_rt[i];
	}
	return ((total / time) * 100);
}
