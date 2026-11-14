//implement those 13 funtions here

#include "musicdb.h"
//#include "main.c"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct MusicDB{//for the entrire catalog of music
    Artist **list_of_artists;//points to an array of artist pointers
    size_t numb_artists;
    size_t artists_size;//number of pointers that can be held

    Song **list_of_songs;
    size_t numb_songs;
    size_t songs_size;//number of pointers that can be held
};


//1.if cant create db, return empty db or NULL. initialize values too
MusicDB *db_create(void){
    MusicDB db_new=malloc(sizeof(MusicDB));//for a struct above.
    if(db_new==NULL){
        return NULL;
    }

    db_new->list_of_artists=NULL;//since a array
    db_new->list_of_songs=NULL;
    db_new->numb_artists=0;
    db_new->numb_songs=0;
    db_new->numb_songs=0;
    db_new->songs_size=0;
    return db_new;
};


//1.frees the db (song, title, artist, artist names, every array)
void db_destroy(MusicDB *db){

}


/*
1. reads the txt files given and adds the records to the db from /data.
2. 0 success. -1 failure
3.remoce whitseapces on both ends of each line
4. FAILURES when file cant be opened, files dont have the same #lines, empty artist/song, a year that isnt an int from[1000,3000], 
    a rating that isnt a number from 0.0 to 5.0, a number of raters  that isnt a non-negative integer.
5. (last line has no \n)
*/
int db_load(MusicDB *db, const char *dir){

}


/*1.total numeber of songs in db.
2. 0 if NULL 
*/
size_t db_song_count(const MusicDB *db){
    if(db==NULL){
        return 0;
    }
    db->numb_songs;
}


/*1.total numeber of artists in db.
2. 0 if NULL 
*/
size_t db_artist_count(const MusicDB *db){
    if(db==NULL){
        return 0;
    }
    db->numb_artists;
}


/*1. returns a song in index position i
2.NULL if i out of range
reutn the pointer not the actual value to the song req*/
const Song *db_get(const MusicDB *db, size_t i){
    if(i>= db->numb_songs){
        return NULL;
    }
    return db->list_of_songs[i]//retirns address of the song we want
}


/*1. adds a song
2. creates the artist if no artist with same name. add to the db too
3.0 is success -1 is failure or NULL or when memory runs out
4. song count incr and artist count incr, if new artist
add song to the artist array
malloc for the arrays. add NULL checks everywhewe
*/
int db_push(MusicDB *db, const char *title, const char *artist, double rating, int year, unsigned long num_rated){
    Song *new_song = malloc(sizeof(Song));
    if (new_song==NULL){
        return -1;
    }

    new_song->title =malloc(strlen(title)+1);//null op
    if(new_song->title==NULL){
        free(new_song);
        return -1;
    }
    strcpy(new_song->title, title);//to copy the title chars into the allocated mem


    Artist *artist_exists=NULL;
    for(size_t i=0; i<db->numb_artists; i++){
        if(strcmp(db->list_of_artists[i]->name, artist)==0){//each slot in list_of_artitis is an artist struct 
            artist_exists=db->list_of_artists[i];
            break;
        }
    }

    int new_artist_ornot=0;
    //if the artist does not exist, create one
    if (artist_exists==NULL){
        artist_exists=malloc(sizeof(Artist));

        artist_exists->name=malloc(strlen(artist)+1);
        strcpy(artist_exists->name, artist);

        artist_exists->n_songs=0;
        artist_exists->cap=0;
        artist_exists->songs=NULL; //array
        new_artist_ornot=1;
    }

    //add the artist to the db now
    if(new_artist_ornot==1){
        db->list_of_artists=realloc(db->list_of_artists, (db->numb_artists+1)*sizeof(Artist*));//extra artist memory needed
        
        db->list_of_artists[db->numb_artists]=artist_exists;
        db->numb_artists++;
    }

    //finnish thte other values of the Song struct
    new_song->rating=(float)rating;//struct song has this as float;
    new_song->num_rated=num_rated;
    new_song->year=year;
    new_song->id = db->numb_songs;
    new_song->artist =artist_exists;

    //add song to the array
    db->list_of_songs=realloc(db->list_of_songs, (db->numb_songs+1)*sizeof(Song*));
    db->list_of_songs[db->numb_songs]=new_song;
    db->numb_songs++;

    return 0;
}


/*1. prints header line
"%-35s %-25s %-5s %-8s %s\n" with the texts Song Title, Artist, Year, Rating, People Rated
2. prints the first lim (limit) songs.
"%-35.35s %-25.25s %-5d %-8.2f %lu\n" (title, artist name, year, rating, number of raters).
3. if lim==0 or lim>count
*/
void db_disp(const MusicDB *db, FILE *out, size_t lim){

}


/*1. calls pred(song,key) for every song
2. stored in *out (a new array of poitners that point to the matchign song)
3. returns the number of matches
4.0 is nothign matches or runs out of memory. sets *out=NULL.
5. caller frees the array when donw
(song obj not copied, so we hav epointers to the original songs)
*/
size_t db_search(const MusicDB *db, song_pred pred, const void *key, const Song ***out){

}


/*1. reorders db accorign to sort card (0-3)
2.ratings compared to decimals in the file.
3. qsort()
4. do nothign if unknwn card numebr
*/
void db_sort(MusicDB *db, int card){

}


/*1. returns the #songs that whose year is [start, start+9]
2. if best!=NULL, *best= (song with the largest num_rated (smnaller id wins if a tie) ) or NULL if none
3. PTR ONLY. walk with the aarray of pointers. dont contatin ']' or'['. dont use integer loop index
*/
size_t db_count_decade(const MusicDB *db, int start, const Song **best){

}


/*1. returns artist with most songs(ties the name that comes frist by strcmp) 
2, if none, returns NULL.
3. PTR ONLY. walk with the aarray of pointers. dont contatin ']' or'['. dont use integer loop index 
*/
const Artist *db_top_artist(const MusicDB *db){

}