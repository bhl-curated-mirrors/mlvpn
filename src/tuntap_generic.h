#ifndef MLVPN_TUNTAP_GENERIC_H
#define MLVPN_TUNTAP_GENERIC_H

#include "config.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

/* Needed to have this here because arpa.h include need it */
#ifdef HAVE_OPENBSD
 #include <netinet/in.h>
#endif

#include "buffer.h"
#include "privsep.h"
#include "debug.h"

/* Not sure if that's usefull. Just doing it in seek of maximum portability. */
#ifndef IFNAMSIZ
 #define IFNAMSIZ 64
#endif

enum tuntap_type {
    MLVPN_TUNTAPMODE_TUN,
    MLVPN_TUNTAPMODE_TAP
};

struct tuntap_s
{
    int fd;
    int mtu;
    char devname[IFNAMSIZ];
    enum tuntap_type type;
    pktbuffer_t *sbuf;
};

#include "mlvpn.h"

int mlvpn_tuntap_alloc(struct tuntap_s *tuntap);
int mlvpn_tuntap_read(struct tuntap_s *tuntap);
int mlvpn_tuntap_write(struct tuntap_s *tuntap);

/* runs as root! */
int root_tuntap_open(int tuntapmode, char *devname);

#endif