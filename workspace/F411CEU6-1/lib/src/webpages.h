/***
	Using a text editor:
	size = <n_chars> - 2 x <n_lines> - (<n_lines> - 1) - <escape_chars>
***/


#ifndef _WEBPAGES_H_
	#define _WEBPAGES_H_

#include <stdint.h>
#include <stddef.h>

typedef struct {
	char* str;
	size_t size;
}web_page;

web_page webpage_1(void);
web_page webpage_2(void);
web_page webpage_3(void);
web_page webpage_4(void);
web_page webpage_5(void);
web_page webpage_6(void);
web_page webpage_7(void);

web_page webpage_200(void);

#endif

/*** EOF ***/

