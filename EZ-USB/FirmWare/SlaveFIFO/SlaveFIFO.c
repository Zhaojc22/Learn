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
#define bmEP6IRQ 0x40

#define false 0
#define true ( !false )
#define POWER_LED_OFF()    do{ IOE &= ~0x0C; } while(false)
#define POWER_LED_RED()    do{ IOE &= ~0x08; IOE |= 0x04; } while(false)
#define POWER_LED_GREEN()  do{ IOE &= ~0x04; IOE |= 0x08; } while(false)

void TD_Init(void)
{
   CPUCS = ((CPUCS & ~bmCLKSPD) | bmCLKSPD1);
	SYNCDELAY;

   //�ӿڿ��ƼĴ���
   //b7: 0=ѡ���ⲿʱ��Դ��1=ѡ���ڲ�ʱ��Դ
   //b6��0=�ڲ�ʱ��30MHz��1=�ڲ�ʱ��48MHz
   //b3: 0=FIFOͬ�����У�1=FIFO�첽����
   //b[1:0]��ѡ��ӿ�ģʽ, 00=Prots,01=Reserved,10=GPIF,11=Slave,
	IFCONFIG |= 0xCB;	  
	SYNCDELAY;

	REVCTL = 0x03; //�ų�һЩ����Ҫ�Ĵ��󣬲��Ǳ��룬��ʱ��֪������
	SYNCDELAY;

	EP6CFG = 0xE0;
	SYNCDELAY;

	FIFORESET = 0x80;
	SYNCDELAY;

	FIFORESET = 0x86;
	SYNCDELAY;

	FIFORESET = 0x00;
	SYNCDELAY;

	EP6FIFOCFG = 0x0C;  //00001100  b0=0,ѡ��8λ����
	SYNCDELAY;

	PORTCCFG = 0x00;  // Set Port C All pins are Prot C 

   OEC = 0xFF; //���õĴ�PortC�����������
   AUTOPTRSETUP |= 0x01;
}

void TD_Poll(void)
{
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
void ISR_Ep2inout(void) interrupt 0
{
}
void ISR_Ep4inout(void) interrupt 0
{
}
void ISR_Ep6inout(void) interrupt 0
{
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

