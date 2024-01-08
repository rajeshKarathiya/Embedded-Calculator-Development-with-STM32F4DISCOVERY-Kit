#include "stm32f407xx.h"

void LCD_command(unsigned char command);
void LCD_data(char data);
void LCD_init(void);
void PORTS_init(void);

void msdelay(int n);
uint8_t j = 0, row = 0, col = 0;

int main(void)
{
  // Enable clock for Port C
  RCC->AHB1ENR |= 8;
  RCC->AHB1ENR |= 4;

  // Set pin 4 to 7 of port C as ip mode (pull-up)(C1-C4) pin 0-3 output mode(R1-R4)
  GPIOC->MODER &= 0xFFFF0000; // clear required field
  GPIOC->MODER |= 0x00000055; // clear required field
  GPIOC->PUPDR &= 0xFFFF00FF; // clear required field
  GPIOC->PUPDR |= 0x00005500; // Pull Up

  // LED PA-5 to output mode
  GPIOD->MODER &= 0xF0FFFFFF; // clear required field
  GPIOD->MODER |= 0x05000000; // clear required field

  GPIOD->BSRR = 0x10000000;
  int number[6] = {0, 0, 0, 0, 0, 0}, tenth = 1, temp = 0, i = 0;
  char operator[5] = {'','','','',''};
  bool update[6] = {0, 0, 0, 0, 0, 0};
  bool f = 0, n = 0, s = 0;
  char lcdarr[];
  int m = 0;
  while (1)
  {
    GPIOC->ODR &= 0xFFFFFFF0;
    GPIOC->ODR |= 0x0000000E;
    if (!(GPIOC->IDR & (1 << 4))) // Scan for key press 1
    {
      while (!(GPIOC->IDR & (1 << 4)))
        row = 1;
      col = 0;
    }
    if (!(GPIOC->IDR & (1 << 5))) // Scan for key press 2
    {
      while (!(GPIOC->IDR & (1 << 5)))
        ;
      row = 1;
      col = 1;
    }
    if (!(GPIOC->IDR & (1 << 6))) // Scan for key press 3
    {
      while (!(GPIOC->IDR & (1 << 6)))
        ;
      row = 1;
      col = 2;
    }
    if (!(GPIOC->IDR & (1 << 7))) // Scan for key press A
    {
      while (!(GPIOC->IDR & (1 << 7)))
        ;
      row = 1;
      col = 3;
    }

    GPIOC->ODR &= 0xFFFFFFF0;
    GPIOC->ODR |= 0x0000000D;

    if (!(GPIOC->IDR & (1 << 4))) // Scan for key press 4
    {
      while (!(GPIOC->IDR & (1 << 4)))
        ;
      row = 2;
      col = 0;
    }
    if (!(GPIOC->IDR & (1 << 5))) // Scan for key press 5
    {
      while (!(GPIOC->IDR & (1 << 5)))
        ;
      row = 2;
      col = 1;
    }
    if (!(GPIOC->IDR & (1 << 6))) // Scan for key press 6
    {
      while (!(GPIOC->IDR & (1 << 6)))
        ;
      row = 2;
      col = 2;
    }
    if (!(GPIOC->IDR & (1 << 7))) // Scan for key press B
    {
      while (!(GPIOC->IDR & (1 << 7)))
        ;
      row = 2;
      col = 3;
    }
    GPIOC->ODR &= 0xFFFFFFF0;
    GPIOC->ODR |= 0x0000000B;

    if (!(GPIOC->IDR & (1 << 4))) // Scan for key press 7
    {
      while (!(GPIOC->IDR & (1 << 4)))
        ;
      row = 3;
      col = 0;
    }
    if (!(GPIOC->IDR & (1 << 5))) // Scan for key press 8
    {
      while (!(GPIOC->IDR & (1 << 5)))
        ;
      row = 3;
      col = 1;
    }
    if (!(GPIOC->IDR & (1 << 6))) // Scan for key press 9
    {
      while (!(GPIOC->IDR & (1 << 6)))
        ;
      row = 3;
      col = 2;
    }
    if (!(GPIOC->IDR & (1 << 7))) // Scan for key press C
    {
      while (!(GPIOC->IDR & (1 << 7)))
        ;
      row = 3;
      col = 3;
    }
    GPIOC->ODR &= 0xFFFFFFF0;
    GPIOC->ODR |= 0x00000007;

    if (!(GPIOC->IDR & (1 << 4))) // Scan for key press *
    {
      while (!(GPIOC->IDR & (1 << 4)))
        ;
      row = 4;
      col = 0;
    }
    if (!(GPIOC->IDR & (1 << 5))) // Scan for key press 0
    {
      while (!(GPIOC->IDR & (1 << 5)))
        ;
      row = 4;
      col = 1;
    }
    if (!(GPIOC->IDR & (1 << 6))) // Scan for key press #
    {
      while (!(GPIOC->IDR & (1 << 6)))
        ;
      row = 4;
      col = 2;
    }
    if (!(GPIOC->IDR & (1 << 7))) // Scan for key press D
    {
      while (!(GPIOC->IDR & (1 << 7)))
        ;
      row = 4;
      col = 3;
    }
    static char keys[16] =
        {
            "1",
            "2",
            "3",
            "+",
            "4",
            "5",
            "6",
            "-",
            "7",
            "8",
            "9",
            "*",
            "=",
            "0",
            "~",
            "/"};
    int k = row - 1 + col * 4;
    lcdarr[m] = keys[k];
    m++;
    if ((k == 14) & (s == 0))
    {
      n = 1;
      continue;
    }
    s = 1;
    if (k == 12)
    {
      break;
    }
    else if ((k == 3) | (k == 7) | (k == 11) | (k == 15))
    {
      if (n == 1)
      {
        temp = temp * (-1);
      }
      if (f == 0)
      {
        number[0] = temp;
      }
      else if (f == 1)
      {
        number[1] = temp;
      }
      else if (f == 2)
      {
        number[2] = temp;
      }
      else if (f == 3)
      {
        number[3] = temp;
      }
      else if (f == 4)
      {
        number[4] = temp;
      }

      else if (f == 5)
      {
        number[5] = temp;
      }
      temp = 0;
      operator[i] = keys[i];
      i++;
      f++;
      s = 0;
      if (i == 5)
      {
        break;
      }
    }
    else
    {
      temp = temp * tenth + (int)keys[k];
      tenth = tenth * 10;
    }

    for (j = 0; j < row; j++)
    {
      GPIOD->BSRR = (1 << 12); // Set bit corresponds to portA bit 12
      msdelay(500);
      GPIOD->BSRR = (1 << 28); // Clear bit corresponds to portA bit 28
      msdelay(500);
    }
    msdelay(10000);
    for (j = 0; j < col; j++)
    {
      GPIOD->BSRR = (1 << 13); // Set bit corresponds to portd bit 12
      msdelay(500);
      GPIOD->BSRR = (1 << 29); // Clear bit corresponds to portA bit 28
      msdelay(500);
    }
    row = 0;
    col = 0;
    // msdelay(1000);
  }
  for (i = 0; i < 5; i++)
  {
    if (operator[i] == '/')
    {
      int fis = i, sec = i;
      while (update[tep] == 1)
      {
        fis--;
      }
      while (update[sec] == 1)
      {
        sec++;
      }
      number[fis] = number[fis] / number[sec];
      update[sec] = 1;
    }
  }
  for (i = 0; i < 5; i++)
  {
    if (operator[i] == '*')
    {
      int fis = i, sec = i;
      while (update[tep] == 1)
      {
        fis--;
      }
      while (update[sec] == 1)
      {
        sec++;
      }
      number[fis] = number[fis] * number[sec];
      update[sec] = 1;
    }
  }
  for (i = 0; i < 5; i++)
  {
    if (operator[i] == '+')
    {
      int fis = i, sec = i;
      while (update[tep] == 1)
      {
        fis--;
      }
      while (update[sec] == 1)
      {
        sec++;
      }
      number[fis] = number[fis] + number[sec];
      update[sec] = 1;
    }
  }
  for (i = 0; i < 5; i++)
  {
    if (operator[i] == '-')
    {
      int fis = i, sec = i;
      while (update[tep] == 1)
      {
        fis--;
      }
      while (update[sec] == 1)
      {
        sec++;
      }
      number[fis] = number[fis] - number[sec];
      update[sec] = 1;
    }
  }
  int answer = 0;
  for (int i = 0; i < 5; i++)
  {
    if (update[i] == 0)
    {
      answer = number[i];
      break;
    }
  }
  LCD_init();
  LCD_command(0x01);
  LCD_command(0x80); // first line
  delayMs(500);
  /* Write "hello" on LCD */
  for (u = 0; u < 16; u++)
  {
    LCD_data(lcdarr[u]);
  }
  LCD_command(0xC0); // second line
  delayMs(1000);
  LCD_data(answer);
  delayMs(1000);
  LCD_command(0x01);
}

void LCD_init(void)
{
  PORTS_init();
  delayMs(30); /* initialization sequence */
  LCD_command(0x30);
  delayMs(10);
  LCD_command(0x30);
  delayMs(1);
  LCD_command(0x30);
  LCD_command(0x38); /* set 8-bit data, 2-line, 5x7 font */
  LCD_command(0x06); /* move cursor right after each char */
  LCD_command(0x01); /* clear screen, move cursor to home */
  LCD_command(0x0F); /* turn on display, cursor blinking */
}
void PORTS_init(void)
{
  RCC->AHB1ENR |= 0x06; /* enable GPIOB/C clock */
  /* PB5 for LCD R/S */
  /* PB6 for LCD R/W */
  /* PB7 for LCD EN */
  GPIOB->MODER &= ~0x0000FC00; /* clear pin mode */
  GPIOB->MODER |= 0x00005400;  /* set pin output mode */
  GPIOB->BSRR = 0x00C00000;    /*turn off EN and R/W */
  /* PC0-PC7 for LCD D0-D7, respectively. */
  GPIOC->MODER &= ~0x0000FFFF; /* clear pin mode */
  GPIOC->MODER |= 0x00005555;  /* set pin output mode */
}
/ CD and Keyboard Interfacing /
    void LCD_command(unsigned char command)
{
  GPIOB->BSRR = (RS | RW) << 16; /* RS = 0, R/W = 0 */
  GPIOC->ODR = command;          /* put command on data bus */
  GPIOB->BSRR = EN;              /* pulse E high */
  delayMs(0);
  GPIOB->BSRR = EN << 16; /* clear E */
  if (command < 4)
    delayMs(2); /* command 1 and 2 needs up to 1.64ms */
  else
    delayMs(1); /* all others 40 us */
}
void LCD_data(char data)
{
  GPIOB->BSRR = RS;       /* RS = 1 */
  GPIOB->BSRR = RW << 16; /* R/W = 0 */
  GPIOC->ODR = data;      /* put data on data bus */
  GPIOB->BSRR = EN;       /* pulse E high */
  delayMs(0);
  GPIOB->BSRR = EN << 16; /* clear E */
  delayMs(1);
}
void LCD_ready(void)
{
  char status;
  /* change to read configuration to poll the status register */
  GPIOC->MODER &= ~0x0000FFFF; /* clear pin mode */
  GPIOB->BSRR = RS << 16;      /* RS = 0 for status register */
  GPIOB->BSRR = RW;            /* R/W = 1 for read */
  do
  {                   /* stay in the loop until it is not busy */
    GPIOB->BSRR = EN; /* pulse E high */
    delayMs(0);
    status = GPIOC->IDR;    /* read status register */
    GPIOB->BSRR = EN << 16; /* clear E */
    delayMs(0);
  } while (status & 0x80); /* check busy bit */
  /* return to default write configuration */
  GPIOB->BSRR = RW << 16;     /* R/W = 0, LCD input */
  GPIOC->MODER |= 0x00005555; /* Port C as output */
}

void msdelay(int n)
{
  int i;
  for (; n > 0; n--)
    for (i = 0; i < 3195; i++)
      ;
}