#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sndfile.h>

#define FILE_LEN 190
#define BUFFER_LEN 1024
#define	MAX_CHANNELS 6

int flow(char* file_name);
int print_sfinfo(SF_INFO sfinfo);


int main (int argc, char** argv) {
	char *file_name;
    file_name = NULL;
    if (argc > 1)
    {
        file_name = argv[1];
        flow(file_name);
    }
    else
        printf("Please provide a file\nsample-generator filename\n");
    return 0;
}


int print_sfinfo(SF_INFO sfinfo) {
        printf("\n\n===== File info ======\n");
        printf("Frames %ld\n", sfinfo.frames);
        printf("Samplerate %d\n", sfinfo.samplerate);
        printf("Channels %d\n", sfinfo.channels);
        printf("Format %d\n", sfinfo.format);
        printf("Sections %d\n", sfinfo.sections);
        printf("Seekable %d\n", sfinfo.seekable);
        return 0;
}

static void
process_data (double *data, int count, int channels)
{	double channel_gain [MAX_CHANNELS] = { 0.5, 0.8, 0.1, 0.4, 0.4, 0.9 } ;
    int k, chan ;

    for (chan = 0 ; chan < channels ; chan ++)
        for (k = chan ; k < count ; k+= channels)
            data [k] *= channel_gain [chan] ;

    return ;
}

// Returns a string formated with date/time.wav
char *rand_name(char *string) {
    time_t t = time(NULL);
    srand((unsigned) time(&t) + 420);
    struct tm tm = *localtime(&t);
    // sprintf(string, "output_%d-%02d-%02d %02d:%02d:%02d.wav", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec + 420);
    sprintf(string, "output_%d.wav", rand());
    return 0;
}

int makefile(SNDFILE *infile, SNDFILE *outfile, SF_INFO sf_info) {
        int i = 0;
        int x = 1;
        int readcount;
        static double data[BUFFER_LEN];
        char *name = malloc(sizeof(char) * 100);

        while ((readcount = sf_read_double(infile, data, BUFFER_LEN))) {
            process_data(data, readcount, sf_info.channels);
            sf_write_double (outfile, data, readcount);
            if (i >= FILE_LEN)
            {
                sf_close(outfile);
                sprintf(name, "output_%d.wav", x);
                printf("filename = %s\n", name);
                outfile = sf_open(name, SFM_WRITE, &sf_info);
                x++;
                i = 0;
            }
            i++;
        }
        if (i < FILE_LEN)
        {
            sf_close(outfile);
        }
}

int flow(char* file_name) {
    SNDFILE *infile, *outfile;
    SF_INFO sf_info;

    infile = sf_open(file_name, SFM_READ, &sf_info);
    print_sfinfo(sf_info);
    print_sfinfo(sf_info);
    if (infile)
    {
        outfile = sf_open("output_0.wav", SFM_WRITE, &sf_info);
        printf("\n\nOpened %s\n", file_name);
        makefile(infile, outfile, sf_info);
        sf_close(infile);
    }
}

