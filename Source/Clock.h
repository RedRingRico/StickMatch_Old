#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#ifdef WIN32
#else
#include <sys/mman.h>
#include <linux/fb.h>
#include <unistd.h>
#include <stropts.h>

int memfd;

volatile unsigned long *memregs32;
volatile unsigned short *memregs16;

unsigned char initphys (void)
{
    memfd = open("/dev/mem", O_RDWR);
    if (memfd == -1)
    {
        printf ("Open failed for /dev/mem\n");
        return 0;
    }

    memregs32 = (unsigned long*) mmap(0, 0x10000, PROT_READ|PROT_WRITE, MAP_SHARED, memfd, 0xc0000000);
    
    if (memregs32 == (unsigned long *)0xFFFFFFFF) return 0;
    memregs16 = (unsigned short *)memregs32;

    return 1;
}

void closephys (void)
{
    close (memfd);
}
#endif

#define SYS_CLK_FREQ 7372800

void SetClock(unsigned int MHZ)
{
#ifdef WIN32
#else
    if (!initphys()) return;
    
  unsigned int v;
  unsigned int mdiv,pdiv=3,scale=0;
  MHZ*=1000000;
  mdiv=(MHZ*pdiv)/SYS_CLK_FREQ;

  mdiv=((mdiv-8)<<8) & 0xff00;
  pdiv=((pdiv-2)<<2) & 0xfc;
  scale&=3;
  v = mdiv | pdiv | scale;
  
    unsigned int l = memregs32[0x808>>2];// Get interupt flags
  memregs32[0x808>>2] = 0xFF8FFFE7;   //Turn off interrupts
  memregs16[0x910>>1]=v;              //Set frequentie
  while(memregs16[0x0902>>1] & 1);    //Wait for the frequentie to be ajused
  memregs32[0x808>>2] = l;            //Turn on interrupts

    closephys();
#endif
}

unsigned int GetClock()
{
#ifdef WIN32
  return 303;
#else
    if (!initphys()) return 0;
    
  unsigned int i;
  unsigned int reg,mdiv,pdiv,scale;

  reg = memregs16[0x912>>1];
  mdiv = ((reg & 0xff00) >> 8) + 8;
  pdiv = ((reg & 0xfc) >> 2) + 2;
  scale = reg & 3;
  
  i = (memregs16[0x91c>>1] & 7)+1;

    closephys();

  return ((SYS_CLK_FREQ * mdiv) / (pdiv << scale)) / i;
#endif
}
