#define DOT_RADIUS 10

typedef struct dot{
    double x,y;
    int remaining_frames;
    int points;
    struct dot* next, *prev;
} dot;

dot* dots;
int points = 0;

void init_dots(){
    dots = (dot*) malloc(sizeof(dot));
    dots->next = dots->prev = 0;
}

void add_dot(double x, double y){
    dot* new_dot = (dot*) malloc(sizeof(dot));
    dots->prev = new_dot;
    new_dot->next = dots;
    dots = new_dot;
    int r = rand();
    if (r<RAND_MAX/19*8){
	new_dot->points = 1;
	new_dot->remaining_frames = 30*FPS;
    }
    else if (r<RAND_MAX/19*12){
	new_dot->points = 5;
	new_dot->remaining_frames = 15*FPS;
    }
    else if (r<RAND_MAX/19*16){
	new_dot->points = -50;
	new_dot->remaining_frames = 30*FPS;
    }
    else if (r<RAND_MAX/19*18){
	new_dot->points = 25;
	new_dot->remaining_frames = 15*FPS/2;
    }
    else{
	new_dot->points = 0;
	new_dot->remaining_frames = 15*FPS/2;
    }
    new_dot->x = x;
    new_dot->y = y;
    new_dot->prev = 0;
}

void remove_dot(dot* to_remove){
    to_remove->next->prev = to_remove->prev;
    if (to_remove->prev){
	to_remove->prev->next = to_remove->next;
    }
    else{
	dots = to_remove->next;
    }
    free(to_remove);
}

void update_dots(){
    dot* current = dots;
    double x = player_get_x();
    double y = player_get_y();
    while (current->next){
	if (current->remaining_frames == 0){
	    remove_dot(current);
	}
	else{
	    --(current->remaining_frames);
	}
	double dist = sqrt((x-current->x)*(x-current->x) + (y-current->y)*(y-current->y));
	if (dist < DOT_RADIUS + player.dot_r){
	    points += current->points;
	    if(current->points == 0)
		settings.frames_remaining += 15*FPS;
	    remove_dot(current);
	}
	current = current->next;
    }
}

    
