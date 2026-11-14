#include"musicdb.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int arg1, char *arg2[]){//2 arguments
    if(arg1!=3){
        return 1;
    }

    if (strlen(arg2[2])!=4){
        printf("incorrect student id. need only 4 digits");
        return 1;
    }

    int tens_id=arg2[2][2]-'0';
    int ones_id=arg2[2][3]-'0';
    int L=(tens_id+ones_id)%4;
    int D=tens_id%5;
    int T=ones_id%5;
    int S=(tens_id+(2*ones_id))%4;

    MusicDB *database = db_create();

    if (database ==NULL){
        printf("couldnt create db");
        return 1;
    }
    //load the given txt files
    if(db_load(database, arg2[1])!=0){///secodn arg is data in our command "... data 3456"
        printf("couldnt load db");
        db_destroy(database);
        return 1;
    }

    printf("ENEB340 REPORT\n");
    printf("card: L=%d D=%d T=%d S=%d\n", L,D,T,S);
    printf("[A] sizeof(Song)=%zu tail_padding=%zu\n", sizeof(Song), tail_padding);
    printf("[A] offsets title=%zu artist=%zu year=%zu rating=%zu num_rated=%zu id=%zu\n",offsetof(Song, title),offsetof(Song, artist),offsetof(Song, year),offsetof(Song,rating),offsetof(Song, num_rating),offsetof(Song,id));

    printf("[B] songs=%zu artists=%zu", db_song_count(database), db_artist_count(database));
    const Song *first_song= db_get(database,0);
    printf("[B] song[0]: %s | %s | %d | %f | %lu", first->title,first->artist->name,(int)first->year,(double)first->rating,first->num_rated);
    const Artist topmost=db_top_artist(databse);
    printf("[B] top_artist: %s (%zu songs)");

    printf("[C] push1 -> songs=%zu artists=%zu");
    printf("[C] push2 -> songs=%zu artists=%zu");
    printf("[C] beatles_songs=%zu");

    printf("[D] Q1 decade=1990 count=885 best_id=3869 best_title=Play That Funky Music");
    printf("[D] Q2 rating>=4.50 rated>=1400000 count=444 first_id=0 last_id=4990");
    printf("[D] sort card 3 top5 ids: 1311 3267 4075 3940 2621");

    db_destroy(database);
    return 0;



}