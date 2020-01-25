#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sndfile.h>

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
    struct tm tm = *localtime(&t);
    sprintf(string, "output_%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return string;
}

int flow(char* file_name) {
    SNDFILE *infile, *outfile;
    SF_INFO sf_info;
    static double data [BUFFER_LEN];
    int readcount;
    char string[100];

    infile = sf_open(file_name, SFM_READ, &sf_info);
    print_sfinfo(sf_info);
    outfile = sf_open(rand_name(string), SFM_WRITE, &sf_info);
    print_sfinfo(sf_info);
    if (infile)
    {
        printf("Opened %s", file_name);
        int i = 0;
        while ((readcount = sf_read_double(infile, data, BUFFER_LEN))) {
            i++;
                process_data(data, readcount, sf_info.channels);
                sf_write_double (outfile, data, readcount);
            if (i >= 500)
            {
                sf_close(outfile);
                i = 0;
                outfile = sf_open(rand_name(string), SFM_WRITE, &sf_info);
            }
        }
        sf_close(infile);
        sf_close(outfile);
    }
}

