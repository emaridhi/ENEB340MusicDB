//implement those 13 funtions here

#define _POSIX_C_SOURCE 200809L 
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


//1.frees the db (song, title, artist, artist names, every array). use free() everywhere
void db_destroy(MusicDB *db){
    //loop to free arrays
    for(size_t i=0;i<db->numb_songs;i++){
        free(db->list_of_songs[i]->title);
        free(db->list_of_songs[i]);
    }
    free(db->list_of_songs);

    for(size_t i=0;i<db->numb_artists;i++){
        free(db->list_of_artists[i]->name);
        free(db->list_of_artists[i]->songs);
        free(db->list_of_artists[i]);
    }
    free(db->list_of_artists);
    free(db);
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
    if(db==NULL||dir==NULL){
        return -1;
    }
    char path[512]; 

    snprintf(path, sizeof(path), "%s/artists.txt", dir);//creatign the file path strign builder.
    FILE *artists_file= fopen(path,"r");

    snprintf(path, sizeof(path),"%s/people_rated.txt", dir);
    FILE *people_rated_file= fopen(path,"r");

    snprintf(path, sizeof(path),"%s/ratings.txt", dir);
    FILE *ratings_file= fopen(path,"r");

    snprintf(path, sizeof(path),"%s/songs.txt", dir);//remove whitsepaces later
    FILE *songs_file= fopen(path,"r");

    snprintf(path, sizeof(path),"%s/year.txt", dir);
    FILE *year_file= fopen(path,"r");

    //failures
    if(artists_file==NULL||people_rated_file==NULL||ratings_file==NULL||songs_file==NULL||year_file==NULL){
        printf("error");
        return -1;}

    //remove whistepecs. hold values for eaech line correspondingly in each of the 5 txt, remove the spaces, and then stor in db with the push fn.
    char *title_line=NULL;
    char *artist_line=NULL;
    char *year_line=NULL;
    char *rating_line=NULL;
    char *people_rated_line=NULL;
    size_t title_mem=0;
    size_t artist_mem=0;
    size_t year_mem=0;
    size_t rating_mem=0;
    size_t people_rated_mem=0;

    int eof_or_not=1;
    while(eof_or_not){
    //no fgets. alternative
        ssize_t title_length =getline(&title_line,&title_mem,songs_file);
        ssize_t artist_length =getline(&artist_line,&artist_mem,songs_file);
        ssize_t year_length =getline(&year_line,&year_mem,songs_file);
        ssize_t rating_length =getline(&rating_line,&rating_mem,songs_file);
        ssize_t people_rated_length =getline(&people_rated_line,&people_rated_mem,songs_file);

        if (title_length==-1&&artist_length==-1&&year_length==-1&&rating_length==-1&&people_rated_length==-1){//if same number of line
            break;
        } else if(title_length==-1||artist_length==-1 ||year_length==-1 ||rating_length==-1||people_rated_length==-1){
            return -1;
        }
    }
    while(isspace((unsigned char)*title_line)){
        title_line++;
    }
    while(isspace((unsigned char)*artist_line)){
        artist_line++;
    }

    if(title_line[0]=='\0'||artist_line[0]='\0'){
        return -1;
    }
}


/*1.total numeber of songs in db.
2. 0 if NULL 
*/
size_t db_song_count(const MusicDB *db){
    if(db==NULL){
        return 0;
    }
    return db->numb_songs;
}


/*1.total numeber of artists in db.
2. 0 if NULL 
*/
size_t db_artist_count(const MusicDB *db){
    if(db==NULL){
        return 0;
    }
    return db->numb_artists;
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
3. if lim==0 or lim>count means all
use datastream
*/
void db_disp(const MusicDB *db, FILE *out, size_t lim){
    if(db==NULL){
        return;
    }
    fprintf(out,"%-35s %-25s %-5s %-8s %s\n", "Song Title","Artist", "Year", "Rating", "People Rated");

    if(lim==0||lim>db->numb_songs){
        lim=db->numb_songs
    }

    for(size_t i=0;i<lim;i++){
        const Song *s=db->list_of_songs[i];
        fprintf(out,"%-35.35s %-25.25s %-5d %-8.2f %lu\n",s->title, s->artist->name, (int)s->year, (double)s->rating, (unsigned long)->num_rated);
    }
}


/*1. calls pred(song,key) for every song
2. stored in *out (a new array of poitners that point to the matchign song)
3. returns the number of matches
4.0 is nothign matches or runs out of memory. sets *out=NULL.
5. caller frees the array when donw
(song obj not copied, so we hav epointers to the original songs)
*/
size_t db_search(const MusicDB *db, song_pred pred, const void *key, const Song ***out){
    if(out==NULL){
        return 0;}
    *out=NULL;

    size_t matches_count=0;
    for(size_t i=0;i<db->n_songs;i++){
        if(pred(db->songs[i], key)){
            matches_count++;
        }
    }
    if(matches_count==0){
        return 0;
    } 
    
    const Song **match_songs =malloc(count*sizeof(Song*));
    if(matches_songs==NULL){
        return 0;
    }

    //fill the array now
    size_t l=0;
    for(size_t m=0; m<db->n_songs;m++){
        if(pred(db->songs[m],key)){
            match_songs[l]= db->songs[m];
            m++;
        }
    }
    *out=match_songs;
    return matches_count;        
}






/*1. reorders db accorign to sort card (0-3)
2.ratings compared to decimals in the file.
3. qsort()
4. do nothign if unknwn card numebr
(diff criteria, maybe use helpers)
*/
void db_sort(MusicDB *db, int card){
    if(card==0){//rating descending, then num_rated descending
        qsort(db->songs,db->n_songs,sizeof(Song*),comp_card0);
    } else if(card==1){//rating descending, then num_rated descending
        qsort(db->songs,db->n_songs,sizeof(Song*),comp_card1);
    }
    else if(card==2){//rating descending, then num_rated descending
        qsort(db->songs,db->n_songs,sizeof(Song*),comp_card2);
    }
    else if(card==3){//rating descending, then num_rated descending
        qsort(db->songs,db->n_songs,sizeof(Song*),comp_card3);
    }
}

//helepr for qsort. tryignto aces the values of the two songs we want to cmpare
int comp_card0(const void *elem1, const void*elem2){//rating descending, then num_rated descending
    const Song*song1= *(Song* cost*)elem1;
    const Song*song2= *(Song* cost*)elem2;

    if(song1->rating>song2->rating){
        return -1;
    } else if(song1->rating< song2->rating){
        return 1;
    }if(song1->num_rated>song2->num_rated){
        return -1;
    }
    else if(song1->num_rated<song2->num_rated){
        return 1;
    } return 0;
}

int comp_card1(const void *elem1, const void*elem2){//year ascending, then title ascending (strcmp byte order)
    const Song*song1= *(Song* cost*)elem1;
    const Song*song2= *(Song* cost*)elem2;

    if(song1->year>song2->year){
        return -1;
    } else if(song1->year< song2->year){
        return 1;
    }
    return strcmp(song1->title, song2->title)
}

int comp_card2(const void *elem1, const void*elem2){//artist name ascending (strcmp), then year descending
    const Song*song1= *(Song* cost*)elem1;
    const Song*song2= *(Song* cost*)elem2;

    int name_cmp = strcmp(song1->artist->name, song2->artist->name);

    if(song1->year>song2->year){
        return -1;
    } else if(song1->year< song2->year){
        return 1;
    }
    return 0;
}

int comp_card3(const void *elem1, const void*elem2){//num_rated descending, then rating descending
    const Song*song1= *(Song* cost*)elem1;
    const Song*song2= *(Song* cost*)elem2;

    if(song1->num_rated>song2->num_rated){
        return -1;
    } else if(song1->num_rated< song2->num_rated){
        return 1;
    }else if(song1->rating< song2->rating){
        return -1;
    }else if(song1->rating< song2->rating){
        return 1;
    }
}




/*1. returns the #songs that whose year is [start, start+9]
2. if best!=NULL, *best= (song with the largest num_rated (smnaller id wins if a tie) ) or NULL if none
3. PTR ONLY. walk with the aarray of pointers. dont contatin ']' or'['. dont use integer loop index
*/
size_t db_count_decade(const MusicDB *db, int start, const Song **best){
    if (best!=NULL){
        *best=NULL;
    }
    size_t songs_yearrange=0;
    const song *best_song=NULL;
    int start_year=start;
    int end_year=start+9;

    //need pointers poting to starta nd end
    Song **start_point=db->songs;
    Song **end_point=db->songs+ db->n_songs;
    while(start_point<end_end){
        Song *song=*start_point;

        //complete this.

    }



}


/*1. returns artist with most songs(ties the name that comes frist by strcmp) 
2, if none, returns NULL.
3. PTR ONLY. walk with the aarray of pointers. dont contatin ']' or'['. dont use integer loop index 
*/
const Artist *db_top_artist(const MusicDB *db){

}