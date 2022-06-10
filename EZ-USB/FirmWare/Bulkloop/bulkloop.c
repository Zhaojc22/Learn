#pragma NOIV
#include "fx2.h"
#include "fx2regs.h"
#include "syncdly.h"

extern BOOL GotSUD; // Received setup data flag
extern BOOL Sleep;
extern BOOL Rwuen;
extern BOOL Selfpwr;

BYTE Configuration;    // Current configuration
BYTE AlternateSetting; // Alternate settings

#define bmEP2IRQ 0x10
#define bmEP4IRQ 0x20
#define bmEP6IRQ 0x40
#define bmEP8IRQ 0x80

#define false 0
#define true (!false)
#define POWER_LED_OFF() \
   do                   \
   {                    \
      IOE &= ~0x0C;     \
   } while (false)
#define POWER_LED_RED() \
   do                   \
   {                    \
      IOE &= ~0x08;     \
      IOE |= 0x04;      \
   } while (false)
#define POWER_LED_GREEN() \
   do                     \
   {                      \
      IOE &= ~0x04;       \
      IOE |= 0x08;        \
   } while (false)

void TD_Init(void)
{
   CPUCS = ((CPUCS & ~bmCLKSPD) | bmCLKSPD1);
   SYNCDELAY;

   IFCONFIG |= 0x40;
   SYNCDELAY;

   EP2CFG = 0xA2;
   SYNCDELAY;
   EP6CFG = 0xE2;
   SYNCDELAY;

   EP4CFG = 0xA2;
   SYNCDELAY;
   EP8CFG = 0xE2;
   SYNCDELAY;

   EP2BCL = 0x80;
   SYNCDELAY;
   EP2BCL = 0x80;
   SYNCDELAY;

   EP4BCL = 0x80;
   SYNCDELAY;
   EP4BCL = 0x80;
   SYNCDELAY;

   AUTOPTRSETUP |= 0x01;

   USBIE != bmSOF;
   EPIE = bmEP2IRQ | bmEP4IRQ | bmEP6IRQ | bmEP8IRQ;
   OEE = 0xFF;
}

void TD_Poll(void)
{
   WORD i;
   WORD count;
   if (!(EP2468STAT & bmEP2EMPTY))
   {
      if (!(EP2468STAT & bmEP6FULL))
      {
         APTR1H = MSB(&EP2FIFOBUF);
         APTR1L = LSB(&EP2FIFOBUF);
         AUTOPTRH2 = MSB(&EP6FIFOBUF);
         AUTOPTRL2 = LSB(&EP6FIFOBUF);

         count = (EP2BCH << 8) + EP2BCL;

         for (i = 0x00; i < count; i++)
         {
            EXTAUTODAT2 = EXTAUTODAT1;
         }
         EP6BCH = EP2BCH;
         SYNCDELAY;
         EP6BCL = EP2BCL;
         SYNCDELAY;
         EP2BCL = 0x80;
      }
   }

   if (!(EP2468STAT & bmEP4EMPTY))
   {
      if (!(EP2468STAT & bmEP8FULL))
      {
         APTR1H = MSB(&EP4FIFOBUF);
         APTR1L = LSB(&EP4FIFOBUF);
         AUTOPTRH2 = MSB(&EP8FIFOBUF);
         AUTOPTRL2 = LSB(&EP8FIFOBUF);

         count = (EP4BCH << 8) + EP4BCL;

         for (i = 0x00; i < count; i++)
         {
            EXTAUTODAT2 = EXTAUTODAT1;
         }
         EP8BCH = EP4BCH;
         SYNCDELAY;
         EP8BCL = EP4BCL;
         SYNCDELAY;
         EP4BCL = 0x80;
      }
   }
}

BOOL TD_Suspend(void) // Called before the device goes into suspend mode
{
   return (TRUE);
}

BOOL TD_Resume(void) // Called after the device resumes
{
   return (TRUE);
}

BOOL DR_GetDescriptor(void)
{
   return (TRUE);
}

BOOL DR_SetConfiguration(void) // Called when a Set Configuration command is received
{
   Configuration = SETUPDAT[2];
   return (TRUE); // Handled by user code
}

BOOL DR_GetConfiguration(void) // Called when a Get Configuration command is received
{
   EP0BUF[0] = Configuration;
   EP0BCH = 0;
   EP0BCL = 1;
   return (TRUE); // Handled by user code
}
BOOL DR_SetInterface(void) // Called when a Set Interface command is received
{
   AlternateSetting = SETUPDAT[2];
   return (TRUE); // Handled by user code
}

BOOL DR_GetInterface(void) // Called when a Set Interface command is received
{
   EP0BUF[0] = AlternateSetting;
   EP0BCH = 0;
   EP0BCL = 1;
   return (TRUE); // Handled by user code
}

BOOL DR_GetStatus(void)
{
   return (TRUE);
}

BOOL DR_ClearFeature(void)
{
   return (TRUE);
}

BOOL DR_SetFeature(void)
{
   return (TRUE);
}

BOOL DR_VendorCmnd(void)
{
   return (TRUE);
}

void ISR_Sudav(void) interrupt 0
{
   GotSUD = TRUE; // Set flag
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSUDAV; // Clear SUDAV IRQ
}

// Setup Token Interrupt Handler
void ISR_Sutok(void) interrupt 0
{
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSUTOK; // Clear SUTOK IRQ
}

void ISR_Sof(void) interrupt 0
{

   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSOF; // Clear SOF IRQ
}

void ISR_Ures(void) interrupt 0
{
   // whenever we get a USB reset, we should revert to full speed mode
   pConfigDscr = pFullSpeedConfigDscr;
   ((CONFIGDSCR xdata *)pConfigDscr)->type = CONFIG_DSCR;
   pOtherConfigDscr = pHighSpeedConfigDscr;
   ((CONFIGDSCR xdata *)pOtherConfigDscr)->type = OTHERSPEED_DSCR;

   EZUSB_IRQ_CLEAR();
   USBIRQ = bmURES; // Clear URES IRQ
}

void ISR_Susp(void) interrupt 0
{
   Sleep = TRUE;
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmSUSP;
}

void ISR_Highspeed(void) interrupt 0
{
   if (EZUSB_HIGHSPEED())
   {
      pConfigDscr = pHighSpeedConfigDscr;
      ((CONFIGDSCR xdata *)pConfigDscr)->type = CONFIG_DSCR;
      pOtherConfigDscr = pFullSpeedConfigDscr;
      ((CONFIGDSCR xdata *)pOtherConfigDscr)->type = OTHERSPEED_DSCR;
   }
   EZUSB_IRQ_CLEAR();
   USBIRQ = bmHSGRANT;
}

void ISR_Ep0ack(void) interrupt 0
{
}
void ISR_Stub(void) interrupt 0
{
}
void ISR_Ep0in(void) interrupt 0
{
}
void ISR_Ep0out(void) interrupt 0
{
}
void ISR_Ep1in(void) interrupt 0
{
}
void ISR_Ep1out(void) interrupt 0
{
}
BYTE LEDFLAG = 0;
void ISR_Ep2inout(void) interrupt 0
{
   if (LEDFLAG)
   {
      POWER_LED_RED();
      LEDFLAG = !LEDFLAG;
   }
   else
   {
      POWER_LED_GREEN();
      LEDFLAG = !LEDFLAG;
   }
   EZUSB_IRQ_CLEAR();
   EPIRQ = bmEP2IRQ; // Clear IRQ
}
void ISR_Ep4inout(void) interrupt 0
{
}

void ISR_Ep6inout(void) interrupt 0
{
   // Clear IRQ 	dum = D2OFF;
}
void ISR_Ep8inout(void) interrupt 0
{
}
void ISR_Ibn(void) interrupt 0
{
}
void ISR_Ep0pingnak(void) interrupt 0
{
}
void ISR_Ep1pingnak(void) interrupt 0
{
}
void ISR_Ep2pingnak(void) interrupt 0
{
}
void ISR_Ep4pingnak(void) interrupt 0
{
}
void ISR_Ep6pingnak(void) interrupt 0
{
   EZUSB_IRQ_CLEAR();
   EPIRQ = bmEP6IRQ;
}
void ISR_Ep8pingnak(void) interrupt 0
{
}
void ISR_Errorlimit(void) interrupt 0
{
}
void ISR_Ep2piderror(void) interrupt 0
{
}
void ISR_Ep4piderror(void) interrupt 0
{
}
void ISR_Ep6piderror(void) interrupt 0
{
}
void ISR_Ep8piderror(void) interrupt 0
{
}
void ISR_Ep2pflag(void) interrupt 0
{
}
void ISR_Ep4pflag(void) interrupt 0
{
}
void ISR_Ep6pflag(void) interrupt 0
{
}
void ISR_Ep8pflag(void) interrupt 0
{
}
void ISR_Ep2eflag(void) interrupt 0
{
}
void ISR_Ep4eflag(void) interrupt 0
{
}
void ISR_Ep6eflag(void) interrupt 0
{
}
void ISR_Ep8eflag(void) interrupt 0
{
}
void ISR_Ep2fflag(void) interrupt 0
{
}
void ISR_Ep4fflag(void) interrupt 0
{
}
void ISR_Ep6fflag(void) interrupt 0
{
}
void ISR_Ep8fflag(void) interrupt 0
{
}
void ISR_GpifComplete(void) interrupt 0
{
}
void ISR_GpifWaveform(void) interrupt 0
{
}

