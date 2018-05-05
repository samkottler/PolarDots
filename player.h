struct{
    double circle_t,circle_r;
    double dot_r;
}player={0,100,5};

double player_get_x(){
    return cos(player.circle_t)*player.circle_r;
}

double player_get_y(){
    return sin(player.circle_t)*player.circle_r;
}

void player_rotate(double theta){
    player.circle_t += theta;
}
