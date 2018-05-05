struct{
    double circle_t,circle_r;
    double dot_r;
    double speed; //pixels per second
}player={0,100,5,20*M_PI};

double player_get_x(){
    return cos(player.circle_t)*player.circle_r;
}

double player_get_y(){
    return sin(player.circle_t)*player.circle_r;
}

void player_rotate(double direction){
    player.circle_t += direction*player.speed/FPS/player.circle_r;
    if (player.circle_t < 0)
	player.circle_t+=2*M_PI;
    if (player.circle_t > 2*M_PI)
	player.circle_t-=2*M_PI;
}

void player_move_radial(double direction){
    player.circle_r += direction*player.speed/FPS;
    if (player.circle_r<0.1)
	player.circle_r=0.1;
}
