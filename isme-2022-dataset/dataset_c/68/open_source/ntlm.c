/*
   3APA3A simpliest proxy server
   (c) 2002-2016 by Vladimir Dubrovin <3proxy@3proxy.ru>

   please read License Agreement

*/

#include "proxy.h"
struct ntlmchal {
	unsigned char sig[8];
	unsigned char messtype[4];
	unsigned char dom_len[2];
	unsigned char dom_max_len[2];
	unsigned char dom_offset[4];
	unsigned char flags[4];
	unsigned char challenge[8];
	unsigned char reserved[8];
	unsigned char addr_len[2];
	unsigned char addr_max_len[2];
	unsigned char addr_offset[4];
	unsigned char data[1];
};

struct ntlmreq {
	unsigned char sig[8];
	unsigned char messtype[4];
	unsigned char flags[4];
	unsigned char dom_len[2];
	unsigned char dom_max_len[2];
	unsigned char dom_offset[4];
	unsigned char pad1[2];
	unsigned char host_len[2];
	unsigned char host_max_len[2];
	unsigned char host_offset[4];
	unsigned char pad2[2];
	unsigned char data[1];
};

int text2unicode(const char * text, char * buf, int buflen){
	int count = 0;
	buflen = ((buflen>>1)<<1);
	if(!text || !buflen) return 0;
	do {
		buf[count++] = toupper(*text++);
		buf[count++] = '\0';
	} while (*text && count < buflen);
	return count;
}

void unicode2text(const char *unicode, char * buf, int len){
	int i;
	if(!unicode || !len) return;
	for(i=0; i<len; i++){
		buf[i] = unicode[(i<<1)];
	}
	buf[i] = 0;
}

void genchallenge(struct clientparam *param, char * challenge, char *buf){
	struct ntlmchal *chal;
	char tmpbuf[1024];
	char hostname[128];
	int len, i;
	

	chal = (struct ntlmchal *)tmpbuf;
	memset(chal, 0, 1024);
	memcpy(chal->sig, "NTLMSSP", 8);
	chal->messtype[0] = 2;
	gethostname(hostname, 128);
	hostname[15] = 0;
	len = (((int)strlen(hostname)) << 1);
	chal->dom_len[0] = len;
	chal->dom_max_len[0] = len;
	chal->dom_offset[0] =  (unsigned char)((unsigned char *)chal->data - (unsigned char *)chal);
	chal->flags[0] = 0x03;
	chal->flags[1] = 0x82;
	chal->flags[2] = 0x81;
	chal->flags[3] = 0xA0;
	text2unicode(hostname, (char *)chal->data, 64);
	time((time_t *)challenge);
	memcpy(challenge+4, SAADDR(&param->sincr), 4);
	challenge[1]^=*SAPORT(&param->sincr);
	for(i = 0; i < 8; i++) challenge[i] ^= myrand(challenge, 8);
	memcpy(chal->challenge, challenge, 8);
	en64((unsigned char *)tmpbuf, (unsigned char *)buf, (int)((unsigned char *)chal->data - (unsigned char *)chal) + len);	
}

bool numeric_starts_with_alpha(char *str, token_t token) {
    if (token.type != NUMERIC || token.len == 0) return false;

    size_t idx = 0;

    uint8_t *ptr = (uint8_t *)str + token.offset;
    size_t len = token.len;

    int32_t ch;
    ssize_t char_len;

    bool contains_letter = false;
    bool append_char = true;

    while (idx < len) {
        char_len = utf8proc_iterate(ptr, len, &ch);
        
        if (char_len <= 0) break;

        bool is_hyphen = utf8_is_hyphen(ch);
        int cat = utf8proc_category(ch);

        bool is_letter = utf8_is_letter(cat);
        bool is_number = utf8_is_number(cat);

        if (is_number) {
            return contains_letter;
        } else if (is_letter) {
            contains_letter = true;
        }

        ptr += char_len;
        idx += char_len;
    }

    return false;
}
