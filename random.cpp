#include<ctime>
#include<cstdlib>


void start_random()
{
	static bool seeded=false;
	if(!seeded){
		srand( (unsigned)time( NULL ) );
		seeded = true;
	}	
}

float rnd(){
	start_random();
	return (-1)+(float)rand()/16384;
}


float rnd(float rangemin, float rangemax){
	start_random();
	return rangemin + (float)rand()*(rangemax-rangemin)/32768.0;
}


int rnd(int range){
	start_random();
	return rand() % range;
}
