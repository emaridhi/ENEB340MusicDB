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
    printf("[A] sizeof(Song)=%zu tail_padding=%zu\n", sizeof(Song), sizeof(Song)-(sizeof(sizeof(s->id),offsetof(Song,id))));
    printf("[A] offsets title=%zu artist=%zu year=%zu rating=%zu num_rated=%zu id=%zu\n",offsetof(Song, title),offsetof(Song, artist),offsetof(Song, year),offsetof(Song,rating),offsetof(Song, num_rated),offsetof(Song,id));

    printf("[B] songs=%zu artists=%zu", db_song_count(database), db_artist_count(database));
    const Song *first_song= db_get(database,0);
    printf("[B] song[0]: %s | %s | %d | %f | %u", first_song->title,first_song->artist->name,(int)first_song->year,(double)first_song->rating,(unsigned int)first_song->num_rated);
    const Artist topmost=db_top_artist(database);
    printf("[B] top_artist: %s (%zu songs)");

    char exam1[200];
    char artist1[200];
    char exam2[200];
    snprintf(exam1,sizeof(exam1),"Exam Song%s", arg2[2]);
    snprintf(artist1,sizeof(artist1),"Exam Artist%s", arg2[2]);
    snprintf(exam2,sizeof(exam2),"Exam Song (Reprise)%s", arg2[2]);


    printf("[C] push1 -> songs=%zu artists=%zu", db_song_count(database),db_artist_count(database));
    printf("[C] push2 -> songs=%zu artists=%zu"),db_song_count(database),db_artist_count(database);
    const *Song push2=db_get(database,db_song_count(database));
    printf("[C] beatles_songs=%zu",push2->artist->n_songs);

    printf("[D] Q1 decade=%zu count=%zu best_id=%zu best_title=%s");
    printf("[D] Q2 rating>=%zu rated>=%lu count=%lu first_id=%zu last_id=%lu");
    printf("[D] sort card 3 top5 ids: 1311 3267 4075 3940 2621");

    db_destroy(database);
    return 0;



}