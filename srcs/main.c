#include <stdio.h>
#include <stdlib.h>
#include "libavformat/avformat.h"
#include "error.h"

void	check_error(int errcode)
{
	char errbuff[512] = {};
	if (!av_strerror(errcode, errbuff, 512) && errcode != 0)
		printf("**********\nError %d\n%s\n**********\n", errcode, errbuff);
	else return;
}

int 	main(int ac, char **av)
{

	// /home/anthony/Documents/projects/sample-generator
	const char *url = NULL;
	AVFormatContext *s = NULL;
	s = avformat_alloc_context();
	int ret = 0;
	if (ac == 2)
	{
		url = av[1];
		printf("Opening %s\n", url);
	}	
	else
		return (1);
	
	if ((ret = avformat_open_input(&s, url, NULL, NULL)) < 0)
	{
		check_error(ret);
		printf("Failed to open %s\nAborting\n", url);
		abort();
	}
	else
	{
		printf("opened %s\n", url);
	}
	return(0);
}

